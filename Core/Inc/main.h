/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

void task1_handler(void);
void task2_handler(void);
void task3_handler(void);
void task4_handler(void);

#define TASK_STACK_SIZE 1024
#define SRAM_START 0x20000000U
#define SRAM_SIZE  (128 * 1024)
#define SRAM_END   (SRAM_START + SRAM_SIZE)

#define T1_STACK_START    (SRAM_END)
#define T2_STACK_START    ((SRAM_END) - (1 * TASK_STACK_SIZE))
#define T3_STACK_START    ((SRAM_END) - (2 * TASK_STACK_SIZE))
#define T4_STACK_START 	  ((SRAM_END) - (3 * TASK_STACK_SIZE))
#define SCHED_TASK_STACK  ((SRAM_END) - (4 * TASK_STACK_SIZE))

#endif /* __MAIN_H */
