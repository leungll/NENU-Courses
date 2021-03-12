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
		
		function checkSid(){
			var flag;
			//获取文件框值
			var sid = document.getElementById("sid").value;
			var reg = /^[0-9]{6,15}$/i;
			if(sid == ""){
				document.getElementById("sidspan").innerHTML = "* 学号不能为空".fontcolor("red").fontsize("2px");
				return false;
			}else if(!reg.test(sid)){
				document.getElementById("sidspan").innerHTML = "* 学号只能是6到15位的数字".fontcolor("red").fontsize("2px");
				return false;	
			}else{
				//1.创建异步交互对象
				var xhr = createXmlHttp();
				//2.设置监听
				xhr.onreadystatechange = function(){
					if(xhr.readyState == 4){	//数据返回完毕
						if(xhr.status == 200){		//http操作正常
							var text = xhr.responseText;
							if("t" == text){
								document.getElementById("sidspan").innerHTML = "* 该学号已被使用".fontcolor("red").fontsize("2px");
							}else{	
								document.getElementById("sidspan").innerHTML = "* 该学号可以使用".fontcolor("green").fontsize("2px");
								document.getElementById("password").value=sid;
								document.getElementById("passwordspan").innerHTML = "* 默认密码为学号".fontcolor("green").fontsize("2px");	
							}	
						}
					}
				}
				//3.打开连接
				xhr.open("GET","${pageContext.request.contextPath}/student_findBySid.action?time="+new Date().getTime()+"&sid="+sid,true);
				//4.发送
				xhr.send(null);		
			}
		}
		function createXmlHttp(){
		   var xmlHttp;
		   try{ // Firefox, Opera 8.0+, Safari
		        xmlHttp=new XMLHttpRequest();
		    }
		    catch (e){
			   try{// Internet Explorer
			         xmlHttp=new ActiveXObject("Msxml2.XMLHTTP");
			         xmlHttp.setrequestheader("content-type","application/x-www-form-urlencoded; charset=utf-8");
			      }
			    catch (e){
			      try{
			         xmlHttp=new ActiveXObject("Microsoft.XMLHTTP");
			      }
			      catch (e){}
			      }
		    }
			return xmlHttp;
		 }
		 
		 //校验学生姓名
		 function checkName(){
		 	var name = document.getElementById("name").value;
		 	var namespan = document.getElementById("namespan");
		 	var flag;
		 	if(name == ""){
		 		namespan.innerHTML = "* 姓名不能为空".fontcolor("red").fontsize("2px");
		 		flag = false;
		 	}else{
		 		namespan.innerHTML = "* 该姓名可以使用".fontcolor("green").fontsize("2px");
		 		flag = true;
		 	}
		 	return flag;
		 }
		 //校验学生密码
		 function checkPassword(){
		 	var password = document.getElementById("password").value;
		 	var passwordspan = document.getElementById("passwordspan");
		 	var reg = /^[0-9]{6,15}$/i;
		 	var flag;
		 	if(password == ""){
		 		passwordspan.innerHTML = "* 密码不能为空".fontcolor("red").fontsize("2px");
		 		flag = false;
		 	}else if(!reg.test(password)){
				document.getElementById("passwordspan").innerHTML = "* 密码只能是6到15位的数字".fontcolor("red").fontsize("2px");
				flag = false;	
			}else{
		 		flag = true;
		 	}
		 	return flag;
		 }
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
		 function checkBJ(){
		 	var bjname = document.getElementById("bjname").value;
		 	var bjnamespan = document.getElementById("bjnamespan");
		 	var flag;
		 	if(bjname == "----请选择班级----"){
		 		bjnamespan.innerHTML = "* 请选择班级".fontcolor("red").fontsize("2px");
		 		flag = false;
		 	}else{
		 		bjnamespan.innerHTML = "";
		 		flag = true;
		 	}
		 	return flag;
		 }
		 function checkForm(){
			var sidspan = document.getElementById("sidspan");
			if(checkName() && checkPassword() && checkPhone() && checkBJ() && sidspan.innerText == "* 该学号可以使用"){
				return true;
			}else{
				return false;
			}
		 }
	</script>
  </head>
  
  <body>
  	<div class="divtitle">
		<strong>添加学生</strong>
    </div>
  	<div id="div1">
   		<form id="form1" action="${pageContext.request.contextPath }/student_addStudentSX.action?tid=<s:property value="#session.existTeacher.tid"/>" method="post" target="mainFrame" onsubmit="return checkForm()">
   			<table>
   				<tr>
   					<td style="text-align:right;">学号:</td>
   					<td><input id="sid" type="text" name="sid" onblur="checkSid()"/></td>
   					<td style="text-align:left;"><span id="sidspan"></span></td>
   				</tr>
   				<tr>
   					<td style="text-align:right;">姓名:</td>
   					<td><input id="name" type="text" name="name" onblur="checkName()"/></td>
   					<td style="text-align:left;"><span id="namespan"></span></td>
   				</tr>
   				<tr>
   					<td style="text-align:right;">密码:</td>
   					<td><input id="password" type="text" name="password" onblur="checkPassword()"/></td>
   					<td style="text-align:left;"><span id="passwordspan"></span></td>
   				</tr>
   				<tr>
   					<td style="text-align:right;">电话:</td>
   					<td><input id="phone" type="text" name="phone" onblur="checkPhone()"/></td>
   					<td style="text-align:left;"><span id="phonespan"></span></td>
   				</tr>
   				
   				<tr>
   					<td style="text-align:right;">班级:</td>
   					<td>
   						<select name="bjid" id="bjname" onblur="checkBJ()">
   							<option value="----请选择班级----">----请选择班级----</option>
   							<s:iterator var ="s" value="listbj" >
   							<option value="<s:property value="#s.bjid"/>"><s:property value="#s.bjname"/></option>
   							</s:iterator>
   						</select>
   					</td>
   					<td style="text-align:left;"><span id="bjnamespan"></span></td>
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
