/*
;************************************************************************************************************
;*									  	 北京达盛科技有限公司
;*                                     	    研    发    部
;*
;*                                 	    http://www.techshine.com
;*
;*--------------------------------------------- 文件信息 ----------------------------------------------------                                      
;*
;* 文件名称 : MAIN.c	
;* 文件功能 : 应用主程序
;* 补充说明 : 
;*-------------------------------------------- 最新版本信息 -------------------------------------------------
;* 修改作者 : ARM开发小组
;* 修改日期 : 2004/00/00
;* 版本声明 : V1.0.1
;*-------------------------------------------- 历史版本信息 -------------------------------------------------
;* 文件作者 : ARM开发小组
;* 创建日期 : 2004/06/25
;* 版本声明 : v1.0.0
;*-----------------------------------------------------------------------------------------------------------
;*-----------------------------------------------------------------------------------------------------------
;************************************************************************************************************
;*/

#include "..\inc\config.h"

/*
*************************************************************************************************************
- 函数名称 : Main(void)
- 函数说明 : 系统的主程序入口
- 输入参数 : 无
- 输出参数 : 无
*************************************************************************************************************
*/
 
void Main()                            
{ 
 	char p;
 	Target_Init(); //目标初始化
  	while(1)
  	{	
 		switch(key_number)
 		{
 			case 0:
  				send_byte(cmd_test); 	//测试键
  				break;
            
            case 1:
                for(p=0;p<8;p++)         //右移8位
                {
            		send_byte(0xA0);
            		send_byte(0xC8+7);    
            		send_byte(p);
                    long_delay();
                    
                    Delay(1000);
                 }
       		    break;
  
  			case 2:
  				 
  				for(p=0;p<8;p++)         //循环右移
                 {
            		send_byte(0xA0);
            		send_byte(0xC8+7);    
            		
            		send_byte(p);
                    long_delay();
                    
                    Delay(1000);
                 }
                for(;;)
                 {
                    if (key_number!=2)
                    {
                        break;
                    }
                    Delay(1000);
                    send_byte(0xA2);
                }
  				break;
  	
  			case 3:
  			  	write7279(decode1+5,key_number/16*8);
    	        write7279(decode1+4,key_number & 0x0f);
				break;
  			
  			case 4:
  			 	send_byte(cmd_reset);    //复位键
  				break;
  	
  			case 5:
  			  	write7279(decode1+5,key_number/16*8);
    	        write7279(decode1+4,key_number & 0x0f);
  			    break;
  			
  			case 6:
  			  	write7279(decode1+5,key_number/16*8);
    	        write7279(decode1+4,key_number & 0x0f);
  				break;
  			
  			case 7:
  			  	write7279(decode1+5,key_number/16*8);
    	        write7279(decode1+4,key_number & 0x0f);
  				break;
  		
  			case 8:
  		  	    write7279(decode1+5,key_number/16*8);
    	        write7279(decode1+4,key_number & 0x0f);
  				break;
  			
  			case 9:
  		  	    for(p=0;p<8;p++)         //左移
                {
            		send_byte(0xA1);
            		send_byte(0xC8);    
            		send_byte(p);
                    long_delay();
                    
                    Delay(1000);
                }
                break;
  			
  			case 10:
  			  	for(p=0;p<8;p++)         //左移
                {
            		send_byte(0xA1);
            		send_byte(0xC8);    
            		send_byte(p);
                    long_delay();
                    
                    Delay(1000);
                }
                for(;;)
                {
                    if (key_number!=10)
                    {
                   		break;
                  	}
                    Delay(1000);
                    send_byte(0xA3);
                }
         		break;
  			
  			case 11:
  			  	write7279(decode1+5,key_number/16*8);
    	        write7279(decode1+4,key_number & 0x0f);
  				break;
  	
  			case 12:
  				write7279(decode1+5,key_number/16*8);
    	        write7279(decode1+4,key_number & 0x0f);
  				break;
  	
  			case 13:
  				write7279(decode1+5,key_number/16*8);
    	        write7279(decode1+4,key_number & 0x0f);
  				break;
  	
  			case 14:
  			  	write7279(decode1+5,key_number/16*8);
    	        write7279(decode1+4,key_number & 0x0f);
  				break;
  
  			case 15:
  			    write7279(decode1+5,key_number/16*8);
    	        write7279(decode1+4,key_number & 0x0f);
  				break;
		}
 		key_number = 0xff;
 		Delay(50);
	}
}
