#include "servo.h"

/*******************************************************************************
 *
 ******************************************************************************/
void ServoInit(Servo *s, uint8_t gpio, bool invert) {
  gpio_set_function(gpio, GPIO_FUNC_PWM);
  s->gpio = gpio;
  s->slice = pwm_gpio_to_slice_num(gpio);
  s->chan = pwm_gpio_to_channel(gpio);
  pwm_set_enabled(s->slice, false);
  s->on = false;
  s->speed = 0;
  s->resolution = pwm_set_freq_duty(s->slice,
                                s->chan, 50, 0);
  pwm_set_duty(s->slice, s->chan, 250);
  if (s->chan) {
    pwm_set_output_polarity(s->slice, false, invert);
  }
  else {
    pwm_set_output_polarity(s->slice, invert, false);
  }
  s->invert = invert;
}

/*******************************************************************************
 *
 ******************************************************************************/
void ServoOn(Servo *s) {
  pwm_set_enabled(s->slice, true);
  s->on = true;
}

/*******************************************************************************
 *
 ******************************************************************************/
void ServoOff(Servo *s) {
  pwm_set_enabled(s->slice, false);
  s->on = false;
}

/*******************************************************************************
 *
 ******************************************************************************/
void ServoPosition(Servo *s, uint32_t p) {
  pwm_set_dutyH(s->slice, s->chan, p*10+250);
}

uint32_t pwm_set_freq_duty(uint8_t slice_num, uint8_t chan, uint32_t f, int d) {
  uint32_t clock = 125000000;
  uint32_t divider16 = clock / f / 4096 + (clock % (f * 4096) != 0);
  if (divider16 / 16 == 0) {
    divider16 = 16;
  }
  uint32_t wrap = clock * 16 / divider16 / f - 1;
  pwm_set_clkdiv_int_frac(slice_num, divider16/16, divider16 & 0xF);
  pwm_set_wrap(slice_num, wrap);
  pwm_set_chan_level(slice_num, chan, wrap * d / 100);
  return wrap;
}
