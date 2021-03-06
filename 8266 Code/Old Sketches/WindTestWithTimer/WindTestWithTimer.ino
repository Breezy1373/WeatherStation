#include <Wire.h>
#include <Ticker.h>
#include <ESP8266WiFi.h>

//Timer
Ticker timer;


//Wind Speed
float radius = 0.105; //metres from center pin to middle of cup
volatile int seconds = 0;
volatile int revolutions = 0; //counted by interrupt
volatile int rps = -1; // read revs per second (5 second interval)
volatile int mps = 0;  //wind speed metre/sec
float mph = 0;
float maxMph = 0;
void ICACHE_RAM_ATTR rps_fan();
void ICACHE_RAM_ATTR onTime();

void setup() {  
  Serial.begin(115200);

  //Initialize Ticker every 0.5s
  timer1_attachInterrupt(onTime); // Add ISR Function
  timer1_enable(TIM_DIV16, TIM_EDGE, TIM_SINGLE);
  /* Dividers:
    TIM_DIV1 = 0,   //80MHz (80 ticks/us - 104857.588 us max)
    TIM_DIV16 = 1,  //5MHz (5 ticks/us - 1677721.4 us max)
    TIM_DIV256 = 3  //312.5Khz (1 tick = 3.2us - 26843542.4 us max)
  Reloads:
    TIM_SINGLE  0 //on interrupt routine you need to write a new value to start the timer again
    TIM_LOOP  1 //on interrupt the counter will start with the same value again
  */
  
  // Arm the Timer for our 5s Interval
  timer1_write(5000000); // 5000000 / 1 second - 5 ticks per us from TIM_DIV16 == 500,000 us interval 


  //Anemometer  
  pinMode(14, INPUT);  //D1
  attachInterrupt(digitalPinToInterrupt(14), rps_fan, CHANGE);  
  
}  
  
  
// executed every time the interrupt 0 (pin2) gets low, ie one rev of cups.
void rps_fan() {
  revolutions++;
  Serial.print(revolutions);
}//end of interrupt routine

// ISR to Fire when Timer is triggered
void onTime() {
  seconds++;
  if (seconds == 5) { //make 5 for each output
    seconds = 0;
    rps = revolutions;
    revolutions = 0;
  }
  // Re-Arm the timer as using TIM_SINGLE
  timer1_write(5000000);//12us
}


void loop() {  
  if (rps != -1) { //Update every 5 seconds, this will be equal to reading frequency (Hz)x5.
    mph = rps * 3.1414 * 2 * radius * 12 * 60 / 1604;
  }

  // Record Max wind speed
  if (mph > maxMph) {
    maxMph = mph;    
  }
  
  Serial.print("Wind Speed: ");
  Serial.print(mph);
  Serial.print("mph");
  Serial.print('\n');
  
  Serial.print("Max Wind Speed: ");
  Serial.print(maxMph);
  Serial.print("mph");
  Serial.print('\n');
  
  delay(5000);
}
