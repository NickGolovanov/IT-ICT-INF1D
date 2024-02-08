int ledRed = 9;
int ledOrange = 10;
int ledGreen = 11;

void setup() {
 pinMode(ledRed, OUTPUT);
 pinMode(ledOrange, OUTPUT);
 pinMode(ledGreen, OUTPUT);
}

void loop() {
  // Red light for 3 seconds
  digitalWrite(ledRed, LOW);  
  delay(3000);                  
  digitalWrite(ledRed, HIGH); 
  delay(500);  

  // Green light for 4 seconds
  digitalWrite(ledGreen, LOW); 
  delay(4000);                  
  digitalWrite(ledGreen, HIGH); 
  delay(500);

  // Orange light for 1 second
  digitalWrite(ledOrange, LOW); 
  delay(1000);                   
  digitalWrite(ledOrange, HIGH); 
  delay(500);
}
