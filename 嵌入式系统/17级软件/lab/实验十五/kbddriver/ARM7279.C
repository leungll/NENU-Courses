/*
;************************************************************************************************************
;*				        				北京精仪达盛科技有限公司
;*                                     	     研    发    部
;*
;*                                 	     http://www.techshine.com
;*
;*--------------------------------------------- 文件信息 ----------------------------------------------------                                      
;*
;* 文件名称 : ARM7279.c	
;* 文件功能 : 该文件为S3C44B0硬件平台的键盘程序。
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
#include "keydriver.h"
#define  s_clr   *((volatile unsigned *)0x04800000) = 0x1
#define  s_set   *((volatile unsigned *)0x04800000) = 0x2
unsigned char key_number=0xff;
/*
*************************************************************************************************************
- 函数名称 : void KeyINT_Init(void)
- 函数说明 : 键盘中断的初始化
- 输入参数 : 无
- 输出参数 : 无
*************************************************************************************************************
*/
void KeyINT_Init(void)													             
{
     if ((rINTPND & BIT_EINT4567))
    {
    	rI_ISPC = BIT_EINT4567;
    }
    rINTMSK  = ~(BIT_GLOBAL|BIT_EINT4567);								//使用外部中断4
    pISR_EINT4567 = (int)Key_ISR;
    
}

/*
*************************************************************************************************************
- 函数名称 : void Key_ISR(void)
- 函数说明 : 键盘中断的服务子程序
- 输入参数 : 无
- 输出参数 : 无
*************************************************************************************************************
*/
void __irq Key_ISR( void )
{ 
	int j,rr;
	
	//rINTMSK  = (BIT_GLOBAL|BIT_EINT4567);   // 关中断
	
	rr = rEXTINPND;
	
	#if ARMII
	if (rr == 0x2)
	#else
	if (rr == 0x1)
	#endif
	
   	{
  		//send_byte(cmd_test); 						//测试指令
  		
  		for(j=0;j<20;j++);							//延时
  	//	send_byte(cmd_reset); 						//清除显示
  		
  		key_number = read7279(cmd_read);
  		  		
  		#if ARMII
  		switch(key_number)
  		{ 

  		  case 0x04 :
  		   key_number = 0x08;
  		   break;
  		  case 0x05 :
  		   key_number = 0x09;
  		   break;
  		  case 0x06 :
  		   key_number = 0x0A;
  		   break;
  		  case 0x07 :
  		   key_number = 0x0B;
  		   break;
  		  case 0x08 :
  		   key_number = 0x04;
  		   break; 
  		  case 0x09 :
  		   key_number = 0x05;
  		   break;
  		  case 0x0A :
  		   key_number = 0x06;
  		   break;
  		  case 0x0b :
  		   key_number = 0x07;
  		   break;
  		 
  		   default:
  		    break;

  	     }
    //  	write7279(decode1+5,key_number/16*8);
    //	write7279(decode1+4,key_number & 0x0f);
    	
    	#else
    	switch(key_number)
  		{ 
  		
  		   case 0x0f :
  		   key_number = 0x04;
  		   break;
  		  case 0x07 :
  		   key_number = 0x00;
  		   break;
  		  case 0x08 :
  		   key_number = 0x0f;
  		   break;
  		  case 0x00 :
  		   key_number = 0x0b;
  		   break;
  		  case 0x09 :
  		   key_number = 0x07;
  		   break;
  		  case 0x01 :
  		   key_number = 0x03;
  		   break; 
  		  case 0x0a :
  		   key_number = 0x0e;
  		   break;
  		  case 0x02 :
  		   key_number = 0x0a;
  		   break;
  		  case 0x0b :
  		   key_number = 0x06;
  		   break;
  		  case 0x03 :
  		   key_number = 0x02;
  		   break;
  		  case 0x0c :
  		   key_number = 0x0d;
  		   break;
  		  case 0x04 :
  		   key_number = 0x09;
  		   break;
  		  case 0x0d :
  		   key_number = 0x05;
  		   break;
  		  case 0x05 :
  		   key_number = 0x01;
  		   break;
  		  case 0x0e :
  		   key_number = 0x0c;
  		   break;
  		  case 0x06 :
  		   key_number = 0x08;
  		   break;
  		   default:
  		    break;

  	     }
    	write7279(decode1+1,key_number/16);
    	write7279(decode1,key_number & 0x0f);
    	
    	#endif 
    	//Uart_Printf(0,"key_number=%x\n",key_number);
    	
  	}
  	#if ARMII
  		rEXTINPND = 0x2; 
  	#else
		rEXTINPND = 0x1; 
	#endif
	rI_ISPC = BIT_EINT4567;
  //	rINTMSK  = ~(BIT_GLOBAL|BIT_EINT4567);
}

/*
*************************************************************************************************************
- 函数名称 : void long_delay(void)
- 函数说明 : 长延时程序
- 输入参数 : 无
- 输出参数 : 无
*************************************************************************************************************
*/
void long_delay(void)
{ 
	unsigned char i;
   	for (i=0;i<0x70;i++)
   	{
	}
	
}

/*
*************************************************************************************************************
- 函数名称 : void short_delay(void)
- 函数说明 : 短延时程序
- 输入参数 : 无
- 输出参数 : 无
*************************************************************************************************************
*/
void short_delay(void)
{ 
	int i;
  	for(i=0;i<50;i++)
  	{
  	}

}

/*
*************************************************************************************************************
- 函数名称 : void send_byte(unsigned char out_byte )
- 函数说明 : 向7279发送一个字节的程序
- 输入参数 : out_byte
- 输出参数 : 无
*************************************************************************************************************
*/
void send_byte(unsigned char out_byte )
{
	unsigned int  i;
  	clrcs1;
  	s_clr;
  	long_delay();
  	for (i=0;i<8;i++)
  	{   
  		if (0x80 == (out_byte & 0x80))  
      	{ 
      		setdat;
      	}
      	else
      	{
      		clrdat;
      	}
      	setclk;
      	short_delay();
      	clrclk;
      	short_delay();
      	out_byte = out_byte<<1 ;
  	}
  	clrdat;
  
 }
 
/*
*************************************************************************************************************
- 函数名称 : unsigned char receive_byte (void)
- 函数说明 : 向7279接收一个字节的程序
- 输入参数 : 无
- 输出参数 : in_byte
*************************************************************************************************************
*/
unsigned char receive_byte (void)    
{
   	unsigned int i,in_byte;
   	setdat;
   	s_set;
   	long_delay();
   	#if ARMII
   	rPCONF = 0x9215A; 							//set the PF5 to input I/O
   	#else
   	rPCONE = 0x823EA; 						//set the PE7 to input I/O
   	#endif
    for(i=0;i<8;i++)
    {
    	setclk;
    	short_delay();
    	in_byte = in_byte<<1;
    	#if ARMII
    	if (0x01 == (rPDATF>>5 & 0x01))
    	#else
    	if (0x01 == (rPDATE>>7 & 0x01))
    	#endif
    	{ 
    		in_byte = (in_byte | (0x01));
    	}
    	
   	 	clrclk;
    	short_delay();
    }
    #if ARMII
    	 rPCONF = 0x9255A;						//set the PF5 to output I/O
    #else
    	rPCONE = 0x827EA;						//set the PE7 to output I/O
    #endif 
    clrdat;
    s_clr;
    short_delay();
    return(in_byte);
}
 
/*
*************************************************************************************************************
- 函数名称 : unsigned char read7279(unsigned char comand)
- 函数说明 : 读键盘指令程序
- 输入参数 : 无
- 输出参数 : in_byte
*************************************************************************************************************
*/    
unsigned char read7279(unsigned char comand)
{
  	send_byte(comand);
   	return (receive_byte());
}

/*
*************************************************************************************************************
- 函数名称 : void write7279 (unsigned char cmd, unsigned char dat)
- 函数说明 : 写键盘指令程序
- 输入参数 : 无
- 输出参数 : in_byte
*************************************************************************************************************
*/   
void write7279 (unsigned char cmd, unsigned char dat)
{
	send_byte(cmd);
 	send_byte(dat);
}

/*
*************************************************************************************************************
*-													结束文件                                               -*
*************************************************************************************************************
*/
    



