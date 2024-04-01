/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "delay.h"
#include "Ch455h.h"
#include "Global.h"
#include "Key.h"
#include "LcdDraw.h"
#include "Time.h"
#include "SignalDraw.h"
#include "WaveOperate.h"
#include "MessageTR.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
  uint32_t d_time = 0;
  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */
  
  
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_SPI5_Init();
  MX_TIM6_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  delay_init(180);
  CH455_Init();
  CH455_Write( CH455_DIG0 | bcd_num[0] );
  CH455_Write( CH455_DIG1 | bcd_num[0] );
  CH455_Write( CH455_DIG2 | bcd_num[0] );
  CH455_Write( CH455_DIG3 | bcd_num[0] );
  HAL_UART_Receive_IT(&huart1, (uint8_t *)&uart_res, 1);
  HAL_TIM_Base_Start_IT(&htim6);
  GJH_LCD_Init();
  GJH_Wave_Init();
  GJH_TR_Init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  CH455_Write( CH455_DIG3 | bcd_num[10] );

  while (1)
  {

    //获取fps
    d_time = GJH_Get_D_Time();
    fps = 1000 / (d_time * BASE_TIME);
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

    GJH_Buff_UI_Draw();
    //绘制fft波形
    GJH_Buff_Wave_Draw();
    if (is_fft_show)
    {  
        GJH_Buff_FFT_Draw();
    }
    GJH_LCD_Show();
    
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 25;
  RCC_OscInitStruct.PLL.PLLN = 360;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Activate the Over-Drive mode
  */
  if (HAL_PWREx_EnableOverDrive() != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

//GPIO中断
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    //CH455H检测到按钮按下
	if (GPIO_Pin == CH455_INT_Pin)
    {
        switch(CH455_Read())
        {
            case 0x44:
                GJH_Key_On(1);
                break;
            case 0x45:
                GJH_Key_On(2);
                break;
            case 0x46:
                GJH_Key_On(3);
                break;
            case 0x47:
                GJH_Key_On(4);
                break;
            case 0x4C:
                GJH_Key_On(5);
                break;
            case 0x4D:
                GJH_Key_On(6);
                break;
            case 0x4E:
                GJH_Key_On(7);
                break;
            case 0x4F:
                GJH_Key_On(8);
                break;
            case 0x54:
                GJH_Key_On(9);
                break;
            case 0x55:
                GJH_Key_On(10);
                break;
            case 0x56:
                GJH_Key_On(11);
                break;
            case 0x57:
                GJH_Key_On(12);
                break;
            case 0x5C:
                GJH_Key_On(13);
                break;
            case 0x5D:
                GJH_Key_On(14);
                break;
            case 0x5E:
                GJH_Key_On(15);
                break;
            case 0x5F:
                GJH_Key_On(16);
                break;
            default:
                GJH_Key_On(0);
                break;
        }
        CH455_Write( CH455_SYSON );         //抗干扰，刷新CH455寄存器
        
	}
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    UNUSED(huart);
    if (huart->Instance == USART1)
    {
        uart_rx_last_time = GJH_Get_Time();
        uart_rx_buff[uart_rx_counter++] = uart_res;
        HAL_UART_Receive_IT(&huart1, (uint8_t *)&uart_res, 1);
    }
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
