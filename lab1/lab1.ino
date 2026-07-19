int i = 1;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(3000);
  Serial.println("Hello, Raspberry Pi Pico!");
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("Count: ");  
  Serial.println(i++);
  delay(1000); // this speeds up the simulation
}
