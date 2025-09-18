int analogPin = 32;
int val = 0;
void setup() {
  Serial.begin(9600);
}

void loop() {
  val = analogRead(analogPin);
  Serial.print("val = "); 
  Serial.println(val); 
  delay(500);
}