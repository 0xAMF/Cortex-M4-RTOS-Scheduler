#include "../Inc/main.h"

#define DELAY_COUNT_1MS    (1250U)
#define DELAY_COUNT_500MS  (500U * DELAY_COUNT_1MS)
#define DELAY_COUNT_250MS  (250U * DELAY_COUNT_1MS)
#define DELAY_COUNT_125MS  (125U * DELAY_COUNT_1MS)
#define DELAY_COUNT_1S     (1000U * DELAY_COUNT_1MS)


void delay(uint32_t count) {
	for (int i = 0; i < count; i++) {

	}
}

void gpio_pins_init(void) {
	__HAL_RCC_GPIOA_CLK_ENABLE();
	// 10, 11, 12, 15
		GPIO_InitTypeDef pa10 = {
				.Pin = GPIO_PIN_10,
				.Mode = GPIO_MODE_OUTPUT_PP,
				.Speed = GPIO_SPEED_LOW,
				.Pull = GPIO_NOPULL

		};
		GPIO_InitTypeDef pa11 = {
				.Pin = GPIO_PIN_11,
				.Mode = GPIO_MODE_OUTPUT_PP,
				.Speed = GPIO_SPEED_LOW,
				.Pull = GPIO_NOPULL

		};
		GPIO_InitTypeDef pa12 = {
				.Pin = GPIO_PIN_12,
				.Mode = GPIO_MODE_OUTPUT_PP,
				.Speed = GPIO_SPEED_LOW,
				.Pull = GPIO_NOPULL

		};
		GPIO_InitTypeDef pa15 = {
				.Pin = GPIO_PIN_15,
				.Mode = GPIO_MODE_OUTPUT_PP,
				.Speed = GPIO_SPEED_LOW,
				.Pull = GPIO_NOPULL

		};

		HAL_GPIO_Init(GPIOA, &pa10);
		HAL_GPIO_Init(GPIOA, &pa11);
		HAL_GPIO_Init(GPIOA, &pa12);
		HAL_GPIO_Init(GPIOA, &pa15);
}


int main(void)
{

	gpio_pins_init();

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
    while(1) {
    	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_10);
    	delay(DELAY_COUNT_1S);
    }
}

void task2_handler(void) {
    while(1) {
    	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_11);
    	delay(DELAY_COUNT_500MS);
    }
}

void task3_handler(void) {
    while(1) {
    	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_12);
    	delay(DELAY_COUNT_250MS);
    }
}

void task4_handler(void) {
    while(1) {
    	HAL_GPIO_TogglePin(GPIOA, GPIO_PIN_15);
    	delay(DELAY_COUNT_125MS);
    }
}
