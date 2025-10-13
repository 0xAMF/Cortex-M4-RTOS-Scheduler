#ifndef STM32F411CE_H
#define STM32F411CE_H

#include <stdint.h>

/* Base addresses for peripheral buses */
#define PERIPH_BASE           ((uint32_t)0x40000000)
#define APB1PERIPH_BASE       PERIPH_BASE
#define APB2PERIPH_BASE       (PERIPH_BASE + 0x00010000)
#define AHB1PERIPH_BASE       (PERIPH_BASE + 0x00020000)
#define AHB2PERIPH_BASE       (PERIPH_BASE + 0x10000000)

/* AHB1 Peripherals */
#define GPIOA_BASE            (AHB1PERIPH_BASE + 0x0000)
#define GPIOB_BASE            (AHB1PERIPH_BASE + 0x0400)
#define GPIOC_BASE            (AHB1PERIPH_BASE + 0x0800)
#define GPIOD_BASE            (AHB1PERIPH_BASE + 0x0C00)
#define GPIOE_BASE            (AHB1PERIPH_BASE + 0x1000)
#define RCC_BASE              (AHB1PERIPH_BASE + 0x3800)

/* APB1 Peripherals */
#define TIM2_BASE             (APB1PERIPH_BASE + 0x0000)
#define USART2_BASE           (APB1PERIPH_BASE + 0x4400)

/* APB2 Peripherals */
#define USART1_BASE           (APB2PERIPH_BASE + 0x1000)
#define SYSCFG_BASE           (APB2PERIPH_BASE + 0x3800)
#define EXTI_BASE             (APB2PERIPH_BASE + 0x3C00)

/* System Control Space (SCS) */
#define SCS_BASE              (0xE000E000UL)
#define SYSTICK_BASE          (SCS_BASE + 0x0010UL)
#define SCB_BASE              (SCS_BASE + 0x0D00UL)  // Base address of SCB

/* Fault bit masks */
#define MEMFAULTENA_MASK      (1U << 16)
#define BUSFAULTENA_MASK      (1U << 17)
#define USGFAULTENA_MASK      (1U << 18)

/* Peripheral register structures */
typedef struct {
    volatile uint32_t MODER;
    volatile uint32_t OTYPER;
    volatile uint32_t OSPEEDR;
    volatile uint32_t PUPDR;
    volatile uint32_t IDR;
    volatile uint32_t ODR;
    volatile uint32_t BSRR;
    volatile uint32_t LCKR;
    volatile uint32_t AFR[2];
} GPIO_t;

typedef struct {
    volatile uint32_t CR;
    volatile uint32_t PLLCFGR;
    volatile uint32_t CFGR;
    volatile uint32_t CIR;
    volatile uint32_t AHB1RSTR;
    // ... (other RCC registers)
} RCC_t;

typedef struct {
    volatile uint32_t CTRL;
    volatile uint32_t LOAD;
    volatile uint32_t VAL;
    volatile uint32_t CALIB;
} SysTick_t;


/* System Control Block (SCB) structure definition */
typedef struct
{
  volatile const  uint32_t CPUID;           /*!< Offset: 0x000 (R/ )  CPUID Base Register */
  volatile uint32_t ICSR;                   /*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
  volatile uint32_t VTOR;                   /*!< Offset: 0x008 (R/W)  Vector Table Offset Register */
  volatile uint32_t AIRCR;                  /*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
  volatile uint32_t SCR;                    /*!< Offset: 0x010 (R/W)  System Control Register */
  volatile uint32_t CCR;                    /*!< Offset: 0x014 (R/W)  Configuration Control Register */
  volatile uint8_t  SHP[12U];               /*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  volatile uint32_t SHCSR;                  /*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
  volatile uint32_t CFSR;                   /*!< Offset: 0x028 (R/W)  Configurable Fault Status Register */
  volatile uint32_t HFSR;                   /*!< Offset: 0x02C (R/W)  HardFault Status Register */
  volatile uint32_t DFSR;                   /*!< Offset: 0x030 (R/W)  Debug Fault Status Register */
  volatile uint32_t MMFAR;                  /*!< Offset: 0x034 (R/W)  MemManage Fault Address Register */
  volatile uint32_t BFAR;                   /*!< Offset: 0x038 (R/W)  BusFault Address Register */
  volatile uint32_t AFSR;                   /*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register */
} SCB_t;

/* Peripheral declarations */
#define GPIOA               ((GPIO_t *) GPIOA_BASE)
#define GPIOB               ((GPIO_t *) GPIOB_BASE)
#define GPIOC               ((GPIO_t *) GPIOC_BASE)
#define RCC                 ((RCC_t  *) RCC_BASE)
#define SysTick             ((SysTick_t *) SYSTICK_BASE)
#define SCnSCB_ACTLR        (*(volatile uint32_t *)0xE000E008UL)
#define SCB                 ((SCB_t *)SCB_BASE)


#endif /* STM32F411CE_H */
