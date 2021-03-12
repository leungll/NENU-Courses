<%@page contentType="text/html;charset=gb2312"%>
<head>
	<meta http-equiv="Content-Type" content="text/html;charset=gb2312"/>
	<title>服务端, 实现后台无刷新更新页面. 异步的</title>
</head>
<!-- 这个是服务端, 不仅可以做校验, 当然还可以做数据保存等. 这就实现了页面和逻辑分离 -->
<%
	//1. 接受传递过来的参数
	String id = request.getParameter("id");
	String name = request.getParameter("name");

	System.out.println("id="+id+",name="+name);

	//2. 数据检测(在后台对数据进行检测)
	if(id==null || id.trim().length()==0)
	{
		out.println("Id can't be null or empty!");
	}else
		if(id!=null&&id.equals("nenu.edu")){
			out.println("id has been registered!");
	}else{
		out.println("everything is OK!");
	}
%>