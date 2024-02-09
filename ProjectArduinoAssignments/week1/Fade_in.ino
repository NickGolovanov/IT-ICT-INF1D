
int ledRed = 11; 
int bright = 0;

void setup() {
  pinMode(ledRed, OUTPUT);
}

void loop() {
  for (bright = 0; bright <=255; bright += 5){
    analogWrite(ledRed, bright); 
    delay(30);
  }

}
