#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "timer.h"
#include "usart.h"

/*文件
    目的：使用串口输入角度通过TIM4CH1输出指定个数脉冲控制步进电机角度定位
    开发板:STM32c8t6
    引脚使用:   PB6    TIM4CH1脉冲通道
                PB5    控制方向IO口
                
    有问题联系我哈，QQ：2460693657
*/
static int target_angle = 0;        //目标角度
static int pulse = 0;               //脉冲个数
static double actual_angle = 0;     //实际角度
int main(void)
{		
    int len = 0;
    DIR_Init();
    delay_init();
    uart_init(9600);
    LED_Init();
    TIM4_PWM_Init(200,450);     //配置定时器PWM输出通道，以及脉冲输出频率（对应电机转动速度：15r/min）但不使能定时器
    TIM_SetCompare2(TIM4,100);  //设置占空比arr/2=50%
    while(1)
    {
        delay_ms(500);
        LED1 = !LED1;
        if(USART_RX_STA&0x8000)
        {		
            len=USART_RX_STA&0x3fff;        //得到此次接收到的数据长度
            USART_RX_BUF[len]=0;         //得到字符串
            if(len==1){
                target_angle =  USART_RX_BUF[0] - 0x30;       //字符转为数值
            }
            else if(len == 2){
                target_angle =  (USART_RX_BUF[0] - 0x30)*10 + USART_RX_BUF[1] - 0x30;
            }
            else if(len == 3){
                target_angle =  (USART_RX_BUF[0] - 0x30)*100 + (USART_RX_BUF[1] - 0x30)*10+USART_RX_BUF[2] - 0x30;
            }
            printf("************************************\r\n");
            printf("目标角度：%d度\r\n",target_angle);
            USART_RX_STA=0;     //结束，清除标志位
            TIM_Cmd(TIM4, ENABLE);  //开启定时器
        }
    }
}

//定时器4中断服务程序
void TIM4_IRQHandler(void)   //TIM4中断
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //检查指定的TIM中断发生与否:TIM 中断源 
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  //清除TIMx的中断待处理位:TIM 中断源 
        TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);//使能定时器1更新中断

        pulse++;    //中断一次，累计脉冲加一
        actual_angle = pulse * 9.0 /80.0;   //每个脉冲对应9/80 = 0.1125°
        if(actual_angle >= target_angle)
        {
            printf("累计脉冲个数：%d",pulse);
            pulse = 0;
            TIM_Cmd(TIM4, DISABLE);  //关闭定时器
            printf("实际转动角度：%.2lf\r\n",actual_angle);
        }
	}
}


