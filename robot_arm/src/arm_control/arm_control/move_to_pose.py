#!/usr/bin/env python3
"""
Send a single Cartesian pose to MoveIt and execute on Gazebo.
MoveIt solves IK automatically.
Usage: ros2 run arm_control move_to_pose
"""
import rclpy
import time
import threading
from rclpy.node import Node
from rclpy.action import ActionClient
from rclpy.executors import MultiThreadedExecutor
from moveit_msgs.action import MoveGroup
from moveit_msgs.msg import (Constraints, PositionConstraint,
                              OrientationConstraint, BoundingVolume)
from geometry_msgs.msg import PoseStamped, Vector3
from shape_msgs.msg import SolidPrimitive


class PoseSender(Node):
    def __init__(self):
        super().__init__('pose_sender')
        self._client = ActionClient(self, MoveGroup, '/move_action')
        self.get_logger().info('Waiting for MoveGroup...')
        self._client.wait_for_server()
        self.get_logger().info('Connected!')

    def move_to(self, x, y, z, qx=0.0, qy=0.0, qz=0.0, qw=1.0):
        """
        Move end effector to Cartesian pose.
        MoveIt solves IK and executes on Gazebo automatically.
        """
        # Build pose
        pose = PoseStamped()
        pose.header.frame_id = 'base_footprint'
        pose.header.stamp = self.get_clock().now().to_msg()
        pose.pose.position.x = float(x)
        pose.pose.position.y = float(y)
        pose.pose.position.z = float(z)
        pose.pose.orientation.x = float(qx)
        pose.pose.orientation.y = float(qy)
        pose.pose.orientation.z = float(qz)
        pose.pose.orientation.w = float(qw)

        # Build goal
        goal = MoveGroup.Goal()
        goal.request.group_name = 'robot_arm'
        goal.request.num_planning_attempts = 10
        goal.request.allowed_planning_time = 5.0
        goal.request.max_velocity_scaling_factor = 0.5
        goal.request.max_acceleration_scaling_factor = 0.5

        # Position constraint
        pos_c = PositionConstraint()
        pos_c.header = pose.header
        pos_c.link_name = 'end_effector_link'
        pos_c.target_point_offset = Vector3(x=0.0, y=0.0, z=0.0)
        prim = SolidPrimitive()
        prim.type = SolidPrimitive.BOX
        prim.dimensions = [0.07, 0.07, 0.07]
        bv = BoundingVolume()
        bv.primitives = [prim]
        bv.primitive_poses = [pose.pose]
        pos_c.constraint_region = bv
        pos_c.weight = 1.0

        # Orientation constraint
        # ori_c = OrientationConstraint()
        # ori_c.header = pose.header
        # ori_c.link_name = 'end_effector_link'
        # ori_c.orientation = pose.pose.orientation
        # ori_c.absolute_x_axis_tolerance = 0.4
        # ori_c.absolute_y_axis_tolerance = 0.4
        # ori_c.absolute_z_axis_tolerance = 0.4
        # ori_c.weight = 1.0

        constraints = Constraints()
        constraints.position_constraints = [pos_c]
        # constraints.orientation_constraints = [ori_c]
        goal.request.goal_constraints = [constraints]

        self.get_logger().info(
            f'Sending pose: x={x:.3f} y={y:.3f} z={z:.3f} '
            f'to end_effector_link in base_footprint frame'
        )
        self.get_logger().info('MoveIt will solve IK and execute on Gazebo...')

        # Send and wait
        future = self._client.send_goal_async(goal)
        while not future.done():
            time.sleep(0.05)

        goal_handle = future.result()
        if not goal_handle.accepted:
            self.get_logger().error('Goal rejected!')
            return False

        result_future = goal_handle.get_result_async()
        while not result_future.done():
            time.sleep(0.05)

        result = result_future.result().result
        if result.error_code.val == 1:
            self.get_logger().info('Success! Robot moved to target pose ✓')
            return True
        else:
            self.get_logger().error(
                f'Failed - error code: {result.error_code.val}'
            )
            return False


def main():
    rclpy.init()

    node = PoseSender()

    # Spin in background
    executor = MultiThreadedExecutor()
    executor.add_node(node)
    thread = threading.Thread(target=executor.spin, daemon=True)
    thread.start()

    time.sleep(1.0)

    # ── Set your target pose here ──────────────────────────────────────
    # These are in the base_footprint frame (meters)
    # Current home position is: x=-0.081, y=0.037, z=0.436
    # Try moving slightly from home:

    TARGET_X = -0.081
    TARGET_Y =  0.037
    TARGET_Z =  0.380   # 5cm lower than home

    # Orientation - keep same as home (identity)
    TARGET_QX = 0.0
    TARGET_QY = 0.0
    TARGET_QZ = 0.0
    TARGET_QW = 1.0
    # ──────────────────────────────────────────────────────────────────

    node.move_to(
        TARGET_X, TARGET_Y, TARGET_Z,
        TARGET_QX, TARGET_QY, TARGET_QZ, TARGET_QW
    )

    executor.shutdown()
    rclpy.shutdown()


if __name__ == '__main__':
    main()