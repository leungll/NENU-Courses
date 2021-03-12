/*
;************************************************************************************************************
;*				        				北京精仪达盛科技有限公司
;*                                     	     研    发    部
;*
;*                                 	     http://www.techshine.com
;*
;*--------------------------------------------- 文件信息 ----------------------------------------------------                                      
;*
;* 文件名称 : 44blib.c	
;* 文件功能 : 该文件为S3C44B0硬件平台的通用函数初始化。
;* 补充说明 : 
;*-------------------------------------------- 最新版本信息 -------------------------------------------------
;* 修改作者 : ARM7开发小组
;* 修改日期 : 2004/04/25
;* 版本声明 : V1.0.1
;*-------------------------------------------- 历史版本信息 -------------------------------------------------
;* 文件作者 : ARM7开发小组
;* 创建日期 : 2004/04/20
;* 版本声明 : v1.0.0
;*-----------------------------------------------------------------------------------------------------------
;*-----------------------------------------------------------------------------------------------------------
;************************************************************************************************************
;*/
#include "..\inc\44b.h"
#include "..\inc\44blib.h"
#include "..\inc\option.h"

#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define STACKSIZE    0xa00 			
#define HEAPEND     (_ISR_STARTADDRESS - STACKSIZE - 0x500) 
extern char Image$$RW$$Limit[];
void *mallocPt = Image$$RW$$Limit;
static int delayLoopCount = 400;

/*
*************************************************************************************************************
- 函数名称 :  void Delay(int time)
- 函数说明 :  系统延时
- 输入参数 :  time
- 输出参数 :  无
*************************************************************************************************************
*/
void Delay(int time)
{														              // time=0: 通过看门狗定时器调整延时函数
    int i,adjust = 0;									                            // time>0: 循环时间的数目
    													                                        // 最小 100us 
    if (time == 0)
    {
		time = 200;
		adjust = 1;
		delayLoopCount = 400;
		rWTCON = ((MCLK/1000000 - 1)<<8 ) | (2<<3);  	          // 1/64, Watch-dog,nRESET,interrupt disable
	 	rWTDAT = 0xffff;
		rWTCNT = 0xffff;	 
		rWTCON = ((MCLK/1000000-1)<<8)|(2<<3)|(1<<5); 	    // 1/64,Watch-dog enable, nRESET,interrupt disable 
    }
    
    for (;time>0;time--)
		for (i=0;i<delayLoopCount;i++);
		
    if (adjust == 1)
    {
		rWTCON = ((MCLK/1000000-1)<<8)|(2<<3);
		i = 0xffff - rWTCNT;   							                            //  1count/16us?????????
		delayLoopCount = 400*100/(i*64/200);			                              //  400*100/(i*64/200)   
    }
}

/*
*************************************************************************************************************
- 函数名称 :  Port_Init(void)
- 函数说明 :  端口初始化
- 输入参数 :  无
- 输出参数 :  无
*************************************************************************************************************
*/
	//注意:应遵循配置端口的次序
	// 1) 设定端口初值 2) 配置控制寄存器 3) 配置上拉电阻寄存器
void Port_Init(void)
{
	//端口A控制组 
	//  BIT 9	8	7	6	5	4	3	2	1	0            
	//      ADDR24	ADDR23	ADDR22	ADDR21	ADDR20	ADDR19	ADDR18	ADDR17	ADDR16	ADDR0   	      
	//      0,	0,	1,	1,	1,	1,	1,	1,	1,	1    
	
	rPCONA = 0x1ff;
		
	//端口B控制组
	//  BIT  10    9     8         7         6	5      4     3       2	    1	   0	    
	//      /CS5   /CS4  /CS3     /CS2       /CS1   0      0     /SRAS   /SCAS  SCLK   SCKE      
	//       	  ethernet    NANFLASH  USB    LED    LED    Sdram   Sdram  Sdram  Sdram     
	//      1,      1,    1,      1,         1,     0,     0,    1,      1,     1,     1          
	rPDATB = 0x7cf;
	rPCONB = 0x7cf;
    
	//端口C控制组
	// BIT    15	  14	   13     12	 11	    10	    9		8            7		  6	5	4	3	2	1	0           
	//        O	  0	   RXD1   TXD1	 nCTS1	   nCTS0    O	      M/S	    lcd	         lcd	lcd    lcd 	IIS	IIS	IIS	IIS             
	//        NAN_CLE NAN_ALE  Uart1  Uart1	 nCTS1	   nCTS0  NAN_CE      USB           VD4	         VD5	VD6    VD7    IISCLK	IISDI	IISDO	IISLRCK   
	//        01	  01	   11	  11	 11	    11	    01	       01           11	          11	11	11	11	 11	11	11                   

	// BIT	  
	//		 
	//		  
	//		  
	rPDATC = 0xffff;	//All IO is high
	rPCONC = 0x5ff5ffff;	
	rPUPC  = 0x0000;	//PULL UP RESISTOR should be enabled to I/O

	//端口D控制组
	//  BIT   7       6      5      4      3      2      1     0                                                      
	//        VFRAME  VM     VLINE  VCLK   VD3    VD2    VD1   VDO                                                      
	//        10      10     10     10     10     10     10    10                                                     
	//rPDATD= 0xff;
	rPCOND= 0xaaaa;
	rPUPD = 0x00;
	
	//端口E控制组
	//  Bit	 8		  7	      6		  5		 4		3		2		1		0	
	//		CODECLK	  TOUT4	  TOUT3	  TOUT2	 TOUT1	TOUT0	RXD0	TXD0	IN	
	//			10	  01	  10	  10	 10		10		10		10		00	
	rPDATE = 0x1;
	rPCONE = 0x26AA8;
	rPUPE  = 0x1FE;

	//端口F控制组
	//  Bit  8		  7		   6		5		 4	      3		   2	  1       0                          
	//       out     in        out      out      nXDREQ0  nXDACK0  nWAIT  IICSDA  IICSCL                  
	//       001	 000	   001		001	     11		  11	   10	  10      10                      
	rPDATF = 0x1FF;
	rPCONF = 0x827EA;
	rPUPF  = 0x0;

	//端口G控制组
	//  BIT  7   	6      5   	  4   	 3     2   	 1      0    	 
	//       INT7   INT6   INT5   out   INT3  INT2  INT1   INT0     
	//       11     11     11     01     11    11    11     11       
	rPDATG = 0x00;
	rPCONG = 0xfdff;
	rPUPG  = 0x0;	
	
	rSPUCR=0x7;  			//D15-D0 pull-up disable
	rEXTINT=0x22202222;       	//所有的外部硬件中断为低电平触发
	//rEXTINT=0x00;       	//所有的外部硬件中断为低电平触发
}
/*
*************************************************************************************************************
- 函数名称 : Uart_Init(int mclk,int baud,char port)
- 函数说明 : 串口初始化
- 输入参数 : mclk,baud
- 输出参数 : 无
*************************************************************************************************************
*/
void Uart_Init(int mclk,int baud,char port)
{
    int i;
    if (mclk == 0)
	{
		mclk = MCLK;
    }
    i = mclk / (baud * 16);							                 // 圆整 (int)((mclk/16.)/baud + 0.5) -1;
    if (port == 0)
    {												                                 //UART0 配置各控制寄存器
        rUFCON0 = 0x0;           					                                             // 禁用 FIFO 
        rUMCON0 = 0x0;
        rULCON0=0x3;     							                //正常模式,无奇偶校验,一个停止位,8个数据位
        //rULCON0=0x7;     						                    //正常模式,无奇偶校验,两个停止位,8个数据位
        rUCON0=0x245;     //RX边沿触发,TX电平触发,禁用延时中断,使用RX 错误中断,正常操作模式,中断请求或表决模式
        rUBRDIV0 = i;								                       //( (int)(mclk/16/baud + 0.5) -1 );
     }
    else if (port == 1)
    {												                                 //UART0 配置各控制寄存器
	 	rUFCON1 = 0x0;								                                             // 禁用 FIFO
    	rUMCON1 = 0x0;
        rULCON1 = 0x3;     							                //正常模式,无奇偶校验,一个停止位,8个数据位
    	//rULCON1 = 0x7;							                //正常模式,无奇偶校验,两个停止位,8个数据位							
    	rUCON1  = 0x245;  //RX边沿触发,TX电平触发,禁用延时中断,使用RX 错误中断,正常操作模式,中断请求或表决模式
    	rUBRDIV1 = i;								                      //( (int)(mclk/16./baud + 0.5) -1 );
    }
    for(i=0;i<100;i++);
}

/*
*************************************************************************************************************
- 函数名称 : Uart_TxEmpty(int port)
- 函数说明 : 等待发送转换寄存器空
- 输入参数 : port
- 输出参数 : 无
*************************************************************************************************************
*/
void Uart_TxEmpty(char port)
{
    if (port == 0)
		while(!(rUTRSTAT0 & 0x4)); 					                                  //一直等到发送转换器空.
    else
    	while(!(rUTRSTAT1 & 0x4)); 					                                  //一直等到发送转换器空.
}

/*
*************************************************************************************************************
- 函数名称 : Uart_Getch
- 函数说明 : 选择接收数据就绪的串口 
- 输入参数 : port
- 输出参数 : RdURXH0()，RdURXH1()
*************************************************************************************************************
*/
char Uart_Getch(char port)
{
    if (port == 0)
    {	    
		while(!(rUTRSTAT0 & 0x1)); 					                                          //接收数据就绪
		return RdURXH0();
    }
    else
    {
		while(!(rUTRSTAT1 & 0x1)); 					                                          //接收数据就绪
		return	rURXH1;
    }
}

/*
*************************************************************************************************************
- 函数名称 : Uart_GetKey
- 函数说明 : 得到串口的键值
- 输入参数 : port
- 输出参数 : RdURXH0()或0，rURXH1或0
*************************************************************************************************************
*/
char Uart_GetKey(char port)
{
    if (port == 0)
    {	    
		if(rUTRSTAT0 & 0x1)    						                                           //接收数据就绪
    	    return RdURXH0();
		else
	    	return 0;
    }
    else
    {
		if(rUTRSTAT1 & 0x1)    						                                           //接收数据就绪
	    	return rURXH1;
		else
	    	return 0;
    }
}

/*
*************************************************************************************************************
- 函数名称 : Uart_GetString(char *string)
- 函数说明 : 串口得到字符串
- 输入参数 : string
- 输出参数 : 无
*************************************************************************************************************
*/
void Uart_GetString(char *string,char port)
{
    char *string2 = string;
    char c;
    
    while ((c = Uart_Getch(port)) != '\r')
    {
		if (c == '\b')
		{
	    	if ((int)string2 < (int)string)
	    	{
				Uart_Printf(port,"\b \b");
				string--;
	    	}
		}
		else 
		{
	    	*string++=c;
	    	Uart_SendByte(c,port);
		}
    }
    *string='\0';
    Uart_SendByte('\n',port);
}

/*
*************************************************************************************************************
- 函数名称 : Uart_GetIntNum(void)
- 函数说明 : 得到串口初始号
- 输入参数 : 无
- 输出参数 : 无
*************************************************************************************************************
*/
int Uart_GetIntNum(char port)
{
    char str[30];
    char *string = str;
    int base = 10;
    int minus = 0;
    int lastIndex;
    int result = 0;
    int i;
    
    Uart_GetString(string,port);
    
    if (string[0] == '-')
    {
        minus = 1;
        string++;
    }
    
    if (string[0]=='0' && (string[1]=='x' || string[1]=='X'))
    {
		base = 16;
		string += 2;
    }
    
    lastIndex = strlen(string) - 1;
    if (string[lastIndex]=='h' || string[lastIndex]=='H')
    {
		base = 16;
		string[lastIndex] = 0;
		lastIndex--;
    }

    if (base == 10)
    {
		result = atoi(string);
		result = minus ? (-1*result):result;
    }
    else
    {
		for (i=0;i<=lastIndex;i++)
		{
    	    if (isalpha(string[i]))
	    	{
				if (isupper(string[i]))
		    		result = (result<<4)+string[i]-'A'+10;
				else
		    		result = (result<<4)+string[i]-'a'+10;
	    	}
	    	else
	    	{
				result = (result<<4)+string[i]-'0';
	    	}
		}
	
		result = minus ? (-1*result):result;
    }
    return result;
}

/*
*************************************************************************************************************
- 函数名称 : Uart_SendByte(int data)
- 函数说明 : 串口发送字节
- 输入参数 : data
- 输出参数 : 无
*************************************************************************************************************
*/
void Uart_SendByte(int data,char port)
{
    if (port == 0)
    {
		if (data == '\n')
		{
	    	while(!(rUTRSTAT0 & 0x2));
	    	//Delay(1);									                                 //由于高端的较慢响应 
	    	WrUTXH0('\r');
		}
		
		while(!(rUTRSTAT0 & 0x2)); 						                                  //一直等到 THR 为空
		//Delay(1);
		WrUTXH0(data);
    }
    else
    {
		if(data=='\n')
		{
    	    while(!(rUTRSTAT1 & 0x2));
	    	//Delay(10);								                                //由于高端的较慢响应
	    	rUTXH1='\r';
		}
		
		while(!(rUTRSTAT1 & 0x2));  					                                  //一直等到 THR 为空
		//Delay(10);
		rUTXH1=data;
    }	
}
		
/*
*************************************************************************************************************
- 函数名称 : Uart_SendString(char *pt)
- 函数说明 : 串口发送字符串
- 输入参数 : pt
- 输出参数 : 无
*************************************************************************************************************
*/
void Uart_SendString(char *pt,char port)
{
    while(*pt)
	Uart_SendByte(*pt++,port);
}

/*
*************************************************************************************************************
- 函数名称 : Uart_Printf(char *fmt,...)
- 函数说明 : 串口打印字符
- 输入参数 : fmt ...
- 输出参数 : 无
*************************************************************************************************************
*/
void Uart_Printf(char port,char *fmt,...)                         //如果您不使用 vsprintf(), 代码量将大幅减少
{
    va_list ap;
    char string[256];
   
    va_start(ap,fmt);
    vsprintf(string,fmt,ap);
    Uart_SendString(string,port);
    va_end(ap);
}

/*
*************************************************************************************************************
- 函数名称 : ChangePllValue(int mdiv,int pdiv,int sdiv)
- 函数说明 : 改变PLL的值
- 输入参数 : int mdiv,int pdiv,int sdiv
- 输出参数 : 无
*************************************************************************************************************
*/
void ChangePllValue(int mdiv,int pdiv,int sdiv)
{
    rPLLCON = (mdiv<<12)|(pdiv<<4)|sdiv;
}

/*
*************************************************************************************************************
- 函数名称 : malloc
- 函数说明 : 动态分配函数
- 输入参数 : nbyte
- 输出参数 : 无
*************************************************************************************************************
*/
void * malloc(unsigned nbyte) 
{
    void *returnPt=mallocPt;

    mallocPt = (int *)mallocPt + nbyte/4 + ((nbyte%4)>0);                                        //对齐4字节

    if ((int)mallocPt > HEAPEND)
    {
		mallocPt = returnPt;
		return NULL;
    }
    return returnPt;
}

/*
*************************************************************************************************************
- 函数名称 : free
- 函数说明 : 动态释放函数
- 输入参数 : *pt
- 输出参数 : 无
*************************************************************************************************************
*/
void free(void *pt)

{
    mallocPt=pt;
}

/*
*************************************************************************************************************
- 函数名称 : Cache_Flush(void)
- 函数说明 : 高速缓存清空
- 输入参数 : 无
- 输出参数 : 无
*************************************************************************************************************
*/
void Cache_Flush(void)
{
    int i,saveSyscfg;
    
    saveSyscfg = rSYSCFG;
    rSYSCFG = SYSCFG_0KB; 						//把CACHE变为内部RAM		      
    
    for (i=0x10004000;i<0x10004800;i+=16)    
    {					   
		*((int *)i) = 0x0;		   
    }
    rSYSCFG = saveSyscfg; 			    
}

/*
*************************************************************************************************************
- 函数名称 : Timer_Start
- 函数说明 : 启动定时器
- 输入参数 : divider
- 输出参数 : 无
*************************************************************************************************************
*/
void Timer_Start(int divider)  											       //0:16us,1:32us 2:64us 3:128us
{
    rWTCON = ((MCLK/1000000-1)<<8)|(divider<<3);
    rWTDAT = 0xffff;
    rWTCNT = 0xffff;   
    															   // 1/16/(65+1),nRESET & interrupt  disable
    rWTCON = ((MCLK/1000000-1)<<8)|(divider<<3)|(1<<5);	
}

/*
*************************************************************************************************************
- 函数名称 : Timer_Stop
- 函数说明 : 停止定时器
- 输入参数 : 无
- 输出参数 : (0xffff-rWTCNT)
*************************************************************************************************************
*/
int Timer_Stop(void)
{
    rWTCON = ((MCLK/1000000-1)<<8);
    return (0xffff-rWTCNT);
}

/*
*************************************************************************************************************
*-                            				结束文件													   -*
*************************************************************************************************************
*/