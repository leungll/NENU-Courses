<%--
  Created by IntelliJ IDEA.
  User: huawei
  Date: 2018/12/23
  Time: 12:07
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/fmt" prefix="fmt" %>
<html>
<head>
    <title>登录界面</title>
</head>
<body>
<table border="1" cellspacing="0" cellpadding="0" style="text-align: center;font-size: 20px">
<form method="post" action="${website}/user/list">
<tr>
<td>序号</td>
<td>用户名</td>
<td>操作</td>
</tr>
<c:forEach items="${userList}" var="user" varStatus="status">
<tr>
<td>${status.index+1}</td>
    <input value="${user.id}" hidden />
<td>${user.username}</td>
<td><a href="${website}user/del/${user.id}">删除</a></td>
</tr>
</c:forEach>

</form>
</table>
</body>
</html>
