#include <gpio.h>

void gpio_setup(uint32_t gpio_port, enum gpio_mode mode, uint16_t gpios)
{
  unsigned i;

  uint32_t high = GPIO_P_MODEH(gpio_port);
  uint32_t low = GPIO_P_MODEL(gpio_port);

  for (i = 0; i < 8; i++) {
    if (gpios & (1 << i)) {
      low &= ~GPIO_P_MODE_MODEx_MASK(i);
      low |= GPIO_P_MODE_MODEx(i, mode);
    }

    if (gpios & (1 << (i + 8))) {
      high &= ~GPIO_P_MODE_MODEx_MASK(i);
      high |= GPIO_P_MODE_MODEx(i, mode);
    }
  }

  GPIO_P_MODEL(gpio_port) = low;
  GPIO_P_MODEH(gpio_port) = high;
}

void gpio_set(uint32_t gpio_port, uint16_t gpios)
{
  GPIO_P_DOUTSET(gpio_port) = gpios;
}

void gpio_clear(uint32_t gpio_port, uint16_t gpios)
{
  GPIO_P_DOUTCLR(gpio_port) = gpios;
}

void gpio_toggle(uint32_t gpio_port, uint16_t gpios)
{
  GPIO_P_DOUTTGL(gpio_port) = gpios;
}
