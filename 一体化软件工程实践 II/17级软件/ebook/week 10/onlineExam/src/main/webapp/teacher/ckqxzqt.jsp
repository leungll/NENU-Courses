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
    
    <title>My JSP 'ckbj.jsp' starting page</title>
    
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
		}#div1{
		   margin:60px 0 0 0;
		   padding:0px;
		   width:100%;
		   height:99%;  
		   font-size:14px;
		   position:absolute;
		   text-align: center;
		}
		#div2{
			margin:0 0 0 30px;
			padding:0px;
			width:900px;
			border: 1px solid #F0F0F0;
		}
		
		.divtitle{
			height: 40px;
			line-height: 40px;
			color: #3180D8;
			font-family: "Microsoft YaHei";
			border-bottom: 1px dotted #ededed;
			float: left;
		}
		.divtitle2{
			margin: 10px 0 0 50px;
			float:left;
		}
		table{
			border:0px;
			margin:0px;
			padding:0px;
			width:100%;
			text-align: center;
			font-size: 12px;
			color:#6D6D6D;
		}
		tr{
			margin:0px;
			padding:0px;
		}
		td{
			margin:0px;
			padding:0px;
			border-bottom: 1px solid #F0F0F0;
		}
		#div2 a:link,#div2 a:visited{
			color:#1183C2;
			text-decoration:none;
		}
		#div2 a:hover{
			color:#df4011;
		}
		.pagediv{
			height: 20px;
			float: right;
			margin-bottom: 10px;
			font-size: 12px;
		}
	</style>
	<script type="text/javascript">
	
		function checkForm(){
			var qt = document.getElementById("qt").value;
			var qscope = document.getElementById("qscope").value;
			var qdifficulty = document.getElementById("qdifficulty").value;
			if(qt == "---???????????????---"){
				alert("?????????????????????");
				return false;
			}else if(qscope == "---??????????????????---"){
				alert("?????????????????????");
				return false;
			}else if(qdifficulty == "---??????????????????---"){
				alert("?????????????????????");
				return false;
			}else{
				return true;
			}
		}
	</script>
  </head>
  
  <body>
	<div class="divtitle">
		<strong>???????????????</strong>	
    </div>
    <div class="divtitle2">
    	<form action="${pageContext.request.contextPath }/question_ckQuestion.action?tid=<s:property value="#session.existTeacher.tid" />&page=1" target="mainFrame" method="post" onsubmit="return checkForm()">
    		<select id="qt" name="qtid">
    			<option value="---???????????????---">---???????????????---</option>
    			<s:iterator var="qt" value="listqt">
    				<option value="<s:property value="#qt.qtid"/>"><s:property value="#qt.qtname"/></option>
    			</s:iterator>
    		</select>
    		<select id="qscope" name="qscope">
    			<option value="---??????????????????---">---??????????????????---</option>
    			<option value="????????????">????????????</option>
    			<option value="????????????">????????????</option>
    			<option value="????????????">????????????</option>
    			<option value="????????????">????????????</option>
    			<option value="????????????">????????????</option>
    			<option value="????????????">????????????</option>
    			<option value="????????????">????????????</option>
    			<option value="????????????">????????????</option>
    			<option value="????????????">????????????</option>
    			<option value="????????????">????????????</option>
    		</select>
    		<select id="qdifficulty" name="qdifficulty">
    			<option value="---??????????????????---">---??????????????????---</option>
    			<option>??????</option>
    			<option>??????</option>
    			<option>??????</option>
    		</select>
    		<input type="submit" value="??????"/>
    	</form>
    </div>
    <div id="div1">
  	  <div id="div2">
   		<table border="0px" cellspacing="0px">
   			<tr style="background-color: #DEEFFF">
   				<td style="width: 70px">????????????</td>
   				<td style="width:620px;">????????????</td>
				<td style="width:70px">????????????</td>
				<td style="width:70">????????????</td>
				<td>??????</td>
			</tr>
   			<s:iterator value="pageBean.list" var="q">
   			  <tr>
   			  	<td><s:property value="#q.qid"/></td>
   			  	<td style="text-align: left;"><s:property value="#q.qcontent"/></td>
   			  	<td><s:property value="#q.qscope"/></td>
   			  	<td><s:property value="#q.qdifficulty"/></td>
   			  	<td><a href="${pageContext.request.contextPath }/question_ckQuestionXX.action?qid=<s:property value="#q.qid"/>">??????</a>&nbsp;|&nbsp;<a href="${pageContext.request.contextPath }/question_delQuestion.action?qid=<s:property value="#q.qid"/>">??????</a></td>
   			  </tr>
   			</s:iterator>
   		</table>
   		<div class="pagediv">
   		<s:if test="pageBean.list != null">
   			<span>???<s:property value="pageBean.page"/>/<s:property value="pageBean.totalPage"/>???&nbsp;</span>
   			<s:if test="pageBean.page != 1">
   				<a href="${pageContext.request.contextPath }/question_ckQuestion.action?tid=<s:property value="#session.existTeacher.tid" />&page=<s:property value="pageBean.page-1"/>&qid=<s:property value="pageBean.list[0].qid"/>&qtid=<s:property value="pageqtid"/>">&nbsp;?????????&nbsp;</a>
   			</s:if>
   			<s:iterator var="i" begin="1" end="pageBean.totalPage">
   				<a href="${pageContext.request.contextPath }/question_ckQuestion.action?tid=<s:property value="#session.existTeacher.tid" />&page=<s:property value="#i"/>&qid=<s:property value="pageBean.list[0].qid"/>&qtid=<s:property value="pageqtid"/>">&nbsp;<s:property value="#i"/>&nbsp;</a>
   			</s:iterator>
   			<s:if test="pageBean.page != pageBean.totalPage">
   				<a href="${pageContext.request.contextPath }/question_ckQuestion.action?tid=<s:property value="#session.existTeacher.tid" />&page=<s:property value="pageBean.page+1"/>&qid=<s:property value="pageBean.list[0].qid"/>&qtid=<s:property value="pageqtid"/>">&nbsp;?????????</a>
   			</s:if>
   		</s:if>
   		</div>
   		</div>
  	</div>
  </body>
</html>
