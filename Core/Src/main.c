
#include "main.h"

uint8_t button_State = 0;
uint8_t number = 0;
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

// Segment numbers stored in the array
uint8_t ledorder[10] = {
        0x3f,  // 0
        0x06,  // 1
        0x5b,  // 2
        0x4f,  // 3
        0x66,  // 4
        0x6d,  // 5
        0x7d,  // 6
        0x07,  // 7
        0x7f,  // 8
        0x67   // 9
};

void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{

  UNUSED(GPIO_Pin);
    if ((HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_13)) == GPIO_Pin)
    {
    		button_State = 1;
    }
    else
    {

    }



}
void ORDER_UPDATE(uint8_t number){
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, ((number>>0)&0x01));
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, ((number>>1)&0x01));
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_2, ((number>>2)&0x01));
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_3, ((number>>3)&0x01));
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, ((number>>4)&0x01));
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, ((number>>5)&0x01));
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, ((number>>6)&0x01));
}

int main(void)
{

  HAL_Init();


  SystemClock_Config();


  MX_GPIO_Init();

  while (1)
  {
	  	  if(button_State == 1)
	  	  {
	  		  if(number == 9)
	  		  {
	  			  number = 0;
	  		  }
	  		  else
	  		  {
	  			  number++;
	  		  }
	  		button_State = 0;
	  	  }
	  	  else if(number == 0)
	  	  {
	  		  number = 9;
	  	  }
	  	  else
	  	  {
	  		  number --;
	  	  }
	  	ORDER_UPDATE(ledorder[number]);
	  		  HAL_Delay(500);
  }

}

void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};


  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }


  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.SYSCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_APB1_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}


static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOF_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();


  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6, GPIO_PIN_RESET);


  GPIO_InitStruct.Pin = User_Button_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(User_Button_GPIO_Port, &GPIO_InitStruct);


  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3
                          |GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);


  HAL_NVIC_SetPriority(EXTI4_15_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI4_15_IRQn);


}


void Error_Handler(void)
{

  __disable_irq();
  while (1)
  {
  }

}

#ifdef  USE_FULL_ASSERT

void assert_failed(uint8_t *file, uint32_t line)
{

}
#endif
