#!/usr/bin/env python3

import rclpy
import math
import serial
import time

from rclpy.node import Node
from sensor_msgs.msg import JointState
from sensor_msgs.msg import Joy


class JointStateToSerial(Node):

    def __init__(self):

        super().__init__('joint_state_to_serial')

        # =====================================================
        # SERIAL
        # =====================================================

        # CHANGE THIS TO YOUR ESP32 PORT
        # Example:
        # Linux  -> /dev/ttyUSB0
        # Ubuntu -> /dev/ttyACM0
        # Windows -> COM3

        self.serial_port = '/dev/ttyUSB0'
        self.baudrate = 115200

        try:

            self.ser = serial.Serial(
                self.serial_port,
                self.baudrate,
                timeout=1
            )

            time.sleep(2)

            self.get_logger().info(
                f'Serial connected on {self.serial_port}'
            )

        except Exception as e:

            self.get_logger().error(
                f'Failed to open serial port: {e}'
            )

            self.ser = None

        # =====================================================
        # SUBSCRIBERS
        # =====================================================

        self.joint_state_sub = self.create_subscription(
            JointState,
            '/joint_states',
            self.joint_state_callback,
            10
        )

        self.joy_sub = self.create_subscription(
            Joy,
            '/joy',
            self.joy_callback,
            10
        )

        # =====================================================
        # TIMER
        # =====================================================

        # Send data at 20 Hz
        self.timer = self.create_timer(
            0.05,
            self.send_serial_data
        )

        # =====================================================
        # STORED ANGLES
        # =====================================================

        self.stepper_deg = 0

        self.joint_1_deg = 90
        self.joint_2_deg = 90

        self.bracket_deg = 90
        self.end_effector_deg = 90

        self.gripper_angle = 90

        # =====================================================
        # JOYSTICK
        # =====================================================

        self.previous_buttons = [0] * 16

        self.get_logger().info(
            'Serial bridge node started'
        )

    # =====================================================
    # JOINT STATES CALLBACK
    # =====================================================

    def joint_state_callback(self, msg):

        # HARDCODED ORDER FROM /joint_states:
        #
        # 0 -> bracket_1_joint
        # 1 -> end_effector_joint
        # 2 -> joint_1
        # 3 -> joint_2
        # 4 -> left_clamp_joint
        # 5 -> right_clamp_joint
        # 6 -> stepper_joint

        bracket_joint = (msg.position[0])
        end_effector_joint = msg.position[1]
        joint_1 = msg.position[2]
        joint_2 = msg.position[3]
        stepper_joint = msg.position[6]

        # =====================================================
        # CONVERT TO DEGREES
        # =====================================================

        self.bracket_deg = int(
            round(-1*(math.degrees(bracket_joint)) + 90)
        )

        self.end_effector_deg = int(
            round(math.degrees(end_effector_joint) + 90)
        )

        self.joint_1_deg = int(
            round(-1*(math.degrees(joint_1)) + 90)
        )

        self.joint_2_deg = int(
            round(-1*math.degrees(joint_2) + 90)
        )

        self.stepper_deg = int(
            round(math.degrees(stepper_joint))
        )

        # =====================================================
        # CLAMP LIMITS
        # =====================================================

        self.bracket_deg = max(
            0,
            min(180, self.bracket_deg)
        )

        self.end_effector_deg = max(
            0,
            min(180, self.end_effector_deg)
        )

        self.joint_1_deg = max(
            0,
            min(180, self.joint_1_deg)
        )

        self.joint_2_deg = max(
            0,
            min(180, self.joint_2_deg)
        )

    # =====================================================
    # JOYSTICK CALLBACK
    # =====================================================

    def joy_callback(self, msg):

        # Detect button edge
        def pressed(button_index):

            return (
                msg.buttons[button_index] == 1 and
                self.previous_buttons[button_index] == 0
            )

        # Square
        if pressed(0):
            self.gripper_angle = 0

        # X
        elif pressed(1):
            self.gripper_angle = 45

        # Circle
        elif pressed(2):
            self.gripper_angle = 90

        # Triangle
        elif pressed(3):
            self.gripper_angle = 135

        # L1
        elif pressed(4):
            self.gripper_angle += 10

        # R1
        elif pressed(5):
            self.gripper_angle -= 10

        # Clamp range
        self.gripper_angle = max(
            0,
            min(180, self.gripper_angle)
        )

        # Save previous state
        self.previous_buttons = list(msg.buttons)

    # =====================================================
    # SERIAL SEND LOOP
    # =====================================================

    def send_serial_data(self):

        if self.ser is None:
            return

        # FINAL ORDER:
        #
        # stepper,joint1,joint2,bracket,end_effector,gripper

        data_string = (
            f'{self.stepper_deg},'
            f'{self.joint_1_deg},'
            f'{self.joint_2_deg},'
            f'{self.bracket_deg},'
            f'{self.end_effector_deg},'
            f'{self.gripper_angle}\n'
        )

        try:

            self.ser.write(
                data_string.encode()
            )

            self.get_logger().info(
                f'Sent: {data_string.strip()}'
            )

        except Exception as e:

            self.get_logger().error(
                f'Serial write failed: {e}'
            )

    # =====================================================
    # CLEANUP
    # =====================================================

    def destroy_node(self):

        if self.ser is not None:
            self.ser.close()

        super().destroy_node()


# =========================================================
# MAIN
# =========================================================

def main():

    rclpy.init()

    node = JointStateToSerial()

    try:
        rclpy.spin(node)

    except KeyboardInterrupt:
        pass

    node.destroy_node()

    rclpy.shutdown()


if __name__ == '__main__':
    main()