const int analogPin = A0;
const int minVolt = 22;
const int R_tot = 7000000;

void setup(){
  Serial.begin(9600);
}

void loop(){
  int voltageread = analogRead(analogPin);
  float voltage = voltageread * (5/1024.0);
  Serial.println(voltage);

  float current = voltage/R_tot;
  Serial.println(current);

 
    delay(1000);
}
