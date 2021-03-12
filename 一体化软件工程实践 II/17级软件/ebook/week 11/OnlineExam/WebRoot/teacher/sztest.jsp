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
		 function checkState(){
		 	var state = document.getElementById("state").value;
		 	var statespan = document.getElementById("statespan");
		 	var flag;
		 	if(state == "----考场状态----"){
		 		statespan.innerHTML = "* 请选择考场状态".fontcolor("red").fontsize("2px");
		 		flag = false;
		 	}else{
		 		statespan.innerHTML = "";
		 		flag = true;
		 	}
		 	return flag;
		 }
		 function checkMode(){
		 	var mode = document.getElementById("mode").value;
		 	var trqpid = document.getElementById("trqpid");
		 	var modespan = document.getElementById("modespan");
		 	var flag;
		 	if(mode == "----考试方式----"){
		 		modespan.innerHTML = "* 请选择考试方式".fontcolor("red").fontsize("2px");
		 		flag = false;
		 	}else{
		 		if(mode == 3){
		 			trqpid.style.display = "table-row";
		 		}else{
		 			trqpid.style.display = "none";
		 		}
		 		modespan.innerHTML = "";
		 		flag = true;
		 	}
		 	return flag;
		 }
		 function checkTname(){
		 	var tname = document.getElementById("tname").value;
		 	var tnamespan = document.getElementById("tnamespan");
		 	var flag;
		 	if(tname == ""){
		 		tnamespan.innerHTML = "* 请输入考试名称".fontcolor("red").fontsize("2px");
		 		flag = false;
		 	}else{
		 		tnamespan.innerHTML = "";
		 		flag = true;
		 	}
		 	return flag;
		 }
		 function checkQpid(){
		 	var qpid = document.getElementById("qpid").value;
		 	var qpidspan = document.getElementById("qpidspan");
		 	var flag;
		 	if(qpid == -1){
		 		qpidspan.innerHTML = "* 请指定试卷".fontcolor("red").fontsize("2px");
		 		flag = false;
		 	}else{
		 		qpidspan.innerHTML = "";
		 		flag = true;
		 	}
		 	return flag;
		 }
		 function checkForm(){
			var qpid = document.getElementById("qpid").value;
		 	var qpidspan = document.getElementById("qpidspan");
		 	var mode = document.getElementById("mode").value;
		 	if(mode == 3){
		 		if(qpid == -1){
		 			qpidspan.innerHTML = "* 请指定试卷".fontcolor("red").fontsize("2px");
		 			return false;
		 		}
		 	}
			if(checkState() && checkMode() && checkTname()){
				return true;
			}else{
				return false;
			}
		 }
	</script>
  </head>
  
  <body>
  	<div class="divtitle">
		<strong>设置考试</strong>
    </div>
  	<div id="div1">
   		<form id="form1" action="${pageContext.request.contextPath }/testControl_addTestControl.action" method="post" target="mainFrame" onsubmit="return checkForm()">
   			<table>
   				<tr>
   					<td style="text-align:right;">考场状态:</td>
   					<td>
   						<select name="state" id="state" onblur="checkState()">
   							<option value="----考场状态----">----考场状态----</option>
   							<option value=1>开启考场</option>
   							<option value=0>关闭考场</option>
   						</select>
   					</td>
   					<td style="text-align:left;"><span id="statespan"></span></td>
   				</tr>
   				<tr>
   					<td style="text-align:right;">考试方式:</td>
   					<td>
   						<select name="mode" id="mode" onblur="checkMode()">
   							<option value="----考试方式----">----考试方式----</option>
   							<option value=2>随机抽卷</option>
   							<option value=3>指定试卷</option>
   						</select>
   					</td>
   					<td style="text-align:left;"><span id="modespan"></span></td>
   				</tr>
   				
   				<tr>
   					<td style="text-align:right;">考试名称:</td>
   					<td><input id="tname" type="text" name="tname" onblur="checkTname()"/></td>
   					<td style="text-align:left;"><span id="tnamespan"></span></td>
   				</tr>
   				<tr id="trqpid" style="display: none;">
   					<td style="text-align:right;">指定试卷:</td>
   					<td>
   						<select name="qpid" id="qpid" onblur="checkQpid()">
   							<option value="-1">----指定试卷----</option>
   							<s:iterator value="list" var="qp">
   								<option value="<s:property value="#qp.qpid"/>">第<s:property value="#qp.qpid"/>套试卷</option>
   							</s:iterator>	
   						</select>
   					</td>
   					<td style="text-align:left;"><span id="qpidspan"></span></td>
   				</tr>
   				<tr>
   					<td colspan="3">
   						<input style="width:100px; height:30px" type="submit" value="提交设置"/>
                        <input style="width:100px; height:30px" type="reset" value="重置"/>
   					</td>
   				</tr>
   			</table>
   		</form>
   		
  	</div>
  </body>
</html>
