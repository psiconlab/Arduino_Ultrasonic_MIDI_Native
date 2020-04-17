#include <NewPing.h>

#define TRIGGER_PIN 12
#define ECHO_PIN 11

int index = 0;
int total = 0;
int average = 0;
int readings[] ={0,0,0,0,0,0,0,0,0,0};
int numReadings = 10;

int lastUltraMIDIValue = 0;
int averagedCurrentUltraMIDIValue;

int distInCm;
int difference;

#define MAX_DISTANCE 50 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define MAX_RESPONSE 64  //64 is halfway to prevent huge jumps
#define MIN_RESPONSE 2  //to prevent wobbles

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance...

void loop_ultrasonic()
{
  //ULTRASONIC
  unsigned int aPing = sonar.ping(); // Send ping, get ping time in microseconds (aPing).
  distInCm = aPing / US_ROUNDTRIP_CM;
  
  int currentUltraMIDIValue = map(distInCm, MIN_RESPONSE, MAX_DISTANCE, 0, 127);
  currentUltraMIDIValue = constrain(currentUltraMIDIValue, 0, 127);

  //interpolate
  total = total - readings[index];
  readings[index] = currentUltraMIDIValue;
  total = total + readings[index]; 
  index = index + 1;
  if (index >= numReadings)
  {
    index = 0;           
  }
  average = total / numReadings;
  averagedCurrentUltraMIDIValue = average;// * 127;
  
  difference = abs(lastUltraMIDIValue - currentUltraMIDIValue);

  if ( averagedCurrentUltraMIDIValue != lastUltraMIDIValue  && difference < MAX_RESPONSE && difference > MIN_RESPONSE ) 
  {
    velocity = averagedCurrentUltraMIDIValue; //THIS VARIABLE IS ACCESSED BY THE MAIN SCRIPT
    
    lastUltraMIDIValue = averagedCurrentUltraMIDIValue;
  }

  delay(20); // delay in between reads for stability with ultrasonic
}

