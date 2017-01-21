#include "Timer.h"
long totalScore = 0;
int top = 2;
int soso = 1;
int bad = 0;
const int scoreThreshold = 1000; // May not be proper. Fix it later.
Timer timer;
const int soundSensor = 2;

// Special thanks to Rob Faludi who wrote the fantastic code.
void buzz(int targetPin, long frequency, long length) {
  long delayValue = 1000000/frequency/2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length/ 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to 
  //// get the total number of cycles to produce
 for (long i=0; i < numCycles; i++){ // for the calculated length of time...
    digitalWrite(targetPin,HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin,LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait againf or the calculated delay value
  }
}

void doAfter1(){
  Serial.print(totalScore);
  //Will be executed when the sleeping time is up for the first time(10 mins).
  
  if(totalScore > scoreThreshold) {
    //You've slept well enough dude!
    //Raise the buzzer.
    buzz(8, 2500, 3000); // Not sure if the pin is really 8. Just trying out.
  }
}

void doAfter2(){
  //Will be executed when the sleeping time is up for the second time(11 mins).
  //Get up UNCONDITIONALLY. // Raise the buzzer.
  
  buzz(8, 2500, 3000); // Not sure if the pin is really 8. Just trying out.
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(13, OUTPUT);
  pinMode(soundSensor, INPUT);
  digitalWrite(13, LOW);
  totalScore = 0;
  timer.after(600000, doAfter1);
  timer.after(660000, doAfter2);
  // Suppose our client sleeps for only 10min.
}

void loop() {
  // put your main code here, to run repeatedly:
  //digitalWrite(13, LOW);
  //digitalWrite(13, LOW);
  timer.update();
  delay(1000);
  int heardSnoore = digitalRead(soundSensor);
  boolean onTheBack = digitalRead(A0) && digitalRead(A1) && digitalRead(A2) && digitalRead(A3);
  boolean badHori = (digitalRead(A0) && digitalRead(A1)) || (digitalRead(A2) && digitalRead(A3));
  if(onTheBack) {
    totalScore += top;
  }
  else if(badHori){
    totalScore += bad;
  }
  else{
    totalScore += soso;
  }
  if(heardSnoore){
    // Deduct the total score if we hear a snoore.
    //We are snoore nazis.
    totalScore -= 1;
  }
  //Serial.println(totalScore);
  //digitalWrite(13, HIGH);
}
