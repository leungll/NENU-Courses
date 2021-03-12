<%@ page language="java" import="java.util.*" pageEncoding="utf-8"%>
<%@ taglib uri="/struts-tags" prefix="s"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD XHTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>My JSP 'ckxx.jsp' starting page</title>
    
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
		   position:absolute;
		}
		.divtitle{
			height: 40px;
			line-height: 40px;
			color: #3180D8;
			font-family: "Microsoft YaHei";
			border-bottom: 1px dotted #ededed;
		}
	</style>
  </head>
  
  <body>
    <div class="divtitle">
		<strong>查看信息</strong>
    </div>
  	<div id="div1">
   		<table style="text-align: center;" border="0px">
   			<tr>
   				<td style="text-align: right;">教师编号：</td>
   				<td><s:property value="t.tid" /></td>
   			</tr>
   			<tr>
   				<td style="text-align: right;">姓名：</td>
   				<td><s:property value="t.tname" /></td>
   			</tr>
   			<tr>
   				<td style="text-align: right;">密码：</td>
   				<td><s:property value="t.password"/></td>
   			</tr>
   			<tr>
   				<td style="text-align: right;">电话：</td>
   				<td><s:property value="t.phone"/></td>
   			</tr>
   			<tr>
   				<td style="text-align: right;">邮箱：</td>
   				<td><s:property value="t.email"/></td>
   			</tr>
   		</table>
  	</div>
  </body>
</html>
