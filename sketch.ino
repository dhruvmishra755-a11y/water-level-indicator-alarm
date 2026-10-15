// Smart Water Tank Monitoring System
// Arduino UNO + HC-SR04 + 4 LEDs + buzzer
// Thresholds are examples; calibrate for your tank.

const int trigPin = 9;
const int echoPin = 10;
const int ledLow = 2;
const int ledMid = 3;
const int ledHigh = 4;
const int ledFull = 5;
const int buzzer = 6;

const int lowLevelDistance = 30;
const int midLevelDistance = 20;
const int fullLevelDistance = 10;

bool tankWasFull = false;
unsigned long lastSensorWarning = 0;

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledLow, OUTPUT);
  pinMode(ledMid, OUTPUT);
  pinMode(ledHigh, OUTPUT);
  pinMode(ledFull, OUTPUT);
  pinMode(buzzer, OUTPUT);
  allIndicatorsOff();

  Serial.println("================================");
  Serial.println("   SMART WATER TANK MONITOR");
  Serial.println("================================");
  Serial.println("System started successfully!");
  Serial.println("Monitoring water level...");
}

void loop() {
  float distance = measureDistance();

  if (distance < 0 || distance > 400) {
    allIndicatorsOff();
    if (millis() - lastSensorWarning >= 2000) {
      Serial.println("WARNING: Sensor reading unavailable!");
      Serial.println("Check sensor and connections.");
      lastSensorWarning = millis();
    }
    delay(200);
    return;
  }

  Serial.print("Distance to water: ");
  Serial.print(distance, 1);
  Serial.println(" cm");

  if (distance > lowLevelDistance) {
    allIndicatorsOff();
    digitalWrite(ledLow, HIGH);
    Serial.println("WATER LEVEL: LOW");
    Serial.println("Status: Water tank needs filling.");
    tankWasFull = false;
  } else if (distance > midLevelDistance) {
    allIndicatorsOff();
    digitalWrite(ledLow, HIGH);
    digitalWrite(ledMid, HIGH);
    Serial.println("WATER LEVEL: MEDIUM");
    Serial.println("Status: Water level is rising.");
    tankWasFull = false;
  } else if (distance > fullLevelDistance) {
    allIndicatorsOff();
    digitalWrite(ledLow, HIGH);
    digitalWrite(ledMid, HIGH);
    digitalWrite(ledHigh, HIGH);
    Serial.println("WATER LEVEL: HIGH");
    Serial.println("Warning: Tank is nearly full!");
    tankWasFull = false;
  } else {
    digitalWrite(ledLow, HIGH);
    digitalWrite(ledMid, HIGH);
    digitalWrite(ledHigh, HIGH);
    digitalWrite(ledFull, HIGH);
    tone(buzzer, 1200);

    if (!tankWasFull) {
      Serial.println();
      Serial.println("********************************");
      Serial.println("          TANK FULL!");
      Serial.println("********************************");
      Serial.println("WARNING: WATER LEVEL MAXIMUM!");
      Serial.println("ACTION: TURN WATER OFF NOW!");
      Serial.println("Prevent water overflow.");
      Serial.println("********************************");
      tankWasFull = true;
    }
  }

  Serial.println("--------------------------------");
  delay(1000);
}

float measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  unsigned long duration = pulseIn(echoPin, HIGH, 30000);
  if (duration == 0) return -1;
  return duration * 0.0343 / 2.0;
}

void allIndicatorsOff() {
  digitalWrite(ledLow, LOW);
  digitalWrite(ledMid, LOW);
  digitalWrite(ledHigh, LOW);
  digitalWrite(ledFull, LOW);
  noTone(buzzer);
}
