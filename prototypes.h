#ifndef PROTOTYPES_H
#define PROTOTYPES_H

void interruptCallback(uint _gpio,  uint32_t _eventMask);
void setupMotionDetector(void);
void setupButtonServo(void);
void setup(void);
void executeButtonPress(void);
void TurnOnAirFreshener(void);
void returnToSteadyState(void);
void TurnDeviceOff(void);

#endif
