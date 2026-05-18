#include <ESP32Servo.h>
#include <micro_ros_arduino.h>

#include <rcl/rcl.h>
#include <rcl/error_handling.h>
#include <rclc/rclc.h>
#include <rclc/executor.h>
#include <rclc/timer.h>

#include <std_msgs/msg/float32_multi_array.h>

// =======================
// PIN DEFINITIONS
// =======================

// Servos
#define JOINT1_PIN    13
#define JOINT2_PIN    12
#define BRACKET_PIN   14
#define EE_PIN        27
#define GRIPPER_PIN   26

// Stepper
#define STEP_PIN      25
#define DIR_PIN       33

#define LED_PIN       2

#define STEPS_PER_REV 200
#define STEP_DELAY_US 5000

// =======================
// SERVO OBJECTS
// =======================

Servo joint1;
Servo joint2;
Servo bracket;
Servo ee;
Servo gripper;

// =======================
// ROS2 OBJECTS
// =======================

rcl_node_t node;
rcl_subscription_t subscriber;
rcl_timer_t servo_timer;
rclc_executor_t executor;
rclc_support_t support;
rcl_allocator_t allocator;

std_msgs__msg__Float32MultiArray msg;
float motor_data[6];

// =======================
// STEP STATE
// =======================

volatile double target_stepper_deg = 0.0;
volatile double current_stepper_deg = 0.0;
volatile bool stepper_new_target = false;

SemaphoreHandle_t stepper_mutex;

// =======================
// SERVO TARGETS
// =======================

volatile int16_t target_servo[5] = {90, 90, 90, 90, 90};
volatile bool new_cmd = false;

// =======================
// STATE MACHINE
// =======================

enum states {
    WAITING_AGENT,
    AGENT_AVAILABLE,
    AGENT_CONNECTED,
    AGENT_DISCONNECTED
};

states state = WAITING_AGENT;

// =======================
// MACROS
// =======================

#define RCCHECK(fn) { rcl_ret_t rc = fn; if (rc != RCL_RET_OK) error_loop(); }

#define EXECUTE_EVERY_N_MS(ms, code) \
  do { static uint32_t last = 0; \
  if (uxr_millis() - last >= ms) { code; last = uxr_millis(); } } while(0)

// =======================
// ERROR LOOP
// =======================

void error_loop() {
    while (1) {
        digitalWrite(LED_PIN, !digitalRead(LED_PIN));
        delay(100);
    }
}

// =======================
// STEPPER TASK (Core 0)
// =======================

void stepperTask(void *pvParameters)
{
    pinMode(STEP_PIN, OUTPUT);
    pinMode(DIR_PIN, OUTPUT);

    while (true)
    {
        if (xSemaphoreTake(stepper_mutex, portMAX_DELAY) == pdTRUE)
        {
            double target = target_stepper_deg;
            double current = current_stepper_deg;
            bool has_new = stepper_new_target;

            if (has_new)
                stepper_new_target = false;

            xSemaphoreGive(stepper_mutex);

            if (has_new)
            {
                double delta = target - current;
                long steps = (long)(delta * STEPS_PER_REV / 360.0);

                if (steps != 0)
                {
                    digitalWrite(DIR_PIN, steps > 0 ? HIGH : LOW);
                    steps = abs(steps);

                    for (long i = 0; i < steps; i++)
                    {
                        digitalWrite(STEP_PIN, HIGH);
                        delayMicroseconds(STEP_DELAY_US);
                        digitalWrite(STEP_PIN, LOW);
                        delayMicroseconds(STEP_DELAY_US);
                    }

                    if (xSemaphoreTake(stepper_mutex, portMAX_DELAY) == pdTRUE)
                    {
                        current_stepper_deg = target;
                        xSemaphoreGive(stepper_mutex);
                    }
                }
            }
        }

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

// =======================
// CALLBACK
// =======================

void subscription_callback(const void *msgin)
{
    const std_msgs__msg__Float32MultiArray *msg =
        (const std_msgs__msg__Float32MultiArray *)msgin;

    if (msg->data.size < 6)
        return;

    // [0] stepper
    if (xSemaphoreTake(stepper_mutex, 0) == pdTRUE)
    {
        target_stepper_deg = msg->data.data[0];
        stepper_new_target = true;
        xSemaphoreGive(stepper_mutex);
    }

    // [1..5] servos
    target_servo[0] = (int16_t)constrain(msg->data.data[1], 0, 180);
    target_servo[1] = (int16_t)constrain(msg->data.data[2], 0, 180);
    target_servo[2] = (int16_t)constrain(msg->data.data[3], 0, 180);
    target_servo[3] = (int16_t)constrain(msg->data.data[4], 0, 180);
    target_servo[4] = (int16_t)constrain(msg->data.data[5], 0, 180);

    new_cmd = true;
}

// =======================
// TIMER (50Hz servo update)
// =======================

void servo_timer_callback(rcl_timer_t *timer, int64_t last_call_time)
{
    (void) last_call_time;
    if (timer == NULL || !new_cmd)
        return;

    new_cmd = false;

    joint1.write(target_servo[0]);
    joint2.write(target_servo[1]);
    bracket.write(target_servo[2]);
    ee.write(target_servo[3]);
    gripper.write(target_servo[4]);
}

// =======================
// CREATE ENTITIES
// =======================

bool create_entities()
{
    allocator = rcl_get_default_allocator();

    RCCHECK(rclc_support_init(&support, 0, NULL, &allocator));
    RCCHECK(rclc_node_init_default(&node, "esp32_arm_node", "", &support));

    RCCHECK(rclc_subscription_init_default(
        &subscriber,
        &node,
        ROSIDL_GET_MSG_TYPE_SUPPORT(std_msgs, msg, Float32MultiArray),
        "/servo_angles"
    ));

    // buffer
    msg.data.data = motor_data;
    msg.data.size = 6;
    msg.data.capacity = 6;

    RCCHECK(rclc_timer_init_default(
        &servo_timer,
        &support,
        RCL_MS_TO_NS(20),
        servo_timer_callback
    ));

    RCCHECK(rclc_executor_init(&executor, &support.context, 2, &allocator));
    RCCHECK(rclc_executor_add_subscription(
        &executor,
        &subscriber,
        &msg,
        &subscription_callback,
        ON_NEW_DATA
    ));

    RCCHECK(rclc_executor_add_timer(&executor, &servo_timer));

    digitalWrite(LED_PIN, HIGH);
    return true;
}

// =======================
// DESTROY ENTITIES
// =======================

void destroy_entities()
{
    rcl_timer_fini(&servo_timer);
    rcl_subscription_fini(&subscriber, &node);
    rcl_node_fini(&node);
    rclc_executor_fini(&executor);
    rclc_support_fini(&support);

    digitalWrite(LED_PIN, LOW);
}

// =======================
// SETUP
// =======================

void setup()
{
    pinMode(LED_PIN, OUTPUT);

    ESP32PWM::allocateTimer(0);
    ESP32PWM::allocateTimer(1);
    ESP32PWM::allocateTimer(2);
    ESP32PWM::allocateTimer(3);

    joint1.attach(JOINT1_PIN);
    joint2.attach(JOINT2_PIN);
    bracket.attach(BRACKET_PIN);
    ee.attach(EE_PIN);
    gripper.attach(GRIPPER_PIN);

    joint1.write(90);
    joint2.write(90);
    bracket.write(90);
    ee.write(90);
    gripper.write(90);

    stepper_mutex = xSemaphoreCreateMutex();

    xTaskCreatePinnedToCore(
        stepperTask,
        "StepperTask",
        4096,
        NULL,
        2,
        NULL,
        0
    );

    set_microros_wifi_transports(
        "Humanoid",
        "123456789",
        "10.135.31.80 ",
        8888
    );

    delay(2000);
}

// =======================
// LOOP (STATE MACHINE)
// =======================

void loop()
{
    switch (state)
    {
        case WAITING_AGENT:
            EXECUTE_EVERY_N_MS(500,
                state = (rmw_uros_ping_agent(1000, 5) == RMW_RET_OK)
                    ? AGENT_AVAILABLE : WAITING_AGENT;
            );
            break;

        case AGENT_AVAILABLE:
            state = create_entities() ? AGENT_CONNECTED : WAITING_AGENT;
            break;

        case AGENT_CONNECTED:
            EXECUTE_EVERY_N_MS(200,
                state = (rmw_uros_ping_agent(1000, 5) == RMW_RET_OK)
                    ? AGENT_CONNECTED : AGENT_DISCONNECTED;
            );

            if (state == AGENT_CONNECTED)
                rclc_executor_spin_some(&executor, RCL_MS_TO_NS(10));

            break;

        case AGENT_DISCONNECTED:
            destroy_entities();
            state = WAITING_AGENT;
            break;
    }
}