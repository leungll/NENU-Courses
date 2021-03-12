<%@ page language="java" import="java.util.*" pageEncoding="utf-8"%>
<%@ taglib uri="/struts-tags" prefix="s"%>
<%
String path = request.getContextPath();
String basePath = request.getScheme()+"://"+request.getServerName()+":"+request.getServerPort()+path+"/";
%>

<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN">
<html>
  <head>
    <base href="<%=basePath%>">
    
    <title>My JSP 'starttest.jsp' starting page</title>
    
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
		   text-align: center;
		}
		#div1_2{
			margin: 0 0 0 120px;
			padding:0;
			width:1014px;
			height: 600px;
			
		}
		#div2{
			margin:0 0 0 10px;
			padding:0px;
			width:200px;
			height:100%;
			float: left;
			border:1px solid #F0F0F0;
			background-color:#C0CEDC;
		
		}
		#div3{
			margin:0;
			padding:0;
			height: 500px;
			width:798px;
			height:100%;
			text-align:left;
			border:2px solid #F0F0F0;
			float: left;
			overflow-y:scroll; 
		}
	</style>
	<script type="text/javascript">
		history.go(1);
		var i;
	    var t;
	    function check1(x){
	    	t = x*60;
	    	i = self.setInterval("jishi()",1000);
	    }
	    function jishi(){
	    	h = parseInt(t/3600);
	    	m = parseInt((t-h*60*60)/60);
	    	mm = t-h*60*60-m*60;
	    	document.getElementById("span1").innerHTML = h+"时"+m+"分"+mm+"秒";
	    	t--;
	    	if(t == 600){
	    		alert("距离考试结束还有10分钟，请抓紧时间！");
	    	}
	    	if(t<0){
	    		i = window.clearInterval(i);
	    		var tnid = document.getElementById("span2").lang;
	    		alert("考试结束");
	    		window.location.href ="${pageContext.request.contextPath}/testNote_closeTestNote.action?tnid="+tnid;
	    	}
	    }
	    
	    function checkSubmit(node){
	    	var qid = node.name;
	    	var qanswer = node.value;
	    	var tnid = document.getElementById("span2").lang;
	    	if(qanswer != ""){
	    		qanswer = encodeURI(qanswer);
				qanswer = encodeURI(qanswer);
	    		//1.创建异步交互对象
				var xhr = createXmlHttp();
				//2.设置监听
				xhr.onreadystatechange = function(){
					
					if(xhr.readyState == 4){	//数据返回完毕
						if(xhr.status == 200){		//http操作正常
							var text = xhr.responseText;	
						}
					}
				}
				//3.打开连接
				xhr.open("GET","${pageContext.request.contextPath}/answerState_saveAnswerState.action?time="+new Date().getTime()+"&tnid="+tnid+"&qid="+qid+"&qanswer="+qanswer,true);
				//4.发送
				xhr.send(null);		
	    	}else{
	    		return null;
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
	    
	    function check(){
	    	var tnid = document.getElementById("span2").lang;
			if(confirm("您确定要交卷吗?")){
				window.location.href ="${pageContext.request.contextPath}/testNote_closeTestNote.action?tnid="+tnid;
			}else{
			
			}
	    }
	</script>
  </head>
  
  <body onload="check1(<s:property value="qp.time"/>);">
  <div id="div1">
  	<div id="div1_2">
  	
  	  <div id="div2">
  	  <table style="font-size: 12px; margin: auto;">
  	  	<tr>
  	  		<td style="text-align: center;" colspan="2"><span id="span2" lang="<s:property value="tn.tnid"/>"><s:property value="tn.tname"/></span></td>
  	  	</tr>
  		<tr>
  			<td style="text-align: center;" colspan="2">考生信息</td>
  		</tr>
  		<tr>
  			<td style="text-align: right;">学号：</td>
  			<td style="text-align: left;"><s:property value="stu.sid"/></td>
  		</tr>
  		<tr>
  			<td style="text-align: right;">姓名：</td>
  			<td style="text-align: left;"><s:property value="stu.name"/></td>
  		</tr>
  		<tr>
  			<td style="text-align: center;" colspan="2">距离考试结束还有:</td>
  		</tr>
  		<tr>
  			<td style="text-align: center;" colspan="2"><span id="span1"></span></td>
  		</tr>
  		<tr><td style="text-align: center;" colspan="2"><input type="button" size="100px;" value="交&nbsp;&nbsp;&nbsp;&nbsp;卷" onclick="check()"/></td></tr>
  	</table>
   	 </div>
   	 <div id="div3">
   	 	<s:if test="listxzqpq != null">
			<span>一、单选题</span><br/>
			<s:iterator value="listxzqpq" var="qpq">	
				<span><s:property value="#qpq.num"/>、<s:property value="#qpq.question.qcontent"/></span><br/>
				<input name="<s:property value="#qpq.question.qid"/>" type="radio" value="<s:property value="#qpq.question.aoption"/>" onblur="checkSubmit(this)">A&nbsp;&nbsp;<s:property value="#qpq.question.aoption"/><br/>
				<input name="<s:property value="#qpq.question.qid"/>" type="radio" value="<s:property value="#qpq.question.boption"/>" onblur="checkSubmit(this)">B&nbsp;&nbsp;<s:property value="#qpq.question.boption"/><br/>
				<input name="<s:property value="#qpq.question.qid"/>" type="radio" value="<s:property value="#qpq.question.coption"/>" onblur="checkSubmit(this)">C&nbsp;&nbsp;<s:property value="#qpq.question.coption"/><br/>
				<input name="<s:property value="#qpq.question.qid"/>" type="radio" value="<s:property value="#qpq.question.doption"/>" onblur="checkSubmit(this)">D&nbsp;&nbsp;<s:property value="#qpq.question.doption"/><br/>
			</s:iterator>
	   		<br/>
   		</s:if>
   		<s:if test="listpdqpq != null">
			<span>二、判断题</span><br/>
	   		<s:iterator value="listpdqpq" var="qpq">
	   			<span><s:property value="#qpq.num"/>、<s:property value="#qpq.question.qcontent"/></span><br/>
	   			<input name="<s:property value="#qpq.question.qid"/>" type="radio" value="对" onblur="checkSubmit(this)"/>对<br/>
	   			<input name="<s:property value="#qpq.question.qid"/>" type="radio" value="错" onblur="checkSubmit(this)"/>错<br/>
	   		</s:iterator>
			<br/>
		</s:if>
		<s:if test="listtkqpq != null">
		<span>三、读程序题</span><br/>
   		<s:iterator value="listtkqpq" var="qpq">
   			<spam><s:property value="#qpq.num"/>、</spam><br/>
   			<textarea readonly="readonly" style="resize:none; overflow-y:auto" cols="90" rows="8"><s:property value="#qpq.question.qcontent"/></textarea><br/>
   			请输入结果:<input name="<s:property value="#qpq.question.qid"/>" type="text" onblur="checkSubmit(this)"/><br/>
   		</s:iterator>
   		</s:if>
   	 </div>
   	</div>
</div>
   
  </body>
</html>
