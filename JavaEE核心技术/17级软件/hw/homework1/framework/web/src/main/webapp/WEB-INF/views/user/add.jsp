<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/fmt" prefix="fmt" %>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>注册</title>
    <link rel="stylesheet" type="text/css" href="../../../css/base/login2.css"/>
    <script type="text/javascript" src="../../../js/code2.js" ></script>
</head>
<body>
<div class="clearfix">
    <!-- left nav start -->
    <div class="index_left fl">
        <div class="logo"><img src="../../../img/icon/loga.jpg" /></div>
        <div class="nav">
            <ul>
                <li><a href="${website}/carousel/list2">网站首页</a></li>
                <li><a href="风景.html">风景赏析</a></li>
                <li><a href="人物.html">人物风情</a></li>
                <li><a href="城市.html">城市纵览</a></li>
                <li id="nav_01"><a href="${website}/user/toLogin">登录注册</a></li>
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

    <div class="fl transbox">
        <form class="form" action="${website}user/add" method="post" >
            <div class="form-head">
                <h2>新用户注册</h2>
                <p>已有账号？<a href="${website}/user/toLogin">立即登录</a></p>
            </div>
            <div class="form-body">
                <div class=ui-input>
                    <input type="text" placeholder="昵称" id="name" name="username"/>
                </div>
                <div class="ui-input narrow-input">
                    <div>
                        <input type="text" placeholder="输入验证码" id="input" />
                        <input type="button" id="checkCode" class="code" onclick="createCode()" />
                        <a class="sms-button" href="#" onclick="createCode()">看不清楚</a><br>
                        <input type="button" value="验证" onclick="validate()" />
                    </div>
                </div>
                <div class="ui-input">
                    <input type="password" id="passage" placeholder="密码，6-16位，区分大小写" name="password"/>
                </div>
                <div class=ui-input>
                    <input type="text" placeholder="个性签名" id="name"  name="sig" />
                </div>
                <button class="ui-button ui-button--primary" >注册</button>
            </div>
        </form>
        <div class="if_sure"><h3>${msg}</h3></div>
    </div>
</div>
</body>
</html>

