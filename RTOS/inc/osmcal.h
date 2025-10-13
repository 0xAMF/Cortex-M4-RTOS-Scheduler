#ifndef SYSTICK_H
#define SYSTICK_H

#include <stdint.h>
#include "osmcal_conf.h"

#define DUMMY_XPSR 0x01000000
#define DUMMY_LR   0xFFFFFFFD

void systick_init(uint32_t tickHz);
__attribute__((naked)) void sched_stack_init(uint32_t stacktop);
void task_stack_init(void);
void sysfaults_enable(void);
__attribute__((naked))void switch_to_psp(void);

#endif
