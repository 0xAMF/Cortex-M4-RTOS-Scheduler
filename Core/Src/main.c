#include "../Inc/main.h"
#include "../../RTOS/inc/osmcal.h"


int main(void)
{
	sysfaults_enable();

	systick_init(1000);

	sched_stack_init(SCHED_TASK_STACK);

	task_stack_init();

	switch_to_psp();

	task1_handler();

	while (1)
	{
	}
}


void task1_handler(void) {
    while(1);
}

void task2_handler(void) {
    while(1);
}

void task3_handler(void) {
    while(1);
}

void task4_handler(void) {
    while(1);
}
