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
		
		function checkbjname(){
			var flag;
			//获取文件框值
			var bj = document.getElementById("bj").value;
			bj = encodeURI(bj);
			bj = encodeURI(bj);
			//1.创建异步交互对象
			var xhr = createXmlHttp();
			//2.设置监听
			xhr.onreadystatechange = function(){
				
				if(xhr.readyState == 4){	//数据返回完毕
					if(xhr.status == 200){		//http操作正常
						var text = xhr.responseText;
						if("t" == text){
							document.getElementById("bjspan").innerHTML = "* 班级名已存在".fontcolor("red").fontsize("2px");
						}else{
							
							document.getElementById("bjspan").innerHTML = "* 班级名可以使用".fontcolor("green").fontsize("2px");
						}	
					}
				}
			}
			//3.打开连接
			xhr.open("GET","${pageContext.request.contextPath}/bj_findByName.action?time="+new Date().getTime()+"&bjname="+bj,true);
			//4.发送
			xhr.send(null);		
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
		 function checkForm(){
			var bj = document.getElementById("bj").value;
			var bjspan = document.getElementById("bjspan");
			if(bj ==""){
				bjspan.innerHTML = "* 班级名称不能为空".fontcolor("red").fontsize("2px");
				return false;
			}else if("* 班级名已存在" == bjspan.innerText && bjspan.innerText !=""){
				return false;
			}else{
				return true;
			}	
		}
	</script>
  </head>
  
  <body>
  	<div class="divtitle">
		<strong>添加班级</strong>
    </div>
  	<div id="div1">
   		<form id="form1" action="${pageContext.request.contextPath }/bj_addbjsx.action?tid=<s:property value="#session.existTeacher.tid"/>" method="post" target="mainFrame" onsubmit="return checkForm()">
   			<table>
   				<tr>
   					<td style="text-align:right;">班级名称:</td>
   					<td><input id="bj" type="text" name="bjname" onblur="checkbjname()"/></td>
   					<td style="text-align:left;"><span id="bjspan"></span></td>
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
