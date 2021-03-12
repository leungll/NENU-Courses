;/*
;************************************************************************************************************
;*				        				北京精仪达盛科技有限公司
;*                                     	     研    发    部
;*
;*                                 	     http://www.techshine.com
;*
;*--------------------------------------------- 文件信息 ----------------------------------------------------                                      
;*
;* 文件名称 : 44binit.s	
;* 文件功能 : 该文件为ARM7硬件平台的C语言启动代码，用于分配中断向量表，初始化ISR地址，初始化堆栈空间，
;*            初始化应用程序执行环境，配置存储器系统，设定时钟周期，呼叫主应用程序。
;* 补充说明 : 基于S3C44B0的ARM7硬件平台的启动代码
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
 
    GET ..\inc\option.inc
    GET ..\inc\memcfg.inc
 
    IMPORT	|Image$$RO$$Limit|  		         ;// 声明输入ROM区中的RW地址(即:存储RO代码最后地址的下一地址)
    IMPORT	|Image$$RW$$Base|   		                                          ;// 声明输入RAM区的开始地址
    IMPORT	|Image$$ZI$$Base|   		                                     ;// 声明输入零初始化区的开始地址
    IMPORT	|Image$$ZI$$Limit|  		                             ;// 声明输入零初始化区的末地址的下一地址

    IMPORT  Main    					                                           ;// 声明输入主程序入口地址
   
    AREA    Init,CODE,READONLY

    ENTRY 
    b ResetHandler  					                                               ;//调试用的程序入口地址
    b HandlerUndef  					 ;//从未定义向量地址跳到一个地址，该地址存放进入未定义服务子程序的地址
    b HandlerSWI    					 ;//从软中断向量地址跳到一个地址，该地址存放进入软中断服务子程序的地址
    b HandlerPabort 	 ;//从指令预取指终止向量地址跳到一个地址，该地址存放进入指令预取指终止服务子程序的地址
    b HandlerDabort 				 ;//从数据终止向量地址跳到一个地址，该地址存放进入数据终止服务子程序的地址
    b .		    						                                                           ;//系统保留
    subs pc,lr,#4   					                                                   ;//使用向量中断方式
    b HandlerFIQ						       ;//从FIQ向量地址跳到一个地址，该地址存放进入FIQ服务子程序的地址
	
;/*********************************************** 注意! ******************************************************/

	   ;// 如果向量中断模式使能, 上面两条指令应按下面给出的相应改变
	   ;// b HandlerIRQ  ->  subs pc,lr,#4
	   ;// b HandlerFIQ  ->  subs pc,lr,#4

;/******************************* S3C44B0X中断控制器的向量中断的向量地址表 ***********************************/	
VECTOR_BRANCH
    ldr pc,=HandlerEINT0    																      ;//0x00000020
    ldr pc,=HandlerEINT1    																	  ;//0x00000024	
    ldr pc,=HandlerEINT2    																	  ;//0x00000028
    ldr pc,=HandlerEINT3    																	  ;//0x0000002C
    ldr pc,=HandlerEINT4567 																	  ;//0x00000030
    ldr pc,=HandlerTICK	    																	  ;//0x00000034
    
    	ldr pc,=HandlerDef																		  ;//0x00000038
    	ldr pc,=HandlerDef																		  ;//0x0000003C
    	
    ldr pc,=HandlerZDMA0    																	  ;//0x00000040
    ldr pc,=HandlerZDMA1    																	  ;//0x00000044
    ldr pc,=HandlerBDMA0    																	  ;//0x00000048
    ldr pc,=HandlerBDMA1    																	  ;//0x0000004C
    ldr pc,=HandlerWDT	    																	  ;//0x00000050
    ldr pc,=HandlerUERR01   																	  ;//0x00000054
    
    	ldr pc,=HandlerDef																		  ;//0x00000058
    	ldr pc,=HandlerDef																		  ;//0x0000005C
    	
    ldr pc,=HandlerTIMER0   																	  ;//0x00000060
    ldr pc,=HandlerTIMER1   																	  ;//0x00000064
    ldr pc,=HandlerTIMER2   																	  ;//0x00000068
    ldr pc,=HandlerTIMER3   																	  ;//0x0000006C
    ldr pc,=HandlerTIMER4   																	  ;//0x00000070
    ldr pc,=HandlerTIMER5   																	  ;//0x00000074
    
    	ldr pc,=HandlerDef																		  ;//0x00000078
    	ldr pc,=HandlerDef																		  ;//0x0000007C
    	
    ldr pc,=HandlerURXD0    																	  ;//0x00000080
    ldr pc,=HandlerURXD1    																	  ;//0x00000084
    ldr pc,=HandlerIIC	    																	  ;//0x00000088
    ldr pc,=HandlerSIO	    																	  ;//0x0000008C
    ldr pc,=HandlerUTXD0    																	  ;//0x00000090
    ldr pc,=HandlerUTXD1    																	  ;//0x00000094
    
    	ldr pc,=HandlerDef																		  ;//0x00000098
    	ldr pc,=HandlerDef																		  ;//0x0000009C
    	
    ldr pc,=HandlerRTC	    																	  ;//0x000000A0
    
    	ldr pc,=HandlerDef		    															  ;//0x000000A4
    	ldr pc,=HandlerDef			    														  ;//0x000000A8
    	ldr pc,=HandlerDef			    														  ;//0x000000AC
    	ldr pc,=HandlerDef			    														  ;//0x000000B0
    	ldr pc,=HandlerDef	    																  ;//0x000000B4
    	ldr pc,=HandlerDef																		  ;//0x000000B8
    	ldr pc,=HandlerDef																	      ;//0x000000BC
    	
    ldr pc,=HandlerADC	    																	  ;//0x000000C0
    
    	ldr pc,=HandlerDef			    														  ;//0x000000C4
    	ldr pc,=HandlerDef			    														  ;//0x000000C8
    	ldr pc,=HandlerDef			    														  ;//0x000000CC
    	ldr pc,=HandlerDef			    														  ;//0x000000D0
    	ldr pc,=HandlerDef		 																  ;//0x000000D4
    	ldr pc,=HandlerDef																		  ;//0x000000D8
    	ldr pc,=HandlerDef																		  ;//0x000000DC
    	
	ldr pc,=EnterPWDN       														  ;//0x000000E0 = EnterPWDN
    	LTORG	

HandlerFIQ      HANDLER  	HandleFIQ
HandlerIRQ		HANDLER  	HandleIRQ     															;//没有使用!
HandlerUndef	HANDLER  	HandleUndef
HandlerSWI		HANDLER  	HandleSWI
HandlerDabort	HANDLER  	HandleDabort
HandlerPabort	HANDLER  	HandlePabort

HandlerADC      VHANDLER 	HandleADC
HandlerRTC      VHANDLER 	HandleRTC
HandlerUTXD1	VHANDLER 	HandleUTXD1
HandlerUTXD0	VHANDLER 	HandleUTXD0
HandlerSIO		VHANDLER 	HandleSIO
HandlerIIC		VHANDLER 	HandleIIC
HandlerURXD1	VHANDLER 	HandleURXD1
HandlerURXD0	VHANDLER 	HandleURXD0
HandlerTIMER5	VHANDLER 	HandleTIMER5
HandlerTIMER4	VHANDLER 	HandleTIMER4
HandlerTIMER3	VHANDLER 	HandleTIMER3
HandlerTIMER2	VHANDLER 	HandleTIMER2
HandlerTIMER1	VHANDLER 	HandleTIMER1
HandlerTIMER0	VHANDLER 	HandleTIMER0
HandlerUERR01	VHANDLER 	HandleUERR01
HandlerWDT	    VHANDLER 	HandleWDT
HandlerBDMA1	VHANDLER 	HandleBDMA1
HandlerBDMA0	VHANDLER 	HandleBDMA0
HandlerZDMA1	VHANDLER 	HandleZDMA1
HandlerZDMA0	VHANDLER 	HandleZDMA0
HandlerTICK	    VHANDLER 	HandleTICK
HandlerEINT4567	VHANDLER 	HandleEINT4567
HandlerEINT3	VHANDLER 	HandleEINT3
HandlerEINT2	VHANDLER	HandleEINT2
HandlerEINT1	VHANDLER 	HandleEINT1
HandlerEINT0	VHANDLER 	HandleEINT0

HandlerDef
     stmfd   sp!,{r0,r1}																		;//r0,r1入栈
     ldr     r0,=I_PMST													 ;//把中断主从优先级分配器地址放入r0
     ldr     r1,[r0]																 ;//把其里面的内容放入r1
     str     r1,[r0]							             ;//把寄存器r1的内容放入中断主从优先级分配器地址
     ldmfd   sp!,{r0,r1}						                                ;//原r0,r1工作寄存器内容出栈
     subs    pc,lr,#4							                                         ;//跳回到原执行地址
     
;/*
;************************************************************************************************************
;**						                         程序开始		                                           **
;************************************************************************************************************
;*/

ResetHandler
    ldr	    r0,=WTCON	    														;//把看门狗定时器地址给r0 
    mov     r1,#0x00             																	;//赋初值		
    str	    r1,[r0]																	      ;//关闭看门狗定时器

    ldr	    r0,=INTMSK							                                  ;//把屏蔽中断寄存器地址给r0 
    mov     r1,#0x07ffffff   					                                                    ;//赋初值 
    str	    r1,[r0]								                                              ;//关闭所有中断
	
;/*
;************************************************************************************************************
;**	                                             时钟控制器配置                                            **
;************************************************************************************************************
;*/
    
    ldr	r0,=LOCKTIME							                                  ;//把上锁时间定时器地址给r0
    ldr r1,=0x8fc;        						         ;//赋初值count = t_lock * Fin = 230us * 10MHz = 2300
    str	r1,[r0]									                   ;//写入上锁时间定时器，PLL稳定时间为230 us

    [ PLLONSTART
	ldr	r0,=PLLCON								                                     ;//PLL控制寄存器地址给r0
	ldr	r1,=((M_DIV<<12) + (P_DIV<<4) + S_DIV)	                           ;//设定锁相环 Fin=10MHz,Fout=40MHz
	str	r1,[r0]									                                         ;//写入PLL控制寄存器
    ]

    ldr	    r0,=CLKCON							                                     ;//把时钟控制器地址给r0	 
    ldr	    r1,=0x7ff8							                              ;//给所有外设单元的时钟打开赋值	
    str	    r1,[r0]								                                            ;//写入时钟控制器
;/*
;************************************************************************************************************
;**			                                   DMA寄存器配置                                               ** 	
;************************************************************************************************************
;*/
    ldr     r0,=BDIDES0       
    ldr     r1,=0x40000000   													;//BDIDES0 复位值为 0x40000000	 
    str     r1,[r0]

    ldr     r0,=BDIDES1      
    ldr     r1,=0x40000000   													;//BDIDES1 复位值为 0x40000000	 
    str     r1,[r0]	
;/*
;************************************************************************************************************
;**			                                   存储器寄存器配置                                            ** 	
;************************************************************************************************************
;*/
    
    ldr	    r0,=SMRDATA							                                  ;//把配置数据的存放地址送入
    ldmia   r0!,{r1-r13}							                                            ;//存入寄存器
    mov     r0,#0x01c80000            			                                        ;//加载总线控制器地址
    stmia   r0!,{r1-r13}							                                ;//送入控制字到总线控制器
    
;/*
;************************************************************************************************************
;**                                               初始化堆栈                                               ** 
;************************************************************************************************************
;*/
    
    bl	    InitStacks
	
;/*
;************************************************************************************************************
;**                                          初始化应用程序执行环境                                        **
;************************************************************************************************************
;*/
    
    LDR	    r0, =|Image$$RO$$Limit|				      ;//输入ROM区中的RW地址(即:存储RO代码最后地址的下一地址)
    LDR	    r1, =|Image$$RW$$Base|				                                           ;//RAM区的开始地址
    LDR	    r3, =|Image$$ZI$$Base|				                                      ;//零初始化区的开始地址
			
    CMP	    r0, r1	    						                                         ;//比较地址是否相同?
    BEQ	    %F1
0		
    CMP	    r1, r3	    						                                         ;//比较地址是否相同?
    LDRCC   r2, [r0], #4    					                       ;//把ROM区中的RW地址中的数据放入寄存器		 
    STRCC   r2, [r1], #4    					 ;//把寄存器中的数据放入RAM区中，放完后，刚好到达ZI区的首地址
    BCC	    %B0
1		
    LDR	    r1, =|Image$$ZI$$Limit| 			                              ;//零初始化区的末地址的下一地址
    MOV	    r2, #0
2		
    CMP	    r3, r1	    						                                  ;//对零初始化区进行零初始化
    STRCC   r2, [r3], #4
    BCC	    %B2

;/*
;************************************************************************************************************
;**                                              呼叫主应用程序                                            **
;************************************************************************************************************
;*/
    
    b       Main
     
;/*
;************************************************************************************************************
;**                                          堆栈初始化应用程序                                            **
;************************************************************************************************************
;*/    
InitStacks    
    MOV     R0, LR
																			      ;//设置管理模式堆栈
    MSR     CPSR_c, # SVCMODE | NOINT
    LDR     SP, =StackSvc
												                                          ;//设置中断模式堆栈
    MSR     CPSR_c, #IRQMODE | NOINT
    LDR     SP, =StackIrq
												                                      ;//设置快速中断模式堆栈
    MSR     CPSR_c, #FIQMODE | NOINT
    LDR     SP, =StackFiq
												                                          ;//设置中止模式堆栈
    MSR     CPSR_c, #ABORTMODE | NOINT
    LDR     SP, =StackAbt
												                                        ;//设置未定义模式堆栈
    MSR     CPSR_c, #UNDEFMODE | NOINT
    LDR     SP, =StackUnd
												                                          ;//设置系统模式堆栈
    MSR     CPSR_c, #SYSMODE | NOINT 			                                            ;//在此不能开中断
    LDR     SP, =StackUsr
   
    MSR     CPSR_c, #SVCMODE| NOINT				                                                   ;//开中断
    MOV     PC, R0  
    
    LTORG  

;/************************************ 切换到系统模式下启动中断 ********************************************/
            
    EXPORT  StartInterrupt
StartInterrupt    
    MSR     CPSR_c, #SVCMODE 
    MOV  	PC, LR

;/*
;************************************************************************************************************
;**                                          该函数输入掉电模式                                            **
;************************************************************************************************************
;*/
;//void EnterPWDN(int CLKCON);

EnterPWDN
    mov	    r2,r0               													             ;//r0=CLKCON
    ldr	    r0,=REFRESH		
    ldr	    r3,[r0]
    mov	    r1, r3
    orr	    r1, r1, #0x400000   				                                                ;//打开自更新
    str	    r1, [r0]

    nop     					   				                             ;//等待直到自更新开始. 也许不需要。
    nop     					
    nop	    					
    nop
    nop
    nop
    nop
	
	;//输入 POWERDN 模式
    ldr	    r0,=CLKCON
    str	    r2,[r0]
	
	;//等待，直到进入SL_IDLE,STOP 模式，直到唤醒
    mov	    r0,#0xff
0   subs    r0,r0,#1
    bne	    %B0
	
	;//从DRAM/SDRAM 自更新模式中退出。
    ldr	    r0,=REFRESH
    str	    r3,[r0]
    mov	    pc,lr

    LTORG

;/*
;************************************************************************************************************
;** 				                       存储器配置应优化以利于性能发挥                                  **
;************************************************************************************************************

;*** 存储器访问周期参数的设定基则 ***
	; 1) Even FP-DRAM, EDO setting has more late fetch point by half-clock
	; 2) FP-DRAM Parameters:tRCD=3 for tRAC, tcas=2 for pad delay, tcp=2 for bus load.
	; 3) DRAM refresh rate is for 40Mhz. 
	; 4) The memory settings,here, are made the safe parameters even at 66Mhz.
;*/
SMRDATA DATA
;//bank0	16bit BOOT ROM SST39VF160/SST39VF320
;//bank1	16bit USB1.1 PDIUSBD12
;//bank2	8bit Nand Flash K9F2808U0A/K9F5608U0A
;//bank3	RTL8019
;//bank4	No Uesed
;//bank5	No Uesed
;//bank6	16bit SDRAM
;//bank7	16bit SDRAM
    [ BUSWIDTH=16
		DCD  0x11001002	 ; //Bank0   =  16bit BootFlash SST39VF160/SST39VF320) 
;//            ||||||||-	 Bank1   =  8bit PDIUSBD12
;//            ||||||---	 Bank2   =  8bit Nand Flash
;//            |||||----	 Bank3   =  16bit RTL8019
;//            ||||-----	 Bank4~5 =  8bit No Uesd
;//            ||--------	 Bank6~7 =  16bit SDRAM
    | 					;//BUSWIDTH=32
		DCD 0x22222220	;Bank0=OM[1:0], Bank1~Bank7=32bit
    ]
	DCD ((B0_Tacs<<13)+(B0_Tcos<<11)+(B0_Tacc<<8)+(B0_Tcoh<<6)+(B0_Tah<<4)+(B0_Tacp<<2)+(B0_PMC))	;//GCS0
	DCD ((B1_Tacs<<13)+(B1_Tcos<<11)+(B1_Tacc<<8)+(B1_Tcoh<<6)+(B1_Tah<<4)+(B1_Tacp<<2)+(B1_PMC))	;//GCS1 
	DCD ((B2_Tacs<<13)+(B2_Tcos<<11)+(B2_Tacc<<8)+(B2_Tcoh<<6)+(B2_Tah<<4)+(B2_Tacp<<2)+(B2_PMC))	;//GCS2
	DCD ((B3_Tacs<<13)+(B3_Tcos<<11)+(B3_Tacc<<8)+(B3_Tcoh<<6)+(B3_Tah<<4)+(B3_Tacp<<2)+(B3_PMC))	;//GCS3
	DCD ((B4_Tacs<<13)+(B4_Tcos<<11)+(B4_Tacc<<8)+(B4_Tcoh<<6)+(B4_Tah<<4)+(B4_Tacp<<2)+(B4_PMC))	;//GCS4
	DCD ((B5_Tacs<<13)+(B5_Tcos<<11)+(B5_Tacc<<8)+(B5_Tcoh<<6)+(B5_Tah<<4)+(B5_Tacp<<2)+(B5_PMC))	;//GCS5
	[ BDRAMTYPE="DRAM" 
	    DCD ((B6_MT<<15)+(B6_Trcd<<4)+(B6_Tcas<<3)+(B6_Tcp<<2)+(B6_CAN))	;//GCS6 check the MT value in parameter.a
	    DCD ((B7_MT<<15)+(B7_Trcd<<4)+(B7_Tcas<<3)+(B7_Tcp<<2)+(B7_CAN))	;//GCS7
	| 																		;//"SDRAM"
		DCD ((B6_MT<<15)+(B6_Trcd<<2)+(B6_SCAN))							;//GCS6
		DCD ((B7_MT<<15)+(B7_Trcd<<2)+(B7_SCAN))							;//GCS7
	]
	DCD ((REFEN<<23)+(TREFMD<<22)+(Trp<<20)+(Trc<<18)+(Tchr<<16)+REFCNT)	;//REFRESH RFEN=1, TREFMD=0, trp=3clk, trc=5clk, tchr=3clk,count=1113
	DCD 0x10			;//SCLK power down mode, BANKSIZE 32M/32M
	DCD 0x20			;//MRSR6 CL=2clk
	DCD 0x20			;//MRSR7

	ALIGN
;/*
;************************************************************************************************************
;** 				                     数据区分配各模式的堆栈空间                                        **
;************************************************************************************************************
*/
	
	AREA RamData, DATA, READWRITE

	^	(_ISR_STARTADDRESS-0x500)
				
StackUsr	#	256				                                                               ;//0x0C7ffa00
StackSvc	#	256				                                                               ;//0x0C7ffb00
StackUnd	#	256				                                                               ;//0x0C7ffc00
StackAbt	#	256				                                                               ;//0x0C7ffd00
StackIrq	#	256				                                                               ;//0x0C7ffe00
StackFiq	#	0				                                                               ;//0x0C7fff00

;/*
;************************************************************************************************************
;** 				                       数据区确定存放中断向量的地址                                    **
;************************************************************************************************************
*/
	
	^	_ISR_STARTADDRESS
HandleReset		#	4
HandleUndef		#	4
HandleSWI		#	4
HandlePabort	#	4
HandleDabort	#	4
HandleReserved	#	4
HandleIRQ		#	4
HandleFIQ		#	4


HandleADC		#	4
HandleRTC		#	4
HandleUTXD1		#	4
HandleUTXD0		#	4
HandleSIO		#	4
HandleIIC		#	4
HandleURXD1		#	4
HandleURXD0		#	4
HandleTIMER5	#	4
HandleTIMER4	#	4
HandleTIMER3	#	4
HandleTIMER2	#	4
HandleTIMER1	#	4
HandleTIMER0	#	4
HandleUERR01	#	4
HandleWDT		#	4
HandleBDMA1		#	4
HandleBDMA0		#	4
HandleZDMA1		#	4
HandleZDMA0		#	4
HandleTICK		#	4
HandleEINT4567	#	4
HandleEINT3		#	4
HandleEINT2		#	4
HandleEINT1		#	4
HandleEINT0		#	4   	                                                                  ; //0x0c7fff84

;/*
;************************************************************************************************************
;*-                            				结束文件													   -*
;************************************************************************************************************
;*/
		END
