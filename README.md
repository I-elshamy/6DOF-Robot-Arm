# 🤖 Industrial Robotics Project

Welcome to our Industrial Robotics project repository!  
This project was developed as part of the Industrial Robotics course submission and focuses on building, controlling, and simulating a robotic arm system using modern robotics tools and embedded systems.

---

## 🚀 Project Overview

The project combines:

- 🦾 Robotic arm design and control
- ⚙️ ROS 2 integration
- 🎮 Motion planning with MoveIt
- 🔌 Arduino/ESP32 communication
- 🖥️ Simulation and visualization
- 📡 Serial/UART communication

The goal is to create a smart and flexible robotic manipulation system capable of performing automated movements and task execution.

---

## 🛠️ Technologies Used

- **ROS 2**
- **MoveIt 2**
- **Gazebo**
- **RViz**
- **Arduino / ESP32**
- **Python**
- **C++**
- **UART Serial Communication**

---

## 📂 Repository Structure

```bash
src/
 ├── robot_description/
 ├── robot_control/
 ├── moveit_config/
 ├── serial_communication/
 └── simulation/
# Full Stack Robotic Arm System

A complete full-stack robotic arm platform integrating mechanical design, simulation, motion planning, embedded control, and real hardware execution using ROS 2, MoveIt 2, Gazebo, ESP32, MATLAB/Simulink, Arduino, and SolidWorks.

---

# Overview

This project is a multidisciplinary robotics system developed to design, simulate, plan, and control a robotic arm in both virtual and real-world environments.

The system combines multiple parallel control and development stacks:

### 1. ROS 2 + MoveIt 2 Stack
Used for:
- Motion planning
- Robot state management
- Simulation in Gazebo
- Visualization in RViz
- Real-time control via micro-ROS and ESP32

### 2. MATLAB + Simulink + Arduino Hardware Stack (Parallel Control Path)
Used for:
- Trajectory planning and generation in MATLAB/Simulink
- Control system design and validation
- Direct sending of joint angles using Arduino Hardware Support Package
- Servo motor actuation without ROS dependency

This provides an alternative and experimental control pipeline parallel to the ROS 2 ecosystem.

---

# Features

- Full robotic arm CAD design (SolidWorks)
- URDF/Xacro robot modeling
- Gazebo physics simulation
- RViz visualization
- MoveIt 2 motion planning and execution
- MATLAB/Simulink trajectory generation
- Arduino-based direct servo control pipeline
- ESP32 + micro-ROS embedded control integration
- Dual-stack control architecture (ROS2 + MATLAB/Arduino)
- STL mesh generation for simulation and manufacturing

---

# System Architecture

```text
                    ┌──────────────────────┐
                    │      MoveIt 2        │
                    │  Motion Planning      │
                    └─────────┬────────────┘
                              │
                              v
                    ┌──────────────────────┐
                    │        ROS 2         │
                    │     Middleware       │
                    └───────┬───────┬──────┘
                            │       │
                            v       v
                  ┌────────────┐  ┌──────────────┐
                  │   Gazebo   │  │     RViz     │
                  │ Simulation │  │ Visualization│
                  └────────────┘  └──────────────┘
                            │
                            v
                    ┌──────────────────────┐
                    │  micro-ROS Agent     │
                    └─────────┬────────────┘
                              │
                              v
                    ┌──────────────────────┐
                    │        ESP32         │
                    │   Embedded Control   │
                    └─────────┬────────────┘
                              │
                              v
                    ┌──────────────────────┐
                    │    Servo Motors      │
                    └──────────────────────┘
