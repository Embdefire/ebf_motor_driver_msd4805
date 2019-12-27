#ifndef __BASIC_TIM_H
#define	__BASIC_TIM_H

#include "stm32h7xx.h"

#define CW  0
#define CCW 1

#define TRUE 1
#define FALSE 0

#define Pulse_width 20

//ϵͳ״̬
struct GLOBAL_FLAGS {
  //�����������������ʱ��ֵΪ1
  unsigned char running:1;
  //�����ڽ��յ�����ʱ��ֵΪ1
  unsigned char cmd:1;
  //���������������ʱ,ֵΪ1
  unsigned char out_ena:1;
};

extern struct GLOBAL_FLAGS status;
extern int stepPosition;

#define T1_FREQ 1000000     //��ʱ��Ƶ��
#define FSPR    200         //���������Ȧ����
#define SPR     (FSPR*100)  //100ϸ�ֵĲ���
// ��ѧ������ ����MSD_Move�����ļ򻯼���
#define ALPHA (2*3.14159/SPR)                    // 2*pi/spr
#define A_T_x100 ((long)(ALPHA*T1_FREQ*100))     // (ALPHA / T1_FREQ)*100
#define T1_FREQ_148 ((int)((T1_FREQ*0.676)/100)) // divided by 100 and scaled by 0.676
#define A_SQ (long)(ALPHA*2*10000000000)         // 
#define A_x20000 (int)(ALPHA*20000)              // ALPHA*20000
    
//�ٶ�����״̬
#define STOP  0
#define ACCEL 1
#define DECEL 2
#define RUN   3

typedef struct {
  //�������״̬
  unsigned char run_state : 3;
  //������з���
  unsigned char dir : 1;
  //��һ��������ʱ���ڣ�����ʱΪ���ٶ�����
  unsigned int step_delay;
  //��ʼ���ٵ�λ��
  unsigned int decel_start;
  //���پ���
  signed int decel_val;
  //��С��ʱ��������ٶȣ�
  signed int min_delay;
  //���ٻ��߼��ټ�����
  signed int accel_count;
} speedRampData;

//TIMͨ��CH1�����ź궨��
#define  MSD_PULSE_GPIO_CLK()             __GPIOB_CLK_ENABLE()
#define  MSD_PULSE_GPIO_PORT              GPIOB
#define  MSD_PULSE_GPIO_PIN               GPIO_PIN_1


//�߼���ʱ���궨��
#define MSD_PULSE_TIM           		        TIM3
#define ADVANCE_TIM_CLK_ENABLE()       		__TIM3_CLK_ENABLE()
#define ADVANCE_TIM_CH                    TIM_CHANNEL_4

// ��ʱ���ж�
#define            MSD_PULSE_TIM_IRQ                TIM3_IRQn
#define            MSD_PULSE_TIM_IRQHandler         TIM3_IRQHandler

// PWM �źŵ�Ƶ�� F = TIM_CLK/{(ARR+1)*(PSC+1)}
#define            MSD_PULSE_TIM_PERIOD             (10-1)
#define            MSD_PULSE_TIM_PSC                (72-1)

// ��������������
#define            MSD_DIR_GPIO_CLK()               __GPIOD_CLK_ENABLE()
#define            MSD_DIR_PORT                   GPIOD
#define            MSD_DIR_PIN                    GPIO_PIN_11

// ����������ʹ������
#define            MSD_ENA_GPIO_CLK()               __GPIOD_CLK_ENABLE()
#define            MSD_ENA_PORT                     GPIOD
#define            MSD_ENA_PIN                      GPIO_PIN_12


#define DIR(a)	if (a == CW)	\
					HAL_GPIO_WritePin(MSD_DIR_PORT,MSD_DIR_PIN,GPIO_PIN_RESET);\
					else		\
					HAL_GPIO_WritePin(MSD_DIR_PORT,MSD_DIR_PIN,GPIO_PIN_SET)
                    
/**************************��������********************************/

void MSD_Init(void);
void MSD_ENA(FunctionalState NewState);
void MSD_Move(signed int step, unsigned int accel, unsigned int decel, unsigned int speed);

void TIM_Advance_Init(void);

#endif /* __BASIC_TIM_H */

