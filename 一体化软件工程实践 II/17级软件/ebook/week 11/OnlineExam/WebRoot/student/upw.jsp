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
		function checkPW(pw1){
		
			var pw = document.getElementById("pw").value;
			var pwspan = document.getElementById("pwspan");
			var flag;
			if(pw1 != pw){
				pwspan.innerHTML = "* 密码错误".fontcolor("red").fontsize("2px");
				flag = false;
			}else{
				pwspan.innerHTML = "";
				flag = true;
			}
			return flag;
		}
		
		function checkNPW(){
			var npw = document.getElementById("npw").value;
			var npwspan = document.getElementById("npwspan");
			var flag;
			var reg = /^[0-9]{6,11}$/i;
			if(npw == ""){
				npwspan.innerHTML = "* 新密码不能为空".fontcolor("red").fontsize("2px");
				flag = false;
			}else if(!reg.test(npw)){
				npwspan.innerHTML = "* 密码只能是数字共6到11位".fontcolor("red").fontsize("2px");
				flag = false;
			}else{
				npwspan.innerHTML = "";
				flag = true;
			}
			return flag;
		}
		function checkQRPW(){
			var qrpw = document.getElementById("qrpw").value;
			var qrspan = document.getElementById("qrspan");
			var npw = document.getElementById("npw").value;
			var flag;
			if((npw == qrpw) && qrpw != ""){
				qrspan.innerHTML = "";
				flag = true;
			}else{
				qrspan.innerHTML = "* 两次密码不一致".fontcolor("red").fontsize("2px");
				flag = false;
			}
			return flag;
		}
		
		function checkForm(pw1){
			if(checkPW(pw1) && checkNPW() && checkQRPW()){
				return true;
			}else{
				return false;
			}
		}
	</script>
  </head>
  
  <body>
  	<div class="divtitle">
		<strong>修改密码</strong>
    </div>
  	<div id="div1">
   		<form id="form1" action="${pageContext.request.contextPath }/student_updatePW.action?sid=<s:property value="#session.existStudent.sid"/>" method="post" target="mainFrame" onsubmit="return checkForm('<s:property value="#session.existStudent.password" />')">
   			<table>
   				<tr>
   					<td style="text-align:right;">原密码:</td>
   					<td><input id="pw" type="password" /></td>
   					<td style="text-align:left;"><span id="pwspan"></span></td>
   				</tr>
   				<tr>
   					<td style="text-align:right;">新密码:</td>
   					<td><input id="npw" name="npw" type="password" onblur="checkNPW()"/></td>
   					<td style="text-align:left;"><span id="npwspan"></span></td>
   				</tr>
   				<tr>
   					<td style="text-align:right;">确认密码:</td>
   					<td><input id="qrpw" name="qrpw" type="password" onblur="checkQRPW()"/></td>
   					<td style="text-align:left;"><span id="qrspan"></span></td>
   				</tr>
   				<tr>
   					<td colspan="3">
   						<input style="width:100px; height:30px" type="submit" value="提交"/>
                        <input style="width:100px; height:30px" type="reset" value="重置"/>
   					</td>
   				</tr>
   			</table>
   		</form>
  	</div>
  </body>
</html>
