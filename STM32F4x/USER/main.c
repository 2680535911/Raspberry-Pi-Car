#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "usmart.h"
#include "duoji.h"
#include "key.h"
#include "lcd.h"
#include "sdram.h"
//�Զ��庯������usmart_config.c���Ե���
void led_set(u8 sta)
{
    LED0=sta;
}

int main(void)
{
    u8 len;	
	 u8 x=0;
	u8 lcd_id[12];
    HAL_Init();                     //��ʼ��HAL��    
    Stm32_Clock_Init(360,25,2,8);   //����ʱ��,180Mhz
    delay_init(180);
    uart_init(115200);
    LED_Init();
		LCD_Init();                     //LCD��ʼ��
		SDRAM_Init();                   //SDRAM��ʼ��
    duoji_init(2000-1,900-1);//50HzƵ��
    //usmart_dev.init(90);//��ʼ��usmart
    sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//��LCD ID��ӡ��lcd_id���顣	
	while(1)
	{  
		switch(x)
		{
			case 0:LCD_Clear(WHITE);break;
			case 1:LCD_Clear(BLACK);break;
			case 2:LCD_Clear(BLUE);break;
			case 3:LCD_Clear(RED);break;
			case 4:LCD_Clear(MAGENTA);break;
			case 5:LCD_Clear(GREEN);break;
			case 6:LCD_Clear(CYAN);break; 
			case 7:LCD_Clear(YELLOW);break;
			case 8:LCD_Clear(BRRED);break;
			case 9:LCD_Clear(GRAY);break;
			case 10:LCD_Clear(LGRAY);break;
			case 11:LCD_Clear(BROWN);break;
		}
		POINT_COLOR=RED;	  
		LCD_ShowString(10,40,260,32,32,"Apollo STM32F4"); 	

		if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			printf("\r\n�����͵���ϢΪ:\r\n");
			HAL_UART_Transmit(&UART1_Handler,(uint8_t*)USART_RX_BUF,len,1000);	//���ͽ��յ�������
			while(__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_TC)!=SET);		//�ȴ����ͽ���
			printf("\r\n\r\n");//���뻻��
			switch (USART_RX_BUF[0]) {
                case 'A':
                    // ִ��A����
									TIM_SetTIM3Compare1(110);
								//A������к�B���������
									TIM_SetTIM3Compare2(110);
									POINT_COLOR=BLUE;	  
									LCD_ShowString(10,120,260,32,32,"execute A"); 
                    printf("execute A\r\n");
										delay_ms(1000);
                    break;
                case 'B':
                    // ִ��B����
									TIM_SetTIM3Compare1(162);
								//A������к�B���������
									TIM_SetTIM3Compare2(110);
									POINT_COLOR=BLUE;  
									LCD_ShowString(10,120,260,32,32,"execute B"); 
                    printf("execute B\r\n");
										delay_ms(1000);
                    break;
                case 'C':
                    // ִ��C����
									TIM_SetTIM3Compare1(200);
								//A������к�B���������
									TIM_SetTIM3Compare2(110);
									POINT_COLOR=BLUE;	  
									LCD_ShowString(10,120,260,32,32,"execute C"); 
                    printf("execute C\r\n");
										delay_ms(1000);
                    break;
                case 'D':
                    // ִ��D����
									TIM_SetTIM3Compare1(250);
								//A������к�B���������
									TIM_SetTIM3Compare2(110);
										POINT_COLOR=BLUE;	  
										LCD_ShowString(10,120,260,32,32,"execute D"); 
                    printf("execute D\r\n");
										delay_ms(1000);
                    break;
                default:
                    // ���󾯱�
										POINT_COLOR=RED;	  
										LCD_ShowString(10,40,260,32,32,"No result"); 
                    printf("No result \r\n");
                    break;
            }
			USART_RX_STA=0;
		}
		else
		{
		POINT_COLOR=RED;	  
		LCD_ShowString(10,80,260,32,32,"No Found"); 
		//printf("No Found \r\n");
			//delay_ms(1000);
		//���Դ���
        //TIM_SetTIM3Compare2(162);//����
				//delay_ms(3000); 
        //TIM_SetTIM3Compare2(110);//����
				//delay_ms(3000); 
        //TIM_SetTIM3Compare2(200);//����
				//delay_ms(3000); 
	}
		delay_ms(1000);	
}
}
