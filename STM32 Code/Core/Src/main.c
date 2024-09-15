/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stdio.h"
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
TIM_HandleTypeDef htim2;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */


volatile uint32_t Timer_clock = 32; // La fréquence de notre Timer en MHz
volatile int R6 = 1; // Résistance 6 du conditionneur en MegaOhm



// --------- FAIRE LES CALCULS DANS LE CALLBACK ----------- //



//Pour electrode 1
volatile int CalculOK_1;
volatile float Diff_moy_1;
volatile float IC_Valeur1_1;
volatile float IC_Valeur2_1;
volatile int Premiere_capture_1;
//Pour moyenner les valeurs electrode 1
volatile float n_1 = 0;
volatile float Freq_moy_1 = 0;
volatile float Etat_distance_1;
volatile float Capacite_moy_1; // La valeur de la Capacit 1


//Pour electrode 2
volatile int CalculOK_2;
volatile float Diff_moy_2;
volatile float IC_Valeur1_2;
volatile float IC_Valeur2_2;
volatile int Premiere_capture_2;
//Pour moyenner les valeurs electrode 2
volatile float n_2 = 0;
volatile float Freq_moy_2 = 0;
volatile float Etat_distance_2;
volatile float Capacite_moy_2; // La valeur de la Capacit 2


//Pour electrode 3
volatile int CalculOK_3;
volatile float Diff_moy_3;
volatile float IC_Valeur1_3;
volatile float IC_Valeur2_3;
volatile int Premiere_capture_3;
//Pour moyenner les valeurs electrode 3
volatile float n_3 = 0;
volatile float Freq_moy_3 = 0;
volatile float Etat_distance_3;
volatile float Capacite_moy_3; // La valeur de la Capacit 3



// On initialise la valeur de cap_data, pour le formater
uint8_t cap_data_1[5000] = {'\0'};
uint8_t cap_data_2[5000] = {'\0'};
uint8_t cap_data_3[5000] = {'\0'};



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_TIM2_Init(void);
static void MX_USART2_UART_Init(void);
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
  MX_TIM2_Init();
  MX_USART2_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_IC_Start_IT(&htim2, TIM_CHANNEL_1);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  if (Etat_distance_1){
		  HAL_GPIO_WritePin(LED_ROUGE_D4_GPIO_Port, LED_ROUGE_D4_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(LED_BLEU_D5_GPIO_Port, LED_BLEU_D5_Pin, GPIO_PIN_RESET);
	  }
	  else{
		  HAL_GPIO_WritePin(LED_ROUGE_D4_GPIO_Port, LED_ROUGE_D4_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(LED_BLEU_D5_GPIO_Port, LED_BLEU_D5_Pin, GPIO_PIN_SET);
	  }
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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL8;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief TIM2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM2_Init(void)
{

  /* USER CODE BEGIN TIM2_Init 0 */

  /* USER CODE END TIM2_Init 0 */

  TIM_ClockConfigTypeDef sClockSourceConfig = {0};
  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_IC_InitTypeDef sConfigIC = {0};

  /* USER CODE BEGIN TIM2_Init 1 */

  /* USER CODE END TIM2_Init 1 */
  htim2.Instance = TIM2;
  htim2.Init.Prescaler = 0;
  htim2.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim2.Init.Period = 800000000;
  htim2.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim2.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
  if (HAL_TIM_Base_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
  if (HAL_TIM_ConfigClockSource(&htim2, &sClockSourceConfig) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_TIM_IC_Init(&htim2) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim2, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigIC.ICPolarity = TIM_INPUTCHANNELPOLARITY_RISING;
  sConfigIC.ICSelection = TIM_ICSELECTION_DIRECTTI;
  sConfigIC.ICPrescaler = TIM_ICPSC_DIV1;
  sConfigIC.ICFilter = 0;
  if (HAL_TIM_IC_ConfigChannel(&htim2, &sConfigIC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM2_Init 2 */

  /* USER CODE END TIM2_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LED_VERT_D6_Pin|LED_BLEU_D5_Pin|LED_ROUGE_D4_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : LED_VERT_D6_Pin LED_BLEU_D5_Pin LED_ROUGE_D4_Pin */
  GPIO_InitStruct.Pin = LED_VERT_D6_Pin|LED_BLEU_D5_Pin|LED_ROUGE_D4_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */



//HAL_UART_Transmit(&huart2, 'Test', 10*sizeof(char), 200);

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef*htim2){
	if ((htim2->Channel == HAL_TIM_ACTIVE_CHANNEL_1))
	{
		if (Premiere_capture_1 ==0)
		{
			IC_Valeur1_1 = HAL_TIM_ReadCapturedValue(htim2, TIM_CHANNEL_1);
			Premiere_capture_1 =1;
		}
		else if (Premiere_capture_1)
		{
			n_1 ++;
			if(n_1 == 10){
				IC_Valeur2_1 = HAL_TIM_ReadCapturedValue(htim2, TIM_CHANNEL_1);
				if (IC_Valeur2_1 > IC_Valeur1_1)
				{
					Diff_moy_1 = (IC_Valeur2_1 - IC_Valeur1_1)/n_1;
					Freq_moy_1= HAL_RCC_GetPCLK1Freq()/Diff_moy_1; // Frequence en Hz
					CalculOK_1 =1;

					// Calcul de la valeur de la capa en pF
					Capacite_moy_1 = 1000000/(Freq_moy_1*R6); // En Pico PicoFarad

					if (Capacite_moy_1 > 31){
						Etat_distance_1 = 1;
					}
					else{
						Etat_distance_1 = 0;
					}

					// Envoyer les valeurs dans le UART
					sprintf(cap_data_1, "Frequence = %f Hz , Capacite = %f pF , Seuil = %d \n\r", Freq_moy_1, Capacite_moy_1, Etat_distance_1);
					HAL_UART_Transmit(&huart2, cap_data_1, sizeof(cap_data_1), 200);
					n_1 = 0;
				}
				else
					CalculOK_1 =0;
				Premiere_capture_1 = 0;


			}

		}
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
