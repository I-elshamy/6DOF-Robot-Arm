import os
from pathlib import Path
from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import (IncludeLaunchDescription, SetEnvironmentVariable,
                            TimerAction)
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch_ros.parameter_descriptions import ParameterValue
from launch.substitutions import Command
from ament_index_python.packages import get_package_share_directory
from moveit_configs_utils import MoveItConfigsBuilder


def generate_launch_description():

    arm_description_dir = get_package_share_directory('arm_description')

    ros_distro  = os.environ.get('ROS_DISTRO', 'jazzy')
    is_ignition = 'True' if ros_distro == 'humble' else 'False'

    # ── Robot description (xacro → string) ──────────────────────────────
    robot_description = ParameterValue(
        Command([
            'xacro ',
            os.path.join(arm_description_dir, 'urdf', 'robot_arm.urdf.xacro'),
            ' is_ignition:=', is_ignition
        ]),
        value_type=str
    )

    # ── MoveIt config (loads all yamls automatically) ────────────────────
    moveit_config = (
        MoveItConfigsBuilder('robot_arm', package_name='moveit_trial')
        .to_moveit_configs()
    )
    config_dict = moveit_config.to_dict()

    # ── Gazebo resource path ─────────────────────────────────────────────
    gazebo_resource_path = SetEnvironmentVariable(
        name='GZ_SIM_RESOURCE_PATH',
        value=[str(Path(arm_description_dir).parent.resolve())]
    )

    # ── Single robot_state_publisher ─────────────────────────────────────
    # use_sim_time=False - Gazebo controller_manager uses ROS clock
    robot_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='robot_state_publisher',
        output='screen',
        parameters=[
            {'robot_description': robot_description},
            {'use_sim_time': True},
        ]
    )

    # ── Gazebo Harmonic ──────────────────────────────────────────────────
    gazebo = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            os.path.join(
                get_package_share_directory('ros_gz_sim'),
                'launch', 'gz_sim.launch.py'
            )
        ]),
        launch_arguments=[('gz_args', [' -v 4 -r empty.sdf'])]
    )

    # ── Spawn robot in Gazebo ────────────────────────────────────────────
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

    delayed_spawn = TimerAction(
        period=5.0,
        actions=[spawn_robot]
    )
    # ── Clock bridge (Gazebo → ROS) ──────────────────────────────────────
    clock_bridge = Node(
        package='ros_gz_bridge',
        executable='parameter_bridge',
        arguments=['/clock@rosgraph_msgs/msg/Clock[gz.msgs.Clock'],
        output='screen'
    )

    # ── Controllers ──────────────────────────────────────────────────────
    # IMPORTANT: use_sim_time=False for controllers
    # Gazebo's controller_manager uses ROS clock not sim clock
    # Passing use_sim_time=true causes segfault in joint_trajectory_controller
    joint_state_broadcaster_spawner = Node(
        package='controller_manager',
        executable='spawner',
        arguments=[
            'joint_state_broadcaster',
            '--controller-manager', '/controller_manager',
        ],
        parameters=[{'use_sim_time': False}],
        output='screen'
    )

    arm_controller_spawner = Node(
        package='controller_manager',
        executable='spawner',
        arguments=[
            'robot_arm_controller',
            '--controller-manager', '/controller_manager',
        ],
        parameters=[{'use_sim_time': False}],
        output='screen'
    )

    # Delay controllers by 8s to let Gazebo fully initialize
    delayed_controllers = TimerAction(
        period=8.0,
        actions=[
            joint_state_broadcaster_spawner,
            arm_controller_spawner,
        ]
    )

    # ── move_group ───────────────────────────────────────────────────────
    # use_sim_time=False to match controller_manager clock
    move_group_node = Node(
        package='moveit_ros_move_group',
        executable='move_group',
        output='screen',
        parameters=[
            config_dict,
            {'use_sim_time': True},
            {'moveit_controller_manager':
                'moveit_simple_controller_manager/MoveItSimpleControllerManager'},
            {'moveit_simple_controller_manager': {
                'controller_names': ['robot_arm_controller'],
                'robot_arm_controller': {
                    'type': 'FollowJointTrajectory',
                    'action_ns': 'follow_joint_trajectory',
                    'default': True,
                    'joints': [
                        'stepper_joint',
                        'joint_1',
                        'joint_2',
                        'bracket_1_joint',
                        'end_effector_joint',
                    ]
                }
            }},
            {'publish_robot_description_semantic': True},
        ]
    )

    # Delay move_group by 15s to let controllers be ready first
    delayed_moveit = TimerAction(
        period=2.0,
        actions=[move_group_node]
    )

    # ── RViz ─────────────────────────────────────────────────────────────
    rviz_node = Node(
        package='rviz2',
        executable='rviz2',
        output='screen',
        arguments=[
            '-d', str(moveit_config.package_path / 'config' / 'moveit.rviz')
        ],
        parameters=[
            config_dict,
            {'use_sim_time': True},
        ]
    )

    # Delay RViz by 17s to let move_group be ready first
    delayed_rviz = TimerAction(
        period=4.0,
        actions=[rviz_node]
    )

    return LaunchDescription([
    gazebo_resource_path,
    robot_state_publisher,
    # MoveIt first
    delayed_moveit,
    delayed_rviz,
    # Then Gazebo after MoveIt is ready
    TimerAction(period=5.0, actions=[gazebo]),
    TimerAction(period=6.0, actions=[spawn_robot]),
    TimerAction(period=7.0, actions=[clock_bridge]),
    TimerAction(period=15.0, actions=[
        joint_state_broadcaster_spawner,
        arm_controller_spawner,
    ]),
])