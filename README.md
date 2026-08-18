# Autonomous Aquarium Water Monitoring, Fish Feeding & Aerator System

An Arduino-based system that monitors aquarium water quality in real time and automates feeding and water circulation, built as a hardware project for CSE461.

## Overview

The system continuously tracks temperature, turbidity, and pH inside an aquarium, flagging unsafe water conditions with a warning LED. A servo motor handles scheduled feeding, while a DC water pump, driven through an L298N motor driver and relay module, manages circulation.

## Components

- **Microcontroller:** Arduino Uno
- **Sensors:**
  - DS18B20 temperature sensor
  - Turbidity sensor
  - pH sensor (PH-4502C module)
- **Actuators:**
  - DC water pump
  - Servo motor (feeding mechanism)
  - Relay module
- **Chassis:** Hardboard and breadboards
- **Other:** 9V/12V battery, resistors, jumper wires

## Wiring

**Sensors**
| Component | Pin |
|---|---|
| Temperature (DS18B20) data | D2 (with 4.7kΩ pull-up to 5V) |
| Turbidity sensor output | A0 |
| pH sensor output | A1 |
| Warning LED | D7 |

**Actuators**
| Component | Pin |
|---|---|
| DC motor control | D2, D3 (via L298N H-bridge) |
| Servo signal | D9 |
| Relay (pump control) | 12V from battery, 5V from Arduino, GND shared |

## Software Setup

1. Install the [Arduino IDE](https://www.arduino.cc/en/software).
2. In the IDE, go to **Sketch > Include Library > Manage Libraries** and install:
   - `OneWire`
   - `DallasTemperature`
   - `Servo`
3. Connect the Arduino Uno via USB, select the correct board and COM port under **Tools**, then upload the sketch.

## How It Works

- **Turbidity monitoring:** reads an analog value each cycle; if it drops below a threshold (indicating cloudier water), the warning LED turns on.
- **Temperature monitoring:** reads via the DS18B20 sensor and prints both °C and °F over serial.
- **pH monitoring:** reads a raw analog value and converts it to voltage; exact pH requires calibration against known buffer solutions.
- **Feeding cycle:** the servo motor moves to 0°, holds for 10 seconds, then moves to 160° and holds for 1 second, repeating continuously to dispense food.
- **Water circulation:** the DC pump runs continuously forward through the L298N driver.

All sensor readings print to the Serial Monitor at 9600 baud.

## pH Calibration

1. Prepare buffer solutions of known pH (e.g. 4.0, 7.0, 10.0).
2. Connect the sensor's `Po` output to A0 and `G` to GND.
3. Run the calibration sketch and observe the voltage reading in the Serial Monitor.
4. Adjust the onboard offset potentiometer until the reading at pH 7.0 equals 2.50V.
5. Use the recorded voltage-to-pH pairs to build a linear mapping in code.

## Troubleshooting

| Issue | Likely Cause | Fix |
|---|---|---|
| No serial output | Wrong COM port or baud rate | Check Tools > Port, set baud to 9600 |
| Servo not moving | Not on 5V / wrong pin | Confirm connection to D9 with proper voltage |
| DC motor not running | Wiring or H-bridge issue | Check H-bridge wiring; pin1 LOW, pin2 HIGH |
| Temperature reads -127°C | Sensor not detected | Check DS18B20 wiring and pull-up resistor |
| LED never lights for turbidity | Sensor reading stuck high | Test with clean vs. dirty water |
| pH readings look wrong | Sensor uncalibrated | Recalibrate with known buffer solutions |
| Random resets | Power instability | Use a stable power source or add capacitor smoothing |

## Safety & Maintenance

- Always power off before changing any connections.
- Keep the Arduino and electronics away from water contact.
- Clean sensors regularly to prevent buildup affecting readings.
- Use gloves when handling water of unknown quality.

## Known Limitations

- Water level sensor, peristaltic pump, air pump, and solenoid valves were left out of this build due to budget constraints.
- The pH sensor consistently reported a narrow 3–4 pH range regardless of the actual liquid tested; this was traced to the sensor module itself and could not be resolved within the project's budget.
