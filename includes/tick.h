#ifndef TICK_H
#define TICK_H

#include <stdint.h>
#include <stdbool.h>

volatile uint32_t msTicks;

void delay(uint32_t dlyTicks);
void SysTick_Handler(void);

#endif /* TICK_H */
