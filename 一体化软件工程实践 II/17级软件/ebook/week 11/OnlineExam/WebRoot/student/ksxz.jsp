<%@ page language="java" import="java.util.*" pageEncoding="utf-8"%>
<%@ taglib uri="/struts-tags" prefix="s"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>My JSP 'ckbj.jsp' starting page</title>
    
	<meta http-equiv="pragma" content="no-cache">
	<meta http-equiv="cache-control" content="no-cache">
	<meta http-equiv="expires" content="0">    
	<meta http-equiv="keywords" content="keyword1,keyword2,keyword3">
	<meta http-equiv="description" content="This is my page">
	<!--
	<link rel="stylesheet" type="text/css" href="styles.css">
	-->
	<style type="text/css">
		body{
			margin: 0;
			padding: 0;
		}
		#div1{
		   margin:0px;
		   padding:0px;
		   width:100%;
		   height:99%;  
		   font-size:14px;
		   background-color:#C0CEDC;
		   position:absolute;
		   text-align: center;
		}
		#div2{
			margin:0 0 0 200px;
			padding:0px;
			width:500px;
			height:400px;
		
		}
		#div3{
			margin:10px 0 0 0;
			height: 40px;
			line-height: 40px;
			color: #3180D8;
			font-family: "Microsoft YaHei";
			font-size: 20px;
		}
		#div4{
			margin:5px 0 0 10px;
			
		}
	
	</style>
  </head>
  
  <body>
    <div id="div1">
  	  <div id="div2">
   		<div id="div3">
   			<STRONG><s:property value="tc.tname"/>考生须知</STRONG>
   		</div>
   		<div id="div4">
   			<textarea readonly="readonly" style="font-size:12px; resize:none; overflow-y:scroll; " rows="15px" cols="60px">
一、考生入座不得携带书籍、笔记、纸张、计算器、报刊、电子设备及通信工具等，不得携带任何存储设备(包括移动硬盘、光盘、U盘、MP3、掌上电脑等)。书包、雨伞、大衣等物一律放在考场指定位置。
二、考生开始考试后禁止刷新页面，如果因刷新页面造成无法考试等其他问题由考生自己承担。
三、考生如果遇到计算机系统或网络通讯故障，可举手示意，由监考人员处理。对试题不理解时，不得向监考人员询问。
四、考生在考场内必须保持安静。提前交卷的考生须举手示意，待监考人员确认后方可离场。考试终了时间一到，考生作答系统自动关闭。
五、考生应服从上机考试工作人员的管理，接受监考人员的监督和检查。
六、考生若没有按照要求进行答题、交卷，将不能正确记录相关信息，后果由考生自己承担。
   			</textarea>
   		</div>
   		<div id="div5">
   			<form action="${pageContext.request.contextPath }/testControl_ckTestControlMode.action?sid=<s:property value="#session.existStudent.sid"/>" method="post" target="_blank">
   				<input type="submit" value="同意并进入考场"/>
   			</form>
   		</div>
   	 </div>
  	</div>
  </body>
</html>
