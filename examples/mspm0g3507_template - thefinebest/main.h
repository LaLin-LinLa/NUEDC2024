#ifndef __MAIN_H
#define __MAIN_H
#ifdef __cplusplus
extern "C" {
#endif
#include "ti_msp_dl_config.h"
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "math.h"

	
//快速低通滤波
#define UTILS_LP_FAST(value, sample, filter_constant)    (value -= (filter_constant) * ((value) - (sample)))
//限幅
#define _LimitMax(input, max)   \
    {                          \
        if (input > max)       \
        {                      \
            input = max;       \
        }                      \
        else if (input < -max) \
        {                      \
            input = -max;      \
        }                      \
    }
#define _ABS(X)  (((X)>0)?(X):-(X))

#define u32 unsigned int
#define u16 unsigned short
#define u8 unsigned char
	
#define no_voltage_enable_default 0
#define no_voltage_upper_default 7.2f
#define no_voltage_lower_default 5.5f

#define turn_kp_default1						30.0f 	//基于红外对管识别轨迹时,自主寻迹的位置控制器比例参数KP	
#define turn_ki_default1						0.0f		//基于红外对管识别轨迹时,自主寻迹的位置控制器积分参数KI	
#define turn_kd_default1						150			//基于红外对管识别轨迹时,自主寻迹的位置控制器微分参数KD	
#define turn_scale_default        	0.15f		//转向控制器输出转换到轮子期望差速时的量程转换系数


extern float vcc;
extern void _delay_us(uint16_t us);
extern void _delay_ms(uint16_t ms);
extern void nop();

#ifdef __cplusplus
}
#endif
#endif
