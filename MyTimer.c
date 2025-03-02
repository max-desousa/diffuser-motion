#include "MyTimer.h"

uint32_t myTimer;

void SetTimer(uint32_t _millis) {
  myTimer = _millis;
}

bool DecrementTimer(uint32_t _ellapsedMillis) {
  bool returnValue = false;

  if (0 != myTimer) {

    if (_ellapsedMillis >= myTimer) {
      myTimer = 0;
      returnValue = true;
    }
    else {
      myTimer -= _ellapsedMillis;
    }
  }
  
  return returnValue;
}
