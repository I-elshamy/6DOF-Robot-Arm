# ROS2 Workspace (MoveIt 2 + Gazebo + ESP32 Control)

This directory contains the ROS 2 control stack for the robotic arm, including simulation, motion planning, and real hardware execution using micro-ROS.

The system was generated using **MoveIt Setup Assistant** and extended with custom nodes for real-time joint control and ESP32 integration.

---

# Overview

This ROS 2 stack is responsible for:

- Robot description (URDF/Xacro)
- Motion planning using MoveIt 2
- Simulation in Gazebo
- Visualization in RViz
- Joint state monitoring
- Conversion of joint states → servo commands
- Communication with ESP32 via micro-ROS

---

# System Pipeline

```text
MoveIt 2 (Motion Planning)
        │
        v
Joint Trajectory Controller (ROS2)
        │
        v
Joint States Topic (/joint_states)
        │
        v
Custom ROS2 Node
(joint_state_to_servo)
        │
        │ converts joint angles → servo angles
        v
Micro-ROS Publisher
        │
        v
micro-ROS Agent (PC side)
        │
        v
ESP32 Subscriber
        │
        v
Servo Motors


# Running the Project (ROS2 Stack)

## Full Launch Commands

```bash
# 1. Launch RViz and visualize the robot URDF (check robot model, joints, and TF tree)
ros2 launch arm_description display.launch.py

# 2. Launch Gazebo simulation + MoveIt 2 motion planning (full simulated robot control stack)
ros2 launch arm_description moveit_gazebo.launch.py

# 3. Run custom control node that converts /joint_states into servo angles for ESP32
ros2 run arm-control control_micro

# 4. Launch joystick driver to control gripper/clamp manually
ros2 run joy joy_node

# 5. Start micro-ROS agent (UDP over WiFi) to bridge ROS2 and ESP32 firmware
ros2 run micro_ros_agent micro_ros_agent udp4 --port 8888
