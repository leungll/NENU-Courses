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
		}#div1{
		   margin:60px 0 0 0;
		   padding:0px;
		   width:100%;
		   height:99%;  
		   font-size:14px;
		   position:absolute;
		   text-align: center;
		}
		#div2{
			margin:0 0 0 30px;
			padding:0px;
			width:900px;
			border: 1px solid #F0F0F0;
		}
		
		.divtitle{
			height: 40px;
			line-height: 40px;
			color: #3180D8;
			font-family: "Microsoft YaHei";
			border-bottom: 1px dotted #ededed;
			float: left;
		}
		table{
			border:0px;
			margin:0px;
			padding:0px;
			width:100%;
			text-align: center;
			font-size: 12px;
			color:#6D6D6D;
		}
		tr{
			margin:0px;
			padding:0px;
		}
		td{
			margin:0px;
			padding:0px;
			border-bottom: 1px solid #F0F0F0;
		}
	</style>
  </head>
  
  <body>
	<div class="divtitle">
		<strong>查看试卷中的试题：</strong>	
    </div>
    <div id="div1">
  	  <div id="div2">
   		<table border="0px" cellspacing="0px">
   			<tr style="background-color: #DEEFFF">
   				<td>题号</td>
   				<td style="width:620px;">试题内容</td>
				<td style="width:70px">试题范围</td>
				<td style="width:70">试题难度</td>
				<td style="width: 70px">试题编号</td>
			</tr>
   			<s:iterator value="listqpq" var="qpq">
   			  <tr>
   			  	<td><s:property value="#qpq.num"/></td>
   			  	<td style="text-align: left;"><s:property value="#qpq.question.	qcontent"/></td>
   			  	<td><s:property value="#qpq.question.qscope"/></td>
   			  	<td><s:property value="#qpq.question.qdifficulty"/></td>
   			  	<td><s:property value="#qpq.question.qid"/></td>
   			  </tr>
   			</s:iterator>
   		</table>
   		
   		</div>
  	</div>
  </body>
</html>
