#ifndef MTD_SERVO_H
#define MTD_SERVO_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
  uint gpio;
  uint slice;
  uint chan;
  uint speed;
  uint resolution;
  bool on;
  bool invert;
} Servo;

void ServoInit(Servo *s, uint gpio, bool invert);
void ServoOn(Servo *s);
void ServoOff(Servo *s);
void ServoPosition(Servo *s,uint p);
uint32_t pwm_set_freq_duty(uint slice_num, uint chan,uint32_t f, int d);

#endif
