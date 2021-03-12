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
    
    <title>管理员 'ckbj.jsp' starting page</title>
    
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
			if(qt == "---请选择题型---"){
				alert("请选择试题类型");
				return false;
			}else if(qscope == "---请选试题范围---"){
				alert("请选择试题范围");
				return false;
			}else if(qdifficulty == "---请选试题难度---"){
				alert("请选择试题难度");
				return false;
			}else{
				return true;
			}
		}
	</script>
  </head>
  
  <body>
	<div class="divtitle">
		<strong>查找试题：</strong>	
    </div>
    <div class="divtitle2">
    	<form action="${pageContext.request.contextPath }/question_ckAdminQuestion.action?page=1" target="mainFrame" method="post" onsubmit="return checkForm()">
    		<select id="qt" name="qtid">
    			<option value="---请选择题型---">---请选择题型---</option>
    			<s:iterator var="qt" value="listqt">
    				<option value="<s:property value="#qt.qtid"/>"><s:property value="#qt.qtname"/></option>
    			</s:iterator>
    		</select>
    		<select id="qscope" name="qscope">
    			<option value="---请选试题范围---">---请选试题范围---</option>
    			<option value="第一单元">第一单元</option>
    			<option value="第二单元">第二单元</option>
    			<option value="第三单元">第三单元</option>
    			<option value="第四单元">第四单元</option>
    			<option value="第五单元">第五单元</option>
    			<option value="第六单元">第六单元</option>
    			<option value="第七单元">第七单元</option>
    			<option value="第八单元">第八单元</option>
    			<option value="第九单元">第九单元</option>
    			<option value="第十单元">第十单元</option>
    		</select>
    		<select id="qdifficulty" name="qdifficulty">
    			<option value="---请选试题难度---">---请选试题难度---</option>
    			<option>简单</option>
    			<option>中等</option>
    			<option>困难</option>
    		</select>
    		<input type="submit" value="搜索"/>
    	</form>
    </div>
    <div id="div1">
  	  <div id="div2">
   		<table border="0px" cellspacing="0px">
   			<tr style="background-color: #DEEFFF">
   				<td style="width: 70px">试题编号</td>
   				<td style="width:620px;">试题内容</td>
				<td style="width:70px">试题范围</td>
				<td style="width:70">试题难度</td>
				<td>操作</td>
			</tr>
   			<s:iterator value="pageBean.list" var="q">
   			  <tr>
   			  	<td><s:property value="#q.qid"/></td>
   			  	<td style="text-align: left;"><s:property value="#q.qcontent"/></td>
   			  	<td><s:property value="#q.qscope"/></td>
   			  	<td><s:property value="#q.qdifficulty"/></td>
   			  	<td><a href="${pageContext.request.contextPath }/question_ckQuestionXX.action?qid=<s:property value="#q.qid"/>">查看</a>&nbsp;|&nbsp;<a href="${pageContext.request.contextPath }/question_delAdminQuestion.action?qid=<s:property value="#q.qid"/>">删除</a></td>
   			  </tr>
   			</s:iterator>
   		</table>
   		<div class="pagediv">
   		<s:if test="pageBean.list != null">
   			<span>第<s:property value="pageBean.page"/>/<s:property value="pageBean.totalPage"/>页&nbsp;</span>
   			<s:if test="pageBean.page != 1">
   				<a href="${pageContext.request.contextPath }/question_ckAdminQuestion.action?page=<s:property value="pageBean.page-1"/>&qid=<s:property value="pageBean.list[0].qid"/>&qtid=<s:property value="pageqtid"/>">&nbsp;上一页&nbsp;</a>
   			</s:if>
   			<s:iterator var="i" begin="1" end="pageBean.totalPage">
   				<a href="${pageContext.request.contextPath }/question_ckAdminQuestion.action?page=<s:property value="#i"/>&qid=<s:property value="pageBean.list[0].qid"/>&qtid=<s:property value="pageqtid"/>">&nbsp;<s:property value="#i"/>&nbsp;</a>
   			</s:iterator>
   			<s:if test="pageBean.page != pageBean.totalPage">
   				<a href="${pageContext.request.contextPath }/question_ckAdminQuestion.action?page=<s:property value="pageBean.page+1"/>&qid=<s:property value="pageBean.list[0].qid"/>&qtid=<s:property value="pageqtid"/>">&nbsp;下一页</a>
   			</s:if>
   		</s:if>
   		</div>
   		</div>
  	</div>
  </body>
</html>
