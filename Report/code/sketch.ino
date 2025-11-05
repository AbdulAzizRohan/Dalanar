int gas_sensor = 0;
int temp_sensor = 0;
unsigned long previousLogTime = 0;
const unsigned long logInterval = 5000;  // Log every 5 seconds

void setup() {
  pinMode(A0, INPUT);
  pinMode(A2, INPUT);
  Serial.begin(9600);
  pinMode(7, OUTPUT);
  pinMode(4, OUTPUT);

  // Print CSV headers
  Serial.println("Timestamp,Gas_Reading,Temperature,Status");
}

void loop() {
  gas_sensor = analogRead(A0);
  temp_sensor = map(((analogRead(A2)-20)*3.04), 0, 1023, -40, 125);
  
  // Data logging
  unsigned long currentTime = millis();
  if (currentTime - previousLogTime >= logInterval) {
    logData(currentTime);
    previousLogTime = currentTime;
  }

  // Alarm system
  if (gas_sensor >= 400 || temp_sensor >= 30) {
    tone(7, 200005, 100);
    digitalWrite(4, HIGH);
  } else {
    digitalWrite(7, LOW);
    digitalWrite(4, LOW);
  }

  delay(1000);
}

void logData(unsigned long timestamp) {
  Serial.print(timestamp);
  Serial.print(",");
  Serial.print(gas_sensor);
  Serial.print(",");
  Serial.print(temp_sensor);
  Serial.print(",");
  
  if (gas_sensor >= 400 || temp_sensor >= 30) {
    Serial.println("ALERT");
  } else {
    Serial.println("NORMAL");
  }
}
