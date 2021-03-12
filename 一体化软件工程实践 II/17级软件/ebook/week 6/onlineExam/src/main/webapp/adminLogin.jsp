<%@ page language="java" import="java.util.*" pageEncoding="utf-8"%>
<%@ taglib uri="/struts-tags" prefix="s" %>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD 	XHTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>系统管理员登录/title>
    
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
			margin:0;
			padding:0;	
		}
		.div1{
			background-color:#EDEDED;
			margin:0 auto;
		    padding:0px;
		    width:80%;
		    height:768px;			   
		}
		.div2_1{
			width:100%;
			height:100px;
			background-color:#1183C2;
		}
		.div2_2{
			margin:50px 0 0 250px;
			background-color:#CCC;
			width:50%;
			height:300px;
		}
		.div3_1{
			margin:0;
			padding:0;
			width:80px;
			height:80px;
			float:left;
		}
		.div3_2{
			margin:25px 0 0 200px;
			padding:0px;
			float:left;
			color:#FFF;
			font-size:48px;
		}
		#errspan{
			text-align: center;
			font-size: 14px;
			color: red;
		
		}
		img{
			width:100%;
			height:100%;
			margin:15px 0 0 120px;
		}
		table{
			margin:50px 0 0 0 ;
			padding:50px 0 0 0 ;
			width:500px;
			height:250px;
			text-align:center;
			table-layout:fixed ; 
		}
		
	</style>
	<script type="text/javascript">
		
		function checkId(){
			var uid = document.getElementById("uid").value;
			var idspan = document.getElementById("idspan");
			var reg = /^[0-9]{2,11}$/i;
		
			var flag ;
			if(uid == ""){
				idspan.innerHTML = "* 管理员编号不能为空".fontcolor("red").fontsize("2px");
				flag = false;
			}else if(!reg.test(uid)){
				idspan.innerHTML = "* 管理员编号只能是数字".fontcolor("red").fontsize("2px");
				flag = false;
			}else{
				idspan.innerHTML = "";
				flag = true;
			}
			return flag;
			
		}
		function checkPW(){
			var password = document.getElementById("password").value;
			var pwspan = document.getElementById("pwspan");
			var flag = false;
			if(password == ""){
				pwspan.innerHTML = "* 密码不能为空".fontcolor("red").fontsize("2px");
				flag = false;
			}else{
				pwspan.innerHTML = "";
				flag = true;
			}
			return flag;
		}
		function checkForm(){
			if(checkId() && checkPW()){
				return true;
			}else{
				return false;
			}
		}
	</script>
</head>

<body>
  <div class="div1">
    <div class="div2_1">
        <div class="div3_1">
             <img src="${pageContext.request.contextPath }/images/Logo.jpg"/>
        </div>
        <div class="div3_2">
             <span>在线考试系统</span>
        </div>
    </div>
    <div class="div2_2">
     <center>
     
    	<form id="form1" action="${pageContext.request.contextPath }/admin_login.action" method="post" onsubmit="return checkForm()" >
        	<table border="0px">
            	<tr>
                	<td style="text-align:center" colspan="3">管理员登录</td>  
                </tr>
                <tr>
                	<td style="text-align:right;">用户编号：</td>
                    <td style="text-align:left;">
                    	<input id="uid" type="text" style="width:160px;" name="uid" onblur="checkId()" />
                    </td>
                    <td style="text-align:left;"><span id="idspan"></span></td>
                </tr>
                <tr>
                	<td style="text-align:right;">密&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;码：</td>
                    <td style="text-align:left;">
                    	<input id="password" type="password" style="width:160px;" name="password" onblur="checkPW()"/>
                    </td>
                    <td style="text-align:left;"><span id="pwspan"></span></td>
                </tr>
                 <tr>	
                    <td colspan="3">
                    	<input style="width:100px; height:30px" type="submit" value="登录"/>
                        <input style="width:100px; height:30px" type="reset" value="重置"/>
                    </td>
                </tr>
            </table>  
        </form>
      </center>
      <span id="errspan" style="test"><s:actionerror/></span>
    </div>
  </div>
</body>
</html>
