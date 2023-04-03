#include <Arduino.h>
#include <AccelStepper.h>

AccelStepper lWrist(1, 3, 2); 
AccelStepper rWrist(1, 5, 4);

String serialData;

void setup()
{  
  Serial.begin(9600);

  // Change these to suit your stepper if you want
  lWrist.setMaxSpeed(450);
  lWrist.setAcceleration(35);
  lWrist.moveTo(300);

  rWrist.setMaxSpeed(450);
  rWrist.setAcceleration(35);
  rWrist.moveTo(300);
}

void loop()
{
  if (lWrist.distanceToGo() != 0)
    lWrist.run();

  if (rWrist.distanceToGo() != 0)
    rWrist.run();
}

void serialEvent() {
  serialData = Serial.readString();

  int lPos = parseL(serialData);
  int rPos = parseR(serialData);

  lWrist.moveTo(lPos);
  rWrist.moveTo(rPos);
}

/*
  * Disclaimer to any sane person
  * for some weird reason, the C++ language's
  * String.remove method removes all characters past 
  * the start index or the characters between the start and 
  * end indicies so if you have a hard time wrapping your 
  * head around this, I did too 
*/

int parseL(String data) {
  data.remove(data.indexOf("R"));
  data.remove(data.indexOf("L"), 1);
  return data.toInt();
}

int parseR(String data) {
  data.remove(0, data.indexOf("R") + 1);
  return data.toInt();
}
