<%--
  Created by IntelliJ IDEA.
  User: huawei
  Date: 2018/12/25
  Time: 22:40
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/fmt" prefix="fmt" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>自然风光</title>
    <link rel="stylesheet" type="text/css" href="../../../css/fenye.css">
    <script type="text/javascript" src="../../../js/jquery.js" ></script>
</head>
<body>
<script language="JavaScript">
    $(document).ready(function () {
        var b=1;
        $(".love_button").click(function(){
            if(b){
                $(".love_button").css("background-image","url(../../../img/bigheart.jpg)");
                $("love_value").attr("value","1");
                b--;
            }else{
                $(".love_button").css("background-image","url(../../../img/bigheart2.jpg)");
                $("love_value").attr("value","0");
                b=1;
            }
        });
    });
</script>

<div class="clearfix">

    <!-- left nav start -->
    <div class="index_left fl">
        <div class="logo"><img src="../../../img/icon/loga.jpg" /></div>
        <div class="nav">
            <ul>
                <li><a href="${website}/carousel/list2">网站首页</a></li>
                <li id="nav_01"><a href="${website}/nature/list">自然风光</a></li>
                <li><a href="${website}/user/toPerson">人像写真</a></li>
                <li><a href="${website}/user/toCity">城市建筑</a></li>
                <li><a href="${website}/user/toLogin">登录注册</a></li>
            </ul>
        </div>
        <div class="tel">
            <ul>
                <li><a href="#">回到顶部</a></li>
                <li><a>联系我们</a></li>
                <li class="tel_con">电话：400-000-0000</li>
            </ul>
        </div>
    </div>
    <!-- left nav end-->

    <!--  浮动框  start  -->
    <div id="mySidenav">
        <div id="about">
            <h style="font-size: 30px;font-weight: bold;">About作者</h>
            <p>PeterLau风光摄影</p>
            <p>居住地</br>北京市-朝阳区</p>
            <p>常用标签</br>#佳能 #风光 #城市 #日落 #箭扣长城 #建筑 #旅行 #夜景 #桃花 #乌兰布统</p>
            <ol>
                <li>机身</br>Canon EOS 5D Mark II</li>
                <li>镜头</br>Canon EF 16-35mm f/2.8L II USM</li>
                <li>手机</br>Apple iPhone 7</li>
            </ol>
        </div>
    </div>


    <!--  浮动框   end-->

    <!--  第一张图  start-->
    <div class="index_right fr">
        <form action="${website}/nature/list" method="post" >
            <c:forEach items="${natureList}" var="nature" varStatus="status">
                <tr>
                    <td><input  value="${nature.id}" hidden /></td>
                    <td><input value="${nature.content}"  hidden/></td>
                    <div class="banner"><td><img src="${nature.path}"/></td></div>
                    <button class="love_button" type="submit" >
                        <a href="/nature/update2/${nature.id}" >收藏</a>
                    </button>
                    <input class="love_value" type="text" value="0" style="display:none ">
                    <div class="Introduce">
                        <div class="title">作品简介 / Introduction of works</div>
                        <div class="Introduce_con">
                            <td>${nature.name}</td>
                        </div>
                    </div>
                </tr>
            </c:forEach>
        </form>
    </div>
</div>
</body>
</html>

