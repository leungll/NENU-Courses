<%@ page language="java" import="java.util.*" pageEncoding="utf-8"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD XHTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>My JSP 'bottom.jsp' starting page</title>
    
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
			margin: 0px;
			padding: 0px;
		}
		
		#footer {
                height: 40px;
                line-height: 40px;
                position: fixed;
                bottom: 0;
                width: 100%;
                text-align: center;
                background: #1183C2;
                color: #fff;
                font-family: Arial;
                font-size: 12px;
                letter-spacing: 1px;
            }
	</style>
	
  </head>
  
<body bgcolor="#CCCCCC">
	<div id="footer">CopyRight© 2019 东北师大在线模拟考试系统 </div>
</body>
</html>
