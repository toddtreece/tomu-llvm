#ifndef GPIO_H
#define GPIO_H

#include <tomu.h>

#define GPIO_BASE                   (PERIPH_BASE + 0x06000)

#define GPIO_P(i)                   (GPIO_BASE + (0x24 * (i)))
#define GPIO_PA                     GPIO_P(0)
#define GPIO_PB                     GPIO_P(1)

#define GPIO0                       (1 << 0)
#define GPIO7                       (1 << 7)

#define LED_GREEN_PORT              GPIO_PA
#define LED_GREEN_PIN               GPIO0
#define LED_RED_PORT                GPIO_PB
#define LED_RED_PIN                 GPIO7

#define GPIO_P_DOUTCLR(port)        MMIO32((port) + 0x14)
#define GPIO_P_DOUTSET(port)        MMIO32((port) + 0x10)
#define GPIO_P_DOUTTGL(port)        MMIO32((port) + 0x18)

#define GPIO_P_MODEL(port)          MMIO32((port) + 0x04)
#define GPIO_P_MODEH(port)          MMIO32((port) + 0x08)
#define GPIO_P_MODE_MODEx_MASK(x)   (0x0F << (((x) & 0x7) * 4))
#define GPIO_P_MODE_MODEx(x, mode)  (((mode) << (((x) & 0x7) * 4)) & GPIO_P_MODE_MODEx_MASK(x))

enum gpio_mode {
  GPIO_MODE_DISABLE = 0,
  GPIO_MODE_INPUT,
  GPIO_MODE_INPUT_PULL,
  GPIO_MODE_INPUT_PULL_FILTER,
  GPIO_MODE_PUSH_PULL,
  GPIO_MODE_PUSH_PULL_DRIVE,
  GPIO_MODE_WIRED_OR,
  GPIO_MODE_WIRED_OR_PULL_DOWN,
  GPIO_MODE_WIRED_AND,
  GPIO_MODE_WIRED_AND_FILTER,
  GPIO_MODE_WIRED_AND_PULLUP,
  GPIO_MODE_WIRED_AND_PULLUP_FILTER,
  GPIO_MODE_WIRED_AND_DRIVE,
  GPIO_MODE_WIRED_AND_DRIVE_FILTER,
  GPIO_MODE_WIRED_AND_DRIVE_PULLUP,
  GPIO_MODE_WIRED_AND_DRIVE_PULLUP_FILTER
};

void gpio_setup(uint32_t gpio_port, enum gpio_mode mode, uint16_t gpios);

void gpio_set(uint32_t gpio_port, uint16_t gpios);
void gpio_clear(uint32_t gpio_port, uint16_t gpios);
void gpio_toggle(uint32_t gpio_port, uint16_t gpios);

#endif /* GPIO_H */
