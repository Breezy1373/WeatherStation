#include <Wire.h>

//Wind Speed
float radius = 0.105; //metres from center pin to middle of cup
volatile int seconds = 0;
volatile int revolutions = 0; //counted by interrupt
volatile int rps = -1; // read revs per second (5 second interval)
volatile int mps = 0;  //wind speed metre/sec
float mph = 0;
void ICACHE_RAM_ATTR rps_fan();

void setup() {  
  Serial.begin(115200);
  pinMode(14, INPUT);
  //Anemometer
  attachInterrupt(digitalPinToInterrupt(14), rps_fan, CHANGE);  
  
}  
  
  
// executed every time the interrupt 0 (pin2) gets low, ie one rev of cups.
void rps_fan() {
  rps++;
}//end of interrupt routine


void loop() {  
  if (rps != -1) { //Update every 5 seconds, this will be equal to reading frequency (Hz)x5.
    mph = rps * 3.1414 * 2 * radius * 12 * 60 / 1604;
  }
  Serial.print("Wind Speed: ");
  Serial.print(mph);
  Serial.print("mph");
  Serial.print('\n');
  delay(2000);
}
