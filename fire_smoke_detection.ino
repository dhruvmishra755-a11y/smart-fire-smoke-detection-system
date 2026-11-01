// SMART FIRE AND SMOKE DETECTION SYSTEM
// Arduino UNO
// MQ-series smoke sensor AO -> A0
// IR fire sensor DO -> D2 (LOW means fire detected)
// Active buzzer + -> D8, - -> GND
// Red LED anode -> D9 through 220 ohm resistor, cathode -> GND

#define AQI_SENSOR A0
#define FIRE_SENSOR 2
#define BUZZER 8
#define RED_LED 9

const int smokeThreshold = 800;

bool smokeDetected = false;
bool fireDetected = false;

unsigned long previousMillis = 0;
unsigned long lastSerialMillis = 0;
int currentStep = 0;

enum AlarmMode {
  NORMAL,
  SMOKE_ALARM,
  FIRE_ALARM,
  BOTH_ALARM
};

AlarmMode alarmMode = NORMAL;
AlarmMode previousAlarmMode = NORMAL;

void setup() {
  Serial.begin(9600);

  pinMode(FIRE_SENSOR, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(RED_LED, OUTPUT);

  digitalWrite(BUZZER, LOW);
  digitalWrite(RED_LED, LOW);

  Serial.println("SMART FIRE AND SMOKE DETECTION SYSTEM");
  Serial.println("--------------------------------------");
  Serial.println("System Started");
  Serial.println();
}

void loop() {
  int smokeValue = analogRead(AQI_SENSOR);
  int fireValue = digitalRead(FIRE_SENSOR);

  smokeDetected = smokeValue > smokeThreshold;
  fireDetected = (fireValue == LOW); // Most modules output LOW when fire is detected

  if (smokeDetected && fireDetected) {
    alarmMode = BOTH_ALARM;
  } else if (smokeDetected) {
    alarmMode = SMOKE_ALARM;
  } else if (fireDetected) {
    alarmMode = FIRE_ALARM;
  } else {
    alarmMode = NORMAL;
  }

  // Restart the alarm pattern when the detection condition changes
  if (alarmMode != previousAlarmMode) {
    currentStep = 0;
    previousMillis = millis();
    digitalWrite(BUZZER, LOW);
    digitalWrite(RED_LED, LOW);
    previousAlarmMode = alarmMode;
  }

  // Print status every 500 ms to keep Serial Monitor readable
  if (millis() - lastSerialMillis >= 500) {
    lastSerialMillis = millis();

    Serial.print("Smoke Value: ");
    Serial.print(smokeValue);
    Serial.print(" | Fire: ");
    Serial.print(fireDetected ? "DETECTED" : "NOT DETECTED");
    Serial.print(" | Status: ");

    switch (alarmMode) {
      case NORMAL:      Serial.println("SAFE"); break;
      case SMOKE_ALARM: Serial.println("SMOKE DETECTED"); break;
      case FIRE_ALARM:  Serial.println("FIRE DETECTED"); break;
      case BOTH_ALARM:  Serial.println("FIRE + SMOKE DETECTED"); break;
    }
  }

  switch (alarmMode) {
    case NORMAL:
      digitalWrite(BUZZER, LOW);
      digitalWrite(RED_LED, LOW);
      break;

    case SMOKE_ALARM:
      smokeAlarm();
      break;

    case FIRE_ALARM:
      fireAlarm();
      break;

    case BOTH_ALARM:
      bothAlarm();
      break;
  }
}

// Smoke: short beep, short beep, long beep, pause
void smokeAlarm() {
  const unsigned int durations[] = {150, 150, 150, 150, 600, 600};
  const byte states[] = {HIGH, LOW, HIGH, LOW, HIGH, LOW};

  unsigned long now = millis();
  if (now - previousMillis >= durations[currentStep]) {
    previousMillis = now;
    digitalWrite(BUZZER, states[currentStep]);
    digitalWrite(RED_LED, states[currentStep]);

    currentStep = (currentStep + 1) % 6;
  }
}

// Fire: four short beeps, pause
void fireAlarm() {
  const unsigned int durations[] = {150, 150, 150, 150, 150, 150, 150, 150, 600};
  const byte states[] = {HIGH, LOW, HIGH, LOW, HIGH, LOW, HIGH, LOW, LOW};

  unsigned long now = millis();
  if (now - previousMillis >= durations[currentStep]) {
    previousMillis = now;
    digitalWrite(BUZZER, states[currentStep]);
    digitalWrite(RED_LED, states[currentStep]);

    currentStep = (currentStep + 1) % 9;
  }
}

// Fire + smoke: long beep, pause
void bothAlarm() {
  const unsigned int durations[] = {1200, 500};
  const byte states[] = {HIGH, LOW};

  unsigned long now = millis();
  if (now - previousMillis >= durations[currentStep]) {
    previousMillis = now;
    digitalWrite(BUZZER, states[currentStep]);
    digitalWrite(RED_LED, states[currentStep]);

    currentStep = (currentStep + 1) % 2;
  }
}
