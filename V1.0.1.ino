#include "Timer.h"

long totalScore = 0;
int top = 2;       //on back
int soso = 1;      // on side
int bad = 0;       // horizontal

const int scoreThreshold = 0; // May not be proper. Fix it later. !FIX

Timer timer;

const int soundSensor = 2;     //pin for sound Sensor

int previous = 0;                     //turn count iterators -- previous, current, turnCount
int current = 0;                      // 0, 1, or 2 
int turnCount = 0;

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
  
  //Will be executed when the sleeping time is up for the first time(10 mins).
  //Serial.print("After1 is alright!");
  
  Serial.println(totalScore); // Send the data to the serial port.
  
  Serial.println(turnCount);
  
  if(totalScore > scoreThreshold) {
    //You've slept well enough dude!
    //Raise the buzzer.
    buzz(8, 2500, 3000); 
    
  }
  
}

void doAfter2(){
  
  //Will be executed when the sleeping time is up for the second time(11 mins).
  //Get up UNCONDITIONALLY. // Raise the buzzer.
  //Serial.print("After2 is alright!");
  
  buzz(8, 2500, 3000); 
  
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
  timer.after(8000, doAfter1);
  timer.after(20000, doAfter2);
  // Suppose our client sleeps for only 10min.
}

void loop() {
  // put your main code here, to run repeatedly:
  //digitalWrite(13, LOW);
  //digitalWrite(13, LOW);
  timer.update();
  
  delay(1000);
  
  int heardSnore = digitalRead(soundSensor);
  
  boolean onTheBack = digitalRead(A0) && digitalRead(A1) && digitalRead(A2) && digitalRead(A3);
  
  boolean badHori = (digitalRead(A0) && digitalRead(A1) && !digitalRead(A2) && !digitalRead(A3)) || 
                    (digitalRead(A2) && digitalRead(A3) && !digitalRead(A0) && !digitalRead(A1));
                    
  boolean sidePos = (digitalRead(A0) && digitalRead(A2)) || (digitalRead(A1) && digitalRead(A3)) || 
                    (digitalRead(A0) && digitalRead(A3)) || (digitalRead(A1) && digitalRead(A2));
  
  previous = current;
  
  if(onTheBack) {
    
    totalScore += top;
    current = 2;
    
  }
  else if(badHori){
    
    totalScore += bad;
    current = 0;
    
  }
  else if(sidePos){
    
    totalScore += soso;
    current = 1;
    
  }
  
  if(heardSnore){
    // Deduct the total score if we hear a snoore.
    //We are snore nazis.
    totalScore -= 1;
  }
  
  //Serial.println(totalScore);
  //digitalWrite(13, HIGH);
  
  if(current != previous) {
    turnCount += 1;
  }
}
