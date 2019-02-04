#include <tomu.h>
#include <gpio.h>
#include <tick.h>

extern unsigned int __etext, __data_start__, __data_end__, __bss_start__, __bss_end__, __stack;
volatile uint32_t msTicks = 0;

int main(void)
{
  // disable watchdog
  WDOG_CTRL = 0;

  // enable GPIO peripheral clock
  _CMU_REG(CMU_GPIO) |= _CMU_BIT(CMU_GPIO);

  gpio_setup(LED_RED_PORT, GPIO_MODE_WIRED_AND, LED_RED_PIN);
  gpio_setup(LED_GREEN_PORT, GPIO_MODE_WIRED_AND, LED_GREEN_PIN);

  gpio_set(LED_RED_PORT, LED_RED_PIN);
  gpio_set(LED_GREEN_PORT, LED_GREEN_PIN);

  // set systick clock source to STK_CSR_CLKSOURCE_AHB
  STK_CSR = (STK_CSR & ~STK_CSR_CLKSOURCE) | (STK_CSR_CLKSOURCE_AHB & STK_CSR_CLKSOURCE);

  // set systick automatic reload value
  STK_RVR = (23999 & STK_RVR_RELOAD);

  // enable systick counter
  STK_CSR |= STK_CSR_ENABLE;

  // enable systick interrupt
  STK_CSR |= STK_CSR_TICKINT;

  while(1) {
    delay(1000);
    gpio_toggle(LED_RED_PORT, LED_RED_PIN);
    gpio_toggle(LED_GREEN_PORT, LED_GREEN_PIN);
  }
}

_Noreturn void Reset_Handler(void)
{
  unsigned int *src = &__etext;
  unsigned int *dst = &__data_start__;

  while (dst < &__data_end__)
    *dst++ = *src++;

  for (dst = &__bss_start__; dst < &__bss_end__; dst++)
    *dst = 0;

  main();

  while (1)
    __asm__ volatile ("WFI");
}

_Noreturn void Default_Handler(void)
{
  while (1);
}

__attribute__((section(".isr_vector"),used)) static void *vectors[] = {
  (void *)&__stack,
  (void *)&Reset_Handler,      // Reset Handler
  (void *)&Default_Handler,    // NMI Handler
  (void *)&Default_Handler,    // Hard Fault Handler
  (void *)&Default_Handler,    // MPU Fault Handler
  (void *)&Default_Handler,    // Bus Fault Handler
  (void *)&Default_Handler,    // Usage Fault Handler
  0,                           // Reserved
  0,                           // Reserved
  0,                           // Reserved
  0,                           // Reserved
  (void *)&Default_Handler,    // SVCall Handler
  (void *)&Default_Handler,    // Debug Monitor Handler
  0,                           // Reserved
  (void *)&Default_Handler,    // PendSV Handler
  (void *)&SysTick_Handler,    // SysTick Handler
};
