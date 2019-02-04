#ifndef TOMU_H
#define TOMU_H

#include <stdint.h>
#include <stdbool.h>

#define MMIO32(addr)                (*(volatile uint32_t *)(addr))

#define PERIPH_BASE                 (0x40000000U)
#define WDOG_BASE                   (PERIPH_BASE + 0x88000)
#define CMU_BASE                    (PERIPH_BASE + 0xC8000)

#define WDOG_CTRL                   MMIO32(WDOG_BASE + 0x000)
#define _REG_BIT(base, bit)         (((base) << 5) + (bit))

#define _CMU_REG(i)                 MMIO32(CMU_BASE + ((i) >> 5))
#define _CMU_BIT(i)                 (1 << ((i) & 0x1f))
#define CMU_GPIO                    _REG_BIT(0x044, 8)

#define PPBI_BASE                   (0xE0000000U)
#define SCS_BASE                    (PPBI_BASE + 0xE000)
#define STK_CSR_CLKSOURCE_LSB       2
#define STK_CSR_CLKSOURCE           (1 << STK_CSR_CLKSOURCE_LSB)
#define STK_CSR_CLKSOURCE_AHB       (1 << STK_CSR_CLKSOURCE_LSB)
#define SYS_TICK_BASE               (SCS_BASE + 0x0010)
#define STK_CSR                     MMIO32(SYS_TICK_BASE + 0x00)
#define STK_CSR_TICKINT             (1 << 1)
#define STK_CSR_ENABLE              (1 << 0)
#define STK_RVR                     MMIO32(SYS_TICK_BASE + 0x04)
#define STK_RVR_RELOAD              0x00FFFFFF

#endif /* TOMU_H */
