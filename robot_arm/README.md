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

This section contains all commands required to run the full robotic arm system from simulation to hardware control.

---

## 1. Visualize Robot Model in RViz (URDF Check)

Run this to verify the robot description and joint configuration:

```bash
ros2 launch arm_description display.launch.py
