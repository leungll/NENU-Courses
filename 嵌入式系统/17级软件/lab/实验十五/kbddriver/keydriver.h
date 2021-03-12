/*
;************************************************************************************************************
;*				        				北京精仪达盛科技有限公司
;*                                     	     研    发    部
;*
;*                                 	     http://www.techshine.com
;*
;*--------------------------------------------- 文件信息 ----------------------------------------------------                                      
;*
;* 文件名称 : keydriver.h	
;* 文件功能 : 该文件为S3C44B0硬件平台的键盘程序的配置文件。
;* 补充说明 : 
;*-------------------------------------------- 最新版本信息 -------------------------------------------------
;* 修改作者 : ARM开发小组
;* 修改日期 : 2004/04/25
;* 版本声明 : V1.0.1
;*-------------------------------------------- 历史版本信息 -------------------------------------------------
;* 文件作者 : ARM开发小组
;* 创建日期 : 2004/04/20
;* 版本声明 : v1.0.0
;*-----------------------------------------------------------------------------------------------------------
;*-----------------------------------------------------------------------------------------------------------
;************************************************************************************************************
;*/
#include  "..\startup44b0\inc\44b.h"
#include  <stdio.h>
#include  <math.h>
#define  ARMII 1

/********************************** 送给HD7279指令 *************************************/

#define  cmd_reset 0xa4
#define  cmd_test  0xbf
#define  cmd_read  0x15
#define  decode1   0xc8

#define clr     (*(volatile unsigned *)0x04800000) = 0x01;
#define set     (*(volatile unsigned *)0x04800000) = 0x02;
extern unsigned char key_number;

/********************************** 函数定义 ********************************************/

void          long_delay   (void);
void          short_delay  (void);
void          write7279    (unsigned char,unsigned char);
unsigned char read7279     (unsigned char);
void          send_byte    (unsigned char);
unsigned char receive_byte (void);
void          KeyINT_Init  (void);													            
void          __irq Key_ISR(void);

extern void   Uart_Printf  (char port,char *fmt,...);

/******************************** 7279时钟模拟信号 ***************************************/

#if ARMII
	#define clrcs1     (*(volatile unsigned *)0x08200004) = 0x01;
	#define setcs1     (*(volatile unsigned *)0x08200004) = 0x02;

	#define clrclk     rPDATF = rPDATF & (~(0x1<<8)) 	//GPF8
	#define setclk     rPDATF = rPDATF | (0x1<<8)

	#define clrdat     rPDATF = rPDATF & (~(0x1<<5))	//GPF5
	#define setdat     rPDATF = rPDATF | (0x1<<5)
#else	 
	#define clrcs1     rPDATA = rPDATA & (~(0x1<<8)) //GPA8
	#define setcs1     rPDATA = rPDATA | (0x1<<8)
	#define clrclk     rPDATC = rPDATC & (~(0x1<<8)) //GPC8
	#define setclk     rPDATC = rPDATC | (0x1<<8)
	#define clrdat     rPDATE = rPDATE & (~(0x1<<7))//GPE7
	#define setdat     rPDATE = rPDATE | (0x1<<7) 
#endif
 



/*
*************************************************************************************************************
*-													结束文件                                               -*
*************************************************************************************************************
*/






          
