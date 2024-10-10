#ifndef DRV_OLED_H_
#define DRV_OLED_H_

#include "main.h"

#define OLED_MODE 0
#define SIZE 8
#define XLevelL     0x00
#define XLevelH     0x10
#define Max_Column  128
#define Max_Row     64
#define Brightness  0xFF
#define X_WIDTH     128
#define Y_WIDTH     64



#define OLED_SCLK_Clr() DL_GPIO_clearPins(PORTA_PORT,PORTA_OLED_SCL_PIN);  //CLK
#define OLED_SCLK_Set() DL_GPIO_setPins(PORTA_PORT,PORTA_OLED_SCL_PIN);

#define OLED_SDIN_Clr() DL_GPIO_clearPins(PORTB_PORT,PORTB_OLED_SDA_PIN);  //DIN
#define OLED_SDIN_Set() DL_GPIO_setPins(PORTB_PORT,PORTB_OLED_SDA_PIN);

#define OLED_CMD  0
#define OLED_DATA 1


// Functions to control OLED are as follows
void OLED_WR_Byte(unsigned dat,unsigned cmd);
void OLED_Display_On(void);
void OLED_Display_Off(void);
void OLED_Init(void);
void OLED_Clear(unsigned bit);
void OLED_DrawPoint(u8 x,u8 y,u8 t);
void OLED_Fill(u8 x1,u8 y1,u8 x2,u8 y2,u8 dot);
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size,u8 flag);
void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size,u8 flag);
void OLED_ShowNum2(u8 x,u8 y,u32 num,u8 size1,u8 flag);
void OLED_ShowHexNum(u8 x,u8 y,u32 num,u8 size1,u8 flag);
void OLED_ShowVI(u8 x,u8 y,u32 num,u8 size,u8 flag);
void OLED_ShowII(u8 x,u8 y,u32 num,u8 size2,u8 flag);
void OLED_ShowString(u8 x,u8 y,char *chr,u8 Char_Size,u8 flag);
void OLED_Set_Pos(unsigned char x, unsigned char y);
void Delay_1ms(unsigned int Del_1ms);
void fill_picture(unsigned char fill_Data);
void Picture();
void IIC_Start();
void IIC_Stop();
void Write_IIC_Command(unsigned char IIC_Command);
void Write_IIC_Data(unsigned char IIC_Data);
void Write_IIC_Byte(unsigned char IIC_Byte);
void IIC_Wait_Ack();

#endif
