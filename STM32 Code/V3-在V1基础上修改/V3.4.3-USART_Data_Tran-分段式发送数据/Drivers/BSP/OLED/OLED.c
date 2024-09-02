#include "./BSP/OLED/OLED.h"

uint8_t OLED_DisplayBuf[8][128];

#if( OLED_Communication_Mode == 0 )
/* OLED_4Pin_IIC */

/**
 * @brief       OLEDдSCL�ߵ͵�ƽ
 * @param       Ҫд��SCL�ĵ�ƽֵ����Χ��0/1
 * @retval      ��
 * @note        ���ϲ㺯����ҪдSCLʱ���˺����ᱻ����
 */
void OLED_W_SCL(uint8_t BitValue)
{
  HAL_GPIO_WritePin(OLED_SCL_GPIO_Port, OLED_SCL_Pin, (GPIO_PinState)BitValue);
}

/**
 * @brief       OLEDдSDA�ߵ͵�ƽ
 * @param       Ҫд��SDA�ĵ�ƽֵ����Χ��0/1
 * @retval      ��
 * @note        ���ϲ㺯����ҪдSDAʱ���˺����ᱻ����
 */
void OLED_W_SDA(uint8_t BitValue)
{
  HAL_GPIO_WritePin(OLED_SDA_GPIO_Port, OLED_SDA_Pin, (GPIO_PinState)BitValue);
}

/**
 * @brief       I2C��ʼ
 * @param       ��
 * @retval      ��
 * @note        ��
 */
void OLED_I2C_Start(void)
{
  OLED_W_SDA(1);
  OLED_W_SCL(1);
  OLED_W_SDA(0);
  OLED_W_SCL(0);
}

/**
 * @brief       I2C��ֹ
 * @param       ��
 * @retval      ��
 * @note        ��
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
 * @brief       OLEDдD0��CLK���ߵ͵�ƽ
 * @param       Ҫд��D0�ĵ�ƽֵ����Χ��0/1
 * @retval      ��
 * @note        ���ϲ㺯����ҪдD0ʱ���˺����ᱻ����
 *              �û���Ҫ���ݲ��������ֵ����D0��Ϊ�ߵ�ƽ���ߵ͵�ƽ
 *              ����������0ʱ����D0Ϊ�͵�ƽ������������1ʱ����D0Ϊ�ߵ�ƽ
 */
void OLED_W_D0(uint8_t BitValue)
{
  /*����BitValue��ֵ����D0�øߵ�ƽ���ߵ͵�ƽ*/
  HAL_GPIO_WritePin(OLED_D0_GPIO_Port, OLED_D0_Pin, (GPIO_PinState)BitValue);
}

/**
 * @brief       OLEDдD1��MOSI���ߵ͵�ƽ
 * @param       Ҫд��D1�ĵ�ƽֵ����Χ��0/1
 * @retval      ��
 * @note        ���ϲ㺯����ҪдD1ʱ���˺����ᱻ����
 *              �û���Ҫ���ݲ��������ֵ����D1��Ϊ�ߵ�ƽ���ߵ͵�ƽ
 *              ����������0ʱ����D1Ϊ�͵�ƽ������������1ʱ����D1Ϊ�ߵ�ƽ
 */
void OLED_W_D1(uint8_t BitValue)
{
  /*����BitValue��ֵ����D0�øߵ�ƽ���ߵ͵�ƽ*/
  HAL_GPIO_WritePin(OLED_D1_GPIO_Port, OLED_D1_Pin, (GPIO_PinState)BitValue);
}

/**
 * @brief       OLEDдRES�ߵ͵�ƽ
 * @param       Ҫд��RES�ĵ�ƽֵ����Χ��0/1
 * @retval      ��
 * @note        ���ϲ㺯����ҪдRESʱ���˺����ᱻ����
 *              �û���Ҫ���ݲ��������ֵ����RES��Ϊ�ߵ�ƽ���ߵ͵�ƽ
 *              ����������0ʱ����RESΪ�͵�ƽ������������1ʱ����RESΪ�ߵ�ƽ
 */
void OLED_W_RES(uint8_t BitValue)
{
  /*����BitValue��ֵ����RES�øߵ�ƽ���ߵ͵�ƽ*/
  HAL_GPIO_WritePin(OLED_RES_GPIO_Port, OLED_RES_Pin, (GPIO_PinState)BitValue);
}

/**
 * @brief       OLEDдDC�ߵ͵�ƽ
 * @param       Ҫд��DC�ĵ�ƽֵ����Χ��0/1
 * @retval      ��
 * @note        ���ϲ㺯����ҪдDCʱ���˺����ᱻ����
 *              �û���Ҫ���ݲ��������ֵ����DC��Ϊ�ߵ�ƽ���ߵ͵�ƽ
 *              ����������0ʱ����DCΪ�͵�ƽ������������1ʱ����DCΪ�ߵ�ƽ
 */
void OLED_W_DC(uint8_t BitValue)
{
  /*����BitValue��ֵ����DC�øߵ�ƽ���ߵ͵�ƽ*/
  HAL_GPIO_WritePin(OLED_DC_GPIO_Port, OLED_DC_Pin, (GPIO_PinState)BitValue);
}

///**
// * @brief       OLEDдCS�ߵ͵�ƽ
// * @param       Ҫд��CS�ĵ�ƽֵ����Χ��0/1
// * @retval      ��
// * @note        ���ϲ㺯����ҪдCSʱ���˺����ᱻ����
// *              �û���Ҫ���ݲ��������ֵ����CS��Ϊ�ߵ�ƽ���ߵ͵�ƽ
// *              ����������0ʱ����CSΪ�͵�ƽ������������1ʱ����CSΪ�ߵ�ƽ
// */
//void OLED_W_CS(uint8_t BitValue)
//{
//  /*����BitValue��ֵ����CS�øߵ�ƽ���ߵ͵�ƽ*/
//  HAL_GPIO_WritePin(OLED_CS_GPIO_Port, OLED_CS_Pin, (GPIO_PinState)BitValue);
//}
#endif

/**
 * @brief       ����һ���ֽ�
 * @param       Byte Ҫ���͵�һ���ֽ����ݣ���Χ��0x00~0xFF
 * @retval      ��
 * @note        ��
 */
void OLED_SendByte(uint8_t Byte)
{
  uint8_t i;
  
  #if( OLED_Communication_Mode == 0 )
  /* OLED_4Pin_IIC */
  /*ѭ��8�Σ��������η������ݵ�ÿһλ*/
  for (i = 0; i < 8; i++)
  {
    /*ʹ������ķ�ʽȡ��Byte��ָ��һλ���ݲ�д�뵽SDA��*/
    /*����!�������ǣ������з����ֵ��Ϊ1*/
    OLED_W_SDA(!!(Byte & (0x80 >> i)));
    OLED_W_SCL(1);
    OLED_W_SCL(0);
  }
  
  OLED_W_SCL(1);
  OLED_W_SCL(0);
  #else
  /* OLED_7Pin_SPI */
  /*ѭ��8�Σ��������η������ݵ�ÿһλ*/
  for (i = 0; i < 8; i++)
  {
    /*ʹ������ķ�ʽȡ��Byte��ָ��һλ���ݲ�д�뵽D1��*/
    /*����!�������ǣ������з����ֵ��Ϊ1*/
    OLED_W_D1(!!(Byte & (0x80 >> i)));
    OLED_W_D0(1);                   //����D0���ӻ���D0�����ض�ȡSDA
    OLED_W_D0(0);                   //����D0��������ʼ������һλ����
  }
  #endif
}

/**
 * @brief       OLEDд����
 * @param       Command Ҫд�������ֵ����Χ��0x00~0xFF
 * @retval      ��
 * @note        ��
 */
void OLED_WriteCommand(uint8_t Command)
{
  #if( OLED_Communication_Mode == 0 )
  /* OLED_4Pin_IIC */
  OLED_I2C_Start();                 //I2C��ʼ
  OLED_SendByte(0x78);              //����OLED��I2C�ӻ���ַ
  OLED_SendByte(0x00);              //�����ֽڣ���0x00����ʾ����д����
  OLED_SendByte(Command);           //д��ָ��������
  OLED_I2C_Stop();                  //I2C��ֹ
  #else
  /* OLED_7Pin_SPI */
//  OLED_W_CS(0);                     //����CS����ʼͨ��
  OLED_W_DC(0);                     //����DC����ʾ������������
  OLED_SendByte(Command);           //д��ָ������
//  OLED_W_CS(1);                     //����CS������ͨ��
  #endif
}

/**
 * @brief       OLEDд����
 * @param       Data Ҫд�����ݵ���ʼ��ַ
 * @param       Count Ҫд�����ݵ�����
 * @retval      ��
 * @note        ��
 */
void OLED_WriteData(uint8_t *Data, uint8_t Count)
{
  uint8_t i;
  
  #if( OLED_Communication_Mode == 0 )
  /* OLED_4Pin_IIC */
  OLED_I2C_Start();                 //I2C��ʼ
  OLED_SendByte(0x78);              //����OLED��I2C�ӻ���ַ
  OLED_SendByte(0x40);              //�����ֽڣ���0x40����ʾ����д����
  /*ѭ��Count�Σ���������������д��*/
  for (i = 0; i < Count; i ++)
  {
    OLED_SendByte(Data[i]);         //���η���Data��ÿһ������
  }
  OLED_I2C_Stop();                  //I2C��ֹ
  #else
  /* OLED_7Pin_SPI */
//  OLED_W_CS(0);                     //����CS����ʼͨ��
  OLED_W_DC(1);                     //����DC����ʾ������������
  /*ѭ��Count�Σ���������������д��*/
  for (i = 0; i < Count; i ++)
  {
    OLED_SendByte(Data[i]);         //���η���Data��ÿһ������
  }
//  OLED_W_CS(1);                     //����CS������ͨ��
  #endif
}

/**
 * @brief       OLED��ʼ������
 * @param       ��
 * @retval      ��
 * @note        ʹ��ǰ����Ҫ���ô˳�ʼ������
 */
void OLED_Init(void)
{
  #if( OLED_Communication_Mode == 0 )
  /* OLED_4Pin_IIC */
  /* �ͷ�SCL��SDA */
  OLED_W_SCL(1);
  OLED_W_SDA(1);
  #else
  /* OLED_7Pin_SPI */
  /*������Ĭ�ϵ�ƽ*/
  OLED_W_D0(0);
  OLED_W_D1(1);
  OLED_W_RES(1);
  OLED_W_DC(1);
//  OLED_W_CS(1);
  #endif
  
  /*д��һϵ�е������OLED���г�ʼ������*/
  OLED_WriteCommand(0XAE);    //������ʾ�ر�/��(POR = 0xAE)
                              //�ر� -> 0xAE���� -> 0xAF
  
  OLED_WriteCommand(0X00);    //�����е�ַ����λ(POR = 0x00)
  OLED_WriteCommand(0X10);    //�����е�ַ����λ(POR = 0x10)
  
  OLED_WriteCommand(0XD5);    //������ʾ��Ƶ/����Ƶ��ģʽ
  OLED_WriteCommand(0X80);    //������ʾ��Ƶ/����Ƶ�����ݣ�POR = 0x50��
  
  OLED_WriteCommand(0XA8);    //���ö�·����ģʽ
  OLED_WriteCommand(0X3F);    //����1/64 duty��0x01~0x3F����POR = 0x3F��
  
  OLED_WriteCommand(0XD3);    //������ʾƫ��ģʽ
  OLED_WriteCommand(0X00);    //���ò�ƫ�ƣ�POR = 0x00��
  
  OLED_WriteCommand(0X40);    //������ʾ��ʼ��(POR = 0x40)
  
  OLED_WriteCommand(0XA1);    //���÷ֶ�����ӳ��(ADC)��POR = 0xA0��
                              //���� -> 0xA1�����ҷ��� -> 0xA0
  
  OLED_WriteCommand(0XC8);    //���ó������ɨ�跽��POR = 0xC8��
                              //���� -> 0xc8�����·��� -> 0xC0
  
  OLED_WriteCommand(0XDA);    //���ó���PadӲ������ģʽ
  OLED_WriteCommand(0X12);    //���ó���PadӲ���������ݣ�POR = 0x12��
  
  OLED_WriteCommand(0X81);    //���öԱȶȿ���ģʽ
  OLED_WriteCommand(0XCF);    //���öԱȶȣ�0x00~0xFF��(POR = 0x80)
  
  OLED_WriteCommand(0XD9);    //���÷ŵ�/Ԥ������ģʽ
  OLED_WriteCommand(0XF1);    //���÷ŵ�/Ԥ���������ݣ�POR = 0x22��
                              //�ŵ磺15��Ԥ�䣺1
  
  OLED_WriteCommand(0XDB);    //����VCOMȡ��ѡ��ؿ�ģʽ
  OLED_WriteCommand(0X40);    //����VCOMȡ��ѡ��ؿ����ݣ�POR = 0x35��
  
  OLED_WriteCommand(0XA4);    //����������ʾ�ر�/�򿪣�POR = 0xA4��
                              //������ʾ -> 0xA4��ȫ����ʾ -> 0xA5
  
  OLED_WriteCommand(0XA6);    //��������/������ʾ��POR = 0xA6��
                              //���� -> 0xA6������ -> 0xA7
  
  OLED_WriteCommand(0X8D);    //���ó���ʹ��/ʧ��
  OLED_WriteCommand(0X14);    //���ó���ʧ��
  
  OLED_WriteCommand(0XAF);    //������ʾ�ر�/��(POR = 0xAE)
                              //�ر� -> 0xAE���� -> 0xAF
  
  OLED_Clear();               //����Դ�����
  OLED_Update();              //������ʾ����������ֹ��ʼ����δ��ʾ����ʱ����
}

/**
 * @brief       OLED������ʾ���λ��
 * @param       Page ָ��������ڵ�ҳ��  ��Χ��0~7
 * @param       X ָ��������ڵ�X�����꣬��Χ��0~127
 * @retval      ��
 * @note        OLEDĬ�ϵ�Y�ᣬֻ��8��BitΪһ��д�룬��1ҳ����8��Y������
 */
void OLED_SetCursor(uint8_t Page, uint8_t X)
{
  /*���ʹ�ô˳�������1.3���OLED��ʾ��������Ҫ�����ע��*/
  /*��Ϊ1.3���OLED����оƬ��SH1106����132��*/
  /*��Ļ����ʼ�н����˵�2�У������ǵ�0��*/
  /*������Ҫ��X��2������������ʾ*/
  if(OLED_Size)
  {
    X += 2;
  }
  
  /*ͨ��ָ������ҳ��ַ���е�ַ*/
  OLED_WriteCommand(0xB0 | Page);                 //����ҳλ��
  OLED_WriteCommand(0x10 | ((X & 0xF0) >> 4));    //����Xλ�ø�4λ
  OLED_WriteCommand(0x00 | (X & 0x0F));           //����Xλ�õ�4λ
}

/**
 * @brief       �η�����
 * @param       X ����
 * @param       Y ָ��
 * @retval      ����X��Y�η�
 * @note        ��
 */
uint32_t OLED_Pow(uint32_t X, uint32_t Y)
{
  uint32_t Result = 1;    //���Ĭ��Ϊ1
  
  while (Y --)            //�۳�Y��
  {
    Result *= X;          //ÿ�ΰ�X�۳˵������
  }
  
  return Result;
}

/**
 * @brief       �ж�ָ�����Ƿ���ָ��������ڲ�
 * @param       nvert ����εĶ�����
 * @param       vertx verty ��������ζ����x��y���������
 * @param       testx testy ���Ե��X��y����
 * @retval      ָ�����Ƿ���ָ��������ڲ���0�������ڲ���1�����ڲ�
 * @note        ��
 */
uint8_t OLED_pnpoly(uint8_t nvert, int16_t *vertx, int16_t *verty, int16_t testx, int16_t testy)
{
  int16_t i, j, c = 0;
  
  /*���㷨��W. Randolph Franklin���*/
  /*�ο����ӣ�https://wrfranklin.org/Research/Short_Notes/pnpoly.html*/
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
 * @brief       �ж�ָ�����Ƿ���ָ���Ƕ��ڲ�
 * @param       X Y ָ���������
 * @param       StartAngle EndAngle ��ʼ�ǶȺ���ֹ�Ƕȣ���Χ��-180~180
 *              ˮƽ����Ϊ0�ȣ�ˮƽ����Ϊ180�Ȼ�-180�ȣ��·�Ϊ�������Ϸ�Ϊ������˳ʱ����ת
 * @retval      ָ�����Ƿ���ָ���Ƕ��ڲ���0�������ڲ���1�����ڲ�
 * @note        ��
 */
uint8_t OLED_IsInAngle(int16_t X, int16_t Y, int16_t StartAngle, int16_t EndAngle)
{
  int16_t PointAngle;
  
  PointAngle = atan2(Y, X) / 3.14 * 180;      //����ָ����Ļ��ȣ���ת��Ϊ�Ƕȱ�ʾ
  
  if (StartAngle < EndAngle)                  //��ʼ�Ƕ�С����ֹ�Ƕȵ����
  {
  /*���ָ���Ƕ�����ʼ��ֹ�Ƕ�֮�䣬���ж�ָ������ָ���Ƕ�*/
    if (PointAngle >= StartAngle && PointAngle <= EndAngle)
    {
      return 1;
    }
  }
  else                                        //��ʼ�Ƕȴ�������ֹ�Ƕȵ����
  {
    /*���ָ���Ƕȴ�����ʼ�ǶȻ���С����ֹ�Ƕȣ����ж�ָ������ָ���Ƕ�*/
    if (PointAngle >= StartAngle || PointAngle <= EndAngle)
    {
      return 1;
    }
  }
  
  return 0;                                   //�������������������ж��ж�ָ���㲻��ָ���Ƕ�
}

/**
 * @brief       OLED�Դ�������µ�OLED��Ļ
 * @param       ��
 * @retval      ��
 * @note        ���е���ʾ��������ֻ�Ƕ�OLED�Դ�������ж�д
 *              ������OLED_Update������OLED_UpdateArea����
 *              �ŻὫ�Դ���������ݷ��͵�OLEDӲ����������ʾ
 *              �ʵ�����ʾ������Ҫ�������س�������Ļ�ϣ�������ø��º���
 */
void OLED_Update(void)
{
  uint8_t j;
  
  for (j = 0; j < 8; j ++)
  {
    /*���ù��λ��Ϊÿһҳ�ĵ�һ��*/
    OLED_SetCursor(j, 0);
    /*����д��128�����ݣ����Դ����������д�뵽OLEDӲ��*/
    OLED_WriteData(OLED_DisplayBuf[j], 128);
  }
}

/**
 * @brief       OLED�Դ����鲿�ָ��µ�OLED��Ļ
 * @param       X ָ���������Ͻǵĺ����꣬��Χ��0~127
 * @param       Y ָ���������Ͻǵ������꣬��Χ��0~63
 * @param       Width ָ������Ŀ�ȣ�    ��Χ��0~128
 * @param       Height ָ������ĸ߶ȣ�   ��Χ��0~64
 * @retval      ��
 * @note        �˺��������ٸ��²���ָ��������
 *              �����������Y��ֻ��������ҳ����ͬһҳ��ʣ�ಿ�ֻ����һ�����
 * @note        ���е���ʾ��������ֻ�Ƕ�OLED�Դ�������ж�д
 *              ������OLED_Update������OLED_UpdateArea����
 *              �ŻὫ�Դ���������ݷ��͵�OLEDӲ����������ʾ
 *              �ʵ�����ʾ������Ҫ�������س�������Ļ�ϣ�������ø��º���
 */
void OLED_UpdateArea(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height)
{
  uint8_t j;
  
  /*������飬��ָ֤�����򲻻ᳬ����Ļ��Χ*/
  if (X > 127) {return;}
  if (Y > 63) {return;}
  if (X + Width > 128) {Width = 128 - X;}
  if (Y + Height > 64) {Height = 64 - Y;}
  
  /*����ָ�������漰�����ҳ*/
  /*(Y + Height - 1) / 8 + 1��Ŀ����(Y + Height) / 8������ȡ��*/
  for (j = Y / 8; j < (Y + Height - 1) / 8 + 1; j ++)
  {
    /*���ù��λ��Ϊ���ҳ��ָ����*/
    OLED_SetCursor(j, X);
    /*����д��Width�����ݣ����Դ����������д�뵽OLEDӲ��*/
    OLED_WriteData(&OLED_DisplayBuf[j][X], Width);
  }
}

/**
 * @brief       OLED�Դ�����ȫ������
 * @param       ��
 * @retval      ��
 * @note        ���ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
 */
void OLED_Clear(void)
{
  uint8_t i, j;
  
  for (j = 0; j < 8; j ++)              //����8ҳ
  {
    for (i = 0; i < 128; i ++)          //����128��
    {
      OLED_DisplayBuf[j][i] = 0x00;     //���Դ���������ȫ������
    }
  }
}

/**
 * @brief       OLED�Դ����鲿������
 * @param       X ָ���������Ͻǵĺ����꣬��Χ��0~127
 * @param       Y ָ���������Ͻǵ������꣬��Χ��0~63
 * @param       Width ָ������Ŀ�ȣ�    ��Χ��0~128
 * @param       Height ָ������ĸ߶ȣ�   ��Χ��0~64
 * @retval      ��
 * @note        ���ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
 */
void OLED_ClearArea(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height)
{
  uint8_t i, j;
  
  /*������飬��ָ֤�����򲻻ᳬ����Ļ��Χ*/
  if (X > 127) {return;}
  if (Y > 63) {return;}
  if (X + Width > 128) {Width = 128 - X;}
  if (Y + Height > 64) {Height = 64 - Y;}
  
  for (j = Y; j < Y + Height; j ++)                     //����ָ��ҳ
  {
    for (i = X; i < X + Width; i ++)                    //����ָ����
    {
      OLED_DisplayBuf[j / 8][i] &= ~(0x01 << (j % 8));  //���Դ�����ָ����������
    }
  }
}

/**
 * @brief       OLED�Դ�����ȫ��ȡ��
 * @param       ��
 * @retval      ��
 * @note        ���ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
 */
void OLED_Reverse(void)
{
  uint8_t i, j;
  
  for (j = 0; j < 8; j ++)              //����8ҳ
  {
    for (i = 0; i < 128; i ++)          //����128��
    {
      OLED_DisplayBuf[j][i] ^= 0xFF;    //���Դ���������ȫ��ȡ��
    }
  }
}

/**
 * @brief       OLED�Դ����鲿��ȡ��
 * @param       X ָ���������Ͻǵĺ����꣬��Χ��0~127
 * @param       Y ָ���������Ͻǵ������꣬��Χ��0~63
 * @param       Width ָ������Ŀ�ȣ�    ��Χ��0~128
 * @param       Height ָ������ĸ߶ȣ�   ��Χ��0~64
 * @retval      ��
 * @note        ���ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
 */
void OLED_ReverseArea(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height)
{
  uint8_t i, j;
  
  /*������飬��ָ֤�����򲻻ᳬ����Ļ��Χ*/
  if (X > 127) {return;}
  if (Y > 63) {return;}
  if (X + Width > 128) {Width = 128 - X;}
  if (Y + Height > 64) {Height = 64 - Y;}
  
  for (j = Y; j < Y + Height; j ++)                     //����ָ��ҳ
  {
    for (i = X; i < X + Width; i ++)                    //����ָ����
    {
      OLED_DisplayBuf[j / 8][i] ^= 0x01 << (j % 8);     //���Դ�����ָ������ȡ��
    }
  }
}

/**
 * @brief       OLED��ʾһ���ַ�
 * @param       X ָ���ַ����Ͻǵĺ����꣬��Χ��0~127
 * @param       Y ָ���ַ����Ͻǵ������꣬��Χ��0~63
 * @param       Char ָ��Ҫ��ʾ���ַ���   ��Χ��ASCII��ɼ��ַ�
 * @param       FontSize ָ�������С
 *              ��Χ��OLED_6X8    ��6���أ���8����
 *                    OLED_8X16   ��8���أ���16����
 * @retval      ��
 * @note        ���ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
 */
void OLED_ShowChar(uint8_t X, uint8_t Y, char Char, uint8_t FontSize)
{
  if (FontSize == OLED_8X16)      //����Ϊ��8���أ���16����
  {
    /*��ASCII��ģ��OLED_F8x16��ָ��������8*16��ͼ���ʽ��ʾ*/
    OLED_ShowImage(X, Y, 8, 16, OLED_F8x16[Char - ' ']);
  }
  else if(FontSize == OLED_6X8)   //����Ϊ��6���أ���8����
  {
    /*��ASCII��ģ��OLED_F6x8��ָ��������6*8��ͼ���ʽ��ʾ*/
    OLED_ShowImage(X, Y, 6, 8, OLED_F6x8[Char - ' ']);
  }
}

/**
 * @brief       OLED��ʾ�ַ���
 * @param       X ָ���ַ����Ͻǵĺ����꣬ ��Χ��0~127
 * @param       Y ָ���ַ����Ͻǵ������꣬ ��Χ��0~63
 * @param       String ָ��Ҫ��ʾ���ַ�������Χ��ASCII��ɼ��ַ���ɵ��ַ���
 * @param       FontSize ָ�������С
 *              ��Χ��OLED_6X8    ��6���أ���8����
 *                    OLED_8X16   ��8���أ���16����
 * @retval      ��
 * @note        ���ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
 */
void OLED_ShowString(uint8_t X, uint8_t Y, char *String, uint8_t FontSize)
{
  uint8_t i;
  
  for (i = 0; String[i] != '\0'; i++)     //�����ַ�����ÿ���ַ�
  {
    /*����OLED_ShowChar������������ʾÿ���ַ�*/
    OLED_ShowChar(X + i * FontSize, Y, String[i], FontSize);
  }
}

/**
 * @brief       OLED��ʾ���֣�ʮ���ƣ���������
 * @param       X ָ���ַ����Ͻǵĺ����꣬��Χ��0~127
 * @param       Y ָ���ַ����Ͻǵ������꣬��Χ��0~63
 * @param       Number ָ��Ҫ��ʾ�����֣� ��Χ��0~4294967295
 * @param       Length ָ�����ֵĳ��ȣ�   ��Χ��0~10
 * @param       FontSize ָ�������С
 *              ��Χ��OLED_6X8    ��6���أ���8����
 *                    OLED_8X16   ��8���أ���16����
 * @retval      ��
 * @note        ���ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
 */
void OLED_ShowNum(uint8_t X, uint8_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize)
{
  uint8_t i;
  
  for (i = 0; i < Length; i++)      //�������ֵ�ÿһλ
  {
    /*����OLED_ShowChar������������ʾÿ������*/
    /*Number / OLED_Pow(10, Length - i - 1) % 10 ����ʮ������ȡ���ֵ�ÿһλ*/
    /*+ '0' �ɽ�����ת��Ϊ�ַ���ʽ*/
    OLED_ShowChar(X + i * FontSize, Y, Number / OLED_Pow(10, Length - i - 1) % 10 + '0', FontSize);
  }
}

/**
 * @brief       OLED��ʾ�з������֣�ʮ���ƣ�������
 * @param       X ָ���ַ����Ͻǵĺ����꣬��Χ��0~127
 * @param       Y ָ���ַ����Ͻǵ������꣬��Χ��0~63
 * @param       Number ָ��Ҫ��ʾ�����֣� ��Χ��-2147483648~2147483647
 * @param       Length ָ�����ֵĳ��ȣ�   ��Χ��0~10
 * @param       FontSize ָ�������С
 *              ��Χ��OLED_6X8    ��6���أ���8����
 *                    OLED_8X16   ��8���أ���16����
 * @retval      ��
 * @note        ���ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
 */
void OLED_ShowSignedNum(uint8_t X, uint8_t Y, int32_t Number, uint8_t Length, uint8_t FontSize)
{
  uint8_t i;
  uint32_t Number1;
  
  if (Number >= 0)                        //���ִ��ڵ���0
  {
    OLED_ShowChar(X, Y, '+', FontSize);   //��ʾ+��
    Number1 = Number;                     //Number1ֱ�ӵ���Number
  }
  else                                    //����С��0
  {
    OLED_ShowChar(X, Y, '-', FontSize);   //��ʾ-��
    Number1 = -Number;                    //Number1����Numberȡ��
  }
  
  for (i = 0; i < Length; i++)            //�������ֵ�ÿһλ
  {
    /*����OLED_ShowChar������������ʾÿ������*/
    /*Number1 / OLED_Pow(10, Length - i - 1) % 10 ����ʮ������ȡ���ֵ�ÿһλ*/
    /*+ '0' �ɽ�����ת��Ϊ�ַ���ʽ*/
    OLED_ShowChar(X + (i + 1) * FontSize, Y, Number1 / OLED_Pow(10, Length - i - 1) % 10 + '0', FontSize);
  }
}

/**
 * @brief       OLED��ʾʮ���������֣�ʮ�����ƣ���������
 * @param       X ָ���ַ����Ͻǵĺ����꣬��Χ��0~127
 * @param       Y ָ���ַ����Ͻǵ������꣬��Χ��0~63
 * @param       Number ָ��Ҫ��ʾ�����֣� ��Χ��0x00000000~0xFFFFFFFF
 * @param       Length ָ�����ֵĳ��ȣ�   ��Χ��0~8
 * @param       FontSize ָ�������С
 *              ��Χ��OLED_6X8    ��6���أ���8����
 *                    OLED_8X16   ��8���أ���16����
 * @retval      ��
 * @note        ���ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
 */
void OLED_ShowHexNum(uint8_t X, uint8_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize)
{
  uint8_t i, SingleNumber;
  
  for (i = 0; i < Length; i++)            //�������ֵ�ÿһλ
  {
    /*��ʮ��������ȡ���ֵ�ÿһλ*/
    SingleNumber = Number / OLED_Pow(16, Length - i - 1) % 16;
    
    if (SingleNumber < 10)                //��������С��10
    {
      /*����OLED_ShowChar��������ʾ������*/
      /*+ '0' �ɽ�����ת��Ϊ�ַ���ʽ*/
      OLED_ShowChar(X + i * FontSize, Y, SingleNumber + '0', FontSize);
    }
    else                                  //�������ִ���10
    {
      /*����OLED_ShowChar��������ʾ������*/
      /*+ 'A' �ɽ�����ת��Ϊ��A��ʼ��ʮ�������ַ�*/
      OLED_ShowChar(X + i * FontSize, Y, SingleNumber - 10 + 'A', FontSize);
    }
  }
}

/**
 * @brief       OLED��ʾ���������֣������ƣ���������
 * @param       X ָ���ַ����Ͻǵĺ����꣬��Χ��0~127
 * @param       Y ָ���ַ����Ͻǵ������꣬��Χ��0~63
 * @param       Number ָ��Ҫ��ʾ�����֣� ��Χ��0x00000000~0xFFFFFFFF
 * @param       Length ָ�����ֵĳ��ȣ�   ��Χ��0~16
 * @param       FontSize ָ�������С
 *              ��Χ��OLED_6X8    ��6���أ���8����
 *                    OLED_8X16   ��8���أ���16����
 * @retval      ��
 * @note        ���ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
 */
void OLED_ShowBinNum(uint8_t X, uint8_t Y, uint32_t Number, uint8_t Length, uint8_t FontSize)
{
  uint8_t i;
  
  for (i = 0; i < Length; i++)            //�������ֵ�ÿһλ
  {
    /*����OLED_ShowChar������������ʾÿ������*/
    /*Number / OLED_Pow(2, Length - i - 1) % 2 ���Զ�������ȡ���ֵ�ÿһλ*/
    /*+ '0' �ɽ�����ת��Ϊ�ַ���ʽ*/
    OLED_ShowChar(X + i * FontSize, Y, Number / OLED_Pow(2, Length - i - 1) % 2 + '0', FontSize);
  }
}

/**
 * @brief       OLED��ʾ�������֣�ʮ���ƣ�С����
 * @param       X ָ���ַ����Ͻǵĺ����꣬��Χ��0~127
 * @param       Y ָ���ַ����Ͻǵ������꣬��Χ��0~63
 * @param       Number ָ��Ҫ��ʾ�����֣� ��Χ��-4294967295.0~4294967295.0
 * @param       IntLength ָ�����ֵ�����λ���ȣ���Χ��0~10
 * @param       FraLength ָ�����ֵ�С��λ���ȣ���Χ��0~9��С����������������ʾ
 * @param       FontSize ָ�������С
 *              ��Χ��OLED_6X8    ��6���أ���8����
 *                    OLED_8X16   ��8���أ���16����
 * @retval      ��
 * @note        ���ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
 */
void OLED_ShowFloatNum(uint8_t X, uint8_t Y, double Number, uint8_t IntLength, uint8_t FraLength, uint8_t FontSize)
{
  uint32_t PowNum, IntNum, FraNum;
  
  if (Number >= 0)                        //���ִ��ڵ���0
  {
    OLED_ShowChar(X, Y, '+', FontSize);   //��ʾ+��
  }
  else                                    //����С��0
  {
    OLED_ShowChar(X, Y, '-', FontSize);   //��ʾ-��
    Number = -Number;                     //Numberȡ��
  }
  
  /*��ȡ�������ֺ�С������*/
  IntNum = Number;                        //ֱ�Ӹ�ֵ�����ͱ�������ȡ����
  Number -= IntNum;                       //��Number��������������ֹ֮��С���˵�����ʱ����������ɴ���
  PowNum = OLED_Pow(10, FraLength);       //����ָ��С����λ����ȷ������
  FraNum = round(Number * PowNum);        //��С���˵�������ͬʱ�������룬������ʾ���
  IntNum += FraNum / PowNum;              //��������������˽�λ������Ҫ�ټӸ�����
  
  /*��ʾ��������*/
  OLED_ShowNum(X + FontSize, Y, IntNum, IntLength, FontSize);

  /*��ʾС����*/
  OLED_ShowChar(X + (IntLength + 1) * FontSize, Y, '.', FontSize);

  /*��ʾС������*/
  OLED_ShowNum(X + (IntLength + 2) * FontSize, Y, FraNum, FraLength, FontSize);
}

/**
 * @brief       OLED��ʾ���ִ�
 * @param       X ָ���ַ����Ͻǵĺ����꣬  ��Χ��0~127
 * @param       Y ָ���ַ����Ͻǵ������꣬  ��Χ��0~63
 * @param       Chinese ָ��Ҫ��ʾ�ĺ��ִ�����Χ������ȫ��Ϊ���ֻ���ȫ���ַ�����Ҫ�����κΰ���ַ�
 *              ��ʾ�ĺ�����Ҫ��OLED_Data.c���OLED_CF16x16���鶨��
 *              δ�ҵ�ָ������ʱ������ʾĬ��ͼ�Σ�һ�������ڲ�һ���ʺţ�
 * @retval      ��
 * @note        ���ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
 */
void OLED_ShowChinese(uint8_t X, uint8_t Y, char *Chinese)
{
  uint8_t pChinese = 0;
  uint8_t pIndex;
  uint8_t i;
  
  char SingleChinese[OLED_CHN_CHAR_WIDTH + 1] = {0};
  
  for (i = 0; Chinese[i] != '\0'; i ++)                 //�������ִ�
  {
    SingleChinese[pChinese] = Chinese[i];               //��ȡ���ִ����ݵ�������������
    pChinese ++;                                        //�ƴ�����
    
    /*����ȡ��������OLED_CHN_CHAR_WIDTHʱ����������ȡ����һ�������ĺ���*/
    if (pChinese >= OLED_CHN_CHAR_WIDTH)
    {
      pChinese = 0;                                     //�ƴι���
      
      /*��������������ģ�⣬Ѱ��ƥ��ĺ���*/
      /*����ҵ����һ�����֣�����Ϊ���ַ����������ʾ����δ����ģ�ⶨ�壬ֹͣѰ��*/
      for (pIndex = 0; strcmp(OLED_CF16x16[pIndex].Index, "") != 0; pIndex ++)
      {
        /*�ҵ�ƥ��ĺ���*/
        if (strcmp(OLED_CF16x16[pIndex].Index, SingleChinese) == 0)
        {
          break;                                        //����ѭ������ʱpIndex��ֵΪָ�����ֵ�����
        }
      }
      
      /*��������ģ��OLED_CF16x16��ָ��������16*16��ͼ���ʽ��ʾ*/
      OLED_ShowImage(X + ((i + 1) / OLED_CHN_CHAR_WIDTH - 1) * 16, Y, 16, 16, OLED_CF16x16[pIndex].Data);
    }
  }
}

/**
 * @brief       OLED��ʾͼ��
 * @param       X ָ���������Ͻǵĺ����꣬��Χ��0~127
 * @param       Y ָ���������Ͻǵ������꣬��Χ��0~63
 * @param       Width ָ������Ŀ�ȣ�    ��Χ��0~128
 * @param       Height ָ������ĸ߶ȣ�   ��Χ��0~64
 * @param       Image ָ��Ҫ��ʾ��ͼ��
 * @retval      ��
 * @note        ���ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
 */
void OLED_ShowImage(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height, const uint8_t *Image)
{
  uint8_t i, j;
  
  /*������飬��ָ֤��ͼ�񲻻ᳬ����Ļ��Χ*/
  if (X > 127) {return;}
  if (Y > 63) {return;}
  
  /*��ͼ�������������*/
  OLED_ClearArea(X, Y, Width, Height);
  
  /*����ָ��ͼ���漰�����ҳ*/
  /*(Height - 1) / 8 + 1��Ŀ����Height / 8������ȡ��*/
  for (j = 0; j < (Height - 1) / 8 + 1; j ++)
  {
    /*����ָ��ͼ���漰�������*/
    for (i = 0; i < Width; i ++)
    {
      /*�����߽磬��������ʾ*/
      if (X + i > 127) {break;}
      if (Y / 8 + j > 7) {return;}
      
      /*��ʾͼ���ڵ�ǰҳ������*/
      OLED_DisplayBuf[Y / 8 + j][X + i] |= Image[j * Width + i] << (Y % 8);
      
      /*�����߽磬��������ʾ*/
      /*ʹ��continue��Ŀ���ǣ���һҳ�����߽�ʱ����һҳ�ĺ������ݻ���Ҫ������ʾ*/
      if (Y / 8 + j + 1 > 7) {continue;}
      
      /*��ʾͼ������һҳ������*/
      OLED_DisplayBuf[Y / 8 + j + 1][X + i] |= Image[j * Width + i] >> (8 - Y % 8);
    }
  }
}

/**
 * @brief       OLEDʹ��printf������ӡ��ʽ���ַ���
 * @param       X ָ���ַ����Ͻǵĺ����꣬��Χ��0~127
 * @param       Y ָ���ַ����Ͻǵ������꣬��Χ��0~63
 * @param       FontSize ָ�������С
 *              ��Χ��OLED_6X8    ��6���أ���8����
 *                    OLED_8X16   ��8���أ���16����
 * @param       format ָ��Ҫ��ʾ�ĸ�ʽ���ַ�������Χ��ASCII��ɼ��ַ���ɵ��ַ���
 * @param       ... ��ʽ���ַ��������б�
 * @retval      ��
 * @note        ���ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
 */
void OLED_Printf(uint8_t X, uint8_t Y, uint8_t FontSize, char *format, ...)
{
  char String[30];                              //�����ַ�����
  
  va_list arg;                                  //����ɱ�����б��������͵ı���arg
  va_start(arg, format);                        //��format��ʼ�����ղ����б�arg����
  vsprintf(String, format, arg);                //ʹ��vsprintf��ӡ��ʽ���ַ����Ͳ����б��ַ�������
  va_end(arg);                                  //��������arg
  OLED_ShowString(X, Y, String, FontSize);      //OLED��ʾ�ַ����飨�ַ�����
}

/**
 * @brief       OLED��ָ��λ�û�һ����
 * @param       X ָ���������Ͻǵĺ����꣬��Χ��0~127
 * @param       Y ָ���������Ͻǵ������꣬��Χ��0~63
 * @retval      ��
 * @note        ���ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
 */
void OLED_DrawPoint(uint8_t X, uint8_t Y)
{
  /*������飬��ָ֤��λ�ò��ᳬ����Ļ��Χ*/
  if (X > 127) {return;}
  if (Y > 63) {return;}
  
  /*���Դ�����ָ��λ�õ�һ��Bit������1*/
  OLED_DisplayBuf[Y / 8][X] |= 0x01 << (Y % 8);
}

/**
 * @brief       OLED��ȡָ��λ�õ��ֵ
 * @param       X ָ���������Ͻǵĺ����꣬��Χ��0~127
 * @param       Y ָ���������Ͻǵ������꣬��Χ��0~63
 * @retval      ָ��λ�õ��Ƿ��ڵ���״̬��0��Ϩ��1������
 * @note        ��
 */
uint8_t OLED_GetPoint(uint8_t X, uint8_t Y)
{
  /*������飬��ָ֤��λ�ò��ᳬ����Ļ��Χ*/
  if (X > 127) {return 0;}
  if (Y > 63) {return 0;}
  
  /*�ж�ָ��λ�õ�����*/
  if (OLED_DisplayBuf[Y / 8][X] & 0x01 << (Y % 8))
  {
    return 1;                   //Ϊ1������1
  }
  
  return 0;                     //���򣬷���0
}

/**
 * @brief       OLED����
 * @param       X0 ָ��һ���˵�ĺ����꣬  ��Χ��0~127
 * @param       Y0 ָ��һ���˵�������꣬  ��Χ��0~63
 * @param       X1 ָ����һ���˵�ĺ����꣬��Χ��0~127
 * @param       Y1 ָ����һ���˵�������꣬��Χ��0~63
 * @retval      ��
 * @note        ���ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
 */
void OLED_DrawLine(uint8_t X0, uint8_t Y0, uint8_t X1, uint8_t Y1)
{
  int16_t x, y, dx, dy, d, incrE, incrNE, temp;
  int16_t x0 = X0, y0 = Y0, x1 = X1, y1 = Y1;
  uint8_t yflag = 0, xyflag = 0;
  
  if (y0 == y1)               //���ߵ�������
  {
    /*0�ŵ�X�������1�ŵ�X���꣬�򽻻�����X����*/
    if (x0 > x1) {temp = x0; x0 = x1; x1 = temp;}
    
    /*����X����*/
    for (x = x0; x <= x1; x ++)
    {
      OLED_DrawPoint(x, y0);  //���λ���
    }
  }
  else if (x0 == x1)          //���ߵ�������
  {
    /*0�ŵ�Y�������1�ŵ�Y���꣬�򽻻�����Y����*/
    if (y0 > y1) {temp = y0; y0 = y1; y1 = temp;}
    
    /*����Y����*/
    for (y = y0; y <= y1; y ++)
    {
      OLED_DrawPoint(x0, y);  //���λ���
    }
  }
  else                        //б��
  {
    /*ʹ��Bresenham�㷨��ֱ�ߣ����Ա����ʱ�ĸ������㣬Ч�ʸ���*/
    
    if (x0 > x1)              //0�ŵ�X�������1�ŵ�X����
    {
      /*������������*/
      /*������Ӱ�컭�ߣ����ǻ��߷����ɵ�һ���������������ޱ�Ϊ��һ��������*/
      temp = x0; x0 = x1; x1 = temp;
      temp = y0; y0 = y1; y1 = temp;
    }
    
    if (y0 > y1)              //0�ŵ�Y�������1�ŵ�Y����
    {
      /*��Y����ȡ��*/
      /*ȡ����Ӱ�컭�ߣ����ǻ��߷����ɵ�һ�������ޱ�Ϊ��һ����*/
      y0 = -y0;
      y1 = -y1;
      
      /*�ñ�־λyflag����ס��ǰ�任���ں���ʵ�ʻ���ʱ���ٽ����껻����*/
      yflag = 1;
    }
    
    if (y1 - y0 > x1 - x0)    //����б�ʴ���1
    {
      /*��X������Y���껥��*/
      /*������Ӱ�컭�ߣ����ǻ��߷����ɵ�һ����0~90�ȷ�Χ��Ϊ��һ����0~45�ȷ�Χ*/
      temp = x0; x0 = y0; y0 = temp;
      temp = x1; x1 = y1; y1 = temp;
      
      /*�ñ�־λxyflag����ס��ǰ�任���ں���ʵ�ʻ���ʱ���ٽ����껻����*/
      xyflag = 1;
    }
    
    /*����ΪBresenham�㷨��ֱ��*/
    /*�㷨Ҫ�󣬻��߷������Ϊ��һ����0~45�ȷ�Χ*/
    dx = x1 - x0;
    dy = y1 - y0;
    incrE = 2 * dy;
    incrNE = 2 * (dy - dx);
    d = 2 * dy - dx;
    x = x0;
    y = y0;
    
    /*����ʼ�㣬ͬʱ�жϱ�־λ�������껻����*/
    if (yflag && xyflag){OLED_DrawPoint(y, -x);}
    else if (yflag)     {OLED_DrawPoint(x, -y);}
    else if (xyflag)    {OLED_DrawPoint(y, x);}
    else                {OLED_DrawPoint(x, y);}
    
    while (x < x1)            //����X���ÿ����
    {
      x ++;
      if (d < 0)              //��һ�����ڵ�ǰ�㶫��
      {
        d += incrE;
      }
      else                    //��һ�����ڵ�ǰ�㶫����
      {
        y ++;
        d += incrNE;
      }
      
      /*��ÿһ���㣬ͬʱ�жϱ�־λ�������껻����*/
      if (yflag && xyflag){OLED_DrawPoint(y, -x);}
      else if (yflag)     {OLED_DrawPoint(x, -y);}
      else if (xyflag)    {OLED_DrawPoint(y, x);}
      else                {OLED_DrawPoint(x, y);}
    }
  }
}

/**
 * @brief       OLED������
 * @param       X ָ���������Ͻǵĺ����꣬��Χ��0~127
 * @param       Y ָ���������Ͻǵ������꣬��Χ��0~63
 * @param       Width ָ�����εĿ�ȣ�    ��Χ��0~128
 * @param       Height ָ�����εĸ߶ȣ�   ��Χ��0~64
 * @param       IsFilled ָ�������Ƿ����
 *              ��Χ��OLED_UNFILLED   �����
 *                    OLED_FILLED     ���
 * @retval      ��
 * @note        ���ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
 */
void OLED_DrawRectangle(uint8_t X, uint8_t Y, uint8_t Width, uint8_t Height, uint8_t IsFilled)
{
  uint8_t i, j;
  
  if (!IsFilled)            //ָ�����β����
  {
    /*��������X���꣬����������������*/
    for (i = X; i < X + Width; i ++)
    {
      OLED_DrawPoint(i, Y);
      OLED_DrawPoint(i, Y + Height - 1);
    }
    /*��������Y���꣬����������������*/
    for (i = Y; i < Y + Height; i ++)
    {
      OLED_DrawPoint(X, i);
      OLED_DrawPoint(X + Width - 1, i);
    }
  }
  else                      //ָ���������
  {
    /*����X����*/
    for (i = X; i < X + Width; i ++)
    {
      /*����Y����*/
      for (j = Y; j < Y + Height; j ++)
      {
        /*��ָ�����򻭵㣬���������*/
        OLED_DrawPoint(i, j);
      }
    }
  }
}

/**
 * @brief       OLED��������
 * @param       X0 ָ����һ���˵�ĺ����꣬��Χ��0~127
 * @param       Y0 ָ����һ���˵�������꣬��Χ��0~63
 * @param       X1 ָ���ڶ����˵�ĺ����꣬��Χ��0~127
 * @param       Y1 ָ���ڶ����˵�������꣬��Χ��0~63
 * @param       X2 ָ���������˵�ĺ����꣬��Χ��0~127
 * @param       Y2 ָ���������˵�������꣬��Χ��0~63
 * @param       IsFilled ָ���������Ƿ����
 *              ��Χ��OLED_UNFILLED   �����
 *                    OLED_FILLED     ���
 * @retval      ��
 * @note        ���ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
 */
void OLED_DrawTriangle(uint8_t X0, uint8_t Y0, uint8_t X1, uint8_t Y1, uint8_t X2, uint8_t Y2, uint8_t IsFilled)
{
  uint8_t minx = X0, miny = Y0, maxx = X0, maxy = Y0;
  uint8_t i, j;
  int16_t vx[] = {X0, X1, X2};
  int16_t vy[] = {Y0, Y1, Y2};
  
  if (!IsFilled)            //ָ�������β����
  {
    /*���û��ߺ���������������ֱ������*/
    OLED_DrawLine(X0, Y0, X1, Y1);
    OLED_DrawLine(X0, Y0, X2, Y2);
    OLED_DrawLine(X1, Y1, X2, Y2);
  }
  else                      //ָ�����������
  {
    /*�ҵ���������С��X��Y����*/
    if (X1 < minx) {minx = X1;}
    if (X2 < minx) {minx = X2;}
    if (Y1 < miny) {miny = Y1;}
    if (Y2 < miny) {miny = Y2;}
    
    /*�ҵ�����������X��Y����*/
    if (X1 > maxx) {maxx = X1;}
    if (X2 > maxx) {maxx = X2;}
    if (Y1 > maxy) {maxy = Y1;}
    if (Y2 > maxy) {maxy = Y2;}
    
    /*��С�������֮��ľ���Ϊ������Ҫ��������*/
    /*���������������еĵ�*/
    /*����X����*/
    for (i = minx; i <= maxx; i ++)
    {
      /*����Y����*/
      for (j = miny; j <= maxy; j ++)
      {
        /*����OLED_pnpoly���ж�ָ�����Ƿ���ָ��������֮��*/
        /*����ڣ��򻭵㣬������ڣ���������*/
        if (OLED_pnpoly(3, vx, vy, i, j)) {OLED_DrawPoint(i, j);}
      }
    }
  }
}

/**
 * @brief       OLED��Բ
 * @param       X ָ��Բ��Բ�ĺ����꣬��Χ��0~127
 * @param       Y ָ��Բ��Բ�������꣬��Χ��0~63
 * @param       Radius ָ��Բ�İ뾶�� ��Χ��0~255
 * @param       IsFilled ָ��Բ�Ƿ����
 *              ��Χ��OLED_UNFILLED   �����
 *                    OLED_FILLED     ���
 * @retval      ��
 * @note        ���ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
 */
void OLED_DrawCircle(uint8_t X, uint8_t Y, uint8_t Radius, uint8_t IsFilled)
{
  int16_t x, y, d, j;
  
  /*ʹ��Bresenham�㷨��Բ�����Ա����ʱ�ĸ������㣬Ч�ʸ���*/
  
  d = 1 - Radius;
  x = 0;
  y = Radius;
  
  /*��ÿ���˷�֮һԲ������ʼ��*/
  OLED_DrawPoint(X + x, Y + y);
  OLED_DrawPoint(X - x, Y - y);
  OLED_DrawPoint(X + y, Y + x);
  OLED_DrawPoint(X - y, Y - x);
  
  if (IsFilled)             //ָ��Բ���
  {
    /*������ʼ��Y����*/
    for (j = -y; j < y; j ++)
    {
      /*��ָ�����򻭵㣬��䲿��Բ*/
      OLED_DrawPoint(X, Y + j);
    }
  }
  
  while (x < y)             //����X���ÿ����
  {
    x ++;
    if (d < 0)              //��һ�����ڵ�ǰ�㶫��
    {
      d += 2 * x + 1;
    }
    else                    //��һ�����ڵ�ǰ�㶫�Ϸ�
    {
      y --;
      d += 2 * (x - y) + 1;
    }
    
    /*��ÿ���˷�֮һԲ���ĵ�*/
    OLED_DrawPoint(X + x, Y + y);
    OLED_DrawPoint(X + y, Y + x);
    OLED_DrawPoint(X - x, Y - y);
    OLED_DrawPoint(X - y, Y - x);
    OLED_DrawPoint(X + x, Y - y);
    OLED_DrawPoint(X + y, Y - x);
    OLED_DrawPoint(X - x, Y + y);
    OLED_DrawPoint(X - y, Y + x);
    
    if (IsFilled)           //ָ��Բ���
    {
      /*�����м䲿��*/
      for (j = -y; j < y; j ++)
      {
        /*��ָ�����򻭵㣬��䲿��Բ*/
        OLED_DrawPoint(X + x, Y + j);
        OLED_DrawPoint(X - x, Y + j);
      }
      
      /*�������ಿ��*/
      for (j = -x; j < x; j ++)
      {
        /*��ָ�����򻭵㣬��䲿��Բ*/
        OLED_DrawPoint(X - y, Y + j);
        OLED_DrawPoint(X + y, Y + j);
      }
    }
  }
}

/**
 * @brief       OLED����Բ
 * @param       X ָ����Բ��Բ�ĺ����꣬  ��Χ��0~127
 * @param       Y ָ����Բ��Բ�������꣬  ��Χ��0~63
 * @param       A ָ����Բ�ĺ�����᳤�ȣ���Χ��0~255
 * @param       B ָ����Բ��������᳤�ȣ���Χ��0~255
 * @param       IsFilled ָ����Բ�Ƿ����
 *              ��Χ��OLED_UNFILLED   �����
 *                    OLED_FILLED     ���
 * @retval      ��
 * @note        ���ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
 */
void OLED_DrawEllipse(uint8_t X, uint8_t Y, uint8_t A, uint8_t B, uint8_t IsFilled)
{
  int16_t x, y, j;
  int16_t a = A, b = B;
  float d1, d2;
  
  /*ʹ��Bresenham�㷨����Բ�����Ա��ⲿ�ֺ�ʱ�ĸ������㣬Ч�ʸ���*/
  x = 0;
  y = b;
  d1 = b * b + a * a * (-b + 0.5);
  
  if (IsFilled)             //ָ����Բ���
  {
    /*������ʼ��Y����*/
    for (j = -y; j < y; j ++)
    {
      /*��ָ�����򻭵㣬��䲿����Բ*/
      OLED_DrawPoint(X, Y + j);
      OLED_DrawPoint(X, Y + j);
    }
  }
  
  /*����Բ������ʼ��*/
  OLED_DrawPoint(X + x, Y + y);
  OLED_DrawPoint(X - x, Y - y);
  OLED_DrawPoint(X - x, Y + y);
  OLED_DrawPoint(X + x, Y - y);
  
  /*����Բ�м䲿��*/
  while (b * b * (x + 1) < a * a * (y - 0.5))
  {
    if (d1 <= 0)            //��һ�����ڵ�ǰ�㶫��
    {
      d1 += b * b * (2 * x + 3);
    }
    else                    //��һ�����ڵ�ǰ�㶫�Ϸ�
    {
      d1 += b * b * (2 * x + 3) + a * a * (-2 * y + 2);
      y --;
    }
    
    x ++;
    
    if (IsFilled)           //ָ����Բ���
    {
      /*�����м䲿��*/
      for (j = -y; j < y; j ++)
      {
        /*��ָ�����򻭵㣬��䲿����Բ*/
        OLED_DrawPoint(X + x, Y + j);
        OLED_DrawPoint(X - x, Y + j);
      }
    }
    
    /*����Բ�м䲿��Բ��*/
    OLED_DrawPoint(X + x, Y + y);
    OLED_DrawPoint(X - x, Y - y);
    OLED_DrawPoint(X - x, Y + y);
    OLED_DrawPoint(X + x, Y - y);
  }
  
  /*����Բ���ಿ��*/
  d2 = b * b * (x + 0.5) * (x + 0.5) + a * a * (y - 1) * (y - 1) - a * a * b * b;
  
  while (y > 0)
  {
    if (d2 <= 0)          //��һ�����ڵ�ǰ�㶫��
    {
      d2 += b * b * (2 * x + 2) + a * a * (-2 * y + 3);
      x ++;
    }
    else                  //��һ�����ڵ�ǰ�㶫�Ϸ�
    {
      d2 += a * a * (-2 * y + 3);
    }
    
    y --;
    
    if (IsFilled)         //ָ����Բ���
    {
      /*�������ಿ��*/
      for (j = -y; j < y; j ++)
      {
        /*��ָ�����򻭵㣬��䲿����Բ*/
        OLED_DrawPoint(X + x, Y + j);
        OLED_DrawPoint(X - x, Y + j);
      }
    }
    
    /*����Բ���ಿ��Բ��*/
    OLED_DrawPoint(X + x, Y + y);
    OLED_DrawPoint(X - x, Y - y);
    OLED_DrawPoint(X - x, Y + y);
    OLED_DrawPoint(X + x, Y - y);
  }
}

/**
 * @brief       OLED��Բ��
 * @param       X ָ��Բ����Բ�ĺ����꣬��Χ��0~127
 * @param       Y ָ��Բ����Բ�������꣬��Χ��0~63
 * @param       Radius ָ��Բ���İ뾶����Χ��0~255
 * @param       StartAngle ָ��Բ������ʼ�Ƕȣ���Χ��-180~180
 *              ˮƽ����Ϊ0�ȣ�ˮƽ����Ϊ180�Ȼ�-180�ȣ��·�Ϊ�������Ϸ�Ϊ������˳ʱ����ת
 * @param       EndAngle ָ��Բ������ֹ�Ƕȣ���Χ��-180~180
 *              ˮƽ����Ϊ0�ȣ�ˮƽ����Ϊ180�Ȼ�-180�ȣ��·�Ϊ�������Ϸ�Ϊ������˳ʱ����ת
 * @param       IsFilled ָ��Բ���Ƿ���䣬����Ϊ����
 *              ��Χ��OLED_UNFILLED   �����
 *                    OLED_FILLED     ���
 * @retval      ��
 * @note        ���ô˺�����Ҫ�������س�������Ļ�ϣ�������ø��º���
 */
void OLED_DrawArc(uint8_t X, uint8_t Y, uint8_t Radius, int16_t StartAngle, int16_t EndAngle, uint8_t IsFilled)
{
  int16_t x, y, d, j;
  
  /*�˺�������Bresenham�㷨��Բ�ķ���*/
  
  d = 1 - Radius;
  x = 0;
  y = Radius;
  
  /*�ڻ�Բ��ÿ����ʱ���ж�ָ�����Ƿ���ָ���Ƕ��ڣ��ڣ��򻭵㣬���ڣ���������*/
  if (OLED_IsInAngle(x, y, StartAngle, EndAngle))   {OLED_DrawPoint(X + x, Y + y);}
  if (OLED_IsInAngle(-x, -y, StartAngle, EndAngle)) {OLED_DrawPoint(X - x, Y - y);}
  if (OLED_IsInAngle(y, x, StartAngle, EndAngle))   {OLED_DrawPoint(X + y, Y + x);}
  if (OLED_IsInAngle(-y, -x, StartAngle, EndAngle)) {OLED_DrawPoint(X - y, Y - x);}
  
  if (IsFilled)             //ָ��Բ�����
  {
    /*������ʼ��Y����*/
    for (j = -y; j < y; j ++)
    {
      /*�����Բ��ÿ����ʱ���ж�ָ�����Ƿ���ָ���Ƕ��ڣ��ڣ��򻭵㣬���ڣ���������*/
      if (OLED_IsInAngle(0, j, StartAngle, EndAngle)) {OLED_DrawPoint(X, Y + j);}
    }
  }
  
  while (x < y)             //����X���ÿ����
  {
    x ++;
    
    if (d < 0)              //��һ�����ڵ�ǰ�㶫��
    {
      d += 2 * x + 1;
    }
    else                    //��һ�����ڵ�ǰ�㶫�Ϸ�
    {
      y --;
      d += 2 * (x - y) + 1;
    }
    
    /*�ڻ�Բ��ÿ����ʱ���ж�ָ�����Ƿ���ָ���Ƕ��ڣ��ڣ��򻭵㣬���ڣ���������*/
    if (OLED_IsInAngle( x,  y, StartAngle, EndAngle)) {OLED_DrawPoint(X + x, Y + y);}
    if (OLED_IsInAngle( y,  x, StartAngle, EndAngle)) {OLED_DrawPoint(X + y, Y + x);}
    if (OLED_IsInAngle(-x, -y, StartAngle, EndAngle)) {OLED_DrawPoint(X - x, Y - y);}
    if (OLED_IsInAngle(-y, -x, StartAngle, EndAngle)) {OLED_DrawPoint(X - y, Y - x);}
    if (OLED_IsInAngle( x, -y, StartAngle, EndAngle)) {OLED_DrawPoint(X + x, Y - y);}
    if (OLED_IsInAngle( y, -x, StartAngle, EndAngle)) {OLED_DrawPoint(X + y, Y - x);}
    if (OLED_IsInAngle(-x,  y, StartAngle, EndAngle)) {OLED_DrawPoint(X - x, Y + y);}
    if (OLED_IsInAngle(-y,  x, StartAngle, EndAngle)) {OLED_DrawPoint(X - y, Y + x);}
    
    if (IsFilled)           //ָ��Բ�����
    {
      /*�����м䲿��*/
      for (j = -y; j < y; j ++)
      {
        /*�����Բ��ÿ����ʱ���ж�ָ�����Ƿ���ָ���Ƕ��ڣ��ڣ��򻭵㣬���ڣ���������*/
        if (OLED_IsInAngle( x, j, StartAngle, EndAngle)) {OLED_DrawPoint(X + x, Y + j);}
        if (OLED_IsInAngle(-x, j, StartAngle, EndAngle)) {OLED_DrawPoint(X - x, Y + j);}
      }
      
      /*�������ಿ��*/
      for (j = -x; j < x; j ++)
      {
        /*�����Բ��ÿ����ʱ���ж�ָ�����Ƿ���ָ���Ƕ��ڣ��ڣ��򻭵㣬���ڣ���������*/
        if (OLED_IsInAngle(-y, j, StartAngle, EndAngle)) {OLED_DrawPoint(X - y, Y + j);}
        if (OLED_IsInAngle( y, j, StartAngle, EndAngle)) {OLED_DrawPoint(X + y, Y + j);}
      }
    }
  }
}

/**
 * @brief       OLED������ʼ����
 * @param       ��
 * @retval      ��
 * @note        ��
 */
void OLED_Test_Start(void)
{
  /*��(0, 0)λ����ʾ�ַ�'A'�������СΪ8*16����*/
  OLED_ShowChar(0, 0, 'B', OLED_8X16);
  
  /*��(16, 0)λ����ʾ�ַ���"Hello World!"�������СΪ8*16����*/
  OLED_ShowString(16, 0, "Hello World!", OLED_8X16);
  
  /*��(0, 18)λ����ʾ�ַ�'A'�������СΪ6*8����*/
  OLED_ShowChar(0, 18, 'A', OLED_6X8);
  
  /*��(16, 18)λ����ʾ�ַ���"Hello World!"�������СΪ6*8����*/
  OLED_ShowString(16, 18, "Hello World!", OLED_6X8);
  
  /*��(0, 28)λ����ʾ����12345������Ϊ5�������СΪ6*8����*/
  OLED_ShowNum(0, 28, 12345, 5, OLED_6X8);
  
  /*��(40, 28)λ����ʾ�з�������-66������Ϊ2�������СΪ6*8����*/
  OLED_ShowSignedNum(40, 28, -66, 2, OLED_6X8);
  
  /*��(70, 28)λ����ʾʮ����������0xA5A5������Ϊ4�������СΪ6*8����*/
  OLED_ShowHexNum(70, 28, 0xA5A5, 4, OLED_6X8);
  
  /*��(0, 38)λ����ʾ����������0xA5������Ϊ8�������СΪ6*8����*/
  OLED_ShowBinNum(0, 38, 0xA5, 8, OLED_6X8);
  
  /*��(60, 38)λ����ʾ��������123.45���������ֳ���Ϊ3��С�����ֳ���Ϊ2�������СΪ6*8����*/
  OLED_ShowFloatNum(60, 38, -1243.45, 4, 2, OLED_6X8);
  
  /*��(0, 48)λ����ʾ���ִ�"��ã����硣"�������СΪ�̶���16*16����*/
  OLED_ShowChinese(0, 48, "���׸�");
  
  /*��(96, 18)λ�ô�ӡ��ʽ���ַ����������СΪ6*8���󣬸�ʽ���ַ���Ϊ"[%02d]"*/
  OLED_Printf(96, 18, OLED_6X8, "%+03d", -123);
  
  /*����OLED_Update��������OLED�Դ���������ݸ��µ�OLEDӲ��������ʾ*/
  OLED_Update();
  
  /*��ʱ2000ms���۲�����*/
  HAL_Delay(2000);
  
  /*���OLED�Դ�����*/
  OLED_Clear();
  
  /*��(5, 8)λ�û���*/
  OLED_DrawPoint(5, 8);
  
  /*��ȡ(5, 8)λ�õĵ�*/
  if (OLED_GetPoint(5, 8))
  {
    /*���ָ�������������(10, 4)λ����ʾ�ַ���"YES"�������СΪ6*8����*/
    OLED_ShowString(10, 4, "YES", OLED_6X8);
  }
  else
  {
    /*���ָ����δ����������(10, 4)λ����ʾ�ַ���"NO "�������СΪ6*8����*/
    OLED_ShowString(10, 4, "NO ", OLED_6X8);
  }
  
  /*��(40, 0)��(127, 15)λ��֮�仭ֱ��*/
  OLED_DrawLine(40, 0, 127, 15);
  
  /*��(40, 15)��(127, 0)λ��֮�仭ֱ��*/
  OLED_DrawLine(40, 15, 127, 0);
  
  /*��(0, 20)λ�û����Σ���12���أ���15���أ�δ���*/
  OLED_DrawRectangle(0, 20, 12, 15, OLED_UNFILLED);
  
  /*��(0, 40)λ�û����Σ���12���أ���15���أ����*/
  OLED_DrawRectangle(0, 40, 12, 15, OLED_FILLED);
  
  /*��(20, 20)��(40, 25)��(30, 35)λ��֮�仭�����Σ�δ���*/
  OLED_DrawTriangle(20, 20, 40, 25, 30, 35, OLED_UNFILLED);
  
  /*��(20, 40)��(40, 45)��(30, 55)λ��֮�仭�����Σ����*/
  OLED_DrawTriangle(20, 40, 40, 45, 30, 55, OLED_FILLED);
  
  /*��(55, 27)λ�û�Բ���뾶8���أ�δ���*/
  OLED_DrawCircle(55, 27, 8, OLED_UNFILLED);
  
  /*��(55, 47)λ�û�Բ���뾶8���أ����*/
  OLED_DrawCircle(55, 47, 8, OLED_FILLED);
  
  /*��(82, 27)λ�û���Բ���������12���أ��������8���أ�δ���*/
  OLED_DrawEllipse(82, 27, 12, 8, OLED_UNFILLED);
  
  /*��(82, 47)λ�û���Բ���������12���أ��������8���أ����*/
  OLED_DrawEllipse(82, 47, 12, 8, OLED_FILLED);
  
  /*��(110, 18)λ�û�Բ�����뾶15���أ���ʼ�Ƕ�25�ȣ���ֹ�Ƕ�125�ȣ�δ���*/
  OLED_DrawArc(110, 18, 15, 25, 125, OLED_UNFILLED);
  
  /*��(110, 38)λ�û�Բ�����뾶15���أ���ʼ�Ƕ�25�ȣ���ֹ�Ƕ�125�ȣ����*/
  OLED_DrawArc(110, 38, 15, 25, 125, OLED_FILLED);
  
  /*����OLED_Update��������OLED�Դ���������ݸ��µ�OLEDӲ��������ʾ*/
  OLED_Update();
  
  /*��ʱ2000ms���۲�����*/
  HAL_Delay(2000);
}

/**
 * @brief       OLED������ʼ����
 * @param       ��
 * @retval      ��
 * @note        ��
 */
void OLED_Test(void)
{
  for (uint8_t i = 0; i < 4; i ++)
  {
    /*��OLED�Դ����鲿������ȡ������(0, i * 16)λ�ÿ�ʼ����128���أ���16����*/
    OLED_ReverseArea(0, i * 16, 128, 16);
    
    /*����OLED_Update��������OLED�Դ���������ݸ��µ�OLEDӲ��������ʾ*/
    OLED_Update();
    
    /*��ʱ1000ms���۲�����*/
    HAL_Delay(1000);
    
    /*��ȡ�������ݷ�ת����*/
    OLED_ReverseArea(0, i * 16, 128, 16);
  }
  
  /*��OLED�Դ�����ȫ������ȡ��*/
  OLED_Reverse();
  
  /*����OLED_Update��������OLED�Դ���������ݸ��µ�OLEDӲ��������ʾ*/
  OLED_Update();
  
  /*��ʱ1000ms���۲�����*/
  HAL_Delay(1000);
}
