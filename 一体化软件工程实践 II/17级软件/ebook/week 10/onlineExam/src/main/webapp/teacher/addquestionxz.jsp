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
		}
		
		.divtitle{
			height: 40px;
			line-height: 40px;
			color: #3180D8;
			font-family: "Microsoft YaHei";
			border-bottom: 1px dotted #ededed;
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
		#div2{
			margin:0 0 0 120px;
			padding:0px;
			width:700px;
			
			text-align: center;
			background-color: #A7D4F5;
			border: 2px solid #22546B;
		}
		table{
			border:0px;
			margin:0px;
			padding:0px;
			width:100%;
			text-align: center;
			font-size: 14px;
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
		
		
	</style>
	<script type="text/javascript">
		function checkQcontent(){
			var qcontent = document.getElementById("qcontent").value;
			var qcontentspan = document.getElementById("qcontentspan");	
			var flag;
			if(qcontent == ""){
				qcontentspan.innerHTML = "* 不能为空".fontcolor("red").fontsize("1px");
				flag = false;
			}else{
				qcontentspan.innerHTML = "";
				flag = true;
			}
			return flag;
		}
		function checkAoption(){
			var aoption = document.getElementById("aoption").value;
			var aoptionspan = document.getElementById("aoptionspan");
			var qanswerA = document.getElementById("qanswerA");
			var flag;
			if(aoption == ""){
				aoptionspan.innerHTML = "* 选项A不能为空".fontcolor("red").fontsize("1px");
				flag = false;
			}else{
				aoptionspan.innerHTML = "";
				qanswerA.value = aoption;
				flag = true;
			}
			return flag;
		}
		function checkBoption(){
			var boption = document.getElementById("boption").value;
			var boptionspan = document.getElementById("boptionspan");
			var qanswerB = document.getElementById("qanswerB");
			var flag;
			if(boption == ""){
				boptionspan.innerHTML = "* 选项B不能为空".fontcolor("red").fontsize("1px");
				flag = false;
			}else{
				boptionspan.innerHTML = "";
				qanswerB.value = boption;
				flag = true;
			}
			return flag;
		}
		function checkCoption(){
			var coption = document.getElementById("coption").value;
			var coptionspan = document.getElementById("coptionspan");
			var qanswerC = document.getElementById("qanswerC");
			var flag;
			if(coption == ""){
				coptionspan.innerHTML = "* 选项C不能为空".fontcolor("red").fontsize("1px");
				flag = false;
			}else{
				coptionspan.innerHTML = "";
				qanswerC.value = coption;
				flag = true;
			}
			return flag;
		}
		function checkDoption(){
			var doption = document.getElementById("doption").value;
			var doptionspan = document.getElementById("doptionspan");
			var qanswerD = document.getElementById("qanswerD");
			var flag;
			if(doption == ""){
				doptionspan.innerHTML = "* 选项D不能为空".fontcolor("red").fontsize("1px");
				flag = false;
			}else{
				doptionspan.innerHTML = "";
				qanswerD.value = doption;
				flag = true;
			}
			return flag;
		}
		function checkQscope(){
			var qscope = document.getElementById("qscope").value;
			var qsd = document.getElementById("qsd");
			
			var flag;
			if(qscope == "---请选择试题范围---"){
				qsd.innerHTML = "* 请选择试题范围".fontcolor("red").fontsize("1px");
				flag = false;
			}else{
				qsd.innerHTML = "";
				flag = true;
			}
			return flag;
		}
		function checkQdifficulty(){
			var qdifficulty = document.getElementById("qdifficulty").value;
			var qsd = document.getElementById("qsd");
			var flag; 
			if(qdifficulty == "---请选择试题难度---"){
				qsd.innerHTML = "* 请选择试题难度".fontcolor("red").fontsize("1px");
				flag = false;
			}else{
				qsd.innerHTML = "";
				flag = true;
			}
			return flag;
		}
		function checkOword(){
			var oword = document.getElementById("oword").value; //关键字
			var owordspan = document.getElementById("owordspan");
			var flag;
			if(oword == ""){
				owordspan.innerHTML = "* 请输入关键字".fontcolor("red").fontsize("1px");
				flag = false;
			}else{
				owordspan.innerHTML = "";
				flag = true;
			}
			return flag;
		}
		
		function checkQanalysis(){
			var qanalysis = document.getElementById("qanalysis").value;
			var qanalysisspan = document.getElementById("qanalysisspan");
			var flag ;
			if(qanalysis == ""){
				qanalysisspan.innerHTML = "* 请输入解析".fontcolor("red").fontsize("1px");
				flag = false; 
			}else{
				qanalysisspan.innerHTML = "";
				flag = true; 
			}
			return flag;
		}
		
		function checkForm(){
			var qanswer = document.getElementsByName("qanswer");
			var qanswerspan = document.getElementById("qanswerspan");
			var i ;
			if(checkQcontent() && checkAoption() && checkBoption() &&checkCoption() && checkDoption() && checkQscope() && checkQdifficulty() && checkOword() && checkQanalysis()){
				for(i=0; i<qanswer.length; i++){
					if(qanswer[i].checked == true){
						break;
					}
				}
				if(i>=qanswer.length){
					qanswerspan.innerHTML = "* 请选择正确答案".fontcolor("red").fontsize("1px");
					return false;
				}else{
					return true;
				}
			}else{
				return false;
			}
		}
	</script>
  </head>
  
  <body>
	<div class="divtitle">
		<strong>添加选择题：</strong>
    </div>
    <div id="div1">
    	<div id="div2">
    		<form id="form1" action="${pageContext.request.contextPath }/question_ckXSXZQuestion.action?qtid=1&tid=<s:property value="#session.existTeacher.tid" />" method="post" target="mainFrame" onsubmit="return checkForm()">
    			<table>
    				<tr>
    					<td style="text-align: right; width: 80px;">题目</td>
    					<td style="text-align: left;">
    						<textarea id="qcontent" name="qcontent" style="resize:none; overflow-y:scroll" cols="40" rows="4" onblur="checkQcontent()"></textarea>
    						<span id="qcontentspan"></span>
    					</td>
    				</tr>
    				<tr>
    					<td style="text-align: right; width: 80px;">选项A</td>
    					<td style="text-align: left;">
    						<input id="aoption" name="aoption" size="80px" type="text" onblur="checkAoption()"/>
    						<span id="aoptionspan"></span>
    					</td>
    				</tr>
    				<tr>
    					<td style="text-align: right; width: 80px;">选项B</td>
    					<td style="text-align: left;">
    						<input id="boption" name="boption" size="80px" type="text" onblur="checkBoption()"/>
    						<span id="boptionspan"></span>	
    					</td>
    				</tr>
    				<tr>
    				<td style="text-align: right; width: 80px;">选项C</td>
    					<td style="text-align: left;">
    						<input id="coption" name="coption" size="80px" type="text" onblur="checkCoption()"/>
    						<span id="coptionspan"></span>
    					</td>
    				</tr>
    				<tr>
    					<td style="text-align: right; width: 80px;">选项D</td>
    					<td style="text-align: left;">
    						<input id="doption" name="doption" size="80px" type="text" onblur="checkDoption()"/>
    						<span id="doptionspan"></span>
    					</td>
    				</tr>
    				<tr>
    					<td style="text-align: right; width: 80px;">正确答案</td>
    					<td style="text-align: left;">
    						A<input id="qanswerA" name="qanswer" type="radio" value=""/>
    						B<input id="qanswerB" name="qanswer" type="radio" value=""/>
    						C<input id="qanswerC" name="qanswer" type="radio" value=""/>
    						D<input id="qanswerD" name="qanswer" type="radio" value=""/>
    						<span id="qanswerspan"></span>
    					</td>
    				</tr>
    				<tr>
    					<td style="text-align: right; width: 80px;">试题范围</td>
    					<td style="text-align: left;">
    						<select id="qscope" name="qscope" onblur="checkQscope()">
    								<option value="---请选择试题范围---">---请选择试题范围---</option>
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
    						试题难度<select id="qdifficulty" name="qdifficulty" onblur="checkQdifficulty()">
    								<option value="---请选择试题难度---">---请选择试题难度---</option>
    								<option value="简单">简单</option>
    								<option value="中等">中等</option>
    								<option value="困难">困难</option>
    							 </select>
    						<span id="qsd"></span>
    					</td>
    				</tr>
    				<tr>
    					<td style="text-align: right; width: 80px;">关键字</td>
    					<td style="text-align: left;">
    						<input id="oword" name="oword" type="text" onblur="checkOword()"/>
    						<span id="owordspan">* 关键字表示该试题所考察的知识点</span>
    						
    					</td>
    				</tr>
    				<tr>
    					<td style="text-align: right; width: 80px;">试题解析</td>
    					<td style="text-align: left;">
    						<textarea id="qanalysis" name="qanalysis" style="resize:none; overflow-y:scroll" cols="40" rows="4" onblur="checkQanalysis()"></textarea>
    						<span id="qanalysisspan"></span>
    					</td>
    				</tr>
    				<tr>
    					<td colspan="2"><input style="width: 100px;" type="submit" value="添加试题"/><input style="width: 100px;" type="reset"  value="重&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;置"></td>
    				</tr>
    			</table>
    		</form>
    	</div>
    </div>
    
  </body>
</html>
