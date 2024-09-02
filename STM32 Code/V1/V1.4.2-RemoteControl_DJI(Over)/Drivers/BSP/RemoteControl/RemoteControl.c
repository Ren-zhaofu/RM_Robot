#include "./BSP/RemoteControl/RemoteControl.h"

uint8_t DBUS_BUF[DBUS_BUFLEN];
RC_Information_t RC;

static int UART_Receive_DMA_NO_IT(UART_HandleTypeDef* huart, uint8_t* pData, uint32_t Size)
{
  if (huart->RxState == HAL_UART_STATE_READY)
  {
    if ((pData == NULL) || (Size == 0))
    {
      return HAL_ERROR;
    }
    
    huart->pRxBuffPtr = pData;
    huart->RxXferSize = Size;
    huart->ErrorCode  = HAL_UART_ERROR_NONE;

    /* Enable the DMA Stream */
    HAL_DMA_Start(huart->hdmarx, (uint32_t)&huart->Instance->DR, (uint32_t)pData, Size);

    /* 
    * Enable the DMA transfer for the receiver request by setting the DMAR bit
    * in the UART CR3 register
    */
    SET_BIT(huart->Instance->CR3, USART_CR3_DMAR);

    return HAL_OK;
  }
  else
  {
    return HAL_BUSY;
  }
}

/**
 * @brief       RC_DBUS_UART初始化函数
 * @param       无
 * @retval      无
 * @note        使用前，需要调用此初始化函数
 */
void RC_DBUS_UART_Init(void)
{
  __HAL_UART_CLEAR_IDLEFLAG(&DBUS_HUART);
  __HAL_UART_ENABLE_IT(&DBUS_HUART, UART_IT_IDLE);

  UART_Receive_DMA_NO_IT(&DBUS_HUART, DBUS_BUF, DBUS_MAX_LEN);
}

void RC_Callback_Handler(RC_Information_t *RC, uint8_t *buff)
{
  RC->CH0  = (buff[0] | buff[1] << 8) & 0x07FF;
//  RC->CH0 -= 1024;
  RC->CH1  = (buff[1] >> 3 | buff[2] << 5) & 0x07FF;
  RC->CH1 -= 1024;
  RC->CH2  = (buff[2] >> 6 | buff[3] << 2 | buff[4] << 10) & 0x07FF;
  RC->CH2 -= 1024;
  RC->CH3  = (buff[4] >> 1 | buff[5] << 7) & 0x07FF;
  RC->CH3 -= 1024;

  RC->S1 = ((buff[5] >> 4) & 0x000C) >> 2;
  RC->S2 =  (buff[5] >> 4) & 0x0003;
  
  if ((abs(RC->CH0) > 660) || \
      (abs(RC->CH1) > 660) || \
      (abs(RC->CH2) > 660) || \
      (abs(RC->CH3) > 660))
  {
    memset(RC, 0, sizeof(RC_Information_t));
  }
}

static void UART_RX_Idle_Callback(UART_HandleTypeDef* huart)
{
  /* clear idle it flag avoid idle interrupt all the time */
  __HAL_UART_CLEAR_IDLEFLAG(huart);

  /* handle received data in idle interrupt */
  if (huart == &DBUS_HUART)
  {
    /* clear DMA transfer complete flag */
    __HAL_DMA_DISABLE(huart->hdmarx);

    /* handle dbus data DBUS_BUF from DMA */
    if ((DBUS_MAX_LEN - __HAL_DMA_GET_COUNTER(huart1.hdmarx)) == DBUS_BUFLEN)
    {
      RC_Callback_Handler(&RC, DBUS_BUF);
    }
    
    /* restart dma transmission */
    __HAL_DMA_SET_COUNTER(huart->hdmarx, DBUS_MAX_LEN);
    __HAL_DMA_ENABLE(huart->hdmarx);
  }
}

void UART_Receive_Handler(UART_HandleTypeDef *huart)
{
  if (__HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE) && 
      __HAL_UART_GET_IT_SOURCE(huart, UART_IT_IDLE))
  {
    UART_RX_Idle_Callback(huart);
  }
}
