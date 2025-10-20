#include  "../../RTOS/inc/osmcal.h"
#include  "../../RTOS/inc/osmcal_conf.h"
#include "../../Core/Inc/main.h"
#include <stdint.h>

uint32_t task_psp[MAX_TASKS] = {T1_STACK_START, T2_STACK_START, T3_STACK_START, T4_STACK_START};
uint32_t current_task = 0;

void systick_init(uint32_t tickHz) {
    // calculate reload value --> sysclk / reload value
    uint32_t reload = (SystemCoreClock / tickHz) - 1; // decrement by one to take multishot in consideration

    SysTick->LOAD = reload;

    // enable systick exception
    SysTick->CTRL |= (1 << 1);
    // enable clk source
    SysTick->CTRL |= (1 << 2);
    // enable systick
    SysTick->CTRL |= (1 << 0);
}

__attribute__ ((naked)) void sched_stack_init(uint32_t stacktop) {
	// move the argument of the function 'stacktop' to the MSP stack pointer through Regsiter R0
	__asm volatile("MSR MSP, R0");
	// we can also access the argument like so:__asm volatile("MSR MSP, %0"::"r"(stacktop));
	__asm volatile("BX LR");
}


void task_stack_init(void) {
    uint32_t task_handler[MAX_TASKS] = {
		(uint32_t)&task1_handler,
		(uint32_t)&task2_handler,
		(uint32_t)&task3_handler,
		(uint32_t)&task4_handler
    };

    uint32_t *local_taskpsp;

    for (int i = 0; i < MAX_TASKS; i++) {
	local_taskpsp = (uint32_t *)task_psp[i];
	local_taskpsp--; // point to the end of the stack and the beginning of the stacked registers (XPSR register)
	*local_taskpsp = 0x01000000;

	local_taskpsp--; // point to the next regsiter in the stack, which is the PC
	*local_taskpsp = task_handler[i];

	local_taskpsp--; // point to LR
	*local_taskpsp = 0xFFFFFFFD;
	
	// initialize 14 GPRs with zeros
	for (int i = 0; i < 13; i++) {
	    local_taskpsp--;
	    *local_taskpsp = 0x0;
	}

	// update the actual PSP
	task_psp[i] = (uint32_t)local_taskpsp;
    }
}


void sysfaults_enable(void) {
    // enable memfault, Bus fault, and usage faults
	SCB->SHCSR |= (SCB_SHCSR_MEMFAULTENA_Msk);
    SCB->SHCSR |= (SCB_SHCSR_BUSFAULTENA_Msk);
    SCB->SHCSR |= (SCB_SHCSR_USGFAULTENA_Msk);
}

static uint32_t get_current_psp(void) {
    // the return value is by default stored in R0
    return task_psp[current_task];
}

static void save_psp(uint32_t current_psp) {
	task_psp[current_task] = current_psp;
}

static void update_next_task(void) {
	current_task++;
	current_task %= MAX_TASKS;
}

// switching from MSP to PSP when calling a task (MSP is used by default)
__attribute__((naked)) void switch_to_psp(void) {
	// push LR to stack to preserve the value of the caller function before calling get_current_psp
	__asm volatile("PUSH {LR}");
    // initialize PSP with the task stack
    // branch and link to the get_current_psp function
    __asm volatile("BL get_current_psp");
    __asm volatile("MSR PSP, R0");
    // POP the value of the address of the main function to go back into the LR register
    __asm volatile("POP {LR}");
    // switch to PSP pointer using CONTROL register
    __asm volatile("MOV R0, #0x02"); // 0x00000010
    __asm volatile("MSR CONTROL, R0");
    // go back to the caller
    __asm volatile("BX LR");
}

__attribute__((naked)) void SysTick_Handler(void) {
	// save context of the current task
	// 1. get current value of PSP
	__asm volatile("MRS R0, PSP");
	// 2. using the PSP value we store SF2 (R4-->R11)
	// we can't use PUSH instruction because inside handlers we use MSP not PSP
	__asm volatile("STMDB R0!, {R4-R11}");   // store memory and decrement (similar to PUSH), final address value is stored in R0
	// 3. save current value of PSP
	__asm volatile("PUSH {LR}");
	__asm volatile("BL save_psp");

	// retrieve context of the next task
	// 1. decide which is the next task to run
	__asm volatile("BL update_next_task");
	// 2. get its PSP value
    __asm volatile("BL get_current_psp");
    __asm volatile("POP {LR}");
	// 3. retrieve SF2 (R4-->R11) using PSP value and store them in the processor registers
    __asm volatile("LDMIA R0!, {R4-R11}"); // load values from R0 (which is the value of the PSP that points to R4 of the next task)
    // +--> then increment (simulate POP instruction) and store in the processor registers (from R4 to R11)
    // update PSP value
    __asm volatile("MSR PSP, R0");
    // exit
    __asm volatile("BX LR");
}
