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
		   position:absolute;
		   text-align: center;
		}
		#div2{
			margin:0 0 0 120px;
			padding:0px;
			width:700px;
			border: 1px solid #F0F0F0;
		}
		.divtitle{
			height: 40px;
			line-height: 40px;
			color: #3180D8;
			font-family: "Microsoft YaHei";
			border-bottom: 1px dotted #ededed;
		}
		table{
			border:0px;
			margin:0px;
			padding:0px;
			width:100%;
			text-align: center;
			font-size: 14px;
			color: #6D6D6D;
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
		#div2 a:link,#div2 a:visited{
			color:#1183C2;
			text-decoration:none;
		}
		#div2 a:hover{
			color:#df4011;
		}
		.pagediv{
			height: 20px;
			float: right;
			margin-bottom: 10px;
			font-size: 12px;
		}
	</style>
  </head>
  
  <body>
	<div class="divtitle">
		<strong>查看学生：</strong>
    </div>
    <div id="div1">
  	  <div id="div2">
   		<table border="0px" cellspacing="0px">
   			<tr style="background-color: #DEEFFF">
   				<td>学号</td>
   				<td>姓名</td>
				<td>电话</td>
				<td>班级</td>
				<td>操作</td>
   			</tr>
   			<s:iterator var="s" value="pageBean.list">
   			 <tr>
   				<td><s:property value="#s.sid"/></td>
		  		<td><s:property value="#s.name"/></td>
		  		<td><s:property value="#s.phone"/></td>
		  		<td><s:property value="#s.bj.bjname"/></td>
				<td><a href="${pageContext.request.contextPath}/student_ckTestNote.action?sid=<s:property value="#s.sid"/>">考试记录</a>&nbsp;|&nbsp;<a href="${pageContext.request.contextPath}/student_deleteStudent?tid=<s:property value="#session.existTeacher.tid" />&sid=<s:property value="#s.sid"/>&page=1">删除</a></td>
   			 </tr>
   			</s:iterator>
   		</table>
   		<div class="pagediv">
   			<span>第<s:property value="pageBean.page"/>/<s:property value="pageBean.totalPage"/>页&nbsp;</span>
   			<s:if test="pageBean.page != 1">
   				<a href="${pageContext.request.contextPath }/student_ckAllStudent.action?tid=<s:property value="#session.existTeacher.tid" />&page=<s:property value="pageBean.page-1"/>">&nbsp;上一页&nbsp;</a>
   			</s:if>
   			<s:iterator var="i" begin="1" end="pageBean.totalPage">
   				<a href="${pageContext.request.contextPath }/student_ckAllStudent.action?tid=<s:property value="#session.existTeacher.tid" />&page=<s:property value="#i"/>">&nbsp;<s:property value="#i"/>&nbsp;</a>
   			</s:iterator>
   			<s:if test="pageBean.page != pageBean.totalPage">
   				<a href="${pageContext.request.contextPath }/student_ckAllStudent.action?tid=<s:property value="#session.existTeacher.tid" />&page=<s:property value="pageBean.page+1"/>">&nbsp;下一页</a>
   			</s:if>
   		</div>
   	 </div>
  	</div>
  </body>
</html>
