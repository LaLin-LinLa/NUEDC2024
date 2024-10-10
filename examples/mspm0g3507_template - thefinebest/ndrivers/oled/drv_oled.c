#include "drv_oled.h"
#include "oled_fout.h"

// the storage format is as follow
//[0]0 1 2 3 ... 127
//[1]0 1 2 3 ... 127
//[2]0 1 2 3 ... 127
//[3]0 1 2 3 ... 127
//[4]0 1 2 3 ... 127
//[5]0 1 2 3 ... 127
//[6]0 1 2 3 ... 127
//[7]0 1 2 3 ... 127
//IIC Start
/**********************************************/
void IIC_Start()
{
    OLED_SCLK_Set();
    OLED_SDIN_Set();
    OLED_SDIN_Clr();
    OLED_SCLK_Clr();
}

/**********************************************
//IIC Stop
**********************************************/
void IIC_Stop()
{
OLED_SCLK_Set() ;
//  OLED_SCLK_Clr();
    OLED_SDIN_Clr();
    OLED_SDIN_Set();

}

void IIC_Wait_Ack()
{
    OLED_SCLK_Set() ;
    OLED_SCLK_Clr();
}
/**********************************************
// IIC Write byte
**********************************************/
void Write_IIC_Byte(unsigned char IIC_Byte)
{
    unsigned char i;
    unsigned char m,da;
    da=IIC_Byte;
    OLED_SCLK_Clr();
    for(i=0;i<8;i++)
    {
            m=da;
        //  OLED_SCLK_Clr();
        m=m&0x80;
        if(m==0x80)
        {OLED_SDIN_Set();}
        else OLED_SDIN_Clr();
            da=da<<1;
        OLED_SCLK_Set();
        OLED_SCLK_Clr();
        }


}
/**********************************************
// IIC Write Command
**********************************************/
void Write_IIC_Command(unsigned char IIC_Command)
{
   IIC_Start();
   Write_IIC_Byte(0x78);            //Slave address,SA0=0
    IIC_Wait_Ack();
   Write_IIC_Byte(0x00);            //write command
    IIC_Wait_Ack();
   Write_IIC_Byte(IIC_Command);
    IIC_Wait_Ack();
   IIC_Stop();
}
/**********************************************
// IIC Write Data
**********************************************/
void Write_IIC_Data(unsigned char IIC_Data)
{
   IIC_Start();
   Write_IIC_Byte(0x78);            //D/C#=0; R/W#=0
    IIC_Wait_Ack();
   Write_IIC_Byte(0x40);            //write data
    IIC_Wait_Ack();
   Write_IIC_Byte(IIC_Data);
    IIC_Wait_Ack();
   IIC_Stop();
}
void OLED_WR_Byte(unsigned dat,unsigned cmd)
{
    if(cmd)
            {
   Write_IIC_Data(dat);
        }
    else {
   Write_IIC_Command(dat);

    }


}


/********************************************
// fill_Picture
********************************************/
void fill_picture(unsigned char fill_Data)
{
    unsigned char m,n;
    for(m=0;m<8;m++)
    {
        OLED_WR_Byte(0xb0+m,0);     //page0-page1
        OLED_WR_Byte(0x00,0);       //low column start address
        OLED_WR_Byte(0x10,0);       //high column start address
        for(n=0;n<128;n++)
            {
                OLED_WR_Byte(fill_Data,1);
            }
    }
}

void Delay_1ms(unsigned int Del_1ms)
{
    _delay_ms(Del_1ms);
}


void OLED_Set_Pos(unsigned char x, unsigned char y)
{
    OLED_WR_Byte(0xb0+y,OLED_CMD);
    OLED_WR_Byte(((x&0xf0)>>4)|0x10,OLED_CMD);
    OLED_WR_Byte((x&0x0f),OLED_CMD);
}

void OLED_Display_On(void)
{
    OLED_WR_Byte(0X8D,OLED_CMD);
    OLED_WR_Byte(0X14,OLED_CMD);  //DCDC ON
    OLED_WR_Byte(0XAF,OLED_CMD);  //DISPLAY ON
}

void OLED_Display_Off(void)
{
    OLED_WR_Byte(0X8D,OLED_CMD);
    OLED_WR_Byte(0X10,OLED_CMD);  //DCDC OFF
    OLED_WR_Byte(0XAE,OLED_CMD);  //DISPLAY OFF
}

//0息屏  1全亮
void OLED_Clear(unsigned bit)
{
    u8 i,n;
    for(i=0;i<8;i++)
    {
        OLED_WR_Byte (0xb0+i,OLED_CMD);
        OLED_WR_Byte (0x00,OLED_CMD);
        OLED_WR_Byte (0x10,OLED_CMD);
        for(n=0;n<128;n++)OLED_WR_Byte(bit,OLED_DATA);
    }
}
void OLED_On(void)
{
    u8 i,n;
    for(i=0;i<8;i++)
    {
        OLED_WR_Byte (0xb0+i,OLED_CMD);
        OLED_WR_Byte (0x00,OLED_CMD);
        OLED_WR_Byte (0x10,OLED_CMD);
        for(n=0;n<128;n++)OLED_WR_Byte(1,OLED_DATA);
    }
}

//OLED_WR_Byte(flag ? ~0xFF : 0xFF, OLED_DATA);

//x:0~127
//y:0~63
//size:16/12
//0正常显示，1反显
void OLED_ShowChar(u8 x,u8 y,u8 chr,u8 Char_Size,u8 flag)
{
    unsigned char c=0,i=0;
    c=chr-' ';
    if(x>Max_Column-1){x=0;y=y+2;}
    if(Char_Size ==16)
        {
        OLED_Set_Pos(x,y);
        for(i=0;i<8;i++)
        OLED_WR_Byte((flag ? ~(F8X16[c*16+i]) : F8X16[c*16+i]),OLED_DATA);
        OLED_Set_Pos(x,y+1);
        for(i=0;i<8;i++)
        OLED_WR_Byte((flag ? ~(F8X16[c*16+i+8]) : F8X16[c*16+i+8]),OLED_DATA);
        }
        else {
            OLED_Set_Pos(x,y);
            for(i=0;i<6;i++)
            OLED_WR_Byte((flag ? ~(F6x8[c][i]) : F6x8[c][i]),OLED_DATA);
        }
}

u32 oled_pow(u8 m,u8 n)
{
    u32 result=1;
    while(n--)result*=m;
    return result;
}

void OLED_ShowNum(u8 x,u8 y,u32 num,u8 len,u8 size2,u8 flag)
{
    u8 t,temp;
    u8 enshow=0;
    for(t=0;t<len;t++)
    {
        temp=(num/oled_pow(10,len-t-1))%10;
        if(enshow==0&&t<(len-1))
        {
            if(temp==0)
            {
                OLED_ShowChar(x+(size2/2)*t,y,' ',size2,flag);
                continue;
            }else enshow=1;

        }
        OLED_ShowChar(x+(size2/2)*t,y,temp+'0',size2,flag);
    }
}
//m^n
u32 OLED_Pow(u8 m,u8 n)
{
	u32 result=1;
	while(n--)
	{
	  result*=m;
	}
	return result;
}

void OLED_ShowNum2(u8 x,u8 y,u32 num,u8 size1,u8 flag)
{
	u8 t,temp,m=0,len;
	u32 num1 = num;
	if(size1==8)	m=2;
	while(num1)
	{	len++;	num1 /= 10;	}
	for(t=0;t<len;t++)
	{
		temp=(num/OLED_Pow(10,len-t-1))%10;
		if(temp==0)
			OLED_ShowChar(x+(size1/2+m)*t,y,'0',size1,flag);
		else 
			  OLED_ShowChar(x+(size1/2+m)*t,y,temp+'0',size1,flag);
  }
}

void OLED_ShowVI(u8 x,u8 y,u32 num,u8 size2,u8 flag)
{
    OLED_ShowNum(x+size2*4-1,y,num%10,1,size2,flag);
    OLED_ShowNum(x+size2*3-1,y,num/10%10,1,size2,flag);
    OLED_ShowNum(x+size2*2-1,y,num/100%10,1,size2,flag);
    //OLED_ShowString(x+size2*1-1,y,".",size2,flag);
    //OLED_ShowNum(x-1,y,num/1000,1,size2,flag);
}

void OLED_ShowII(u8 x,u8 y,u32 num,u8 size2,u8 flag)
{
    OLED_ShowNum(x+size2*4-1,y,num%10,1,size2,flag);
	  OLED_ShowString(x+size2*3-1,y,".",size2,flag);
    OLED_ShowNum(x+size2*2-1,y,num/10%10,1,size2,flag);
    OLED_ShowNum(x+size2*1-1,y,num/100%10,1,size2,flag);
}


void OLED_ShowString(u8 x,u8 y,char *chr,u8 Char_Size,u8 flag)
{
    unsigned char j=0;
    while (chr[j]!='\0')
    {       OLED_ShowChar(x,y,chr[j],Char_Size,flag);
						if(Char_Size==16)
							x+=8;
						else 
							x+=6;
        if(x>120){x=0;y+=2;}
            j++;
    }
}

//16进制 
void OLED_ShowHexNum(u8 x,u8 y,u32 num,u8 size1,u8 flag)
{
	u8 t,temp,len=0;
	u32 num1 = num;
	while(num1)
	{	len++;	num1 /= 16;	}
	OLED_ShowString(x,y,"0X",size1,flag);
	for(t=0;t<len;t++)
	{
		temp=(num/OLED_Pow(16,len-t-1))%16;
		if(temp<10)
			OLED_ShowNum2(x+(size1/2)*(t+3),y,temp,size1,flag);
		else
			OLED_ShowChar(x+(size1/2)*(t+3),y,temp+55,size1,flag);
	}
}

void OLED_Init(void)
{
		OLED_SCLK_Set();
		OLED_SDIN_Set();
    Delay_1ms(200);
    OLED_WR_Byte(0xAE,OLED_CMD);//--display off
    OLED_WR_Byte(0x00,OLED_CMD);//---set low column address
    OLED_WR_Byte(0x10,OLED_CMD);//---set high column address
    OLED_WR_Byte(0x40,OLED_CMD);//--set start line address
    OLED_WR_Byte(0xB0,OLED_CMD);//--set page address
    OLED_WR_Byte(0x81,OLED_CMD); // contract control
    OLED_WR_Byte(0xFF,OLED_CMD);//--128
    OLED_WR_Byte(0xA6,OLED_CMD);//--normal / reverse
    OLED_WR_Byte(0xA8,OLED_CMD);//--set multiplex ratio(1 to 64)
    OLED_WR_Byte(0x3F,OLED_CMD);//--1/32 duty
    OLED_WR_Byte(0xD3,OLED_CMD);//-set display offset
    OLED_WR_Byte(0x00,OLED_CMD);//

    OLED_WR_Byte(0xD5,OLED_CMD);//set osc division
    OLED_WR_Byte(0x80,OLED_CMD);//

    OLED_WR_Byte(0xD8,OLED_CMD);//set area color mode off
    OLED_WR_Byte(0x05,OLED_CMD);//

    OLED_WR_Byte(0xD9,OLED_CMD);//Set Pre-Charge Period
    OLED_WR_Byte(0xF1,OLED_CMD);//

    OLED_WR_Byte(0xDA,OLED_CMD);//set com pin configuartion
    OLED_WR_Byte(0x12,OLED_CMD);//

    OLED_WR_Byte(0xDB,OLED_CMD);//set Vcomh
    OLED_WR_Byte(0x30,OLED_CMD);//

    OLED_WR_Byte(0x8D,OLED_CMD);//set charge pump enable
    OLED_WR_Byte(0x14,OLED_CMD);//
		
		OLED_WR_Byte(0xA0,OLED_CMD);//0xa0左右反置 0xa1正常
	  OLED_WR_Byte(0xC0,OLED_CMD);//0xc0上下反置 0xc8正常
    OLED_WR_Byte(0xAF,OLED_CMD);//--turn on oled panel
}





