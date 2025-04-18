#ifndef MTD_SERVO_H
#define MTD_SERVO_H

#include <stdint.h>
#include <stdbool.h>
#include "hardware/gpio.h"
#include "hardware/pwm.h"

typedef struct {
  uint8_t gpio;
  uint8_t slice;
  uint8_t chan;
  uint32_t speed;
  uint32_t resolution;
  bool on;
  bool invert;
} Servo;

void ServoInit(Servo *s, uint8_t gpio, bool invert);
void ServoOn(Servo *s);
void ServoOff(Servo *s);
void ServoPosition(Servo *s, uint32_t p);
uint32_t pwm_set_freq_duty(uint8_t slice_num, uint8_t chan, uint32_t f, int d);

#endif
