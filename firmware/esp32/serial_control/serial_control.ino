#include <ESP32Servo.h>

// =====================================================
// SERVOS
// =====================================================

Servo joint1Servo;
Servo joint2Servo;

Servo bracketServo;
Servo endEffectorServo;

Servo gripperServo;

// =====================================================
// PINS
// =====================================================

#define JOINT1_PIN          13
#define JOINT2_PIN          12

#define BRACKET_PIN         14
#define END_EFFECTOR_PIN    27

#define GRIPPER_PIN         26

// =====================================================
// STEPPER PINS
// =====================================================

#define STEP_PIN    18
#define DIR_PIN     19

// =====================================================
// CURRENT POSITIONS
// =====================================================

int currentStepperAngle = 0;

// =====================================================
// SETUP
// =====================================================

void setup()
{
    Serial.begin(115200);

    // ================= SERVO ATTACH =================

    joint1Servo.attach(JOINT1_PIN);
    joint2Servo.attach(JOINT2_PIN);

    bracketServo.attach(BRACKET_PIN);
    endEffectorServo.attach(END_EFFECTOR_PIN);

    gripperServo.attach(GRIPPER_PIN);

    // ================= STEPPER =================

    pinMode(STEP_PIN, OUTPUT);
    pinMode(DIR_PIN, OUTPUT);

    // ================= INITIAL POSITIONS =================

    joint1Servo.write(90);
    joint2Servo.write(90);

    bracketServo.write(90);
    endEffectorServo.write(90);

    gripperServo.write(90);

    Serial.println("ESP32 Ready");
}

// =====================================================
// LOOP
// =====================================================

void loop()
{
    if (Serial.available())
    {
        String received = Serial.readStringUntil('\n');

        received.trim();

        if (received.length() > 0)
        {
            processData(received);
        }
    }
}

// =====================================================
// PROCESS SERIAL DATA
// =====================================================

void processData(String data)
{
    // Expected format:
    //
    // stepper,joint1,joint2,bracket,end_effector,gripper
    //
    // Example:
    // 0,90,90,90,90,45

    int values[6];

    int index = 0;

    char charArray[100];

    data.toCharArray(charArray, 100);

    char *token = strtok(charArray, ",");

    while (token != NULL && index < 6)
    {
        values[index] = atoi(token);

        token = strtok(NULL, ",");

        index++;
    }

    // Must receive exactly 6 values
    if (index != 6)
    {
        Serial.println("Invalid packet");
        return;
    }

    // =====================================================
    // EXTRACT VALUES
    // =====================================================

    int stepperAngle     = values[0];

    int joint1Angle      = values[1];
    int joint2Angle      = values[2];

    int bracketAngle     = values[3];
    int endEffectorAngle = values[4];

    int gripperAngle     = values[5];

    // =====================================================
    // CLAMP SAFETY
    // =====================================================

    joint1Angle = constrain(joint1Angle, 0, 180);
    joint2Angle = constrain(joint2Angle, 0, 180);

    bracketAngle = constrain(bracketAngle, 0, 180);
    endEffectorAngle = constrain(endEffectorAngle, 0, 180);

    gripperAngle = constrain(gripperAngle, 0, 180);

    // =====================================================
    // WRITE SERVOS
    // =====================================================

    joint1Servo.write(joint1Angle);
    joint2Servo.write(joint2Angle);

    bracketServo.write(bracketAngle);
    endEffectorServo.write(endEffectorAngle);

    gripperServo.write(gripperAngle);

    // =====================================================
    // MOVE STEPPER
    // =====================================================

    moveStepperTo(stepperAngle);

    // =====================================================
    // DEBUG PRINT
    // =====================================================

    Serial.print("Stepper: ");
    Serial.print(stepperAngle);

    Serial.print(" | J1: ");
    Serial.print(joint1Angle);

    Serial.print(" | J2: ");
    Serial.print(joint2Angle);

    Serial.print(" | Bracket: ");
    Serial.print(bracketAngle);

    Serial.print(" | EE: ");
    Serial.print(endEffectorAngle);

    Serial.print(" | Gripper: ");
    Serial.println(gripperAngle);
}

// =====================================================
// SIMPLE STEPPER CONTROL
// =====================================================

void moveStepperTo(int targetAngle)
{
    int difference = targetAngle - currentStepperAngle;

    if (difference == 0)
        return;

    // Direction
    if (difference > 0)
    {
        digitalWrite(DIR_PIN, HIGH);
    }
    else
    {
        digitalWrite(DIR_PIN, LOW);

        difference = -difference;
    }

    // =====================================================
    // CONVERT ANGLE TO STEPS
    // =====================================================

    // Example:
    // 200 step motor
    // 1.8 deg/step

    int steps = difference / 1.8;

    // =====================================================
    // PULSE STEPPER
    // =====================================================

    for (int i = 0; i < steps; i++)
    {
        digitalWrite(STEP_PIN, HIGH);
        delayMicroseconds(5000);

        digitalWrite(STEP_PIN, LOW);
        delayMicroseconds(5000);
    }

    currentStepperAngle = targetAngle;
}