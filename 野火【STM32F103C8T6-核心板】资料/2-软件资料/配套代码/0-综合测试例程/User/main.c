/**
  ******************************************************************************
  * @file    main.c
  * @author  fire
  * @version V1.0
  * @date    2013-xx-xx
  * @brief   rtc ���ԣ���ʾʱ���ʽΪ: xx:xx:xx
  ******************************************************************************
  * @attention
  *
  * ʵ��ƽ̨:Ұ�� F103-MINI STM32 ������ 
  * ��̳    :http://www.firebbs.cn
  * �Ա�    :https://fire-stm32.taobao.com
  *
  ******************************************************************************
  */
	
#include "stm32f10x.h"
#include "./usart/bsp_usart.h"
#include "./rtc/bsp_rtc.h"
#include "./key/bsp_key.h"
#include "./led/bsp_led.h"
#include "./Timbase/bsp_TiMbase.h" 


// N = 2^32/365/24/60/60 = 136 ��

/*ʱ��ṹ�壬Ĭ��ʱ��2000-01-01 00:00:00*/
struct rtc_time systmtime=
{
0,0,0,1,1,2000,0
};

extern __IO uint32_t TimeDisplay ;



//��*��ע�����
//��bsp_rtc.h�ļ��У�

//1.�����ú�USE_LCD_DISPLAY�����Ƿ�ʹ��LCD��ʾ
//2.�����ú�RTC_CLOCK_SOURCE_LSI��RTC_CLOCK_SOURCE_LSE����ʹ��LSE������LSI����

//3.STM32��LSE����Ҫ��ǳ��ϸ�ͬ���ĵ�·������������Ʒʱ����Щ��������⡣
//  ��ʵ����Ĭ��ʹ��LSI����
//  
//4.��������ϣ��RTC������Դ�������Ȼ���У���Ҫ��������ĵ�ز۰�װť�۵�أ�
//  �������Ҹĳ�ʹ���ⲿ����ģʽRTC_CLOCK_SOURCE_LSE
//  ť�۵���ͺţ�CR1220
/**
  * @brief  ������
  * @param  ��  
  * @retval ��
  */
int main()
{
	  USART_Config();		
		Key_GPIO_Config();
    BASIC_TIM_Init();
    LED_GPIO_Config();
  
		/* ����RTC���ж����ȼ� */
	  RTC_NVIC_Config();
	  RTC_CheckAndConfig(&systmtime);
	
	  while (1)
	  {
	    /* ÿ��1s ����һ��ʱ��*/
	    if (TimeDisplay == 1)
	    {
				/* ��ǰʱ�� */
	      Time_Display( RTC_GetCounter(),&systmtime); 		  
	      TimeDisplay = 0;
	    }		
      if( Key_Scan(KEY1_GPIO_PORT,KEY1_GPIO_PIN) == KEY_ON  )
      {
        /*LED1��ת*/
        LED1_TOGGLE;
        printf("KEY 1 is pressed\r\n");
      } 

      if( Key_Scan(KEY2_GPIO_PORT,KEY2_GPIO_PIN) == KEY_ON  )
      {
        /*LED2��ת*/
        LED2_TOGGLE;
        printf("KEY 2 is pressed\r\n");
      }
	  }
}

/***********************************END OF FILE*********************************/

