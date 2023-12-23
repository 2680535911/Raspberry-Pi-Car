#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "usmart.h"
#include "duoji.h"
#include "key.h"
#include "lcd.h"
#include "sdram.h"
//自定义函数，供usmart_config.c调试调用
void led_set(u8 sta)
{
    LED0=sta;
}

int main(void)
{
    u8 len;	
	 u8 x=0;
	u8 lcd_id[12];
    HAL_Init();                     //初始化HAL库    
    Stm32_Clock_Init(360,25,2,8);   //设置时钟,180Mhz
    delay_init(180);
    uart_init(115200);
    LED_Init();
		LCD_Init();                     //LCD初始化
		SDRAM_Init();                   //SDRAM初始化
    duoji_init(2000-1,900-1);//50Hz频率
    //usmart_dev.init(90);//初始化usmart
    sprintf((char*)lcd_id,"LCD ID:%04X",lcddev.id);//将LCD ID打印到lcd_id数组。	
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
			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
			printf("\r\n您发送的消息为:\r\n");
			HAL_UART_Transmit(&UART1_Handler,(uint8_t*)USART_RX_BUF,len,1000);	//发送接收到的数据
			while(__HAL_UART_GET_FLAG(&UART1_Handler,UART_FLAG_TC)!=SET);		//等待发送结束
			printf("\r\n\r\n");//插入换行
			switch (USART_RX_BUF[0]) {
                case 'A':
                    // 执行A操作
									TIM_SetTIM3Compare1(110);
								//A舵机运行后B舵机再运行
									TIM_SetTIM3Compare2(110);
									POINT_COLOR=BLUE;	  
									LCD_ShowString(10,120,260,32,32,"execute A"); 
                    printf("execute A\r\n");
										delay_ms(1000);
                    break;
                case 'B':
                    // 执行B操作
									TIM_SetTIM3Compare1(162);
								//A舵机运行后B舵机再运行
									TIM_SetTIM3Compare2(110);
									POINT_COLOR=BLUE;  
									LCD_ShowString(10,120,260,32,32,"execute B"); 
                    printf("execute B\r\n");
										delay_ms(1000);
                    break;
                case 'C':
                    // 执行C操作
									TIM_SetTIM3Compare1(200);
								//A舵机运行后B舵机再运行
									TIM_SetTIM3Compare2(110);
									POINT_COLOR=BLUE;	  
									LCD_ShowString(10,120,260,32,32,"execute C"); 
                    printf("execute C\r\n");
										delay_ms(1000);
                    break;
                case 'D':
                    // 执行D操作
									TIM_SetTIM3Compare1(250);
								//A舵机运行后B舵机再运行
									TIM_SetTIM3Compare2(110);
										POINT_COLOR=BLUE;	  
										LCD_ShowString(10,120,260,32,32,"execute D"); 
                    printf("execute D\r\n");
										delay_ms(1000);
                    break;
                default:
                    // 错误警报
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
		//测试代码
        //TIM_SetTIM3Compare2(162);//居中
				//delay_ms(3000); 
        //TIM_SetTIM3Compare2(110);//左满
				//delay_ms(3000); 
        //TIM_SetTIM3Compare2(200);//右满
				//delay_ms(3000); 
	}
		delay_ms(1000);	
}
}
