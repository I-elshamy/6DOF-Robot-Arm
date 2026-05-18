from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():

    shape_drawer_node = Node(
        package='arm_control',
        executable='shape_drawer',
        name='shape_drawer',
        output='screen',
        arguments=['square'],   # change to 'square' for square
        parameters=[{'use_sim_time': True}]
    )

    return LaunchDescription([shape_drawer_node])