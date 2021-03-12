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
		
		function checkTid(){
			var flag;
			//获取文件框值
			var tid = document.getElementById("tid").value;
			var reg = /^[0-9]{6,15}$/i;
			if(tid == ""){
				document.getElementById("tidspan").innerHTML = "* 教师编号不能为空".fontcolor("red").fontsize("2px");
				return false;
			}else if(!reg.test(tid)){
				document.getElementById("tidspan").innerHTML = "* 教师编号只能是6到15位的数字".fontcolor("red").fontsize("2px");
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
								document.getElementById("tidspan").innerHTML = "* 该教师编号已被使用".fontcolor("red").fontsize("2px");
							}else{	
								document.getElementById("tidspan").innerHTML = "* 该教师编号可以使用".fontcolor("green").fontsize("2px");
								document.getElementById("password").value=tid;
								document.getElementById("passwordspan").innerHTML = "* 默认密码为教师编号".fontcolor("green").fontsize("2px");	
							}	
						}
					}
				}
				//3.打开连接
				xhr.open("GET","${pageContext.request.contextPath}/teacher_findByTid.action?time="+new Date().getTime()+"&tid="+tid,true);
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
		 
		 //校验教师姓名
		 function checkTname(){
		 	var tname = document.getElementById("tname").value;
		 	var tnamespan = document.getElementById("tnamespan");
		 	var flag;
		 	if(tname == ""){
		 		tnamespan.innerHTML = "* 姓名不能为空".fontcolor("red").fontsize("2px");
		 		flag = false;
		 	}else{
		 		tnamespan.innerHTML = "* 该姓名可以使用".fontcolor("green").fontsize("2px");
		 		flag = true;
		 	}
		 	return flag;
		 }
		 //校验教师密码
		 function checkPassword(){
		 	var password = document.getElementById("password").value;
		 	var passwordspan = document.getElementById("passwordspan");
		 	var reg = /^[0-9]{6,15}$/i;
		 	var flag;
		 	if(password == ""){
		 		passwordspan.innerHTML = "* 密码不能为空".fontcolor("red").fontsize("2px");
		 		flag = false;
		 	}else if(!reg.test(password)){
				passwordspan.innerHTML = "* 密码只能是6到15位的数字".fontcolor("red").fontsize("2px");
				flag = false;	
			}else{
				passwordspan.innerHTML = " 该密码可以使用".fontcolor("green").fontsize("2px");
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
		 
		 function checkForm(){
		 	var tidspan = document.getElementById("tidspan");
		 	if(tidspan.innerText == ""){
		 		tidspan.innerHTML = "* 教师编号不能为空".fontcolor("red").fontsize("2px");
		 	}
		 	if(checkTname() && checkPassword() && checkPhone() && tidspan.innerText == "* 该教师编号可以使用"){
		 		return true;
		 	}else{
		 		return false;
		 	} 	
		 }
	</script>
  </head>
  
  <body>
  	<div class="divtitle">
		<strong>添加教师</strong>
    </div>
  	<div id="div1">
   		<form id="form1" action="${pageContext.request.contextPath }/teacher_addTeacherSX.action" method="post" target="mainFrame" onsubmit="return checkForm()">
   			<table>
   				<tr>
   					<td style="text-align:right;">教师编号:</td>
   					<td><input id="tid" type="text" name="tid" onblur="checkTid()"/></td>
   					<td style="text-align:left;"><span id="tidspan"></span></td>
   				</tr>
   				<tr>
   					<td style="text-align:right;">姓名:</td>
   					<td><input id="tname" type="text" name="tname" onblur="checkTname()"/></td>
   					<td style="text-align:left;"><span id="tnamespan"></span></td>
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
