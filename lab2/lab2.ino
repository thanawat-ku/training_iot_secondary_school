int ledPin = 7;
void setup(){
    pinMode(ledPin, OUTPUT);
    Serial.begin(115200);
}

void loop(){
    digitalWrite(ledPin, HIGH);
          Serial.println("LED On");
    delay(1000);    
    digitalWrite(ledPin, LOW); 
          Serial.println("LED Off");
    delay(1000);    
}
