<%@page contentType="text/html;charset=gb2312"%>
<head>
	<meta http-equiv="Content-Type" content="text/html;charset=gb2312"/>
	<title>客户端, 实现后台无刷新更新页面. 异步的</title>
</head>
<!-- 这个是客户端, 用IE浏览器打开 -->
<script type="text/javascript">
	//大小写敏感的
	var req = null;

	function test()
	{
		//取得当前页面的一些数据
		var id = document.all("id").value;
		var name = document.all("name").value;

		//1. 初始化XMLHttpRequest对象
		req = new ActiveXObject("Microsoft.XMLHTTP");//IE下的.
		//2.  设置对象的属性
		req.onreadystatechange = myDeal;//指定回调方法(Ajax执行完后调用的方法)
		//3. 发出请求. 
		req.open("GET","server.jsp?id="+id+"&name="+name,"false");//不传大文档的话, 用GET就够了, 不需要POST.
		req.send(null);

	}

	//调用完服务端后执行的回调方法. 实现无刷新更新页面
	function myDeal()
	{
		if(req.readyState==4)
		{
			//1.  接受服务端返回的数据
			var ret = req.responseText;	//返回数据类型是文本
			//2. 处理( 这部分以下内容就与Ajax无关了 )
			document.all("myDiv").innerHTML = ret; //将服务器返回的结构添加到网页
		}
	}
</script>

<!--onblur失去焦点时调用-->
id: <input type="text" name="id" onblur="test();"/>*<div id="myDiv" name="myDiv"></div><br/>
name:<input type="text" name="name"/><br/>
<!--onclick点击时调用-->
<input type="button" value="register"/>