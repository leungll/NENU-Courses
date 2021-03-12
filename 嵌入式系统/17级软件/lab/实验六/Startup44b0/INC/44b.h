/*
;************************************************************************************************************
;*				        				北京精仪达盛科技有限公司
;*                                     	     研    发    部
;*
;*                                 	     http://www.techshine.com
;*
;*--------------------------------------------- 文件信息 ----------------------------------------------------                                      
;* 文件名称 : 44b.h
;* 文件功能 : 该文件用特殊标号为S3C44B0硬件平台的特殊寄存器的地址定义
;* 补充说明 : 
;*-------------------------------------------- 最新版本信息 -------------------------------------------------
;* 修改作者 : ARM开发小组
;* 修改日期 : 2004/04/25
;* 版本声明 : V1.0.1
;**------------------------------------------- 历史版本信息 -------------------------------------------------
;* 文件作者 : 三星公司
;* 创建日期 : 2000/03/07
;* 版本声明 : v1.0.0
;*-----------------------------------------------------------------------------------------------------------
;*-----------------------------------------------------------------------------------------------------------
;************************************************************************************************************
;*/

#ifndef __44B0X_H__
#define __44B0X_H__

#include "option.h"

/* 系统寄存器 */
#define rSYSCFG		(*(volatile unsigned *)0x1c00000)

/* 高速缓存寄存器 */
#define rNCACHBE0	(*(volatile unsigned *)0x1c00004)
#define rNCACHBE1	(*(volatile unsigned *)0x1c00008)

/* 总线控制寄存器 */
#define rSBUSCON	(*(volatile unsigned *)0x1c40000)
    
/* 存储器控制寄存器 */
#define rBWSCON		(*(volatile unsigned *)0x1c80000)
#define rBANKCON0	(*(volatile unsigned *)0x1c80004)
#define rBANKCON1	(*(volatile unsigned *)0x1c80008)
#define rBANKCON2	(*(volatile unsigned *)0x1c8000c)
#define rBANKCON3	(*(volatile unsigned *)0x1c80010)
#define rBANKCON4	(*(volatile unsigned *)0x1c80014)
#define rBANKCON5	(*(volatile unsigned *)0x1c80018)
#define rBANKCON6	(*(volatile unsigned *)0x1c8001c)
#define rBANKCON7	(*(volatile unsigned *)0x1c80020)
#define rREFRESH	(*(volatile unsigned *)0x1c80024)
#define rBANKSIZE	(*(volatile unsigned *)0x1c80028)
#define rMRSRB6		(*(volatile unsigned *)0x1c8002c)
#define rMRSRB7		(*(volatile unsigned *)0x1c80030)

/* 串口寄存器 */
#define rULCON0		(*(volatile unsigned *)0x1d00000)
#define rULCON1		(*(volatile unsigned *)0x1d04000)
#define rUCON0		(*(volatile unsigned *)0x1d00004)
#define rUCON1		(*(volatile unsigned *)0x1d04004)
#define rUFCON0		(*(volatile unsigned *)0x1d00008)
#define rUFCON1		(*(volatile unsigned *)0x1d04008)
#define rUMCON0		(*(volatile unsigned *)0x1d0000c)
#define rUMCON1		(*(volatile unsigned *)0x1d0400c)
#define rUTRSTAT0	(*(volatile unsigned *)0x1d00010)
#define rUTRSTAT1	(*(volatile unsigned *)0x1d04010)
#define rUERSTAT0	(*(volatile unsigned *)0x1d00014)
#define rUERSTAT1	(*(volatile unsigned *)0x1d04014)
#define rUFSTAT0	(*(volatile unsigned *)0x1d00018)
#define rUFSTAT1	(*(volatile unsigned *)0x1d04018)
#define rUMSTAT0	(*(volatile unsigned *)0x1d0001c)
#define rUMSTAT1	(*(volatile unsigned *)0x1d0401c)
#define rUBRDIV0	(*(volatile unsigned *)0x1d00028)
#define rUBRDIV1	(*(volatile unsigned *)0x1d04028)

#ifdef __BIG_ENDIAN
#define rUTXH0		(*(volatile unsigned char *)0x1d00023)
#define rUTXH1		(*(volatile unsigned char *)0x1d04023)
#define rURXH0		(*(volatile unsigned char *)0x1d00027)
#define rURXH1		(*(volatile unsigned char *)0x1d04027)
#define WrUTXH0(ch)	(*(volatile unsigned char *)(0x1d00023))=(unsigned char)(ch)
#define WrUTXH1(ch)	(*(volatile unsigned char *)(0x1d04023))=(unsigned char)(ch)
#define RdURXH0()	(*(volatile unsigned char *)(0x1d00027))
#define RdURXH1()	(*(volatile unsigned char *)(0x1d04027))  
#define UTXH0		(0x1d00020+3)  //byte_access address by BDMA
#define UTXH1		(0x1d04020+3)
#define URXH0		(0x1d00024+3)  
#define URXH1		(0x1d04024+3)  

#else //小端
#define rUTXH0		(*(volatile unsigned char *)0x1d00020)
#define rUTXH1		(*(volatile unsigned char *)0x1d04020)
#define rURXH0		(*(volatile unsigned char *)0x1d00024)
#define rURXH1		(*(volatile unsigned char *)0x1d04024)
#define WrUTXH0(ch)	(*(volatile unsigned char *)0x1d00020)=(unsigned char)(ch)
#define WrUTXH1(ch)	(*(volatile unsigned char *)0x1d04020)=(unsigned char)(ch)
#define RdURXH0()	(*(volatile unsigned char *)0x1d00024)
#define RdURXH1()	(*(volatile unsigned char *)0x1d04024)
#define UTXH0		(0x1d00020)    //byte_access address by BDMA
#define UTXH1		(0x1d04020)
#define URXH0		(0x1d00024)
#define URXH1		(0x1d04024)
#endif

/* SIO寄存器 */
#define rSIOCON		(*(volatile unsigned *)0x1d14000)
#define rSIODAT		(*(volatile unsigned *)0x1d14004)
#define rSBRDR		(*(volatile unsigned *)0x1d14008)
#define rIVTCNT		(*(volatile unsigned *)0x1d1400c)
#define rDCNTZ		(*(volatile unsigned *)0x1d14010)

/* IIS寄存器 */
#define rIISCON		(*(volatile unsigned *)0x1d18000)
#define rIISMOD		(*(volatile unsigned *)0x1d18004)
#define rIISPSR		(*(volatile unsigned *)0x1d18008)
#define rIISFCON	(*(volatile unsigned *)0x1d1800c)

#ifdef __BIG_ENDIAN
#define rIISFIF		((volatile unsigned short *)0x1d18012)

#else //Little Endian
#define rIISFIF		((volatile unsigned short *)0x1d18010)
#endif

/* I/O 口寄存器 */
#define rPCONA		(*(volatile unsigned *)0x1d20000)
#define rPDATA		(*(volatile unsigned *)0x1d20004)

#define rPCONB		(*(volatile unsigned *)0x1d20008)
#define rPDATB		(*(volatile unsigned *)0x1d2000c)

#define rPCONC		(*(volatile unsigned *)0x1d20010)
#define rPDATC		(*(volatile unsigned *)0x1d20014)
#define rPUPC		(*(volatile unsigned *)0x1d20018)

#define rPCOND		(*(volatile unsigned *)0x1d2001c)
#define rPDATD		(*(volatile unsigned *)0x1d20020)
#define rPUPD		(*(volatile unsigned *)0x1d20024)

#define rPCONE		(*(volatile unsigned *)0x1d20028)
#define rPDATE		(*(volatile unsigned *)0x1d2002c)
#define rPUPE		(*(volatile unsigned *)0x1d20030)

#define rPCONF		(*(volatile unsigned *)0x1d20034)
#define rPDATF		(*(volatile unsigned *)0x1d20038)
#define rPUPF		(*(volatile unsigned *)0x1d2003c)

#define rPCONG		(*(volatile unsigned *)0x1d20040)
#define rPDATG		(*(volatile unsigned *)0x1d20044)
#define rPUPG		(*(volatile unsigned *)0x1d20048)

#define rSPUCR		(*(volatile unsigned *)0x1d2004c)
#define rEXTINT		(*(volatile unsigned *)0x1d20050)
#define rEXTINPND	(*(volatile unsigned *)0x1d20054)

/* 看门狗寄存器 */
#define rWTCON		(*(volatile unsigned *)0x1d30000)
#define rWTDAT		(*(volatile unsigned *)0x1d30004)
#define rWTCNT		(*(volatile unsigned *)0x1d30008)

/* ADC寄存器 */
#define rADCCON		(*(volatile unsigned *)0x1d40000)
#define rADCPSR		(*(volatile unsigned *)0x1d40004)
#define rADCDAT		(*(volatile unsigned *)0x1d40008)

/* 定时器寄存器 */
#define rTCFG0		(*(volatile unsigned *)0x1d50000)
#define rTCFG1		(*(volatile unsigned *)0x1d50004)
#define rTCON		(*(volatile unsigned *)0x1d50008)

#define rTCNTB0		(*(volatile unsigned *)0x1d5000c)
#define rTCMPB0		(*(volatile unsigned *)0x1d50010)
#define rTCNTO0		(*(volatile unsigned *)0x1d50014)

#define rTCNTB1		(*(volatile unsigned *)0x1d50018)
#define rTCMPB1		(*(volatile unsigned *)0x1d5001c)
#define rTCNTO1		(*(volatile unsigned *)0x1d50020)

#define rTCNTB2		(*(volatile unsigned *)0x1d50024)
#define rTCMPB2		(*(volatile unsigned *)0x1d50028)
#define rTCNTO2		(*(volatile unsigned *)0x1d5002c)

#define rTCNTB3		(*(volatile unsigned *)0x1d50030)
#define rTCMPB3		(*(volatile unsigned *)0x1d50034)
#define rTCNTO3		(*(volatile unsigned *)0x1d50038)

#define rTCNTB4		(*(volatile unsigned *)0x1d5003c)
#define rTCMPB4		(*(volatile unsigned *)0x1d50040)
#define rTCNTO4		(*(volatile unsigned *)0x1d50044)

#define rTCNTB5		(*(volatile unsigned *)0x1d50048)
#define rTCNTO5		(*(volatile unsigned *)0x1d5004c)

/* IIC寄存器 */
#define rIICCON     (*(volatile unsigned *)0x1d60000)
#define rIICSTAT    (*(volatile unsigned *)0x1d60004)
#define rIICADD     (*(volatile unsigned *)0x1d60008)
#define rIICDS      (*(volatile unsigned *)0x1d6000c)

/* RTC 寄存器*/
#ifdef __BIG_ENDIAN
#define rRTCCON		(*(volatile unsigned char *)0x1d70043)
#define rRTCALM     (*(volatile unsigned char *)0x1d70053)
#define rALMSEC     (*(volatile unsigned char *)0x1d70057)
#define rALMMIN     (*(volatile unsigned char *)0x1d7005b)
#define rALMHOUR    (*(volatile unsigned char *)0x1d7005f)
#define rALMDAY     (*(volatile unsigned char *)0x1d70063)
#define rALMMON     (*(volatile unsigned char *)0x1d70067)
#define rALMYEAR    (*(volatile unsigned char *)0x1d7006b)
#define rRTCRST     (*(volatile unsigned char *)0x1d7006f)
#define rBCDSEC     (*(volatile unsigned char *)0x1d70073)
#define rBCDMIN     (*(volatile unsigned char *)0x1d70077)
#define rBCDHOUR    (*(volatile unsigned char *)0x1d7007b)
#define rBCDDAY     (*(volatile unsigned char *)0x1d7007f)
#define rBCDDATE    (*(volatile unsigned char *)0x1d70083)
#define rBCDMON     (*(volatile unsigned char *)0x1d70087)
#define rBCDYEAR    (*(volatile unsigned char *)0x1d7008b)
#define rTICINT     (*(volatile unsigned char *)0x1d7008e)
#else
#define rRTCCON     (*(volatile unsigned char *)0x1d70040)
#define rRTCALM     (*(volatile unsigned char *)0x1d70050)
#define rALMSEC     (*(volatile unsigned char *)0x1d70054)
#define rALMMIN     (*(volatile unsigned char *)0x1d70058)
#define rALMHOUR    (*(volatile unsigned char *)0x1d7005c)
#define rALMDAY     (*(volatile unsigned char *)0x1d70060)
#define rALMMON     (*(volatile unsigned char *)0x1d70064)
#define rALMYEAR    (*(volatile unsigned char *)0x1d70068)
#define rRTCRST     (*(volatile unsigned char *)0x1d7006c)
#define rBCDSEC     (*(volatile unsigned char *)0x1d70070)
#define rBCDMIN     (*(volatile unsigned char *)0x1d70074)
#define rBCDHOUR    (*(volatile unsigned char *)0x1d70078)
#define rBCDDAY     (*(volatile unsigned char *)0x1d7007c)
#define rBCDDATE    (*(volatile unsigned char *)0x1d70080)
#define rBCDMON     (*(volatile unsigned char *)0x1d70084)
#define rBCDYEAR    (*(volatile unsigned char *)0x1d70088)
#define rTICINT     (*(volatile unsigned char *)0x1d7008c)
#endif

/* 时钟&电源管理寄存器 */
#define rPLLCON		(*(volatile unsigned *)0x1d80000)
#define rCLKCON		(*(volatile unsigned *)0x1d80004)
#define rCLKSLOW	(*(volatile unsigned *)0x1d80008)
#define rLOCKTIME	(*(volatile unsigned *)0x1d8000c)

/* 中断寄存器 */
#define rINTCON		(*(volatile unsigned *)0x1e00000)
#define rINTPND		(*(volatile unsigned *)0x1e00004)
#define rINTMOD		(*(volatile unsigned *)0x1e00008)
#define rINTMSK		(*(volatile unsigned *)0x1e0000c)

#define rI_PSLV		(*(volatile unsigned *)0x1e00010)
#define rI_PMST		(*(volatile unsigned *)0x1e00014)
#define rI_CSLV		(*(volatile unsigned *)0x1e00018)
#define rI_CMST		(*(volatile unsigned *)0x1e0001c)
#define rI_ISPR		(*(volatile unsigned *)0x1e00020)
#define rI_ISPC		(*(volatile unsigned *)0x1e00024)

#define rF_ISPR		(*(volatile unsigned *)0x1e00038)
#define rF_ISPC		(*(volatile unsigned *)0x1e0003c)

/* LCD 寄存器*/
#define rLCDCON1	(*(volatile unsigned *)0x1f00000)
#define rLCDCON2	(*(volatile unsigned *)0x1f00004)
#define rLCDCON3	(*(volatile unsigned *)0x1f00040)
#define rLCDSADDR1	(*(volatile unsigned *)0x1f00008)
#define rLCDSADDR2	(*(volatile unsigned *)0x1f0000c)
#define rLCDSADDR3	(*(volatile unsigned *)0x1f00010)
#define rREDLUT		(*(volatile unsigned *)0x1f00014)
#define rGREENLUT	(*(volatile unsigned *)0x1f00018)
#define rBLUELUT	(*(volatile unsigned *)0x1f0001c)
#define rDP1_2		(*(volatile unsigned *)0x1f00020)
#define rDP4_7		(*(volatile unsigned *)0x1f00024)
#define rDP3_5		(*(volatile unsigned *)0x1f00028)
#define rDP2_3		(*(volatile unsigned *)0x1f0002c)
#define rDP5_7		(*(volatile unsigned *)0x1f00030)
#define rDP3_4		(*(volatile unsigned *)0x1f00034)
#define rDP4_5		(*(volatile unsigned *)0x1f00038)
#define rDP6_7		(*(volatile unsigned *)0x1f0003c)
#define rDITHMODE	(*(volatile unsigned *)0x1f00044)

/* ZDMA0寄存器 */
#define rZDCON0		(*(volatile unsigned *)0x1e80000)
#define rZDISRC0	(*(volatile unsigned *)0x1e80004)
#define rZDIDES0	(*(volatile unsigned *)0x1e80008)
#define rZDICNT0	(*(volatile unsigned *)0x1e8000c)
#define rZDCSRC0	(*(volatile unsigned *)0x1e80010)
#define rZDCDES0	(*(volatile unsigned *)0x1e80014)
#define rZDCCNT0	(*(volatile unsigned *)0x1e80018)

/* ZDMA1寄存器 */
#define rZDCON1		(*(volatile unsigned *)0x1e80020)
#define rZDISRC1	(*(volatile unsigned *)0x1e80024)
#define rZDIDES1	(*(volatile unsigned *)0x1e80028)
#define rZDICNT1	(*(volatile unsigned *)0x1e8002c)
#define rZDCSRC1	(*(volatile unsigned *)0x1e80030)
#define rZDCDES1	(*(volatile unsigned *)0x1e80034)
#define rZDCCNT1	(*(volatile unsigned *)0x1e80038)

/* BDMA0 寄存器*/
#define rBDCON0		(*(volatile unsigned *)0x1f80000)
#define rBDISRC0	(*(volatile unsigned *)0x1f80004)
#define rBDIDES0	(*(volatile unsigned *)0x1f80008)
#define rBDICNT0	(*(volatile unsigned *)0x1f8000c)
#define rBDCSRC0	(*(volatile unsigned *)0x1f80010)
#define rBDCDES0	(*(volatile unsigned *)0x1f80014)
#define rBDCCNT0	(*(volatile unsigned *)0x1f80018)

/* BDMA1寄存器 */
#define rBDCON1		(*(volatile unsigned *)0x1f80020)
#define rBDISRC1	(*(volatile unsigned *)0x1f80024)
#define rBDIDES1	(*(volatile unsigned *)0x1f80028)
#define rBDICNT1	(*(volatile unsigned *)0x1f8002c)
#define rBDCSRC1	(*(volatile unsigned *)0x1f80030)
#define rBDCDES1	(*(volatile unsigned *)0x1f80034)
#define rBDCCNT1	(*(volatile unsigned *)0x1f80038)

/* 存放ISR的入口地址 */
#define pISR_RESET		(*(unsigned *)(_ISR_STARTADDRESS+0x00))
#define pISR_UNDEF		(*(unsigned *)(_ISR_STARTADDRESS+0x04))
#define pISR_SWI		(*(unsigned *)(_ISR_STARTADDRESS+0x08))
#define pISR_PABORT		(*(unsigned *)(_ISR_STARTADDRESS+0x0c))
#define pISR_DABORT		(*(unsigned *)(_ISR_STARTADDRESS+0x10))
#define pISR_RESERVED	(*(unsigned *)(_ISR_STARTADDRESS+0x14))
#define pISR_IRQ		(*(unsigned *)(_ISR_STARTADDRESS+0x18))
#define pISR_FIQ		(*(unsigned *)(_ISR_STARTADDRESS+0x1c))

#define aISR_ADC		_ISR_STARTADDRESS+0x20
#define pISR_ADC		(*(unsigned *)(_ISR_STARTADDRESS+0x20))
#define pISR_RTC		(*(unsigned *)(_ISR_STARTADDRESS+0x24))
#define pISR_UTXD1		(*(unsigned *)(_ISR_STARTADDRESS+0x28))
#define pISR_UTXD0		(*(unsigned *)(_ISR_STARTADDRESS+0x2c))

#define pISR_SIO		(*(unsigned *)(_ISR_STARTADDRESS+0x30))
#define pISR_IIC		(*(unsigned *)(_ISR_STARTADDRESS+0x34))
#define pISR_URXD1		(*(unsigned *)(_ISR_STARTADDRESS+0x38))
#define pISR_URXD0		(*(unsigned *)(_ISR_STARTADDRESS+0x3c))

#define pISR_TIMER5		(*(unsigned *)(_ISR_STARTADDRESS+0x40))
#define pISR_TIMER4		(*(unsigned *)(_ISR_STARTADDRESS+0x44))
#define pISR_TIMER3		(*(unsigned *)(_ISR_STARTADDRESS+0x48))
#define pISR_TIMER2		(*(unsigned *)(_ISR_STARTADDRESS+0x4c))

#define pISR_TIMER1		(*(unsigned *)(_ISR_STARTADDRESS+0x50))
#define pISR_TIMER0		(*(unsigned *)(_ISR_STARTADDRESS+0x54))
#define pISR_UERR01		(*(unsigned *)(_ISR_STARTADDRESS+0x58))
#define pISR_WDT		(*(unsigned *)(_ISR_STARTADDRESS+0x5c))

#define pISR_BDMA1		(*(unsigned *)(_ISR_STARTADDRESS+0x60))
#define pISR_BDMA0		(*(unsigned *)(_ISR_STARTADDRESS+0x64))
#define pISR_ZDMA1		(*(unsigned *)(_ISR_STARTADDRESS+0x68))
#define pISR_ZDMA0		(*(unsigned *)(_ISR_STARTADDRESS+0x6c))

#define pISR_TICK		(*(unsigned *)(_ISR_STARTADDRESS+0x70))
#define pISR_EINT4567	(*(unsigned *)(_ISR_STARTADDRESS+0x74))
#define pISR_EINT3		(*(unsigned *)(_ISR_STARTADDRESS+0x78))
#define pISR_EINT2		(*(unsigned *)(_ISR_STARTADDRESS+0x7c))

#define pISR_EINT1		(*(unsigned *)(_ISR_STARTADDRESS+0x80))
#define pISR_EINT0		(*(unsigned *)(_ISR_STARTADDRESS+0x84))

/* 中断挂起位 */
//注意: 像通常的特殊寄存器一样必须清除挂起位。

#define BIT_ADC			(0x1)
#define BIT_RTC			(0x1<<1)
#define BIT_UTXD1		(0x1<<2)
#define BIT_UTXD0		(0x1<<3)
#define BIT_SIO			(0x1<<4)
#define BIT_IIC			(0x1<<5)
#define BIT_URXD1		(0x1<<6)
#define BIT_URXD0		(0x1<<7)
#define BIT_TIMER5		(0x1<<8)
#define BIT_TIMER4		(0x1<<9)
#define BIT_TIMER3		(0x1<<10)
#define BIT_TIMER2		(0x1<<11)
#define BIT_TIMER1		(0x1<<12)
#define BIT_TIMER0		(0x1<<13)
#define BIT_UERR01		(0x1<<14)
#define BIT_WDT			(0x1<<15)
#define BIT_BDMA1		(0x1<<16)
#define BIT_BDMA0		(0x1<<17)
#define BIT_ZDMA1		(0x1<<18)
#define BIT_ZDMA0		(0x1<<19)
#define BIT_TICK		(0x1<<20)
#define BIT_EINT4567	(0x1<<21)
#define BIT_EINT3		(0x1<<22)
#define BIT_EINT2		(0x1<<23)
#define BIT_EINT1		(0x1<<24)
#define BIT_EINT0		(0x1<<25)
#define BIT_GLOBAL		(0x1<<26)

#endif 
/*
*************************************************************************************************************
*-                            				结束文件													   -*
*************************************************************************************************************
*/

