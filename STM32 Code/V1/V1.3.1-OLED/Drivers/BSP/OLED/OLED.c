#include "./BSP/OLED/OLED.h"

uint8_t OLED_DisplayBuf[8][128];

#if( OLED_Communication_Mode == 0 )
/* OLED_4Pin_IIC */

/**
 * @brief       OLED写SCL高低电平
 * @param       要写入SCL的电平值，范围：0/1
 * @retval      无
 * @note        当上层函数需要写SCL时，此函数会被调用
 */
void OLED_W_SCL(uint8_t BitValue)
{
  HAL_GPIO_WritePin(OLED_SCL_GPIO_Port, OLED_SCL_Pin, (GPIO_PinState)BitValue);
}

/**
 * @brief       OLED写SDA高低电平
 * @param       要写入SDA的电平值，范围：0/1
 * @retval      无
 * @note        当上层函数需要写SDA时，此函数会被调用
 */
void OLED_W_SDA(uint8_t BitValue)
{
  HAL_GPIO_WritePin(OLED_SDA_GPIO_Port, OLED_SDA_Pin, (GPIO_PinState)BitValue);
}

/**
 * @brief       I2C起始
 * @param       无
 * @retval      无
 * @note        无
 */
void OLED_I2C_Start(void)
{
  OLED_W_SDA(1);
  OLED_W_SCL(1);
  OLED_W_SDA(0);
  OLED_W_SCL(0);
}

/**
 * @brief       I2C终止
 * @param       无
 * @retval      无
 * @note        无
 */
void OLED_I2C_Stop(void)
{
  OLED_W_SDA(0);
  OLED_W_SCL(1);
  OLED_W_SDA(1);
}
#else
/* OLED_7Pin_SPI */
/**
 * @brief       OLED写D0（CLK）高低电平
 * @param       要写入D0的电平值，范围：0/1
 * @retval      无
 * @note        当上层函数需要写D0时，此函数会被调用
 *              用户需要根据参数传入的值，将D0置为高电平或者低电平
 *              当参数传入0时，置D0为低电平，当参数传入1时，置D0为高电平
 */
void OLED_W_D0(uint8_t BitValue)
{
  /*根据BitValue的值，将D0置高电平或者低电平*/
  HAL_GPIO_WritePin(OLED_D0_GPIO_Port, OLED_D0_Pin, (GPIO_PinState)BitValue);
}

/**
 * @brief       OLED写D1（MOSI）高低电平
 * @param       要写入D1的电平值，范围：0/1
 * @retval      无
 * @note        当上层函数需要写D1时，此函数会被调用
 *              用户需要根据参数传入的值，将D1置为高电平或者低电平
 *              当参数传入0时，置D1为低电平，当参数传入1时，置D1为高电平
 */
void OLED_W_D1(uint8_t BitValue)
{
  /*根据BitValue的值，将D0置高电平或者低电平*/
  HAL_GPIO_WritePin(OLED_D1_GPIO_Port, OLED_D1_Pin, (GPIO_PinState)BitValue);
}

/**
 * @brief       OLED写RES高低电平
 * @param       要写入RES的电平值，范围：0/1
 * @retval      无
 * @note        当上层函数需要写RES时，此函数会被调用
 *              用户需要根据参数传入的值，将RES置为高电平或者低电平
 *              当参数传入0时，置RES为低电平，当参数传入1时，置RES为高电平
 */
void OLED_W_RES(uint8_t BitValue)
{
  /*根据BitValue的值，将RES置高电平或者低电平*/
  HAL_GPIO_WritePin(OLED_RES_GPIO_Port, OLED_RES_Pin, (GPIO_PinState)BitValue);
}

/**
 * @brief       OLED写DC高低电平
 * @param       要写入DC的电平值，范围：0/1
 * @retval      无
 * @note        当上层函数需要写DC时，此函数会被调用
 *              用户需要根据参数传入的值，将DC置为高电平或者低电平
 *              当参数传入0时，置DC为低电平，当参数传入1时，置DC为高电平
 */
void OLED_W_DC(uint8_t BitValue)
{
  /*根据BitValue的值，将DC置高电平或者低电平*/
  HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, (GPIO_PinState)BitValue);
}

///**
// * @brief       OLED写CS高低电平
// * @param       要写入CS的电平值，范围：0/1
// * @retval      无
// * @note        当上层函数需要写CS时，此函数会被调用
// *              用户需要根据参数传入的值，将CS置为高电平或者低电平
// *              当参数传入0时，置CS为低电平，当参数传入1时，置CS为高电平
// */
//void OLED_W_CS(uint8_t BitValue)
//{
//  /*根据BitValue的值，将CS置高电平或者低电平*/
//  HAL_GPIO_WritePin(OLED_CS_GPIO_Port, OLED_CS_Pin, (GPIO_PinState)BitValue);
//}
#endif

/**
 * @brief       发送一个字节
 * @param       Byte 要发送的一个字节数据，范围：0x00~0xFF
 * @retval      无
 * @note        无
 */
void OLED_SendByte(uint8_t Byte)
{
  uint8_t i;
  
  #if( OLED_Communication_Mode == 0 )
  /* OLED_4Pin_IIC */
  /*循环8次，主机依次发送数据的每一位*/
  for (i = 0; i < 8; i++)
  {
    /*使用掩码的方式取出Byte的指定一位数据并写入到SDA线*/
    /*两个!的作用是，让所有非零的值变为1*/
    OLED_W_SDA(!!(Byte & (0x80 >> i)));
    OLED_W_SCL(1);
    OLED_W_SCL(0);
  }
  
  OLED_W_SCL(1);
  OLED_W_SCL(0);
  #else
  /* OLED_7Pin_SPI */
  /*循环8次，主机依次发送数据的每一位*/
  for (i = 0; i < 8; i++)
  {
    /*使用掩码的方式取出Byte的指定一位数据并写入到D1线*/
    /*两个!的作用是，让所有非零的值变为1*/
    OLED_W_D1(!!(Byte & (0x80 >> i)));
    OLED_W_D0(1);                   //拉高D0，从机在D0上升沿读取SDA
    OLED_W_D0(0);                   //拉低D0，主机开始发送下一位数据
  }
  #endif
}

/**
 * @brief       OLED写命令
 * @param       Command 要写入的命令值，范围：0x00~0xFF
 * @retval      无
 * @note        无
 */
void OLED_WriteCommand(uint8_t Command)
{
  #if( OLED_Communication_Mode == 0 )
  /* OLED_4Pin_IIC */
  OLED_I2C_Start();                 //I2C起始
  OLED_SendByte(0x78);              //发送OLED的I2C从机地址
  OLED_SendByte(0x00);              //控制字节，给0x00，表示即将写命令
  OLED_SendByte(Command);           //写入指定的命令
  OLED_I2C_Stop();                  //I2C终止
  #else
  /* OLED_7Pin_SPI */
//  OLED_W_CS(0);                     //拉低CS，开始通信
  OLED_W_DC(0);                     //拉低DC，表示即将发送命令
  OLED_SendByte(Command);           //写入指定命令
//  OLED_W_CS(1);                     //拉高CS，结束通信
  #endif
}

/**
 * @brief       OLED写数据
 * @param       Data 要写入数据的起始地址
 * @param       Count 要写入数据的数量
 * @retval      无
 * @note        无
 */
void OLED_WriteData(uint8_t *Data, uint8_t Count)
{
  uint8_t i;
  
  #if( OLED_Communication_Mode == 0 )
  /* OLED_4Pin_IIC */
  OLED_I2C_Start();                 //I2C起始
  OLED_SendByte(0x78);              //发送OLED的I2C从机地址
  OLED_SendByte(0x40);              //控制字节，给0x40，表示即将写数量
  /*循环Count次，进行连续的数据写入*/
  for (i = 0; i < Count; i ++)
  {
    OLED_SendByte(Data[i]);         //依次发送Data的每一个数据
  }
  OLED_I2C_Stop();                  //I2C终止
  #else
  /* OLED_7Pin_SPI */
//  OLED_W_CS(0);                     //拉低CS，开始通信
  OLED_W_DC(1);                     //拉高DC，表示即将发送数据
  /*循环Count次，进行连续的数据写入*/
  for (i = 0; i < Count; i ++)
  {
    OLED_SendByte(Data[i]);         //依次发送Data的每一个数据
  }
//  OLED_W_CS(1);                     //拉高CS，结束通信
  #endif
}

/**
 * @brief       OLED初始化函数
 * @param       无
 * @retval      无
 * @note        使用前，需要调用此初始化函数
 */
void OLED_Init(void)
{
  #if( OLED_Communication_Mode == 0 )
  /* OLED_4Pin_IIC */
  /* 释放SCL和SDA */
  OLED_W_SCL(1);
  OLED_W_SDA(1);
  #else
  /* OLED_7Pin_SPI */
  /*置引脚默认电平*/
  OLED_W_D0(0);
  OLED_W_D1(1);
  OLED_W_RES(1);
  OLED_W_DC(1);
//  OLED_W_CS(1);
  #endif
  
  /*写入一系列的命令，对OLED进行初始化配置*/
  OLED_WriteCommand(0XAE);    //设置显示关闭/打开(POR = 0xAE)
                              //关闭 -> 0xAE，打开 -> 0xAF
  
  OLED_WriteCommand(0X00);    //设置列地址低四位(POR = 0x00)
  OLED_WriteCommand(0X10);    //设置列地址高四位(POR = 0x10)
  
  OLED_WriteCommand(0XD5);    //设置显示分频/振荡器频率模式
  OLED_WriteCommand(0X80);    //设置显示分频/振荡器频率数据（POR = 0x50）
  
  OLED_WriteCommand(0XA8);    //设置多路调度模式
  OLED_WriteCommand(0X3F);    //设置1/64 duty（0x01~0x3F）（POR = 0x3F）
  
  OLED_WriteCommand(0XD3);    //设置显示偏移模式
  OLED_WriteCommand(0X00);    //设置不偏移（POR = 0x00）
  
  OLED_WriteCommand(0X40);    //设置显示起始线(POR = 0x40)
  
  OLED_WriteCommand(0XA1);    //设置分段重新映射(ADC)（POR = 0xA0）
                              //正常 -> 0xA1，左右反置 -> 0xA0
  
  OLED_WriteCommand(0XC8);    //设置常见输出扫描方向（POR = 0xC8）
                              //正常 -> 0xc8，上下反置 -> 0xC0
  
  OLED_WriteCommand(0XDA);    //设置常用Pad硬件配置模式
  OLED_WriteCommand(0X12);    //设置常用Pad硬件配置数据（POR = 0x12）
  
  OLED_WriteCommand(0X81);    //设置对比度控制模式
  OLED_WriteCommand(0XCF);    //设置对比度（0x00~0xFF）(POR = 0x80)
  
  OLED_WriteCommand(0XD9);    //设置放电/预充周期模式
  OLED_WriteCommand(0XF1);    //设置放电/预充周期数据（POR = 0x22）
                              //放电：15，预充：1
  
  OLED_WriteCommand(0XDB);    //设置VCOM取消选择关卡模式
  OLED_WriteCommand(0X40);    //设置VCOM取消选择关卡数据（POR = 0x35）
  
  OLED_WriteCommand(0XA4);    //设置整个显示关闭/打开（POR = 0xA4）
                              //正常显示 -> 0xA4，全部显示 -> 0xA5
  
  OLED_WriteCommand(0XA6);    //设置正常/反向显示（POR = 0xA6）
                              //正常 -> 0xA6，反向 -> 0xA7
  
  OLED_WriteCommand(0X8D);    //设置充电泵使能/失能
  OLED_WriteCommand(0X14);    //设置充电泵失能
  
  OLED_WriteCommand(0XAF);    //设置显示关闭/打开(POR = 0xAE)
                              //关闭 -> 0xAE，打开 -> 0xAF
  
  OLED_Clear();               //清空显存数组
  OLED_Update();              //更新显示，清屏，防止初始化后未显示内容时花屏
}

/**
 * @brief       OLED设置显示光标位置
 * @param       Page 指定光标所在的页，  范围：0~7
 * @param       X 指定光标所在的X轴坐标，范围：0~127
 * @retval      无
 * @note        OLED默认的Y轴，只能8个Bit为一组写入，即1页等于8个Y轴坐标
 */
void OLED_SetCursor(uint8_t Page, uint8_t X)
{
  /*如果使用此程序驱动1.3寸的OLED显示屏，则需要解除此注释*/
  /*因为1.3寸的OLED驱动芯片（SH1106）有132列*/
  /*屏幕的起始列接在了第2列，而不是第0列*/
  /*所以需要将X加2，才能正常显示*/
  if(OLED_Size)
  {
    X += 2;
  }
  
  /*通过指令设置页地址和列地址*/
  OLED_WriteCommand(0xB0 | Page);                 //设置页位置
  OLED_WriteCommand(0x10 | ((X & 0xF0) >> 4));    //设置X位置高4位
  OLED_WriteCommand(0x00 | (X & 0x0F));           //设置X位置低4位
}

/**
 * @brief       次方函数
 * @param       X 底数
 * @param       Y 指数
 * @retval      等于X的Y次方
 * @note        无
 */
uint32_t OLED_Pow(uint32_t X, uint32_t Y)
{
  uint32_t Result = 1;    //结果默认为1
  
  while (Y --)            //累乘Y次
  {
    Result *= X;          //每次把X累乘到结果上
  }
  
  return Result;
}

/**
 * @brief       判断指定点是否在指定多边形内部
 * @param       nvert 多边形的顶点数
 * @param       vertx verty 包含多边形顶点的x和y坐标的数组
 * @param       testx testy 测试点的X和y坐标
 * @retval      指定点是否在指定多边形内部，0：不在内部，1：在内部
 * @note        无
 */
uint8_t OLED_pnpoly(uint8_t nvert, int16_t *vertx, int16_t *verty, int16_t testx, int16_t testy)
{
  int16_t i, j, c = 0;
  
  /*此算法由W. Randolph Franklin提出*/
  /*参考链接：https://wrfranklin.org/Research/Short_Notes/pnpoly.html*/
  for (i = 0, j = nvert - 1; i < nvert; j = i++)
  {
    if (((verty[i] > testy) != (verty[j] > testy)) &&
      (testx < (vertx[j] - vertx[i]) * (testy - verty[i]) / (verty[j] - verty[i]) + vertx[i]))
    {
      c = !c;
    }
  }
  
  return c;
}

/**
 * @brief       判断指定点是否在指定角度内部
 * @param       X Y 指定点的坐标
 * @param       StartAngle EndAngle 起始角度和终止角度，范围：-180~180
 *              水平向右为0度，水平向左为180度或-180度，下方为正数，上方为负数，顺时针旋转
 * @retval      指定点是否在指定角度内部，0：不在内部，1：在内部
 * @note        无
 */
uint8_t OLED_IsInAngle(int16_t X, int16_t Y, int16_t StartAngle, int16_t EndAngle)
{
  int16_t PointAngle;
  
  PointAngle = atan2(Y, X) / 3.14 * 180;      //计算指定点的弧度，并转换为角度表示
  
  if (StartAngle < EndAngle)                  //起始角度小于终止角度的情况
  {
  /*如果指定角度在起始终止角度之间，则判定指定点在指定角度*/
    if (PointAngle >= StartAngle && PointAngle <= EndAngle)
    {
      return 1;
    }
  }
  else                                        //起始角度大于于终止角度的情况
  {
    /*如果指定角度大于起始角度或者小于终止角度，则判定指定点在指定角度*/
    if (PointAngle >= StartAngle || PointAngle <= EndAngle)
    {
      return 1;
    }
  }
  
  return 0;                                   //不满足以上条件，则判断判定指定点不在指定角度
}

/**
 * @brief       OLED显存数组更新到OLED屏幕
 * @param       无
 * @retval      无
 * @note        所有的显示函数，都只是对OLED显存数组进行读写
 *              随后调用OLED_Update函数或OLED_UpdateArea函数
 *              才会将显存数组的数据发送到OLED硬件，进行显示
 *              故调用显示函数后，要想真正地呈现在屏幕上，还需调用更新函数
 */
void OLED_Update(void)
{
  uint8_t j;
  
  for (j = 0; j < 8; j ++)
  {
    /*设置光标位置为每一页的第一列*/
    OLED_SetCursor(j, 0);
    /*连续写入128个数据，将显存数组的数据写入到OLED硬件*/
    OLED_WriteData(OLED_DisplayBuf[j], 128);
  }
}

/**
 * @brief       OLED显存数组部分更新到OLED屏幕
 * @param       X 指定区域左上角的横坐标，范围：0~127
 * @param       Y 指定区域左上角的纵坐标，范围：0~63
 * @param       Width 指定区域的宽度，    范围：0~128
 * @param       Height 指定区域的高度，   范围：0~64
 * @retval      无
 * @note        此函数会至少更新参数指定的区域
 *              如果更新区域Y轴只包含部分页，则同一页的剩余部分会跟随一起更新
 * @note        所有的显示函数，都只是对OLED显存数组进行读写
 *              随后调用OLED_Update函数或OLED_UpdateArea函数
 *              才会将显存数组的数据发送到OLED硬件，进行显示
 *              故调用显示函数后，要想真正地呈现在屏幕上，还需调用更新函数
 */
void OLED_UpdateArea(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height)
{
  uint8_t j;
  
  /*参数检查，保证指定区域不会超出屏幕范围*/
  if (X > 127) {return;}
  if (Y > 63) {return;}
  if (X + Width > 128) {Width = 128 - X;}
  if (Y + Height > 64) {Height = 64 - Y;}
  
  /*遍历指定区域涉及的相关页*/
  /*(Y + Height - 1) / 8 + 1的目的是(Y + Height) / 8并向上取整*/
  for (j = Y / 8; j < (Y + Height - 1) / 8 + 1; j ++)
  {
    /*设置光标位置为相关页的指定列*/
    OLED_SetCursor(j, X);
    /*连续写入Width个数据，将显存数组的数据写入到OLED硬件*/
    OLED_WriteData(&OLED_DisplayBuf[j][X], Width);
  }
}

/**
 * @brief       OLED显存数组全部清零
 * @param       无
 * @retval      无
 * @note        调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
 */
void OLED_Clear(void)
{
  uint8_t i, j;
  
  for (j = 0; j < 8; j ++)              //遍历8页
  {
    for (i = 0; i < 128; i ++)          //遍历128列
    {
      OLED_DisplayBuf[j][i] = 0x00;     //将显存数组数据全部清零
    }
  }
}

/**
 * @brief       OLED显存数组部分清零
 * @param       X 指定区域左上角的横坐标，范围：0~127
 * @param       Y 指定区域左上角的纵坐标，范围：0~63
 * @param       Width 指定区域的宽度，    范围：0~128
 * @param       Height 指定区域的高度，   范围：0~64
 * @retval      无
 * @note        调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
 */
void OLED_ClearArea(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height)
{
  uint8_t i, j;
  
  /*参数检查，保证指定区域不会超出屏幕范围*/
  if (X > 127) {return;}
  if (Y > 63) {return;}
  if (X + Width > 128) {Width = 128 - X;}
  if (Y + Height > 64) {Height = 64 - Y;}
  
  for (j = Y; j < Y + Height; j ++)                     //遍历指定页
  {
    for (i = X; i < X + Width; i ++)                    //遍历指定列
    {
      OLED_DisplayBuf[j / 8][i] &= ~(0x01 << (j % 8));  //将显存数组指定数据清零
    }
  }
}

/**
 * @brief       OLED显存数组全部取反
 * @param       无
 * @retval      无
 * @note        调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
 */
void OLED_Reverse(void)
{
  uint8_t i, j;
  
  for (j = 0; j < 8; j ++)              //遍历8页
  {
    for (i = 0; i < 128; i ++)          //遍历128列
    {
      OLED_DisplayBuf[j][i] ^= 0xFF;    //将显存数组数据全部取反
    }
  }
}

/**
 * @brief       OLED显存数组部分取反
 * @param       X 指定区域左上角的横坐标，范围：0~127
 * @param       Y 指定区域左上角的纵坐标，范围：0~63
 * @param       Width 指定区域的宽度，    范围：0~128
 * @param       Height 指定区域的高度，   范围：0~64
 * @retval      无
 * @note        调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
 */
void OLED_ReverseArea(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height)
{
  uint8_t i, j;
  
  /*参数检查，保证指定区域不会超出屏幕范围*/
  if (X > 127) {return;}
  if (Y > 63) {return;}
  if (X + Width > 128) {Width = 128 - X;}
  if (Y + Height > 64) {Height = 64 - Y;}
  
  for (j = Y; j < Y + Height; j ++)                     //遍历指定页
  {
    for (i = X; i < X + Width; i ++)                    //遍历指定列
    {
      OLED_DisplayBuf[j / 8][i] ^= 0x01 << (j % 8);     //将显存数组指定数据取反
    }
  }
}

/**
 * @brief       OLED显示一个字符
 * @param       X 指定字符左上角的横坐标，范围：0~127
 * @param       Y 指定字符左上角的纵坐标，范围：0~63
 * @param       Char 指定要显示的字符，   范围：ASCII码可见字符
 * @param       FontSize 指定字体大小
 *              范围：OLED_6X8    宽6像素，高8像素
 *                    OLED_8X16   宽8像素，高16像素
 * @retval      无
 * @note        调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
 */
void OLED_ShowChar(uint8_t X, uint8_t Y, char Char, uint8_t FontSize)
{
  if (FontSize == OLED_8X16)      //字体为宽8像素，高16像素
  {
    /*将ASCII字模库OLED_F8x16的指定数据以8*16的图像格式显示*/
    OLED_ShowImage(X, Y, 8, 16, OLED_F8x16[Char - ' ']);
  }
  else if(FontSize == OLED_6X8)   //字体为宽6像素，高8像素
  {
    /*将ASCII字模库OLED_F6x8的指定数据以6*8的图像格式显示*/
    OLED_ShowImage(X, Y, 6, 8, OLED_F6x8[Char - ' ']);
  }
}

/**
 * @brief       OLED显示字符串
 * @param       X 指定字符左上角的横坐标， 范围：0~127
 * @param       Y 指定字符左上角的纵坐标， 范围：0~63
 * @param       String 指定要显示的字符串，范围：ASCII码可见字符组成的字符串
 * @param       FontSize 指定字体大小
 *              范围：OLED_6X8    宽6像素，高8像素
 *                    OLED_8X16   宽8像素，高16像素
 * @retval      无
 * @note        调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
 */
void OLED_ShowString(uint8_t X, uint8_t Y, char *String, uint8_t FontSize)
{
  uint8_t i;
  
  for (i = 0; String[i] != '\0'; i++)     //遍历字符串的每个字符
  {
    /*调用OLED_ShowChar函数，依次显示每个字符*/
    OLED_ShowChar(X + i * FontSize, Y, String[i], FontSize);
  }
}

/**
 * @brief       OLED显示数字（十进制，正整数）
 * @param       X 指定字符左上角的横坐标，范围：0~127
 * @param       Y 指定字符左上角的纵坐标，范围：0~63
 * @param       Number 指定要显示的数字， 范围：0~4294967295
 * @param       Length 指定数字的长度，   范围：0~10
 * @param       FontSize 指定字体大小
 *              范围：OLED_6X8    宽6像素，高8像素
 *                    OLED_8X16   宽8像素，高16像素
 * @retval      无
 * @note        调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
 */
void OLED_ShowNum(uint8_t X, uint8_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize)
{
  uint8_t i;
  
  for (i = 0; i < Length; i++)      //遍历数字的每一位
  {
    /*调用OLED_ShowChar函数，依次显示每个数字*/
    /*Number / OLED_Pow(10, Length - i - 1) % 10 可以十进制提取数字的每一位*/
    /*+ '0' 可将数字转换为字符格式*/
    OLED_ShowChar(X + i * FontSize, Y, Number / OLED_Pow(10, Length - i - 1) % 10 + '0', FontSize);
  }
}

/**
 * @brief       OLED显示有符号数字（十进制，整数）
 * @param       X 指定字符左上角的横坐标，范围：0~127
 * @param       Y 指定字符左上角的纵坐标，范围：0~63
 * @param       Number 指定要显示的数字， 范围：-2147483648~2147483647
 * @param       Length 指定数字的长度，   范围：0~10
 * @param       FontSize 指定字体大小
 *              范围：OLED_6X8    宽6像素，高8像素
 *                    OLED_8X16   宽8像素，高16像素
 * @retval      无
 * @note        调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
 */
void OLED_ShowSignedNum(uint8_t X, uint8_t Y, int32_t Number, uint8_t Length, uint8_t FontSize)
{
  uint8_t i;
  uint32_t Number1;
  
  if (Number >= 0)                        //数字大于等于0
  {
    OLED_ShowChar(X, Y, '+', FontSize);   //显示+号
    Number1 = Number;                     //Number1直接等于Number
  }
  else                                    //数字小于0
  {
    OLED_ShowChar(X, Y, '-', FontSize);   //显示-号
    Number1 = -Number;                    //Number1等于Number取负
  }
  
  for (i = 0; i < Length; i++)            //遍历数字的每一位
  {
    /*调用OLED_ShowChar函数，依次显示每个数字*/
    /*Number1 / OLED_Pow(10, Length - i - 1) % 10 可以十进制提取数字的每一位*/
    /*+ '0' 可将数字转换为字符格式*/
    OLED_ShowChar(X + (i + 1) * FontSize, Y, Number1 / OLED_Pow(10, Length - i - 1) % 10 + '0', FontSize);
  }
}

/**
 * @brief       OLED显示十六进制数字（十六进制，正整数）
 * @param       X 指定字符左上角的横坐标，范围：0~127
 * @param       Y 指定字符左上角的纵坐标，范围：0~63
 * @param       Number 指定要显示的数字， 范围：0x00000000~0xFFFFFFFF
 * @param       Length 指定数字的长度，   范围：0~8
 * @param       FontSize 指定字体大小
 *              范围：OLED_6X8    宽6像素，高8像素
 *                    OLED_8X16   宽8像素，高16像素
 * @retval      无
 * @note        调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
 */
void OLED_ShowHexNum(uint8_t X, uint8_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize)
{
  uint8_t i, SingleNumber;
  
  for (i = 0; i < Length; i++)            //遍历数字的每一位
  {
    /*以十六进制提取数字的每一位*/
    SingleNumber = Number / OLED_Pow(16, Length - i - 1) % 16;
    
    if (SingleNumber < 10)                //单个数字小于10
    {
      /*调用OLED_ShowChar函数，显示此数字*/
      /*+ '0' 可将数字转换为字符格式*/
      OLED_ShowChar(X + i * FontSize, Y, SingleNumber + '0', FontSize);
    }
    else                                  //单个数字大于10
    {
      /*调用OLED_ShowChar函数，显示此数字*/
      /*+ 'A' 可将数字转换为从A开始的十六进制字符*/
      OLED_ShowChar(X + i * FontSize, Y, SingleNumber - 10 + 'A', FontSize);
    }
  }
}

/**
 * @brief       OLED显示二进制数字（二进制，正整数）
 * @param       X 指定字符左上角的横坐标，范围：0~127
 * @param       Y 指定字符左上角的纵坐标，范围：0~63
 * @param       Number 指定要显示的数字， 范围：0x00000000~0xFFFFFFFF
 * @param       Length 指定数字的长度，   范围：0~16
 * @param       FontSize 指定字体大小
 *              范围：OLED_6X8    宽6像素，高8像素
 *                    OLED_8X16   宽8像素，高16像素
 * @retval      无
 * @note        调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
 */
void OLED_ShowBinNum(uint8_t X, uint8_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize)
{
  uint8_t i;
  
  for (i = 0; i < Length; i++)            //遍历数字的每一位
  {
    /*调用OLED_ShowChar函数，依次显示每个数字*/
    /*Number / OLED_Pow(2, Length - i - 1) % 2 可以二进制提取数字的每一位*/
    /*+ '0' 可将数字转换为字符格式*/
    OLED_ShowChar(X + i * FontSize, Y, Number / OLED_Pow(2, Length - i - 1) % 2 + '0', FontSize);
  }
}

/**
 * @brief       OLED显示浮点数字（十进制，小数）
 * @param       X 指定字符左上角的横坐标，范围：0~127
 * @param       Y 指定字符左上角的纵坐标，范围：0~63
 * @param       Number 指定要显示的数字， 范围：-4294967295.0~4294967295.0
 * @param       IntLength 指定数字的整数位长度，范围：0~10
 * @param       FraLength 指定数字的小数位长度，范围：0~9，小数进行四舍五入显示
 * @param       FontSize 指定字体大小
 *              范围：OLED_6X8    宽6像素，高8像素
 *                    OLED_8X16   宽8像素，高16像素
 * @retval      无
 * @note        调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
 */
void OLED_ShowFloatNum(uint8_t X, uint8_t Y, double Number, uint8_t IntLength, uint8_t FraLength, uint8_t FontSize)
{
  uint32_t PowNum, IntNum, FraNum;
  
  if (Number >= 0)                        //数字大于等于0
  {
    OLED_ShowChar(X, Y, '+', FontSize);   //显示+号
  }
  else                                    //数字小于0
  {
    OLED_ShowChar(X, Y, '-', FontSize);   //显示-号
    Number = -Number;                     //Number取负
  }
  
  /*提取整数部分和小数部分*/
  IntNum = Number;                        //直接赋值给整型变量，提取整数
  Number -= IntNum;                       //将Number的整数减掉，防止之后将小数乘到整数时因数过大造成错误
  PowNum = OLED_Pow(10, FraLength);       //根据指定小数的位数，确定乘数
  FraNum = round(Number * PowNum);        //将小数乘到整数，同时四舍五入，避免显示误差
  IntNum += FraNum / PowNum;              //若四舍五入造成了进位，则需要再加给整数
  
  /*显示整数部分*/
  OLED_ShowNum(X + FontSize, Y, IntNum, IntLength, FontSize);

  /*显示小数点*/
  OLED_ShowChar(X + (IntLength + 1) * FontSize, Y, '.', FontSize);

  /*显示小数部分*/
  OLED_ShowNum(X + (IntLength + 2) * FontSize, Y, FraNum, FraLength, FontSize);
}

/**
 * @brief       OLED显示汉字串
 * @param       X 指定字符左上角的横坐标，  范围：0~127
 * @param       Y 指定字符左上角的纵坐标，  范围：0~63
 * @param       Chinese 指定要显示的汉字串，范围：必须全部为汉字或者全角字符，不要加入任何半角字符
 *              显示的汉字需要在OLED_Data.c里的OLED_CF16x16数组定义
 *              未找到指定汉字时，会显示默认图形（一个方框，内部一个问号）
 * @retval      无
 * @note        调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
 */
void OLED_ShowChinese(uint8_t X, uint8_t Y, char *Chinese)
{
  uint8_t pChinese = 0;
  uint8_t pIndex;
  uint8_t i;
  
  char SingleChinese[OLED_CHN_CHAR_WIDTH + 1] = {0};
  
  for (i = 0; Chinese[i] != '\0'; i ++)                 //遍历汉字串
  {
    SingleChinese[pChinese] = Chinese[i];               //提取汉字串数据到单个汉字数组
    pChinese ++;                                        //计次自增
    
    /*当提取次数到达OLED_CHN_CHAR_WIDTH时，即代表提取到了一个完整的汉字*/
    if (pChinese >= OLED_CHN_CHAR_WIDTH)
    {
      pChinese = 0;                                     //计次归零
      
      /*遍历整个汉字字模库，寻找匹配的汉字*/
      /*如果找到最后一个汉字（定义为空字符串），则表示汉字未在字模库定义，停止寻找*/
      for (pIndex = 0; strcmp(OLED_CF16x16[pIndex].Index, "") != 0; pIndex ++)
      {
        /*找到匹配的汉字*/
        if (strcmp(OLED_CF16x16[pIndex].Index, SingleChinese) == 0)
        {
          break;                                        //跳出循环，此时pIndex的值为指定汉字的索引
        }
      }
      
      /*将汉字字模库OLED_CF16x16的指定数据以16*16的图像格式显示*/
      OLED_ShowImage(X + ((i + 1) / OLED_CHN_CHAR_WIDTH - 1) * 16, Y, 16, 16, OLED_CF16x16[pIndex].Data);
    }
  }
}

/**
 * @brief       OLED显示图像
 * @param       X 指定区域左上角的横坐标，范围：0~127
 * @param       Y 指定区域左上角的纵坐标，范围：0~63
 * @param       Width 指定区域的宽度，    范围：0~128
 * @param       Height 指定区域的高度，   范围：0~64
 * @param       Image 指定要显示的图像
 * @retval      无
 * @note        调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
 */
void OLED_ShowImage(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height, const uint8_t *Image)
{
  uint8_t i, j;
  
  /*参数检查，保证指定图像不会超出屏幕范围*/
  if (X > 127) {return;}
  if (Y > 63) {return;}
  
  /*将图像所在区域清空*/
  OLED_ClearArea(X, Y, Width, Height);
  
  /*遍历指定图像涉及的相关页*/
  /*(Height - 1) / 8 + 1的目的是Height / 8并向上取整*/
  for (j = 0; j < (Height - 1) / 8 + 1; j ++)
  {
    /*遍历指定图像涉及的相关列*/
    for (i = 0; i < Width; i ++)
    {
      /*超出边界，则跳过显示*/
      if (X + i > 127) {break;}
      if (Y / 8 + j > 7) {return;}
      
      /*显示图像在当前页的内容*/
      OLED_DisplayBuf[Y / 8 + j][X + i] |= Image[j * Width + i] << (Y % 8);
      
      /*超出边界，则跳过显示*/
      /*使用continue的目的是，下一页超出边界时，上一页的后续内容还需要继续显示*/
      if (Y / 8 + j + 1 > 7) {continue;}
      
      /*显示图像在下一页的内容*/
      OLED_DisplayBuf[Y / 8 + j + 1][X + i] |= Image[j * Width + i] >> (8 - Y % 8);
    }
  }
}

/**
 * @brief       OLED使用printf函数打印格式化字符串
 * @param       X 指定字符左上角的横坐标，范围：0~127
 * @param       Y 指定字符左上角的纵坐标，范围：0~63
 * @param       FontSize 指定字体大小
 *              范围：OLED_6X8    宽6像素，高8像素
 *                    OLED_8X16   宽8像素，高16像素
 * @param       format 指定要显示的格式化字符串，范围：ASCII码可见字符组成的字符串
 * @param       ... 格式化字符串参数列表
 * @retval      无
 * @note        调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
 */
void OLED_Printf(uint8_t X, uint8_t Y, uint8_t FontSize, char *format, ...)
{
  char String[30];                              //定义字符数组
  
  va_list arg;                                  //定义可变参数列表数据类型的变量arg
  va_start(arg, format);                        //从format开始，接收参数列表到arg变量
  vsprintf(String, format, arg);                //使用vsprintf打印格式化字符串和参数列表到字符数组中
  va_end(arg);                                  //结束变量arg
  OLED_ShowString(X, Y, String, FontSize);      //OLED显示字符数组（字符串）
}

/**
 * @brief       OLED在指定位置画一个点
 * @param       X 指定区域左上角的横坐标，范围：0~127
 * @param       Y 指定区域左上角的纵坐标，范围：0~63
 * @retval      无
 * @note        调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
 */
void OLED_DrawPoint(uint8_t X, uint8_t Y)
{
  /*参数检查，保证指定位置不会超出屏幕范围*/
  if (X > 127) {return;}
  if (Y > 63) {return;}
  
  /*将显存数组指定位置的一个Bit数据置1*/
  OLED_DisplayBuf[Y / 8][X] |= 0x01 << (Y % 8);
}

/**
 * @brief       OLED获取指定位置点的值
 * @param       X 指定区域左上角的横坐标，范围：0~127
 * @param       Y 指定区域左上角的纵坐标，范围：0~63
 * @retval      指定位置点是否处于点亮状态，0：熄灭，1：点亮
 * @note        无
 */
uint8_t OLED_GetPoint(uint8_t X, uint8_t Y)
{
  /*参数检查，保证指定位置不会超出屏幕范围*/
  if (X > 127) {return 0;}
  if (Y > 63) {return 0;}
  
  /*判断指定位置的数据*/
  if (OLED_DisplayBuf[Y / 8][X] & 0x01 << (Y % 8))
  {
    return 1;                   //为1，返回1
  }
  
  return 0;                     //否则，返回0
}

/**
 * @brief       OLED画线
 * @param       X0 指定一个端点的横坐标，  范围：0~127
 * @param       Y0 指定一个端点的纵坐标，  范围：0~63
 * @param       X1 指定另一个端点的横坐标，范围：0~127
 * @param       Y1 指定另一个端点的纵坐标，范围：0~63
 * @retval      无
 * @note        调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
 */
void OLED_DrawLine(uint8_t X0, uint8_t Y0, uint8_t X1, uint8_t Y1)
{
  int16_t x, y, dx, dy, d, incrE, incrNE, temp;
  int16_t x0 = X0, y0 = Y0, x1 = X1, y1 = Y1;
  uint8_t yflag = 0, xyflag = 0;
  
  if (y0 == y1)               //横线单独处理
  {
    /*0号点X坐标大于1号点X坐标，则交换两点X坐标*/
    if (x0 > x1) {temp = x0; x0 = x1; x1 = temp;}
    
    /*遍历X坐标*/
    for (x = x0; x <= x1; x ++)
    {
      OLED_DrawPoint(x, y0);  //依次画点
    }
  }
  else if (x0 == x1)          //竖线单独处理
  {
    /*0号点Y坐标大于1号点Y坐标，则交换两点Y坐标*/
    if (y0 > y1) {temp = y0; y0 = y1; y1 = temp;}
    
    /*遍历Y坐标*/
    for (y = y0; y <= y1; y ++)
    {
      OLED_DrawPoint(x0, y);  //依次画点
    }
  }
  else                        //斜线
  {
    /*使用Bresenham算法画直线，可以避免耗时的浮点运算，效率更高*/
    
    if (x0 > x1)              //0号点X坐标大于1号点X坐标
    {
      /*交换两点坐标*/
      /*交换后不影响画线，但是画线方向由第一、二、三、四象限变为第一、四象限*/
      temp = x0; x0 = x1; x1 = temp;
      temp = y0; y0 = y1; y1 = temp;
    }
    
    if (y0 > y1)              //0号点Y坐标大于1号点Y坐标
    {
      /*将Y坐标取负*/
      /*取负后影响画线，但是画线方向由第一、四象限变为第一象限*/
      y0 = -y0;
      y1 = -y1;
      
      /*置标志位yflag，记住当前变换，在后续实际画线时，再将坐标换回来*/
      yflag = 1;
    }
    
    if (y1 - y0 > x1 - x0)    //画线斜率大于1
    {
      /*将X坐标与Y坐标互换*/
      /*互换后影响画线，但是画线方向由第一象限0~90度范围变为第一象限0~45度范围*/
      temp = x0; x0 = y0; y0 = temp;
      temp = x1; x1 = y1; y1 = temp;
      
      /*置标志位xyflag，记住当前变换，在后续实际画线时，再将坐标换回来*/
      xyflag = 1;
    }
    
    /*以下为Bresenham算法画直线*/
    /*算法要求，画线方向必须为第一象限0~45度范围*/
    dx = x1 - x0;
    dy = y1 - y0;
    incrE = 2 * dy;
    incrNE = 2 * (dy - dx);
    d = 2 * dy - dx;
    x = x0;
    y = y0;
    
    /*画起始点，同时判断标志位，将坐标换回来*/
    if (yflag && xyflag){OLED_DrawPoint(y, -x);}
    else if (yflag)     {OLED_DrawPoint(x, -y);}
    else if (xyflag)    {OLED_DrawPoint(y, x);}
    else                {OLED_DrawPoint(x, y);}
    
    while (x < x1)            //遍历X轴的每个点
    {
      x ++;
      if (d < 0)              //下一个点在当前点东方
      {
        d += incrE;
      }
      else                    //下一个点在当前点东北方
      {
        y ++;
        d += incrNE;
      }
      
      /*画每一个点，同时判断标志位，将坐标换回来*/
      if (yflag && xyflag){OLED_DrawPoint(y, -x);}
      else if (yflag)     {OLED_DrawPoint(x, -y);}
      else if (xyflag)    {OLED_DrawPoint(y, x);}
      else                {OLED_DrawPoint(x, y);}
    }
  }
}

/**
 * @brief       OLED画矩形
 * @param       X 指定矩形左上角的横坐标，范围：0~127
 * @param       Y 指定矩形左上角的纵坐标，范围：0~63
 * @param       Width 指定矩形的宽度，    范围：0~128
 * @param       Height 指定矩形的高度，   范围：0~64
 * @param       IsFilled 指定矩形是否填充
 *              范围：OLED_UNFILLED   不填充
 *                    OLED_FILLED     填充
 * @retval      无
 * @note        调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
 */
void OLED_DrawRectangle(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height, uint8_t IsFilled)
{
  uint8_t i, j;
  
  if (!IsFilled)            //指定矩形不填充
  {
    /*遍历上下X坐标，画矩形上下两条线*/
    for (i = X; i < X + Width; i ++)
    {
      OLED_DrawPoint(i, Y);
      OLED_DrawPoint(i, Y + Height - 1);
    }
    /*遍历左右Y坐标，画矩形左右两条线*/
    for (i = Y; i < Y + Height; i ++)
    {
      OLED_DrawPoint(X, i);
      OLED_DrawPoint(X + Width - 1, i);
    }
  }
  else                      //指定矩形填充
  {
    /*遍历X坐标*/
    for (i = X; i < X + Width; i ++)
    {
      /*遍历Y坐标*/
      for (j = Y; j < Y + Height; j ++)
      {
        /*在指定区域画点，填充满矩形*/
        OLED_DrawPoint(i, j);
      }
    }
  }
}

/**
 * @brief       OLED画三角形
 * @param       X0 指定第一个端点的横坐标，范围：0~127
 * @param       Y0 指定第一个端点的纵坐标，范围：0~63
 * @param       X1 指定第二个端点的横坐标，范围：0~127
 * @param       Y1 指定第二个端点的纵坐标，范围：0~63
 * @param       X2 指定第三个端点的横坐标，范围：0~127
 * @param       Y2 指定第三个端点的纵坐标，范围：0~63
 * @param       IsFilled 指定三角形是否填充
 *              范围：OLED_UNFILLED   不填充
 *                    OLED_FILLED     填充
 * @retval      无
 * @note        调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
 */
void OLED_DrawTriangle(uint8_t X0, uint8_t Y0, uint8_t X1, uint8_t Y1, uint8_t X2, uint8_t Y2, uint8_t IsFilled)
{
  uint8_t minx = X0, miny = Y0, maxx = X0, maxy = Y0;
  uint8_t i, j;
  int16_t vx[] = {X0, X1, X2};
  int16_t vy[] = {Y0, Y1, Y2};
  
  if (!IsFilled)            //指定三角形不填充
  {
    /*调用画线函数，将三个点用直线连接*/
    OLED_DrawLine(X0, Y0, X1, Y1);
    OLED_DrawLine(X0, Y0, X2, Y2);
    OLED_DrawLine(X1, Y1, X2, Y2);
  }
  else                      //指定三角形填充
  {
    /*找到三个点最小的X、Y坐标*/
    if (X1 < minx) {minx = X1;}
    if (X2 < minx) {minx = X2;}
    if (Y1 < miny) {miny = Y1;}
    if (Y2 < miny) {miny = Y2;}
    
    /*找到三个点最大的X、Y坐标*/
    if (X1 > maxx) {maxx = X1;}
    if (X2 > maxx) {maxx = X2;}
    if (Y1 > maxy) {maxy = Y1;}
    if (Y2 > maxy) {maxy = Y2;}
    
    /*最小最大坐标之间的矩形为可能需要填充的区域*/
    /*遍历此区域中所有的点*/
    /*遍历X坐标*/
    for (i = minx; i <= maxx; i ++)
    {
      /*遍历Y坐标*/
      for (j = miny; j <= maxy; j ++)
      {
        /*调用OLED_pnpoly，判断指定点是否在指定三角形之中*/
        /*如果在，则画点，如果不在，则不做处理*/
        if (OLED_pnpoly(3, vx, vy, i, j)) {OLED_DrawPoint(i, j);}
      }
    }
  }
}

/**
 * @brief       OLED画圆
 * @param       X 指定圆的圆心横坐标，范围：0~127
 * @param       Y 指定圆的圆心纵坐标，范围：0~63
 * @param       Radius 指定圆的半径， 范围：0~255
 * @param       IsFilled 指定圆是否填充
 *              范围：OLED_UNFILLED   不填充
 *                    OLED_FILLED     填充
 * @retval      无
 * @note        调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
 */
void OLED_DrawCircle(uint8_t X, uint8_t Y, uint8_t Radius, uint8_t IsFilled)
{
  int16_t x, y, d, j;
  
  /*使用Bresenham算法画圆，可以避免耗时的浮点运算，效率更高*/
  
  d = 1 - Radius;
  x = 0;
  y = Radius;
  
  /*画每个八分之一圆弧的起始点*/
  OLED_DrawPoint(X + x, Y + y);
  OLED_DrawPoint(X - x, Y - y);
  OLED_DrawPoint(X + y, Y + x);
  OLED_DrawPoint(X - y, Y - x);
  
  if (IsFilled)             //指定圆填充
  {
    /*遍历起始点Y坐标*/
    for (j = -y; j < y; j ++)
    {
      /*在指定区域画点，填充部分圆*/
      OLED_DrawPoint(X, Y + j);
    }
  }
  
  while (x < y)             //遍历X轴的每个点
  {
    x ++;
    if (d < 0)              //下一个点在当前点东方
    {
      d += 2 * x + 1;
    }
    else                    //下一个点在当前点东南方
    {
      y --;
      d += 2 * (x - y) + 1;
    }
    
    /*画每个八分之一圆弧的点*/
    OLED_DrawPoint(X + x, Y + y);
    OLED_DrawPoint(X + y, Y + x);
    OLED_DrawPoint(X - x, Y - y);
    OLED_DrawPoint(X - y, Y - x);
    OLED_DrawPoint(X + x, Y - y);
    OLED_DrawPoint(X + y, Y - x);
    OLED_DrawPoint(X - x, Y + y);
    OLED_DrawPoint(X - y, Y + x);
    
    if (IsFilled)           //指定圆填充
    {
      /*遍历中间部分*/
      for (j = -y; j < y; j ++)
      {
        /*在指定区域画点，填充部分圆*/
        OLED_DrawPoint(X + x, Y + j);
        OLED_DrawPoint(X - x, Y + j);
      }
      
      /*遍历两侧部分*/
      for (j = -x; j < x; j ++)
      {
        /*在指定区域画点，填充部分圆*/
        OLED_DrawPoint(X - y, Y + j);
        OLED_DrawPoint(X + y, Y + j);
      }
    }
  }
}

/**
 * @brief       OLED画椭圆
 * @param       X 指定椭圆的圆心横坐标，  范围：0~127
 * @param       Y 指定椭圆的圆心纵坐标，  范围：0~63
 * @param       A 指定椭圆的横向半轴长度，范围：0~255
 * @param       B 指定椭圆的纵向半轴长度，范围：0~255
 * @param       IsFilled 指定椭圆是否填充
 *              范围：OLED_UNFILLED   不填充
 *                    OLED_FILLED     填充
 * @retval      无
 * @note        调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
 */
void OLED_DrawEllipse(uint8_t X, uint8_t Y, uint8_t A, uint8_t B, uint8_t IsFilled)
{
  int16_t x, y, j;
  int16_t a = A, b = B;
  float d1, d2;
  
  /*使用Bresenham算法画椭圆，可以避免部分耗时的浮点运算，效率更高*/
  x = 0;
  y = b;
  d1 = b * b + a * a * (-b + 0.5);
  
  if (IsFilled)             //指定椭圆填充
  {
    /*遍历起始点Y坐标*/
    for (j = -y; j < y; j ++)
    {
      /*在指定区域画点，填充部分椭圆*/
      OLED_DrawPoint(X, Y + j);
      OLED_DrawPoint(X, Y + j);
    }
  }
  
  /*画椭圆弧的起始点*/
  OLED_DrawPoint(X + x, Y + y);
  OLED_DrawPoint(X - x, Y - y);
  OLED_DrawPoint(X - x, Y + y);
  OLED_DrawPoint(X + x, Y - y);
  
  /*画椭圆中间部分*/
  while (b * b * (x + 1) < a * a * (y - 0.5))
  {
    if (d1 <= 0)            //下一个点在当前点东方
    {
      d1 += b * b * (2 * x + 3);
    }
    else                    //下一个点在当前点东南方
    {
      d1 += b * b * (2 * x + 3) + a * a * (-2 * y + 2);
      y --;
    }
    
    x ++;
    
    if (IsFilled)           //指定椭圆填充
    {
      /*遍历中间部分*/
      for (j = -y; j < y; j ++)
      {
        /*在指定区域画点，填充部分椭圆*/
        OLED_DrawPoint(X + x, Y + j);
        OLED_DrawPoint(X - x, Y + j);
      }
    }
    
    /*画椭圆中间部分圆弧*/
    OLED_DrawPoint(X + x, Y + y);
    OLED_DrawPoint(X - x, Y - y);
    OLED_DrawPoint(X - x, Y + y);
    OLED_DrawPoint(X + x, Y - y);
  }
  
  /*画椭圆两侧部分*/
  d2 = b * b * (x + 0.5) * (x + 0.5) + a * a * (y - 1) * (y - 1) - a * a * b * b;
  
  while (y > 0)
  {
    if (d2 <= 0)          //下一个点在当前点东方
    {
      d2 += b * b * (2 * x + 2) + a * a * (-2 * y + 3);
      x ++;
    }
    else                  //下一个点在当前点东南方
    {
      d2 += a * a * (-2 * y + 3);
    }
    
    y --;
    
    if (IsFilled)         //指定椭圆填充
    {
      /*遍历两侧部分*/
      for (j = -y; j < y; j ++)
      {
        /*在指定区域画点，填充部分椭圆*/
        OLED_DrawPoint(X + x, Y + j);
        OLED_DrawPoint(X - x, Y + j);
      }
    }
    
    /*画椭圆两侧部分圆弧*/
    OLED_DrawPoint(X + x, Y + y);
    OLED_DrawPoint(X - x, Y - y);
    OLED_DrawPoint(X - x, Y + y);
    OLED_DrawPoint(X + x, Y - y);
  }
}

/**
 * @brief       OLED画圆弧
 * @param       X 指定圆弧的圆心横坐标，范围：0~127
 * @param       Y 指定圆弧的圆心纵坐标，范围：0~63
 * @param       Radius 指定圆弧的半径，范围：0~255
 * @param       StartAngle 指定圆弧的起始角度，范围：-180~180
 *              水平向右为0度，水平向左为180度或-180度，下方为正数，上方为负数，顺时针旋转
 * @param       EndAngle 指定圆弧的终止角度，范围：-180~180
 *              水平向右为0度，水平向左为180度或-180度，下方为正数，上方为负数，顺时针旋转
 * @param       IsFilled 指定圆弧是否填充，填充后为扇形
 *              范围：OLED_UNFILLED   不填充
 *                    OLED_FILLED     填充
 * @retval      无
 * @note        调用此函数后，要想真正地呈现在屏幕上，还需调用更新函数
 */
void OLED_DrawArc(uint8_t X, uint8_t Y, uint8_t Radius, int16_t StartAngle, int16_t EndAngle, uint8_t IsFilled)
{
  int16_t x, y, d, j;
  
  /*此函数借用Bresenham算法画圆的方法*/
  
  d = 1 - Radius;
  x = 0;
  y = Radius;
  
  /*在画圆的每个点时，判断指定点是否在指定角度内，在，则画点，不在，则不做处理*/
  if (OLED_IsInAngle(x, y, StartAngle, EndAngle))   {OLED_DrawPoint(X + x, Y + y);}
  if (OLED_IsInAngle(-x, -y, StartAngle, EndAngle)) {OLED_DrawPoint(X - x, Y - y);}
  if (OLED_IsInAngle(y, x, StartAngle, EndAngle))   {OLED_DrawPoint(X + y, Y + x);}
  if (OLED_IsInAngle(-y, -x, StartAngle, EndAngle)) {OLED_DrawPoint(X - y, Y - x);}
  
  if (IsFilled)             //指定圆弧填充
  {
    /*遍历起始点Y坐标*/
    for (j = -y; j < y; j ++)
    {
      /*在填充圆的每个点时，判断指定点是否在指定角度内，在，则画点，不在，则不做处理*/
      if (OLED_IsInAngle(0, j, StartAngle, EndAngle)) {OLED_DrawPoint(X, Y + j);}
    }
  }
  
  while (x < y)             //遍历X轴的每个点
  {
    x ++;
    
    if (d < 0)              //下一个点在当前点东方
    {
      d += 2 * x + 1;
    }
    else                    //下一个点在当前点东南方
    {
      y --;
      d += 2 * (x - y) + 1;
    }
    
    /*在画圆的每个点时，判断指定点是否在指定角度内，在，则画点，不在，则不做处理*/
    if (OLED_IsInAngle( x,  y, StartAngle, EndAngle)) {OLED_DrawPoint(X + x, Y + y);}
    if (OLED_IsInAngle( y,  x, StartAngle, EndAngle)) {OLED_DrawPoint(X + y, Y + x);}
    if (OLED_IsInAngle(-x, -y, StartAngle, EndAngle)) {OLED_DrawPoint(X - x, Y - y);}
    if (OLED_IsInAngle(-y, -x, StartAngle, EndAngle)) {OLED_DrawPoint(X - y, Y - x);}
    if (OLED_IsInAngle( x, -y, StartAngle, EndAngle)) {OLED_DrawPoint(X + x, Y - y);}
    if (OLED_IsInAngle( y, -x, StartAngle, EndAngle)) {OLED_DrawPoint(X + y, Y - x);}
    if (OLED_IsInAngle(-x,  y, StartAngle, EndAngle)) {OLED_DrawPoint(X - x, Y + y);}
    if (OLED_IsInAngle(-y,  x, StartAngle, EndAngle)) {OLED_DrawPoint(X - y, Y + x);}
    
    if (IsFilled)           //指定圆弧填充
    {
      /*遍历中间部分*/
      for (j = -y; j < y; j ++)
      {
        /*在填充圆的每个点时，判断指定点是否在指定角度内，在，则画点，不在，则不做处理*/
        if (OLED_IsInAngle( x, j, StartAngle, EndAngle)) {OLED_DrawPoint(X + x, Y + j);}
        if (OLED_IsInAngle(-x, j, StartAngle, EndAngle)) {OLED_DrawPoint(X - x, Y + j);}
      }
      
      /*遍历两侧部分*/
      for (j = -x; j < x; j ++)
      {
        /*在填充圆的每个点时，判断指定点是否在指定角度内，在，则画点，不在，则不做处理*/
        if (OLED_IsInAngle(-y, j, StartAngle, EndAngle)) {OLED_DrawPoint(X - y, Y + j);}
        if (OLED_IsInAngle( y, j, StartAngle, EndAngle)) {OLED_DrawPoint(X + y, Y + j);}
      }
    }
  }
}

/**
 * @brief       OLED测试起始函数
 * @param       无
 * @retval      无
 * @note        无
 */
void OLED_Test_Start(void)
{
  /*在(0, 0)位置显示字符'A'，字体大小为8*16点阵*/
  OLED_ShowChar(0, 0, 'B', OLED_8X16);
  
  /*在(16, 0)位置显示字符串"Hello World!"，字体大小为8*16点阵*/
  OLED_ShowString(16, 0, "Hello World!", OLED_8X16);
  
  /*在(0, 18)位置显示字符'A'，字体大小为6*8点阵*/
  OLED_ShowChar(0, 18, 'A', OLED_6X8);
  
  /*在(16, 18)位置显示字符串"Hello World!"，字体大小为6*8点阵*/
  OLED_ShowString(16, 18, "Hello World!", OLED_6X8);
  
  /*在(0, 28)位置显示数字12345，长度为5，字体大小为6*8点阵*/
  OLED_ShowNum(0, 28, 12345, 5, OLED_6X8);
  
  /*在(40, 28)位置显示有符号数字-66，长度为2，字体大小为6*8点阵*/
  OLED_ShowSignedNum(40, 28, -66, 2, OLED_6X8);
  
  /*在(70, 28)位置显示十六进制数字0xA5A5，长度为4，字体大小为6*8点阵*/
  OLED_ShowHexNum(70, 28, 0xA5A5, 4, OLED_6X8);
  
  /*在(0, 38)位置显示二进制数字0xA5，长度为8，字体大小为6*8点阵*/
  OLED_ShowBinNum(0, 38, 0xA5, 8, OLED_6X8);
  
  /*在(60, 38)位置显示浮点数字123.45，整数部分长度为3，小数部分长度为2，字体大小为6*8点阵*/
  OLED_ShowFloatNum(60, 38, -1243.45, 4, 2, OLED_6X8);
  
  /*在(0, 48)位置显示汉字串"你好，世界。"，字体大小为固定的16*16点阵*/
  OLED_ShowChinese(0, 48, "任兆福");
  
  /*在(96, 18)位置打印格式化字符串，字体大小为6*8点阵，格式化字符串为"[%02d]"*/
  OLED_Printf(96, 18, OLED_6X8, "%+03d", -123);
  
  /*调用OLED_Update函数，将OLED显存数组的内容更新到OLED硬件进行显示*/
  OLED_Update();
  
  /*延时2000ms，观察现象*/
  HAL_Delay(2000);
  
  /*清空OLED显存数组*/
  OLED_Clear();
  
  /*在(5, 8)位置画点*/
  OLED_DrawPoint(5, 8);
  
  /*获取(5, 8)位置的点*/
  if (OLED_GetPoint(5, 8))
  {
    /*如果指定点点亮，则在(10, 4)位置显示字符串"YES"，字体大小为6*8点阵*/
    OLED_ShowString(10, 4, "YES", OLED_6X8);
  }
  else
  {
    /*如果指定点未点亮，则在(10, 4)位置显示字符串"NO "，字体大小为6*8点阵*/
    OLED_ShowString(10, 4, "NO ", OLED_6X8);
  }
  
  /*在(40, 0)和(127, 15)位置之间画直线*/
  OLED_DrawLine(40, 0, 127, 15);
  
  /*在(40, 15)和(127, 0)位置之间画直线*/
  OLED_DrawLine(40, 15, 127, 0);
  
  /*在(0, 20)位置画矩形，宽12像素，高15像素，未填充*/
  OLED_DrawRectangle(0, 20, 12, 15, OLED_UNFILLED);
  
  /*在(0, 40)位置画矩形，宽12像素，高15像素，填充*/
  OLED_DrawRectangle(0, 40, 12, 15, OLED_FILLED);
  
  /*在(20, 20)、(40, 25)和(30, 35)位置之间画三角形，未填充*/
  OLED_DrawTriangle(20, 20, 40, 25, 30, 35, OLED_UNFILLED);
  
  /*在(20, 40)、(40, 45)和(30, 55)位置之间画三角形，填充*/
  OLED_DrawTriangle(20, 40, 40, 45, 30, 55, OLED_FILLED);
  
  /*在(55, 27)位置画圆，半径8像素，未填充*/
  OLED_DrawCircle(55, 27, 8, OLED_UNFILLED);
  
  /*在(55, 47)位置画圆，半径8像素，填充*/
  OLED_DrawCircle(55, 47, 8, OLED_FILLED);
  
  /*在(82, 27)位置画椭圆，横向半轴12像素，纵向半轴8像素，未填充*/
  OLED_DrawEllipse(82, 27, 12, 8, OLED_UNFILLED);
  
  /*在(82, 47)位置画椭圆，横向半轴12像素，纵向半轴8像素，填充*/
  OLED_DrawEllipse(82, 47, 12, 8, OLED_FILLED);
  
  /*在(110, 18)位置画圆弧，半径15像素，起始角度25度，终止角度125度，未填充*/
  OLED_DrawArc(110, 18, 15, 25, 125, OLED_UNFILLED);
  
  /*在(110, 38)位置画圆弧，半径15像素，起始角度25度，终止角度125度，填充*/
  OLED_DrawArc(110, 38, 15, 25, 125, OLED_FILLED);
  
  /*调用OLED_Update函数，将OLED显存数组的内容更新到OLED硬件进行显示*/
  OLED_Update();
  
  /*延时2000ms，观察现象*/
  HAL_Delay(2000);
}

/**
 * @brief       OLED测试起始函数
 * @param       无
 * @retval      无
 * @note        无
 */
void OLED_Test(void)
{
  for (uint8_t i = 0; i < 4; i ++)
  {
    /*将OLED显存数组部分数据取反，从(0, i * 16)位置开始，宽128像素，高16像素*/
    OLED_ReverseArea(0, i * 16, 128, 16);
    
    /*调用OLED_Update函数，将OLED显存数组的内容更新到OLED硬件进行显示*/
    OLED_Update();
    
    /*延时1000ms，观察现象*/
    HAL_Delay(1000);
    
    /*把取反的内容翻转回来*/
    OLED_ReverseArea(0, i * 16, 128, 16);
  }
  
  /*将OLED显存数组全部数据取反*/
  OLED_Reverse();
  
  /*调用OLED_Update函数，将OLED显存数组的内容更新到OLED硬件进行显示*/
  OLED_Update();
  
  /*延时1000ms，观察现象*/
  HAL_Delay(1000);
}
