#!/usr/bin/env python3

import rclpy
import math

from rclpy.node import Node

from sensor_msgs.msg import JointState
from sensor_msgs.msg import Joy

from std_msgs.msg import Float32MultiArray


class JointStateToMicroROS(Node):

    def __init__(self):

        super().__init__('joint_state_to_microros')

        # =====================================================
        # PUBLISHER
        # =====================================================

        self.publisher = self.create_publisher(
            Float32MultiArray,
            '/servo_angles',
            10
        )

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

        self.timer = self.create_timer(
            0.01,
            self.publish_data
        )

        # =====================================================
        # STORED ANGLES
        # =====================================================

        self.stepper_deg = 0.0

        self.joint_1_deg = 90.0
        self.joint_2_deg = 90.0

        self.bracket_deg = 90.0
        self.end_effector_deg = 90.0

        self.gripper_angle = 90.0

        # =====================================================
        # JOYSTICK
        # =====================================================

        self.previous_buttons = [0] * 16

        self.get_logger().info(
            'micro-ROS bridge started'
        )

    # =====================================================
    # JOINT STATES CALLBACK
    # =====================================================

    def joint_state_callback(self, msg):

        if len(msg.position) < 7:
            return

        bracket_joint = msg.position[0]
        end_effector_joint = msg.position[1]
        joint_1 = msg.position[2]
        joint_2 = msg.position[3]
        stepper_joint = msg.position[6]

        self.bracket_deg = round(
            -math.degrees(bracket_joint) + 90
        )

        self.end_effector_deg = round(
            math.degrees(end_effector_joint) + 90
        )

        self.joint_1_deg = round(
            -math.degrees(joint_1) + 90
        )

        self.joint_2_deg = round(
            -math.degrees(joint_2) + 90
        )

        self.stepper_deg = round(
            math.degrees(stepper_joint)
        )

        # Clamp
        self.bracket_deg = max(0, min(180, self.bracket_deg))
        self.end_effector_deg = max(0, min(180, self.end_effector_deg))
        self.joint_1_deg = max(0, min(180, self.joint_1_deg))
        self.joint_2_deg = max(0, min(180, self.joint_2_deg))

    # =====================================================
    # JOYSTICK CALLBACK
    # =====================================================

    def joy_callback(self, msg):

        def pressed(button_index):

            return (
                msg.buttons[button_index] == 1 and
                self.previous_buttons[button_index] == 0
            )

        if pressed(0):
            self.gripper_angle = 0

        elif pressed(1):
            self.gripper_angle = 45

        elif pressed(2):
            self.gripper_angle = 90

        elif pressed(3):
            self.gripper_angle = 135

        elif pressed(4):
            self.gripper_angle += 10

        elif pressed(5):
            self.gripper_angle -= 10

        self.gripper_angle = max(
            0,
            min(180, self.gripper_angle)
        )

        self.previous_buttons = list(msg.buttons)

    # =====================================================
    # PUBLISH LOOP
    # =====================================================

    def publish_data(self):

        msg = Float32MultiArray()

        msg.data = [
            float(self.stepper_deg),
            float(self.joint_1_deg),
            float(self.joint_2_deg),
            float(self.bracket_deg),
            float(self.end_effector_deg),
            float(self.gripper_angle)
        ]

        self.publisher.publish(msg)

        # self.get_logger().info(
        #     f'Published: {msg.data}'
        # )


def main():

    rclpy.init()

    node = JointStateToMicroROS()

    try:
        rclpy.spin(node)

    except KeyboardInterrupt:
        pass

    node.destroy_node()

    rclpy.shutdown()


if __name__ == '__main__':
    main()