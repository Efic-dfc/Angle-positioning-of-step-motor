#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "timer.h"
#include "usart.h"

/*�ļ�
    Ŀ�ģ�ʹ�ô�������Ƕ�ͨ��TIM4CH1���ָ������������Ʋ�������Ƕȶ�λ
    ������:STM32c8t6
    ����ʹ��:   PB6    TIM4CH1����ͨ��
                PB5    ���Ʒ���IO��
                
    ��������ϵ�ҹ���QQ��2460693657
*/
static int target_angle = 0;        //Ŀ��Ƕ�
static int pulse = 0;               //�������
static double actual_angle = 0;     //ʵ�ʽǶ�
int main(void)
{		
    int len = 0;
    DIR_Init();
    delay_init();
    uart_init(9600);
    LED_Init();
    TIM4_PWM_Init(200,450);     //���ö�ʱ��PWM���ͨ�����Լ��������Ƶ�ʣ���Ӧ���ת���ٶȣ�15r/min������ʹ�ܶ�ʱ��
    TIM_SetCompare2(TIM4,100);  //����ռ�ձ�arr/2=50%
    while(1)
    {
        delay_ms(500);
        LED1 = !LED1;
        if(USART_RX_STA&0x8000)
        {		
            len=USART_RX_STA&0x3fff;        //�õ��˴ν��յ������ݳ���
            USART_RX_BUF[len]=0;         //�õ��ַ���
            if(len==1){
                target_angle =  USART_RX_BUF[0] - 0x30;       //�ַ�תΪ��ֵ
            }
            else if(len == 2){
                target_angle =  (USART_RX_BUF[0] - 0x30)*10 + USART_RX_BUF[1] - 0x30;
            }
            else if(len == 3){
                target_angle =  (USART_RX_BUF[0] - 0x30)*100 + (USART_RX_BUF[1] - 0x30)*10+USART_RX_BUF[2] - 0x30;
            }
            printf("************************************\r\n");
            printf("Ŀ��Ƕȣ�%d��\r\n",target_angle);
            USART_RX_STA=0;     //�����������־λ
            TIM_Cmd(TIM4, ENABLE);  //������ʱ��
        }
    }
}

//��ʱ��4�жϷ������
void TIM4_IRQHandler(void)   //TIM4�ж�
{
	if (TIM_GetITStatus(TIM4, TIM_IT_Update) != RESET) //���ָ����TIM�жϷ������:TIM �ж�Դ 
	{
		TIM_ClearITPendingBit(TIM4, TIM_IT_Update);  //���TIMx���жϴ�����λ:TIM �ж�Դ 
        TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);//ʹ�ܶ�ʱ��1�����ж�

        pulse++;    //�ж�һ�Σ��ۼ������һ
        actual_angle = pulse * 9.0 /80.0;   //ÿ�������Ӧ9/80 = 0.1125��
        if(actual_angle >= target_angle)
        {
            printf("�ۼ����������%d",pulse);
            pulse = 0;
            TIM_Cmd(TIM4, DISABLE);  //�رն�ʱ��
            printf("ʵ��ת���Ƕȣ�%.2lf\r\n",actual_angle);
        }
	}
}


