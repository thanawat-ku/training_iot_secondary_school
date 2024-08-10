int swPin = 26;
int old_value = HIGH;

void setup(){
    pinMode(swPin, INPUT_PULLUP);
    Serial2.begin(9600);
}

void loop(){
    int new_value = digitalRead(swPin);
    if(old_value != new_value){
        if(new_value == LOW){
            Serial2.print("ON");
        }else{
            Serial2.print("OFF");
        }
        old_value = new_value;
    }
    delay(100);
}