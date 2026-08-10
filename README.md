# LIS2DW12 Step Counter using nRF52 and Zephyr

## 📌 Project Description

This project implements a simple **step counter** using the **LIS2DW12 accelerometer** with an **nRF52 DK** and **Zephyr RTOS**.

The accelerometer communicates with the nRF52 through the **I²C interface**. The program continuously reads the X, Y, and Z-axis acceleration values, calculates the overall acceleration magnitude, and uses threshold-based detection to identify steps.

## 🔧 Hardware

* nRF52 DK (nRF52832)
* CJMCU-212 / LIS2DW12 accelerometer
* Jumper wires

## 🔌 Communication

The LIS2DW12 is connected to the nRF52 using I²C.

| Signal      | nRF52 |
| ----------- | ----- |
| SDA         | P0.26 |
| SCL         | P0.27 |
| I²C Address | 0x18  |

## ⚙️ Sensor Configuration

The LIS2DW12 is configured with:

* Output Data Rate: 50 Hz
* Measurement range: ±2g
* I²C communication

## 🚶 Step Detection

The program reads six bytes containing the X, Y, and Z-axis data.

The three-axis acceleration values are combined to calculate the acceleration magnitude.

A step is detected when the magnitude exceeds the configured step threshold.

The project uses:

* Step threshold: `18000`
* Reset threshold: `16000`
* Minimum time between detected steps: `300 ms`

The reset threshold allows the system to return to a state where another step can be detected.

## 📊 Output

The program continuously prints:

```text
X = ...
Y = ...
Z = ...
Magnitude = ...
Total Steps = ...
```

When a step is detected:

```text
Step Detected!
```

## 📁 Project Structure

```text
LIS2DW12-Step-Counter/
│
├── src/
│   └── main.c
│
├── CMakeLists.txt
├── prj.conf
└── README.md
```

## 🛠️ Software

* Zephyr RTOS
* nRF Connect SDK
* VS Code
* C programming language

## 🚀 Features

* LIS2DW12 initialization
* I²C communication
* X/Y/Z acceleration reading
* Acceleration magnitude calculation
* Step detection
* Step counting
* Serial/console output

## 📜 License

This project is intended for educational and development purposes.
