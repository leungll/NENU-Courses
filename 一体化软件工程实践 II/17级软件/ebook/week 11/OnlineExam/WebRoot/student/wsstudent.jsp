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
		 //验证手机号码
		 function checkPhone(){
		 	var phone = document.getElementById("phone").value;
		 	var phonespan = document.getElementById("phonespan");
		 	var reg = /^[0-9]{11}$/i;
		 	var flag;
		 	if(phone == ""){
		 		phonespan.innerHTML = "* 手机号不能为空".fontcolor("red").fontsize("2px");
		 		flag = false;
		 	}else if(!reg.test(phone)){
		 		phonespan.innerHTML = "* 手机号只能是11位的数字".fontcolor("red").fontsize("2px");
		 		flag = false;
		 	}else{
		 		phonespan.innerHTML = "* 该手机号可以使用".fontcolor("green").fontsize("2px");
		 		flag = true;
		 	}
		 	return flag;
		 }
		 function checkEmail(){
		 	var email = document.getElementById("email").value;
		 	var emailspan = document.getElementById("emailspan");
		 	var reg = /^\w+@\w+(\.\w+)+$/i;
		 	var flag;
		 	if(email == ""){
		 		emailspan.innerHTML = "* 请输入邮箱".fontcolor("red").fontsize("2px");
		 		flag = false;
		 	}else if(!reg.test(email)){
		 		emailspan.innerHTML = "* 邮箱格式错误".fontcolor("red").fontsize("2px");
		 		flag = false;
		 	}else{
		 		emailspan.innerHTML = "* 该邮箱可以使用".fontcolor("green").fontsize("2px");
		 		flag = true;
		 	}
		 	return flag;
		 }
		 function checkForm(){
			if(checkPhone() && checkEmail()){
				return true;
			}else{
				return false;
			}
		 }
	</script>
  </head>
  
  <body>
  	<div class="divtitle">
		<strong>完善学生信息</strong>
    </div>
  	<div id="div1">
   		<form id="form1" action="${pageContext.request.contextPath }/student_wsStudentSX.action" method="post" target="mainFrame" onsubmit="return checkForm()">
   			<table>
   				<tr>
   					<td style="text-align:right;">学号:</td>
   					<td><input id="sid" type="text" readonly="readonly" name="sid" value="<s:property value="stu.sid"/>"/></td>
   					<td style="text-align:left;"><span id="sidspan"></span></td>
   				</tr>
   				<tr>
   					<td style="text-align:right;">姓名:</td>
   					<td><input id="name" type="text" readonly="readonly" name="name" value="<s:property value="stu.name"/>"></td>
   					<td style="text-align:left;"><span id="namespan"></span></td>
   				</tr>
   				<tr>
   					<td style="text-align:right;">电话:</td>
   					<td><input id="phone" type="text" name="phone"  value="<s:property value="stu.phone"/>" onblur="checkPhone()"/></td>
   					<td style="text-align:left;"><span id="phonespan"></span></td>
   				</tr>
   				<tr>
   					<td style="text-align:right;">邮箱:</td>
   					<td><input id="email" type="text" name="email" value="<s:property value="stu.email"/>" onblur="checkEmail()"/></td>
   					<td style="text-align:left;"><span id="emailspan"></span></td>
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
