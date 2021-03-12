<%@ page language="java" import="java.util.*" pageEncoding="utf-8"%>
<%@ taglib uri="/struts-tags" prefix="s"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD XHTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>My JSP 'left.jsp' starting page</title>
    
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
		   text-align:center;
		   font-size:12px;
		}
		#div1{
		   margin:0px;
		   padding:0px;
		   width:98%;
		   height:99%;  
		   font-size:14px;
		   border:2px solid #CCC;
		   position:absolute;
		}
		#div2_1,#div2_2,#div2_3,#div2_4,#div2_5,#div2_6{
			margin:1px 10px 0px 10px;
			padding:0px;
			border:1px solid #CCC;
		}
		#a1_1,#a1_2,#a1_3,#a1_4,#a1_5,#a1_6{
			background-color:#1978AE;
			display:block;
			width:100%;
			color:#FFF;
			border-bottom:#CCC;
			font-weight:normal;		
		}
		div a:link,div a:visited{
			font-weight:bold;
			color:#446172;
			text-decoration:none;
		}
		div a:hover{
			color:#df4011;
		}
		
		div ul{
			list-style:none;
			margin:0px;
			padding:0px;
			display:none;
		}
		div ul li{
			padding:3px 0;
		}
		
		/*预定义样式*/
		.open{
			display:block;
		}
		.close{
			display:none;
		}
    </style>
    <script type="text/javascript">
		function list(node){
			/*
				首先获得当前节点的父节点div
				在通过父节点获取ul节点
			*/
			var oDivNode = node.parentNode;		//获取父节点div
			var oUlNode = oDivNode.getElementsByTagName("ul")[0];  //获取该父节点下的ul节点
			
			var collUlNodes = document.getElementsByTagName("ul");	//获取所有ul节点
			
			for(var i=0; i<collUlNodes.length; i++){
				if(collUlNodes[i]==oUlNode){
					if(oUlNode.className=="open"){
						oUlNode.className = "close";
					}else{
						oUlNode.className = "open";
					}
				}else{
					collUlNodes[i].className = "close";	
				}
			}
		}
	</script>

  </head>
  
 <body>
  <div id="div1">
  	<div id="div2_1">
        <a id ="a1_1" href="javascript:void(0)" onclick="list(this)">题库管理</a>
        <ul>
            <li><a href="${pageContext.request.contextPath }/question_ckQuestionAndXZQT.action" target="mainFrame">查找试题</a></li>
            <li><a href="${pageContext.request.contextPath }/question_addQuestionXZ.action" target="mainFrame">添加选择题</a></li>
        	<li><a href="${pageContext.request.contextPath }/question_addQuestionPD.action" target="mainFrame">添加判断题</a></li>
        	<li><a href="${pageContext.request.contextPath }/question_addQuestionTK.action" target="mainFrame">添加读程序题</a></li>
        </ul>
    </div>
   
	<div id="div2_2">
        <a id ="a1_2"  href="javascript:void(0)" onclick="list(this)">试卷管理</a>
        <ul>

        </ul>
    </div>
    
	<div id="div2_3">
    	 <a id ="a1_3"  href="javascript:void(0)" onclick="list(this)">班级管理</a>
        <ul>
            <li><a href="${pageContext.request.contextPath }/bj_ckbj.action?tid=<s:property value="#session.existTeacher.tid" />" target="mainFrame">查看班级</a></li>
            <li><a href="${pageContext.request.contextPath }/bj_addbj.action" target="mainFrame">添加班级</a></li>
        </ul>
    </div>
    <div id="div2_5">
    	 <a id ="a1_5"  href="javascript:void(0)" onclick="list(this)">学生管理</a>
        <ul>
         </ul>
    </div>
    <div id="div2_6">
    	 <a id ="a1_6"  href="javascript:void(0)" onclick="list(this)">我的信息</a>
        <ul>
            <li><a href="${pageContext.request.contextPath }/teacher_ckxx.action" target="mainFrame">查看信息</a></li>
            <li><a href="${pageContext.request.contextPath }/teacher_upw.action" target="mainFrame">修改密码</a></li>
        </ul>
    </div> 
  </div>   
</body>
</html>
