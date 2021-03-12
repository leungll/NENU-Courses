<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%--
  Created by IntelliJ IDEA.
  User: liangll
  Date: 2018/8/3
  Time: 20:58
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<!DOCTYPE html>
<html>

<head>
    <meta charset="UTF-8">
    <title></title>
    <link rel="stylesheet" href="../../../css/manager/总_列表.css" />
</head>

<body>
<div class="main">
        <form action="${website}carousel/update/${carousel.id}" method="post" enctype="multipart/form-data">
        <div class="main-top">
            <em>修&nbsp;&nbsp;&nbsp;改</em>
        </div>
        <div class="main-bottom">
            <div class="table1">
            <table class="List">
                <tr>
                    <th>图片</th>
                    <th>简介</th>
                    <th>修改</th>
                    <th>取消</th>
                </tr>
                <tr>
                    <td>
                        <!--<img src="../Image/人物/1.png" />-->
                        <input type="text" name="path" value="${carousel.path}" hidden/>
                        <img name="path" src="${carousel.path}"/>
                    </td>
                    <td>
                        <input type="text" name="name" id="change" value="${carousel.name}"/>
                    </td>
                    <td>
                        <input type="submit" name="submit" value="修改" id="besure" class="change"/>
                    </td>
                    <td>
                        <button class="Delete"><a href="/carousel/list">取消</a></button>
                    </td>
                </tr>
            </table>
            </div>
        </div>
        </form>
</div>
</body>
</html>
