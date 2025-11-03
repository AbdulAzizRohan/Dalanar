int gas_sensor = 0;
int temp_sensor = 0;

void setup() {
  pinMode(A0, INPUT);
  pinMode(A2, INPUT);
  Serial.begin(9600);
  pinMode(7, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop() {
  gas_sensor = analogRead(A0);
  temp_sensor = map(((analogRead(A2)-20)*3.04), 0, 1023, -40, 125);
  
  Serial.print("Gas Index : ");
  Serial.println(gas_sensor);
  Serial.print("Temperature : ");
  Serial.println(temp_sensor);
  
  if (gas_sensor >= 400 || temp_sensor >= 30) {
    tone(7, 200005, 100);
    digitalWrite(4, HIGH);
  } else {
    digitalWrite(7, LOW);
    digitalWrite(4, LOW);
  }
}
