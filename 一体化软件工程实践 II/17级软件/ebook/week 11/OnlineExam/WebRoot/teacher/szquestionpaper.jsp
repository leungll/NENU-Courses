<%@ page language="java" import="java.util.*" pageEncoding="utf-8"%>
<%@ taglib uri="/struts-tags" prefix="s" %>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD XHTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>My JSP 'upw.jsp' starting page</title>
    
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
	<script type="text/javascript">
		function checkForm(pw1){
			var time = document.getElementById("time").value;
			var timespan = document.getElementById("timespan");
			var reg = /^[1-9][0-9]{1,}$/i;
			if(!reg.test(time)){
				timespan.innerHTML = "* 考试时长只能是数字首位不能是0，至少两位".fontcolor("red").fontsize("2px");
				return false;
			}else{
				timespan.innerHTML ="";
				return true;
			}
			
		}
	</script>
  </head>
  
  <body>
  	<div class="divtitle">
		<strong>设置考试时长</strong>
    </div>
  	<div id="div1">
   		<form id="form1" action="${pageContext.request.contextPath }/questionPaper_tjQuestionPaper.action?tid=<s:property value="#session.existTeacher.tid"/>" method="post" target="mainFrame" onsubmit="return checkForm('<s:property value="#session.existTeacher.password" />')">
   			<table>
   				<tr>
   					<td style="text-align:right;">考试时长:</td>
   					<td><input id="time" name="time" type="text" /></td>
   					<td style="text-align:left;"><span id="timespan">分钟</span></td>
   				</tr>
   				<tr>
   					<td colspan="3">
   						<input style="width:100px; height:30px" type="submit" value="添加试题"/>
                        <input style="width:100px; height:30px" type="reset" value="重置"/>
   					</td>
   				</tr>
   			</table>
   		</form>
  	</div>
  </body>
</html>
