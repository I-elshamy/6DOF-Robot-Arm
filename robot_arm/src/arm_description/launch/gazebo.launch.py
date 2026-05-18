from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import IncludeLaunchDescription, SetEnvironmentVariable, TimerAction
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.parameter_descriptions import ParameterValue
from launch.substitutions import Command
from ament_index_python.packages import get_package_share_directory
import os
from pathlib import Path
from launch.actions import ExecuteProcess




def generate_launch_description():

    arm_description_dir = get_package_share_directory('arm_description')

    ros_distro = os.environ.get('ROS_DISTRO', 'jazzy')
    is_ignition = 'True' if ros_distro == 'humble' else 'False'

    robot_description = ParameterValue(
        Command([
            'xacro ',
            os.path.join(arm_description_dir, 'urdf', 'robot_arm.urdf.xacro'),
            ' is_ignition:=', is_ignition
        ]),
        value_type=str
    )
    # Kill any leftover controller processes before starting
    cleanup = ExecuteProcess(
    cmd=['bash', '-c', 
         'pkill -f controller_manager || true; '
         'pkill -f robot_arm_controller || true; '
         'pkill -f joint_state_broadcaster || true; '
         'sleep 1'],
        output='screen'
    )

    robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        parameters=[
            {'robot_description': robot_description},
            {'use_sim_time': True},
        ]
    )

    gazebo_resource_path = SetEnvironmentVariable(
        name='GZ_SIM_RESOURCE_PATH',
        value=[str(Path(arm_description_dir).parent.resolve())]
    )

    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            os.path.join(
                get_package_share_directory('ros_gz_sim'),
                'launch', 'gz_sim.launch.py'
            )
        ]),
        launch_arguments=[('gz_args', [' -v 4 -r empty.sdf'])]
    )

    spawn_robot = Node(
        package='ros_gz_sim',
        executable='create',
        arguments=[
            '-topic', 'robot_description',
            '-name', 'arm',
            '-z', '0.0',
        ],
        output='screen'
    )

    gz_ros2_bridge = Node(
        package='ros_gz_bridge',
        executable='parameter_bridge',
        arguments=['/clock@rosgraph_msgs/msg/Clock[gz.msgs.Clock'],
        output='screen'
    )

    # Spawn controllers with delay to let Gazebo fully initialize
    # NOTE: do NOT pass use_sim_time here - causes segfault in jazzy
    joint_state_broadcaster_spawner = Node(
        package='controller_manager',
        executable='spawner',
        arguments=[
            'joint_state_broadcaster',
            '--controller-manager', '/controller_manager',
        ],
        output='screen'
    )

    arm_controller_spawner = Node(
        package='controller_manager',
        executable='spawner',
        arguments=[
            'robot_arm_controller',
            '--controller-manager', '/controller_manager',
        ],
        output='screen'
    )

    # Delay controller spawning by 8 seconds to give Gazebo time to fully load
    delayed_controllers = TimerAction(
        period=8.0,
        actions=[
            joint_state_broadcaster_spawner,
            arm_controller_spawner,
        ]
    )

    return LaunchDescription([
        cleanup,
        gazebo_resource_path,
        robot_state_publisher,
        gazebo,
        spawn_robot,
        gz_ros2_bridge,
        delayed_controllers,
    ])