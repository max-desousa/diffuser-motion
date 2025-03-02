#ifndef MYTIMER_H
#define MYTIMER_H

#include <stdint.h>
#include <stdbool.h>

void SetTimer(uint32_t _millis);
bool DecrementTimer(uint32_t _ellapsedMillis);

#endif
