#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "hardware/pwm.h"
#include "prototypes.h"
#include "MyTimer.h"
#include "servo.h"

#define MOTION_SENSOR_PIN 16
#define SERVO_PIN 15
#define STEADY_STATE_PWM 0
#define BUTTON_PRESS_PWM 255
//#define DEVICE_ON_DURATION 300000
#define DEVICE_ON_DURATION 30000
#define INTERVAL_DURATION 1000

/* Start Global Variable Declarations */
bool MotionDetected = false;
uint8_t slice_number;
bool DeviceOn = false;
extern uint32_t myTimer;
Servo ButtonServo;
/* End Global Variable Declarations */

void interruptCallback(uint _gpio,  uint32_t _eventMask) {
  if(_gpio == MOTION_SENSOR_PIN) {
    MotionDetected = true;
  }
}

void setupMotionDetector() {
  /* Setup motion sensor settings */
  gpio_init(MOTION_SENSOR_PIN);
  gpio_pull_up(MOTION_SENSOR_PIN);
  gpio_set_irq_enabled(MOTION_SENSOR_PIN, GPIO_IRQ_EDGE_FALL, true);
  gpio_set_irq_callback(interruptCallback);
  irq_set_enabled(IO_IRQ_BANK0, true);
}

void setupButtonServo() {
  /* setup servo that will toggle buttons of device */
  ServoInit(&ButtonServo, SERVO_PIN, false);
}

void setup() {
  stdio_init_all();
  sleep_ms(5000);
  
  printf("Starting Setup Procedure...\n");

  setupMotionDetector();
  setupButtonServo();
  
  printf("Setup Procedure Finished...\n");
}

/*******************************************************************************
 * Function: executeButtonPress
 *
 * Description: Function to handle the pwm's of getting the servo to press the
 * button on the air freshner device. (added sleeps to allow for time for servo
 * to move - may need to calibrate the timing for this to work)
 ******************************************************************************/
void executeButtonPress() {
  printf("Button was pressed\n");
  pwm_set_chan_level(slice_number, PWM_CHAN_B, BUTTON_PRESS_PWM);
  sleep_ms(1000);
}


/*******************************************************************************
 * Function: TurnOnAirFreshener
 *
 * Description: Function to execute enough button presses to turn the device on.
 * (This call will turn my particular device on to the persistent mode)
 ******************************************************************************/
void TurnOnAirFreshener() {
  printf("Turning Device On...\n");
  SetTimer(DEVICE_ON_DURATION);
  executeButtonPress();
  returnToSteadyState();
  MotionDetected = false;
}

/*******************************************************************************
 * Function: ReturnToSteadyState
 *
 * Description: Return the servo to a state where it is certain to not press a 
 * button on the device. 
 ******************************************************************************/
void returnToSteadyState() {
  pwm_set_chan_level(slice_number, PWM_CHAN_B, STEADY_STATE_PWM);
  sleep_ms(1000);
}

/*******************************************************************************
 * Function: TurnDeviceOff
 *
 * Description: Function to execute enough button presses to turn the device off
 * after having been turned on b motion detection.
 ******************************************************************************/
void TurnDeviceOff() {
  printf("Turning Device Off...\n");
  executeButtonPress();
  returnToSteadyState();
}


int main() {
  setup();
  while(true) {
    printf("Starting a new loop...\n");
    uint8_t randomVal = (rand() % 180);
    slice_number = pwm_gpio_to_slice_num(SERVO_PIN);
    printf("\tSlice number is: %d\n", slice_number);
    printf("\trandomVal is: %d\n", randomVal);
    pwm_set_chan_level(slice_number, PWM_CHAN_B, randomVal);
    sleep_ms(5000);
  }
  return 0;
}
