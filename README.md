# 🔥 Smart Fire & Smoke Detection System

An Arduino UNO-based educational prototype that detects smoke and flame conditions using an MQ-series gas sensor and a 4-pin IR fire sensor module. It produces distinct buzzer patterns and synchronizes a red LED with the alarm.

## Features
- Smoke detection using MQ-2 / MQ-135 analog output
- Fire detection using IR fire sensor digital output (DO)
- Three alarm patterns: smoke, fire, and simultaneous fire + smoke
- Red LED synchronized with buzzer
- Serial Monitor status updates every 500 ms
- Adjustable smoke threshold (currently 800)

## Components
| Component | Qty |
|---|---:|
| Arduino UNO | 1 |
| MQ-2 or MQ-135 sensor module | 1 |
| 4-pin IR fire sensor module | 1 |
| Active buzzer | 1 |
| Red LED | 1 |
| 220Ω resistor | 1 |
| Breadboard and jumper wires | As required |

## Connections
| Component pin | Arduino UNO |
|---|---|
| MQ sensor VCC | 5V |
| MQ sensor GND | GND |
| MQ sensor AO | A0 |
| IR fire sensor VCC | 5V |
| IR fire sensor GND | GND |
| IR fire sensor DO | D2 |
| IR fire sensor AO | Not connected |
| Active buzzer + | D8 |
| Active buzzer − | GND |
| Red LED anode (long leg) | D9 through 220Ω resistor |
| Red LED cathode (short leg) | GND |

See [`circuit/connections.md`](circuit/connections.md) for wiring notes.

## Alarm behavior
| Condition | Pattern |
|---|---|
| Normal | Buzzer and LED OFF |
| Smoke only | Two short beeps, one long beep, then pause |
| Fire only | Four short beeps, then pause |
| Smoke + fire | Long beep, then pause |

The LED follows the buzzer's ON/OFF pattern.

## Upload instructions
1. Install/open Arduino IDE.
2. Open `fire_smoke_detection.ino`.
3. Select **Tools → Board → Arduino UNO**.
4. Select the correct port under **Tools → Port**.
5. Upload the sketch.
6. Open Serial Monitor at **9600 baud**.

## Smoke threshold
The sketch uses:
```cpp
const int smokeThreshold = 800;
```
Smoke is flagged when the analog reading is **greater than 800**. Calibrate this threshold using your actual sensor readings; MQ sensors need warm-up and environmental calibration.

## Repository structure
```text
smart-fire-smoke-detection-system/
├── README.md
├── fire_smoke_detection.ino
├── circuit/
│   └── connections.md
├── docs/
│   └── project_report.md
├── images/
│   └── add-your-project-photo.jpg
├── LICENSE
└── .gitignore
```

## Safety disclaimer
This is an educational prototype, not a certified fire alarm. Do not use it as a substitute for certified smoke detectors or professional fire-safety equipment.

## Author
**Dhruv Mishra**  
B.Tech CSE — Artificial Intelligence & Machine Learning

## License
MIT License. See [`LICENSE`](LICENSE).
