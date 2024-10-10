/***//****************************************
      https://github.com/RagingWaves
----------------------------------------------
 * @file        Smooth_Filter.c/h
 * @brief       通用滑动平均滤波器
 * @mark        1.  完成--22.4.8
 * @version     V1.0.0
 * @auther      ZYuan
 * @url         
----------------------------------------------
****************************************//***/

#include "Smooth_Filter.h"

/**
  * @brief  滤波器初始化
  * @param  滤波器
  * @param  滤波器数据深度
  * @retval 1：初始化失败；  0：初始化成功
  */
int SmoothFilter_Init(SmoothFilter_t *smooth_filter, int dp) {
	int i;
#if SMOOTH_FILTER_DATA_DP > 8
	if(dp > SMOOTH_FILTER_DATA_DP)
		return 1;
#else
	if(dp > 8)
		return 1;
#endif
	smooth_filter->dp      = dp;
	smooth_filter->pointer = 0;
	for(i = 0; i < 4; i++) {
		smooth_filter->raw_data[i] = 0;
	}
	return 0;
}

/**
  * @brief  滤波
  * @param  滤波器
  * @param  原始数据
  * @retval 滤波结果
  */
float SmoothFilter_Calc(SmoothFilter_t *smooth_filter, float data) {
	int i;
	float ave = 0;
	smooth_filter->raw_data[smooth_filter->pointer] = data;
	if(++smooth_filter->pointer == smooth_filter->dp)
		smooth_filter->pointer = 0;
	for(i = 0; i < smooth_filter->dp; i++) {
		ave += smooth_filter->raw_data[i];
	}
	ave /= smooth_filter->dp;
	return ave;
}

