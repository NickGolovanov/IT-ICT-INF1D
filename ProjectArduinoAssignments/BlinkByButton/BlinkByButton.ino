int ledRed = 9;
int ledGreen = 10;
int ledOrange = 11;
int ButtonPin = 6;

void setup(){
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledOrange, OUTPUT);
  pinMode(ButtonPin, INPUT);
}

void loop() {
  if(digitalRead(ButtonPin) == LOW){
      digitalWrite(ledRed, LOW);
      delay(3000);
      digitalWrite(ledRed, HIGH);
      delay(500);
    
      digitalWrite(ledOrange, LOW);
      delay(4000);
      digitalWrite(ledOrange, HIGH);
      delay(500);
    
      digitalWrite(ledGreen, LOW);
      delay(1000);
      digitalWrite(ledGreen, HIGH);
      delay(500); 
  }
}
