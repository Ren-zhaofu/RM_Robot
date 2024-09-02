#include "./BSP/RC/RC_PS2.h"

uint16_t HandKEY;

float RC_PS2_KEY;
float RC_PS2_LX;
float RC_PS2_LY;
float RC_PS2_RX;
float RC_PS2_RY;

uint8_t DO_Data[2] = {0x01, 0x42};
uint8_t DI_Data[9] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

uint16_t MASK[] = {
  RC_PS2_SELECT,
  RC_PS2_L3,
  RC_PS2_R3,
  RC_PS2_START,
  RC_PS2_PAD_UP,
  RC_PS2_PAD_RIGHT,
  RC_PS2_PAD_DOWN,
  RC_PS2_PAD_LEFT,
  RC_PS2_L2,
  RC_PS2_R2,
  RC_PS2_L1,
  RC_PS2_R1,
  RC_PS2_GREEN,
  RC_PS2_RED,
  RC_PS2_BLUE,
  RC_PS2_PINK
};

/**
 * @brief       RC_PS2读DI高低电平
 * @param       无
 * @retval      要读入DI的电平值，范围：0/1
 * @note        当上层函数需要读DI时，此函数会被调用
 */
GPIO_PinState RC_PS2_R_DI(void)
{
  GPIO_PinState BitValue;
  
  BitValue = HAL_GPIO_ReadPin(RC_PS2_DI_GPIO_Port, RC_PS2_DI_Pin);
  
  return BitValue;
}

/**
 * @brief       RC_PS2写DO高低电平
 * @param       要写入DO的电平值，范围：0/1
 * @retval      无
 * @note        当上层函数需要写DO时，此函数会被调用
 */
void RC_PS2_W_DO(uint8_t BitValue)
{
  HAL_GPIO_WritePin(RC_PS2_DO_GPIO_Port, RC_PS2_DO_Pin, (GPIO_PinState)BitValue);
}

/**
 * @brief       RC_PS2写CS高低电平
 * @param       要写入CS的电平值，范围：0/1
 * @retval      无
 * @note        当上层函数需要写CS时，此函数会被调用
 */
void RC_PS2_W_CS(uint8_t BitValue)
{
  HAL_GPIO_WritePin(RC_PS2_CS_GPIO_Port, RC_PS2_CS_Pin, (GPIO_PinState)BitValue);
}

/**
 * @brief       RC_PS2写CLK高低电平
 * @param       要写入CLK的电平值，范围：0/1
 * @retval      无
 * @note        当上层函数需要写CLK时，此函数会被调用
 */
void RC_PS2_W_CLK(uint8_t BitValue)
{
  HAL_GPIO_WritePin(RC_PS2_CLK_GPIO_Port, RC_PS2_CLK_Pin, (GPIO_PinState)BitValue);
}

/**
 * @brief       RC_PS2写命令
 * @param       Command 要写入的命令值，范围：0x00~0xFF
 * @retval      无
 * @note        无
 */
void RC_PS2_WriteCommand(uint8_t Command)
{
  volatile uint16_t Ref = 0x01;
  
  DI_Data[1] = 0x00;
  
  for(Ref = 0x01; Ref < 0x0100; Ref <<= 1)
  {
    if(Ref & Command)
    {
      RC_PS2_W_DO(1);
    }
    else
    {
      RC_PS2_W_DO(0);
    }
    
    Delay_us(55);
    
    RC_PS2_W_CLK(1);
    Delay_us(55);
    RC_PS2_W_CLK(0);
    Delay_us(55);
    RC_PS2_W_CLK(1);
    
    Delay_us(55);
    
    if(RC_PS2_R_DI())
    {
      DI_Data[1] = Ref | DI_Data[1];
    }
    
    Delay_us(55);
    
  }
  
  Delay_us(55);
}

/**
 * @brief       RC_PS2清除数据
 * @param       无
 * @retval      无
 * @note        无
 */
void RC_PS2_ClearData(void)
{
  uint8_t i;
  
  for(i = 0; i < 9; i++)
  {
    DI_Data[i] = 0x00;
  }
}

/**
 * @brief       RC_PS2读数据
 * @param       无
 * @retval      无
 * @note        无
 */
void RC_PS2_ReadData(void)
{
  volatile uint8_t Byte = 0;
  volatile uint16_t Ref = 0x01;
  
  RC_PS2_W_CS(0);
  Delay_us(RC_PS2_Delay);
  
  RC_PS2_WriteCommand(DO_Data[0]);    //开始命令
  RC_PS2_WriteCommand(DO_Data[1]);    //请求数据
  
  for(Byte = 2; Byte < 9; Byte++)
  {
    for(Ref = 0x01; Ref < 0x0100; Ref <<= 1)
    {
      RC_PS2_W_CLK(1);
      Delay_us(55);
      RC_PS2_W_CLK(0);
      Delay_us(55);
      RC_PS2_W_CLK(1);
      
      if(RC_PS2_R_DI())
      {
        DI_Data[Byte] = Ref | DI_Data[Byte];
      }
    }
    
    Delay_us(55);
  }
  
  RC_PS2_W_CS(1);
  Delay_us(55);
}

/**
 * @brief       RC_PS2短按函数
 * @param       无
 * @retval      无
 * @note        无
 */
void RC_PS2_ShortPoll(void)
{
  RC_PS2_W_CS(0);
  Delay_us(RC_PS2_Delay);
  RC_PS2_WriteCommand(0x01);
  RC_PS2_WriteCommand(0x42);
  RC_PS2_WriteCommand(0x00);
  RC_PS2_WriteCommand(0x00);
  RC_PS2_WriteCommand(0x00);
  RC_PS2_W_CS(1);
  Delay_us(RC_PS2_Delay);
}

/**
 * @brief       RC_PS2进入配置函数
 * @param       无
 * @retval      无
 * @note        无
 */
void RC_PS2_EnterConfing(void)
{
  RC_PS2_W_CS(0);
  Delay_us(RC_PS2_Delay);
  RC_PS2_WriteCommand(0x01);
  RC_PS2_WriteCommand(0x43);
  RC_PS2_WriteCommand(0x00);
  RC_PS2_WriteCommand(0x01);
  RC_PS2_WriteCommand(0x00);
  RC_PS2_WriteCommand(0x00);
  RC_PS2_WriteCommand(0x00);
  RC_PS2_WriteCommand(0x00);
  RC_PS2_WriteCommand(0x00);
  RC_PS2_W_CS(1);
  Delay_us(RC_PS2_Delay);
}

/**
 * @brief       RC_PS2发送模式设置函数
 * @param       无
 * @retval      无
 * @note        无
 */
void RC_PS2_TurnOnAnalogMode(void)
{
  RC_PS2_W_CS(0);
  Delay_us(RC_PS2_Delay);
  RC_PS2_WriteCommand(0x01);
  RC_PS2_WriteCommand(0x44);
  RC_PS2_WriteCommand(0x00);
  RC_PS2_WriteCommand(0x01);    //软件设置发送模式：Digital=0x00;Analog=0x01
  RC_PS2_WriteCommand(0xee);    //0x03锁存设置，即不可通过按键“MODE”设置模式。
                                //0xEE不锁存软件设置，可通过按键“MODE”设置模式。
  RC_PS2_WriteCommand(0x00);
  RC_PS2_WriteCommand(0x00);
  RC_PS2_WriteCommand(0x00);
  RC_PS2_WriteCommand(0x00);
  RC_PS2_W_CS(1);
  Delay_us(RC_PS2_Delay);
}

/**
 * @brief       RC_PS2振动设置函数
 * @param       无
 * @retval      无
 * @note        无
 */
void RC_PS2_VibrationMode(void)
{
  RC_PS2_W_CS(0);
  Delay_us(RC_PS2_Delay);
  RC_PS2_WriteCommand(0x01);
  RC_PS2_WriteCommand(0x4D);
  RC_PS2_WriteCommand(0x00);
  RC_PS2_WriteCommand(0x00);
  RC_PS2_WriteCommand(0x01);
  RC_PS2_W_CS(1);
  Delay_us(RC_PS2_Delay);
}

/**
 * @brief       RC_PS2完成并保存配置函数
 * @param       无
 * @retval      无
 * @note        无
 */
void RC_PS2_ExitConfing(void)
{
  RC_PS2_W_CS(0);
  Delay_us(RC_PS2_Delay);
  RC_PS2_WriteCommand(0x01);
  RC_PS2_WriteCommand(0x43);
  RC_PS2_WriteCommand(0x00);
  RC_PS2_WriteCommand(0x00);
  RC_PS2_WriteCommand(0x5A);
  RC_PS2_WriteCommand(0x5A);
  RC_PS2_WriteCommand(0x5A);
  RC_PS2_WriteCommand(0x5A);
  RC_PS2_WriteCommand(0x5A);
  RC_PS2_W_CS(1);
  Delay_us(RC_PS2_Delay);
}

/**
 * @brief       RC_PS2初始化函数
 * @param       无
 * @retval      无
 * @note        使用前，需要调用此初始化函数
 */
void RC_PS2_Init(void)
{
  RC_PS2_ShortPoll();
  RC_PS2_ShortPoll();
  RC_PS2_ShortPoll();
  RC_PS2_EnterConfing();
  RC_PS2_TurnOnAnalogMode();
//  RC_PS2_VibrationMode();
  RC_PS2_ExitConfing();
}

/**
 * @brief       RC_PS2获取按键数据函数
 * @param       无
 * @retval      0：按下
                1：未按下
 * @note        无
 */
uint8_t RC_PS2_GetDataKEY(void)
{
  uint8_t Index;
  
  RC_PS2_ClearData();
  RC_PS2_ReadData();
  
  HandKEY = (DI_Data[4] << 8) | DI_Data[3];
  
  for(Index = 0; Index < 16; Index++)
  {
    if((HandKEY & (1 << (MASK[Index] - 1))) == 0)
    {
      return Index + 1;
    }
  }
  
  return 0;
}

/**
 * @brief       RC_PS2获取模拟数据函数
 * @param       摇杆
 * @retval      摇杆的模拟量, 范围0~256
 * @note        无
 */
uint8_t RC_PS2_GetAnologData(uint8_t RC_PS2_Button)
{
  return DI_Data[RC_PS2_Button];
}

/**
 * @brief       RC_PS2获取状态函数
 * @param       无
 * @retval      无
 * @note        无
 */
void RC_PS2_GetStatus(void)
{
  RC_PS2_KEY = RC_PS2_GetDataKEY();
  RC_PS2_LX = RC_PS2_GetAnologData(RC_PSS_LX);
  RC_PS2_LY = RC_PS2_GetAnologData(RC_PSS_LY);
  RC_PS2_RX = RC_PS2_GetAnologData(RC_PSS_RX);
  RC_PS2_RY = RC_PS2_GetAnologData(RC_PSS_RY);
}
