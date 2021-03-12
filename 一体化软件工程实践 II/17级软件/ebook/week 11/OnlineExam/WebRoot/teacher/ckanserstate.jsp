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
			margin:0 0 0 40px;
			padding:0px;
			width:860px;
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
		#div2 a:link,#div2 a:visited{
			color:#1183C2;
			text-decoration:none;
		}
		#div2 a:hover{
			color:#df4011;
		}
	</style>
  </head>
  
  <body>
	<div class="divtitle">
		<strong>查看试卷：</strong>
    </div>
    <div id="div1">
  	  <div id="div2">
   		<table border="0px" cellspacing="0px">
   			<tr style="background-color: #DEEFFF">
   				<td>试题内容</td>
   				<td>试题范围</td>
				<td>试题难度</td>
				<td>考查知识点</td>
				<td>答题情况</td>
				<td>试题详情</td>
   			</tr>
   			<s:iterator value="answerStatesxz" var="a">
   			<tr>
   				<td style="text-align: left;"><s:property value="#a.question.qcontent"/></td>
   				<td><s:property value="#a.question.qscope"/></td>
				<td><s:property value="#a.question.qdifficulty"/></td>
				<td><s:property value="#a.question.oword"/></td>
				<s:if test="#a.state == 1">
					<td>正确</td>
				</s:if>
				<s:if test="#a.state == 2">
					<td>错误</td>
				</s:if>
				<s:if test="#a.state == 3">
					<td>错误</td>
				</s:if>
				<td><a href="${pageContext.request.contextPath }/question_ckQuestionXX.action?qid=<s:property value="#a.question.qid"/>">详情</a></td>
   			</tr>
   			</s:iterator>
   			<s:iterator value="answerStatespd" var="a">
   			<tr>
   				<td style="text-align: left;"><s:property value="#a.question.qcontent"/></td>
   				<td><s:property value="#a.question.qscope"/></td>
				<td><s:property value="#a.question.qdifficulty"/></td>
				<td><s:property value="#a.question.oword"/></td>
				<s:if test="#a.state == 1">
					<td>正确</td>
				</s:if>
				<s:if test="#a.state == 2">
					<td>错误</td>
				</s:if>
				<s:if test="#a.state == 3">
					<td>错误</td>
				</s:if>
				<td><a href="${pageContext.request.contextPath }/question_ckQuestionXX.action?qid=<s:property value="#a.question.qid"/>">详情</a></td>
   			</tr>
   			</s:iterator>
   			<s:iterator value="answerStatestk" var="a">
   			<tr>
   				<td style="text-align: left;"><s:property value="#a.question.qcontent"/></td>
   				<td><s:property value="#a.question.qscope"/></td>
				<td><s:property value="#a.question.qdifficulty"/></td>
				<td><s:property value="#a.question.oword"/></td>
				<s:if test="#a.state == 1">
					<td>正确</td>
				</s:if>
				<s:if test="#a.state == 2">
					<td>错误</td>
				</s:if>
				<s:if test="#a.state == 3">
					<td>错误</td>
				</s:if>
				<td><a href="${pageContext.request.contextPath }/question_ckQuestionXX.action?qid=<s:property value="#a.question.qid"/>">详情</a></td>
   			</tr>
   			</s:iterator>
   		</table>
   		</div>
  	</div>
  </body>
</html>
