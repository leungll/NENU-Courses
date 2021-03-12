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
		
		.divtitle{
			height: 40px;
			line-height: 40px;
			color: #3180D8;
			font-family: "Microsoft YaHei";
			border-bottom: 1px dotted #ededed;
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
			
			text-align: center;
			background-color: #A7D4F5;
			border: 2px solid #22546B;
		}
		table{
			border:0px;
			margin:10px,0,0,10px;
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
		
		
	</style>
  </head>
  
  <body>
	<div class="divtitle">
		<strong>查看试题详细信息：</strong>
    </div>
    <div id="div1">
    	<div id="div2">
    			<table>
    				<tr>
    					<td style="text-align: right; width: 80px;">题目</td>
    					<td style="text-align: left;">
    						<textarea readonly="readonly" id="qcontent" name="qcontent" style="resize:none; overflow-y:scroll" cols="40" rows="4"><s:property value="questionxx.qcontent"/></textarea>
    					</td>
    				</tr>
    				<tr>
    					<td style="text-align: right; width: 80px;">选项A</td>
    					<td style="text-align: left;">
    						<input readonly="readonly" id="aoption" name="aoption" size="80px" type="text" value="<s:property value="questionxx.aoption"/>"/>
    					</td>
    				</tr>
    				<tr>
    					<td style="text-align: right; width: 80px;">选项B</td>
    					<td style="text-align: left;">
    						<input readonly="readonly" id="boption" name="boption" size="80px" type="text" value="<s:property value="questionxx.boption"/>"/>
    					</td>
    				</tr>
    				<tr>
    					<td style="text-align: right; width: 80px;">选项C</td>
    					<td style="text-align: left;">
    						<input readonly="readonly" id="coption" name="coption" size="80px" type="text" value="<s:property value="questionxx.coption"/>"/>
    					</td>
    				</tr>
    				<tr>
    					<td style="text-align: right; width: 80px;">选项D</td>
    					<td style="text-align: left;">
    						<input readonly="readonly" id="doption" name="doption" size="80px" type="text" value="<s:property value="questionxx.doption"/>"/>
    					</td>
    				</tr>
    				<tr>
    					<td style="text-align: right; width: 80px;">正确答案</td>
    					<td style="text-align: left;">
    						<input readonly="readonly" type="text" value="<s:property value="questionxx.qanswer"/>"/>
    					</td>
    				</tr>
    				<tr>
    					<td style="text-align: right; width: 80px;">试题范围</td>
    					<td style="text-align: left;">
    						<input readonly="readonly" name="qscope" type="text" value="<s:property value="questionxx.qscope"/>" />
    						试题难度<input readonly="readonly" name="qdifficulty" type="text" value="<s:property value="questionxx.qdifficulty"/>"/>
    					</td>
    				</tr>
    				<tr>
    					<td style="text-align: right; width: 80px;">关键字</td>
    					<td style="text-align: left;">
    						<input readonly="readonly" id="oword" name="oword" type="text" value="<s:property value="questionxx.oword"/>"/>
    						<span id="owordspan">* 关键字表示该试题所考察的知识点</span>
    						
    					</td>
    				</tr>
    				<tr>
    					<td style="text-align: right; width: 80px;">试题解析</td>
    					<td style="text-align: left;">
    						<textarea readonly="readonly" id="qanalysis" name="qanalysis" style="resize:none; overflow-y:scroll" cols="40" rows="4"><s:property value="questionxx.qanalysis"/></textarea>
    					</td>
    				</tr>
    			</table>
    	</div>
    </div>
  </body>
</html>
