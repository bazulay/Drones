#include "Drone.h"
Drone drone(6, 9);
Drone* droneRef = &drone;
void setup() {
  droneRef->SetUpTempSensor()->SetUpColorSensor()->SetUpBuzzer(13);
  Serial.begin(9600);
}

void loop() {
  drone.PollMessage();
}
