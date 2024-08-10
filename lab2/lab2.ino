int ledPin = 5;
int swPin = 26;

void setup(){
    pinMode(ledPin, OUTPUT);
    pinMode(swPin, INPUT_PULLUP);
}

void loop(){
    if(digitalRead(swPin) == LOW){
        digitalWrite(ledPin, HIGH);
    }else{
        digitalWrite(ledPin, LOW);
    }
    delay(200);
}