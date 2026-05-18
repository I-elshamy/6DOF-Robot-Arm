#!/usr/bin/env python3

import rclpy
import math
import sys
import time
import threading

from rclpy.node import Node
from rclpy.action import ActionClient
from rclpy.executors import MultiThreadedExecutor

from moveit_msgs.action import MoveGroup
from moveit_msgs.msg import (
    Constraints,
    PositionConstraint,
    BoundingVolume,
    JointConstraint,
)

from geometry_msgs.msg import PoseStamped, Vector3
from shape_msgs.msg import SolidPrimitive


class ShapeDrawer(Node):

    def __init__(self):
        super().__init__('shape_drawer')

        self._action_client = ActionClient(
            self,
            MoveGroup,
            '/move_action'
        )

        self.get_logger().info('Waiting for MoveGroup action server...')
        self._action_client.wait_for_server()
        self.get_logger().info('Connected! Ready to draw shapes.')

    def make_pose(self, x, y, z):
        pose = PoseStamped()

        # IMPORTANT:
        # Use the correct planning frame
        pose.header.frame_id = 'base_footprint'

        pose.header.stamp = self.get_clock().now().to_msg()

        pose.pose.position.x = float(x)
        pose.pose.position.y = float(y)
        pose.pose.position.z = float(z)

        # Keep a simple orientation
        # (orientation constraints removed for debugging)
        pose.pose.orientation.x = 0.0
        pose.pose.orientation.y = 0.0
        pose.pose.orientation.z = 0.0
        pose.pose.orientation.w = 1.0

        return pose

    def move_to_pose(self, pose_stamped, description=''):

        goal = MoveGroup.Goal()

        goal.request.group_name = 'robot_arm'

        goal.request.num_planning_attempts = 20
        goal.request.allowed_planning_time = 10.0

        goal.request.max_velocity_scaling_factor = 0.2
        goal.request.max_acceleration_scaling_factor = 0.2

        # -----------------------------
        # POSITION CONSTRAINT ONLY
        # -----------------------------
        pos_constraint = PositionConstraint()

        pos_constraint.header = pose_stamped.header

        pos_constraint.link_name = 'end_effector_link'

        pos_constraint.target_point_offset = Vector3(
            x=0.0,
            y=0.0,
            z=0.0
        )

        primitive = SolidPrimitive()
        primitive.type = SolidPrimitive.BOX

        # Larger tolerance box
        primitive.dimensions = [0.03, 0.03, 0.03]

        bv = BoundingVolume()
        bv.primitives = [primitive]
        bv.primitive_poses = [pose_stamped.pose]

        pos_constraint.constraint_region = bv
        pos_constraint.weight = 1.0

        constraints = Constraints()
        constraints.position_constraints = [pos_constraint]

        goal.request.goal_constraints = [constraints]

        self.get_logger().info(
            f'Moving to {description} '
            f'({pose_stamped.pose.position.x:.3f}, '
            f'{pose_stamped.pose.position.y:.3f}, '
            f'{pose_stamped.pose.position.z:.3f})'
        )

        future = self._action_client.send_goal_async(goal)

        while not future.done():
            time.sleep(0.05)

        goal_handle = future.result()

        if not goal_handle.accepted:
            self.get_logger().error(
                f'Goal rejected for {description}'
            )
            return False

        result_future = goal_handle.get_result_async()

        while not result_future.done():
            time.sleep(0.05)

        result = result_future.result().result

        if result.error_code.val == 1:
            self.get_logger().info(
                f'Reached {description} ✓'
            )

            time.sleep(0.3)
            return True

        else:
            self.get_logger().warn(
                f'Failed {description} '
                f'- error code: {result.error_code.val}'
            )

            return False

    def go_home(self):

        self.get_logger().info(
            'Going to home position...'
        )

        goal = MoveGroup.Goal()

        goal.request.group_name = 'robot_arm'

        goal.request.num_planning_attempts = 10
        goal.request.allowed_planning_time = 5.0

        goal.request.max_velocity_scaling_factor = 0.2
        goal.request.max_acceleration_scaling_factor = 0.2

        joint_names = [
            'stepper_joint',
            'joint_1',
            'joint_2',
            'bracket_1_joint',
            'end_effector_joint'
        ]

        positions = [
            0.0,
            0.0,
            0.0,
            0.0,
            0.0
        ]

        constraints = Constraints()

        for name, pos in zip(joint_names, positions):

            jc = JointConstraint()

            jc.joint_name = name
            jc.position = float(pos)

            jc.tolerance_above = 0.05
            jc.tolerance_below = 0.05

            jc.weight = 1.0

            constraints.joint_constraints.append(jc)

        goal.request.goal_constraints = [constraints]

        future = self._action_client.send_goal_async(goal)

        while not future.done():
            time.sleep(0.05)

        goal_handle = future.result()

        if goal_handle.accepted:

            result_future = goal_handle.get_result_async()

            while not result_future.done():
                time.sleep(0.05)

            self.get_logger().info(
                'At home position!'
            )

            time.sleep(1.0)

        else:
            self.get_logger().error(
                'Failed to reach home'
            )

    def draw_circle(
        self,
        cx,
        cy,
        cz,
        radius=0.02,
        num_points=8
    ):

        self.get_logger().info(
            f'Drawing circle '
            f'r={radius}m at '
            f'({cx:.3f},{cy:.3f},{cz:.3f})'
        )

        for i in range(num_points):

            angle = (
                2.0 * math.pi * i / num_points
            )

            x = cx + radius * math.cos(angle)
            y = cy + radius * math.sin(angle)

            pose = self.make_pose(x, y, cz)

            success = self.move_to_pose(
                pose,
                f'circle point {i+1}/{num_points}'
            )

            if not success:
                self.get_logger().warn(
                    'Skipping failed point...'
                )

        self.get_logger().info(
            'Circle complete!'
        )

    def draw_square(
        self,
        cx,
        cy,
        cz,
        side=0.03
    ):

        self.get_logger().info(
            f'Drawing square side={side}m'
        )

        h = side / 2.0

        corners = [
            (cx - h, cy - h, cz),
            (cx + h, cy - h, cz),
            (cx + h, cy + h, cz),
            (cx - h, cy + h, cz),
        ]

        for i, (x, y, z) in enumerate(corners):

            pose = self.make_pose(x, y, z)

            self.move_to_pose(
                pose,
                f'square point {i+1}/4'
            )

        self.get_logger().info(
            'Square complete!'
        )


def main():

    rclpy.init()

    shape = (
        sys.argv[1]
        if len(sys.argv) > 1
        else 'circle'
    )

    drawer = ShapeDrawer()

    executor = MultiThreadedExecutor()
    executor.add_node(drawer)

    thread = threading.Thread(
        target=executor.spin,
        daemon=True
    )

    thread.start()

    time.sleep(1.0)

    # SAFER POSITION
    # Lower Z for easier IK
    CX = 0.15
    CY = 0.00
    CZ = 0.20

    try:

        drawer.go_home()

        time.sleep(1.0)

        if shape == 'circle':

            drawer.draw_circle(
                CX,
                CY,
                CZ,
                radius=0.02,
                num_points=8
            )

        elif shape == 'square':

            drawer.draw_square(
                CX,
                CY,
                CZ,
                side=0.03
            )

        else:

            drawer.get_logger().error(
                f'Unknown shape: {shape}'
            )

        time.sleep(1.0)

        drawer.go_home()

    except KeyboardInterrupt:
        pass

    finally:

        executor.shutdown()

        drawer.destroy_node()

        rclpy.shutdown()


if __name__ == '__main__':
    main()