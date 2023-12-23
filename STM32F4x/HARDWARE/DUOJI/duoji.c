/*****************************************************************************
�������ܣ�����ͨ�ö�ʱ�����PWM�����ƶ��ת���Ƕȣ����ת���Ƕȷ�Χ��0`-270`

����������������PWMƵ��Ϊ50Hz,��f=1/T,��f=50ʱ��T=0.02s,��20ms��
          ��˿�ͨ������ͨ�ö�ʱ���������Ϊ20ms��PWM����ʹ�������
          
������ã���ʱ��ѡȡͨ�ö�ʱ��3��GPIO�����ΪPB4��PB5

�������ã��Զ�װ��ֵ��2000����ʱ����Ƶϵ����900�����ݹ�ʽ��
          ����Ƶ�ʣ�90M/900=0.1M��PWMƵ�ʣ�0.1M/2000=50Hz
          
�����ܽ᣺����ķ������ھ����Զ���װ��ֵ��ֵ��usΪ��λ����ռ�ձ� = compare / arr
*****************************************************************************/
#include "duoji.h"

TIM_HandleTypeDef TIM3_Handler;
TIM_OC_InitTypeDef TIM3_CH2_Handler;
TIM_OC_InitTypeDef TIM3_CH1_Handler; 

//�����ʼ������������ʹ�õ����Ƕ�ʱ��3ͨ��1��2���PWM
void duoji_init(u16 arr,u16 psc)
{
    TIM3_Handler.Instance=TIM3;//ѡȡͨ�ö�ʱ��3
    TIM3_Handler.Init.Prescaler=psc;//��ʱ����Ƶ
    TIM3_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;//���ϼ���ģʽ
    TIM3_Handler.Init.Period=arr;//�Զ���װ��ֵ
    TIM3_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//
    HAL_TIM_PWM_Init(&TIM3_Handler);//��ʼ��PWM����
	
		TIM3_CH1_Handler.OCMode = TIM_OCMODE_PWM1; //ѡȡģʽ1
		TIM3_CH1_Handler.Pulse = arr/2; //���ñȽ�ֵ��ȷ��ռ�ձ�
		TIM3_CH1_Handler.OCNPolarity = TIM_OCPOLARITY_LOW; //����Ƚϼ���Ϊ��
		HAL_TIM_PWM_ConfigChannel(&TIM3_Handler, &TIM3_CH1_Handler, TIM_CHANNEL_1); //����TIM3ͨ��1
		HAL_TIM_PWM_Start(&TIM3_Handler, TIM_CHANNEL_1); //����PWMͨ��1
	
    TIM3_CH2_Handler.OCMode=TIM_OCMODE_PWM1;//ѡȡģʽ1
    TIM3_CH2_Handler.Pulse=arr/2;//���ñȽ�ֵ��ȷ��ռ�ձ�
    TIM3_CH2_Handler.OCNPolarity=TIM_OCPOLARITY_LOW;//����Ƚϼ���Ϊ��
    HAL_TIM_PWM_ConfigChannel(&TIM3_Handler,&TIM3_CH2_Handler,TIM_CHANNEL_2);//����TIM3ͨ��2
    HAL_TIM_PWM_Start(&TIM3_Handler,TIM_CHANNEL_2);//����PWMͨ��2
	
}

//�ص�����
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
    GPIO_InitTypeDef GPIO_Initure;
    __HAL_RCC_TIM3_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    
    GPIO_Initure.Pin=GPIO_PIN_5;//PB5
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;//�����������
    GPIO_Initure.Pull=GPIO_PULLUP;//����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;//����
    GPIO_Initure.Alternate=GPIO_AF2_TIM3;//����ΪTIM3_CH2
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);//��ʼ��GPIOB
	
		GPIO_Initure.Pin=GPIO_PIN_4;//PB5
    GPIO_Initure.Mode=GPIO_MODE_AF_PP;//�����������
    GPIO_Initure.Pull=GPIO_PULLUP;//����
    GPIO_Initure.Speed=GPIO_SPEED_HIGH;//����
    GPIO_Initure.Alternate=GPIO_AF2_TIM3;//����ΪTIM3_CH2
    HAL_GPIO_Init(GPIOB,&GPIO_Initure);//��ʼ��GPIOB
}

//���� TIM ͨ�� 4 ��ռ�ձ�
//compare:�Ƚ�ֵ
void TIM_SetTIM3Compare1(u32 compare)//A���
{
		TIM3->CCR1 = compare;
}

void TIM_SetTIM3Compare2(u32 compare)//B���
{
    TIM3->CCR2 = compare;
}
