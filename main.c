#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"

#define MOTION_SENSOR_PIN 0
#define SERVO_PIN 1

bool MotionDetected = false;


void interruptCallback(uint _gpio,  uint32_t _eventMask) {
  if(_gpio == MOTION_SENSOR_PIN) {
    MotionDetected = true;
  }
}

void setup() {
  /* Setup motion sensor settings */
  gpio_init(MOTION_SENSOR_PIN);
  gpio_set_irq_enabled(MOTION_SENSOR_PIN, GPIO_IRQ_EDGE_RISE, true);
  gpio_set_irq_callback(interruptCallback);
  irq_set_enabled(IO_IRQ_BANK0, true);

  /* setup servo that will toggle buttons of device */

}

void executeButtonPress() {
  // Do something
  MotionDetected = false;
}

int main() {
  setup();
  while(true) {
   if(MotionDetected) {
     executeButtonPress();
   }
   sleep_ms(1000);
  }
  return 0;
}



