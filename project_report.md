# Project Report: Smart Fire & Smoke Detection System

## 1. Introduction
Fire and smoke hazards can cause injury and property damage. Early detection can help people respond sooner. This project demonstrates a basic Arduino-based prototype that senses smoke/gas levels and infrared radiation associated with flames, then produces audible and visual alerts.

## 2. Objective
To build an educational embedded-system prototype that:
- reads an MQ-series sensor's analog output,
- detects a flame using an IR fire sensor's digital output,
- distinguishes smoke-only, fire-only, and simultaneous detection,
- signals each condition through a buzzer pattern and synchronized red LED.

## 3. Hardware
- Arduino UNO
- MQ-2 or MQ-135 sensor module
- 4-pin IR fire sensor module
- Active buzzer
- Red LED and 220Ω resistor
- Breadboard and jumper wires

## 4. Software
Arduino IDE; sketch written in Arduino C/C++.

## 5. Working Principle
The Arduino reads the MQ sensor from A0. If its value exceeds the configured threshold (800), smoke is flagged. The IR module's DO pin is read on D2; this sketch assumes LOW means flame detected. The controller selects an alarm mode based on the two sensor states.

## 6. Alarm Modes
| Condition | Alarm |
|---|---|
| No detection | Outputs OFF |
| Smoke only | Two short beeps, one long beep, pause |
| Fire only | Four short beeps, pause |
| Fire + smoke | Long beep, pause |

The red LED follows the buzzer's ON/OFF state.

## 7. Testing
1. Observe the MQ sensor's baseline value in Serial Monitor.
2. Allow the MQ sensor to warm up according to its module documentation.
3. Adjust the threshold based on observed readings.
4. Test the IR module using a safe, controlled flame-detection demonstration; do not bring fire near wiring or flammable materials.
5. Confirm each condition and its corresponding alarm.

## 8. Limitations
- MQ readings vary with sensor model, warm-up, calibration, and environment.
- IR flame modules can be affected by ambient infrared sources and line of sight.
- A threshold of 800 is a project setting, not a universal smoke concentration measurement.
- The prototype is not certified for life-safety use.

## 9. Future Scope
- LCD/OLED display
- ESP32 wireless monitoring
- Mobile notifications
- Temperature sensor integration
- Automatic ventilation
- Enclosure and power backup

## 10. Conclusion
The prototype demonstrates sensor integration and event-based alert patterns using an Arduino UNO. It is suitable for learning and demonstration, but must not replace certified fire detection equipment.
