<%@ page language="java" import="java.util.*" pageEncoding="utf-8"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD XHTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>My JSP 'top.jsp' starting page</title>
    
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
		   margin:0px;
		   padding:0px;
		   width:100%;
		   height:100%;
		   font-size:12px;
		   background-color:#1183C2;
		}
		div{
		   margin:0px;
		   padding:0px;
		   width:100%;
		   height:100%;
		   font-size:14px;
		   position:absolute;
		  
		}
		.div2_1{
			float:left;
		}
		.div2_2{
			margin:15px 0 0 140px;
			color:#FFF;
			float:left;
		}
		.div2_3{
			margin:42px 0 0 720px;
			color:#FFF;
			float:right
		}
			
		img{
			width:7%;
			height:80%;
			margin:15px 0 0 20px;
		}
	</style>
	<script language="javascript">
         var t = null;
		 t = setTimeout(time,1000);//开始执行
		 var date = new Date();
		
	     var year = date.getFullYear();
	     var month = date.getMonth()+1;
	     var day = date.getDate();
	     var week = date.getDay();
	
		 function getWeek(num)
		 {
			var weeks = ['星期日','星期一','星期二','星期三','星期四','星期五','星期六'];

			return weeks[num];
		 }
		 function time()
		 {
		    clearTimeout(t);//清除定时器
		    dt = new Date();
		    var h=dt.getHours();
		    var m=dt.getMinutes();
		    var s=dt.getSeconds();
		    document.getElementById("timeShow").innerHTML ="当前系统时间："+year+"-"+month+"-"+day+" "+getWeek(week)+" "+h+":"+m+":"+s;
		    t = setTimeout(time,1000); //设定定时器，循环执行            
		 }
  	</script>
</head>


<body>
	<div>
    	<div class="div2_1">
        	<img src="${pageContext.request.contextPath }/images/logo.jpg" />
        </div>
        <div class="div2_2">
        	<span><h1>在线考试系统</h1></span>
        </div>
        <div class="div2_3">
        	<label id="timeShow"></label>
        </div>
    </div>  
</body>
</html>
