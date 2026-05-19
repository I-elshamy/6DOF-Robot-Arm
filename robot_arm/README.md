# ROS2 Workspace (MoveIt 2 + Gazebo + ESP32 Control Stack)

This workspace contains the complete ROS 2 control pipeline for the robotic arm project, including:

- Robot visualization using RViz
- Motion planning using MoveIt 2
- Physics simulation using Gazebo
- Real hardware communication using micro-ROS and ESP32
- Joystick-based gripper control
- Joint state to servo angle conversion

The stack was initially generated using **MoveIt Setup Assistant** and later extended with custom launch files and control nodes for hardware integration.

---

# System Pipeline

```text
MoveIt 2
    │
    v
ROS 2 Controllers
    │
    v
/joint_states
    │
    v
control_micro node
    │
    v
micro-ROS Agent
    │
    v
ESP32
    │
    v
Servo Motors / Gripper
```

---

# Workspace Features

- Full MoveIt 2 integration
- Gazebo simulation support
- RViz visualization
- ESP32 hardware communication
- micro-ROS WiFi bridge
- Real-time joint state conversion
- Servo angle mapping
- Joystick gripper control
- Parallel simulation + hardware testing

---

# ROS2 Packages

| Package | Description |
|---|---|
| `arm_description` | URDF/Xacro robot model + launch files |
| `arm_moveit_config` | MoveIt Setup Assistant generated package |
| `arm_control` | Joint state to servo conversion node |
| `micro_ros_interface` | ESP32 communication layer |
| `gazebo_simulation` | Gazebo simulation integration |

---

# Running the Project

## 1. Launch RViz and Verify Robot URDF

```bash
# Launch RViz and visualize robot model
ros2 launch arm_description display.launch.py
```

### RViz Screenshot

![RViz](../media/screenshots/rviz.png)

### RViz Demo

![RViz Demo](../media/screencast/rviz.gif)

---

## 2. Launch Gazebo + MoveIt 2 Simulation

```bash
# Launch Gazebo simulation + MoveIt motion planning
ros2 launch arm_description moveit_gazebo.launch.py
```

### Gazebo Screenshot

![Gazebo](../media/screenshots/gazebo.png)

### MoveIt Screenshot

![MoveIt](../media/screenshots/moveit.png)

### MoveIt Demo

![MoveIt Demo](../media/screencast/moveit.gif)

### Gazebo Mimicking MoveIt Motion

![Gazebo Demo](../media/screencast/gazebo.gif)

---

## 3. Run Joint State → Servo Control Node

```bash
# Convert joint states into servo angles for ESP32
ros2 run arm-control control_micro
```

This node:
- Subscribes to `/joint_states`
- Converts joint angles into servo-compatible commands
- Publishes processed angles for ESP32 execution

---

## 4. Launch Joystick Control

```bash
# Launch joystick node for gripper control
ros2 run joy joy_node
```

This node allows:
- Manual gripper opening/closing
- Real-time joystick interaction

---

## 5. Run micro-ROS Agent (WiFi Mode)

```bash
# Start micro-ROS UDP bridge
ros2 run micro_ros_agent micro_ros_agent udp4 --port 8888
```

This creates the communication bridge between:
- ROS 2 host machine
- ESP32 micro-ROS client firmware

---

# ESP32 Firmware Configuration

Before running WiFi mode, edit the firmware located at:

```text
firmware/robot_arm_trial2/
```

Update the network parameters inside the setup function for micro-ROS transports.

Example:

```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
IPAddress agent_ip(192,168,1,100);
```

---

# Recommended Startup Order

```text
1. Start micro-ROS agent
2. Launch RViz (optional URDF verification)
3. Launch Gazebo + MoveIt
4. Run control_micro node
5. Launch joystick node (optional)
```

---

# Topics

## Input Topics

| Topic | Type | Description |
|---|---|---|
| `/joint_states` | `sensor_msgs/JointState` | Joint positions from controllers |

---

## Output Topics

| Topic | Type | Description |
|---|---|---|
| `/servo_angles` | Custom / std_msgs | Servo commands sent to ESP32 |

---

# Dependencies

- ROS 2 Jazzy / Humble
- MoveIt 2
- Gazebo
- RViz
- micro-ROS
- `joy` package
- Python3 / `rclpy`

---

# Notes

- MoveIt Setup Assistant was used for initial robot configuration
- Gazebo and MoveIt are launched together through a custom launch file
- ESP32 receives commands over WiFi using UDP micro-ROS
- System supports both simulation and real hardware execution
- Servo mapping depends on physical calibration

---

# Future Improvements

- Encoder feedback integration
- Closed-loop control
- Force/torque sensing
- Trajectory smoothing
- Computer vision integration
- Autonomous pick-and-place pipeline

---
