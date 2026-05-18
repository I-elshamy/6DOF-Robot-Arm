#!/usr/bin/env python3

import sys
import time
import threading

import rclpy
from rclpy.node import Node
from rclpy.action import ActionClient
from rclpy.executors import MultiThreadedExecutor

from moveit_msgs.action import MoveGroup
from moveit_msgs.msg import (
    Constraints,
    PositionConstraint,
    BoundingVolume
)

from geometry_msgs.msg import (
    PoseStamped,
    Vector3
)

from shape_msgs.msg import SolidPrimitive


class XYZMover(Node):

    def __init__(self):

        super().__init__('xyz_mover')

        # MoveIt action client
        self.move_action = ActionClient(
            self,
            MoveGroup,
            '/move_action'
        )

        self.get_logger().info(
            'Waiting for MoveIt action server...'
        )

        self.move_action.wait_for_server()

        self.get_logger().info(
            'Connected to MoveIt!'
        )

    def move_to_xyz(self, x, y, z):

        # -----------------------------------
        # CREATE TARGET POSE
        # -----------------------------------

        pose = PoseStamped()

        # IMPORTANT:
        # Change this if your planning frame differs
        pose.header.frame_id = 'base_link'

        pose.header.stamp = (
            self.get_clock().now().to_msg()
        )

        pose.pose.position.x = float(x)
        pose.pose.position.y = float(y)
        pose.pose.position.z = float(z)

        # Dummy orientation
        # We will NOT constrain orientation
        pose.pose.orientation.w = 1.0

        # -----------------------------------
        # CREATE MOVEIT GOAL
        # -----------------------------------

        goal = MoveGroup.Goal()

        goal.request.group_name = 'robot_arm'

        goal.request.num_planning_attempts = 20

        goal.request.allowed_planning_time = 10.0

        goal.request.max_velocity_scaling_factor = 0.2

        goal.request.max_acceleration_scaling_factor = 0.2

        # -----------------------------------
        # POSITION CONSTRAINT
        # -----------------------------------

        pos_constraint = PositionConstraint()

        pos_constraint.header = pose.header

        # IMPORTANT:
        # Must match your MoveIt tip link
        pos_constraint.link_name = 'end_effector_link'

        pos_constraint.target_point_offset = Vector3(
            x=0.0,
            y=0.0,
            z=0.0
        )

        # Small acceptable region
        primitive = SolidPrimitive()

        primitive.type = SolidPrimitive.BOX

        primitive.dimensions = [
            0.02,
            0.02,
            0.02
        ]

        bounding_volume = BoundingVolume()

        bounding_volume.primitives = [primitive]

        bounding_volume.primitive_poses = [
            pose.pose
        ]

        pos_constraint.constraint_region = (
            bounding_volume
        )

        pos_constraint.weight = 1.0

        # -----------------------------------
        # FINAL CONSTRAINTS
        # -----------------------------------

        constraints = Constraints()

        constraints.position_constraints = [
            pos_constraint
        ]

        goal.request.goal_constraints = [
            constraints
        ]

        # -----------------------------------
        # SEND GOAL
        # -----------------------------------

        self.get_logger().info(
            f'Moving to: '
            f'x={x:.3f}, '
            f'y={y:.3f}, '
            f'z={z:.3f}'
        )

        future = self.move_action.send_goal_async(
            goal
        )

        while not future.done():
            time.sleep(0.05)

        goal_handle = future.result()

        if not goal_handle.accepted:

            self.get_logger().error(
                'Goal rejected!'
            )

            return False

        # -----------------------------------
        # WAIT FOR RESULT
        # -----------------------------------

        result_future = (
            goal_handle.get_result_async()
        )

        while not result_future.done():
            time.sleep(0.05)

        result = (
            result_future.result().result
        )

        # -----------------------------------
        # CHECK RESULT
        # -----------------------------------

        if result.error_code.val == 1:

            self.get_logger().info(
                'Motion successful!'
            )

            return True

        else:

            self.get_logger().error(
                f'Motion failed! '
                f'Error code: '
                f'{result.error_code.val}'
            )

            return False


def main():

    rclpy.init()

    # -----------------------------------
    # READ XYZ FROM TERMINAL
    # -----------------------------------

    if len(sys.argv) != 4:

        print(
            '\nUsage:\n'
            'ros2 run arm_control xyz_mover '
            'x y z\n'
        )

        return

    x = float(sys.argv[1])
    y = float(sys.argv[2])
    z = float(sys.argv[3])

    mover = XYZMover()

    # Executor thread
    executor = MultiThreadedExecutor()

    executor.add_node(mover)

    thread = threading.Thread(
        target=executor.spin,
        daemon=True
    )

    thread.start()

    time.sleep(1.0)

    try:

        mover.move_to_xyz(x, y, z)

    except KeyboardInterrupt:
        pass

    finally:

        executor.shutdown()

        mover.destroy_node()

        rclpy.shutdown()


if __name__ == '__main__':
    main()