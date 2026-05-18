#!/usr/bin/env python3

import rclpy
from rclpy.node import Node

from std_msgs.msg import Float64MultiArray
from sensor_msgs.msg import JointState

import numpy as np


class BridgeNode(Node):

    def __init__(self):
        super().__init__('bridge_node')

        # ---------------- PARAMETERS ----------------
        self.num_joints = 6
        self.rate_hz = 50.0
        self.alpha = 0.15  # smoothing factor

        # ---------------- STATE ----------------
        self.current_q = np.zeros(self.num_joints)
        self.target_q = np.zeros(self.num_joints)

        self.joint_names = [f'joint_{i+1}' for i in range(self.num_joints)]

        # ---------------- PUBLISHERS ----------------
        self.cmd_pub = self.create_publisher(
            Float64MultiArray,
            '/joint_commands',
            10
        )

        # self.state_pub = self.create_publisher(
        #     JointState,
        #     '/joint_states',
        #     10
        # )

        # ---------------- SUBSCRIBERS ----------------
        self.create_subscription(
            Float64MultiArray,
            '/target_joint_positions',
            self.target_callback,
            10
        )

        # ---------------- TIMER ----------------
        self.timer = self.create_timer(
            1.0 / self.rate_hz,
            self.update_loop
        )

        self.get_logger().info("Bridge Node Started")

    # =========================================================
    # CALLBACK: receive new target from MoveIt or manual node
    # =========================================================
    def target_callback(self, msg: Float64MultiArray):
        if len(msg.data) != self.num_joints:
            self.get_logger().warn("Wrong joint size received")
            return

        self.target_q = np.array(msg.data)

    # =========================================================
    # MAIN LOOP
    # =========================================================
    def update_loop(self):

        # --------- interpolation (smooth motion) ----------
        self.current_q = (
            (1 - self.alpha) * self.current_q +
            self.alpha * self.target_q
        )

        # --------- send command to ESP32 ----------
        cmd_msg = Float64MultiArray()
        cmd_msg.data = self.current_q.tolist()
        self.cmd_pub.publish(cmd_msg)

        # # --------- fake joint states for MoveIt ----------
        # js = JointState()
        # js.header.stamp = self.get_clock().now().to_msg()
        # js.name = self.joint_names
        # js.position = self.current_q.tolist()

        # self.state_pub.publish(js)

        # optional debug
        self.get_logger().debug(f"q = {self.current_q}")


# =========================================================
# MAIN
# =========================================================
def main(args=None):
    rclpy.init(args=args)
    node = BridgeNode()

    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass

    node.destroy_node()
    rclpy.shutdown()


if __name__ == '__main__':
    main()