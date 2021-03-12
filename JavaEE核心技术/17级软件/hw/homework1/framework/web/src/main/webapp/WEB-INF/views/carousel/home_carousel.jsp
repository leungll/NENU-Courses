<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<!DOCTYPE html>
<html>

<head>
    <meta charset="UTF-8">
    <title>pagination-nick</title>
    <link rel="stylesheet" href="../../../css/manager/总_列表.css" type="text/css" />
    <script type="text/javascript" src="../../../js/jquery2.js"></script>
    <script type="text/javascript" src="../../../js/new_file2.js"></script>
    <script type="text/javascript" src="../../../js/new_file.js"></script>

</head>
<body>
<div class="main">
    <div class="main-top">
        <a href="总列表.html"><em>Administrative center</em></a>
        <a href="${website}/carousel/list2"><button id="return">回到首页</button></a>
    </div>
    <div id="notice" class="notice">
        <div id="notice-tit" class="notice-tit">
            <ul>
                <li class="select" class="LI">
                    <a href="#">轮播图管理</a>
                </li>
                <li class="LI">
                    <a href="#">图片管理</a>
                </li>
                <li  class="LI">
                    <a href="#">用户管理</a>
                </li>
            </ul>
        </div>
        <div id="notice-con" class="notice-con">
            <div class="mod" style="display:none">
                <div class="main-bottom">
                    <div class="table1">
                        <table class="List">
                            <tr>
                                <th>名称</th>
                                <th>图片</th>
                                <th>修改</th>
                                <th>删除</th>
                            </tr>
                            <c:forEach items="${carouselList}"  var="carousel" varStatus="status">
                                <tr>
                                    <td>
                                            ${carousel.name}
                                    </td>
                                    <td>
                                        <img src="${carousel.path}"/>
                                    </td>
                                    <td>
                                        <a href="${website}carousel/toUpdate/${carousel.id}"><button type="submit"  value="修改" class="change">修改</button></a>
                                    </td>
                                    <td>
                                        <a href="${website}carousel/del/${carousel.id}"><button type="submit"  value="删除" class="Delete">删除</button></a>
                                    </td>
                                </tr>
                            </c:forEach>
                        </table>
                        <p>一共${page.pages}页</p>
                        <%--<p>一共${page.startRow}页</p>--%>
                        <%--<p>一共${page.endRow}页</p>--%>
                        <%--<p>一共${page.total}页</p>--%>
                        <div style="margin: auto">
                        <div style="float: right;padding: 0px 20px"><a href="${website}carousel/list?page=${page.firstPage}">第一页</a></div>
                        <div style="float: right; padding: 0px 20px"><a href="${website}carousel/list?page=${page.nextPage}" >下一页</a></div>
                            <div style="float: right;padding: 0px 20px"><a href="${website}carousel/list?page=${page.prePage}" >上一页</a></div>
                                <div style="float:right;padding: 0px 20px"> <a href="${website}carousel/list?page=${page.lastPage}">最后页</a></div>
                        </div>
                    </div>
                    <div class="Shangchuan">
                        <form action="/carousel/add" method="post" enctype="multipart/form-data">
                            <button id="through" type="button" class="BUTTON">浏览</button>
                            <input type="file" name="uploadFile" id="file_through" /><!-- 被隐藏 -->
                            <input type="text" name="name" id="photo_title" placeholder="请输入图片标题" />
                            <button type="submit" name="photo_submit" id="photo_submit" class="BUTTON">上传</button>
                        </form>

                    </div>
                </div>
            </div>
            <div class="mod" style="display:none">
                <div class="main-bottom">
                    <div class="table1">
                        <table class="List">
                            <tr>
                                <th>简介</th>
                                <th>图片</th>
                                <th>修改</th>
                                <th>删除</th>
                            </tr>
                            <c:forEach items="${natureList}"  var="nature" varStatus="status">
                                <tr>
                                    <td>
                                            ${nature.name}
                                    </td>
                                    <td>
                                        <img src="${nature.path}"/>
                                    </td>
                                    <td>
                                        <a href="${website}nature/toUpdate/${nature.id}"><button type="submit"  value="修改" class="change">修改</button></a>
                                    </td>
                                    <td>
                                        <a href="${website}nature/del/${nature.id}"><button type="submit"  value="删除" class="Delete">删除</button></a>
                                    </td>
                                </tr>
                            </c:forEach>
                        </table>
                    </div>
                    <div class="pagination-nick"></div>

                    <div class="Shangchuan">
                        <form action="/nature/add1" method="post" enctype="multipart/form-data">
                            <button id="through1" type="button" class="BUTTON">浏览</button>
                            <input type="file" name="uploadFile2" id="file_through1" /><!-- 被隐藏 -->
                            <input type="text" name="name" id="photo_title1" placeholder="请输入图片标题" />
                            <button type="submit" name="photo_submit" id="photo_submit1" class="BUTTON">上传</button>
                        </form>
                    </div>
                </div>
            </div>
            <div class="mod" style="display:none">
                <div class="main-bottom">
                    <div class="table1">
                        <table class="List1">
                            <form action="${website}/user/list" method="post" >
                            <tr>
                                <th>编号</th>
                                <th>用户名</th>
                                <th>状态</th>
                                <th>修改</th>
                                <th>删除</th>
                            </tr>
                                <c:forEach items="${userList}" var="user" varStatus="status">
                            <tr>
                                <td>
                                    ${status.index+1}
                                    <input value="${user.id}" hidden />
                                </td>
                                <td>
                                    <p>${user.username}</p>
                                </td>
                                <td>${user.power}</td>
                                <td>
                                    <button class="change"><a href="${website}/user/update2/${user.id}">修改</a></button>
                                </td>
                                <td>
                                    <button class="Delete"><a href="/user/del/${user.id}">删除</a></button>
                                </td>
                            </tr>
                                </c:forEach>
                            </form>
                        </table>
                    </div>
                </div>
            </div>
        </div>
    </div>
</div>


<%--<script type="text/javascript" src="../../../js/总列表.js"></script>--%>
</body>

</html>