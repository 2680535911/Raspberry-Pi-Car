/*****************************************************************************
函数功能：利用通用定时器输出PWM波控制舵机转动角度，舵机转动角度范围：0`-270`

舵机分析：舵机接收PWM频率为50Hz,由f=1/T,当f=50时，T=0.02s,即20ms，
          因此可通过配置通用定时器输出周期为20ms的PWM波来使舵机工作
          
相关配置：定时器选取通用定时器3，GPIO口输出为PB4、PB5

参数设置：自动装载值：2000，定时器分频系数：900，根据公式：
          计数频率：90M/900=0.1M，PWM频率：0.1M/2000=50Hz
          
个人总结：输出的方波周期就是自动重装载值的值（us为单位），占空比 = compare / arr
*****************************************************************************/
#include "duoji.h"

TIM_HandleTypeDef TIM3_Handler;
TIM_OC_InitTypeDef TIM3_CH2_Handler;
TIM_OC_InitTypeDef TIM3_CH1_Handler; 

//舵机初始化函数，这里使用到的是定时器3通道1、2输出PWM
void duoji_init(u16 arr,u16 psc)
{
    TIM3_Handler.Instance=TIM3;//选取通用定时器3
    TIM3_Handler.Init.Prescaler=psc;//定时器分频
    TIM3_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;//向上计数模式
    TIM3_Handler.Init.Period=arr;//自动重装载值
    TIM3_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//
    HAL_TIM_PWM_Init(&TIM3_Handler);//初始化PWM配置
	
		TIM3_CH1_Handler.OCMode = TIM_OCMODE_PWM1; //选取模式1
		TIM3_CH1_Handler.Pulse = arr/2; //设置比较值，确定占空比
		TIM3_CH1_Handler.OCNPolarity = TIM_OCPOLARITY_LOW; //输出比较极性为低
		HAL_TIM_PWM_ConfigChannel(&TIM3_Handler, &TIM3_CH1_Handler, TIM_CHANNEL_1); //配置TIM3通道1
		HAL_TIM_PWM_Start(&TIM3_Handler, TIM_CHANNEL_1); //开启PWM通道1
	
    TIM3_CH2_Handler.OCMode=TIM_OCMODE_PWM1;//选取模式1
    TIM3_CH2_Handler.Pulse=arr/2;//设置比较值，确定占空比
    TIM3_CH2_Handler.OCNPolarity=TIM_OCPOLARITY_LOW;//输出比较极性为低
    HAL_TIM_PWM_ConfigChannel(&TIM3_Handler,&TIM3_CH2_Handler,TIM_CHANNEL_2);//配置TIM3通道2
    HAL_TIM_PWM_Start(&TIM3_Handler,TIM_CHANNEL_2);//开启PWM通道2
	
}

//回调函数
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_TIM3_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    
    GPIO_Initure.Pin=GPIO_PIN_5;//PB5
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;//复用推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;//上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;//高速
    GPIO_Initure.Alternate=GPIO_AF2_TIM3;//复用为TIM3_CH2
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);//初始化GPIOB
	
		GPIO_Initure.Pin=GPIO_PIN_4;//PB5
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;//复用推挽输出
    GPIO_Initure.Pull=GPIO_PULLUP;//上拉
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;//高速
    GPIO_Initure.Alternate=GPIO_AF2_TIM3;//复用为TIM3_CH2
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);//初始化GPIOB
}

//设置 TIM 通道 4 的占空比
//compare:比较值
void TIM_SetTIM3Compare1(u32 compare)//A舵机
{
		TIM3->CCR1 = compare;
}

void TIM_SetTIM3Compare2(u32 compare)//B舵机
{
    TIM3->CCR2 = compare;
}
