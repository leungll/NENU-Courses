<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/fmt" prefix="fmt" %>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>登录</title>
    <script type="text/javascript" src="../../../js/jquery.js" ></script>
    <script type="text/javascript" src="../../../js/code2.js" ></script>
    <link rel="stylesheet" type="text/css" href="../../../css/base/login2.css">
    <link rel="stylesheet" type="text/css" href="../../../css/base/reset.css">
</head>
<body>
<div class="clearfix">
    <div class="index_left fl">
        <div class="logo"><img src="../../../img/icon/loga.jpg"></div>
        <div class="nav">
            <ul>
                <li><a href="${website}/carousel/list2">网站首页</a></li>
                <li><a href="${website}/nature/list">风景赏析</a></li>
                <li><a href="${website}/user/toPerson">人物风情</a></li>
                <li><a href="${website}/user/toCity">城市纵览</a></li>
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
    <div class="fl transbox">
        <form class="form"   action="${website}/user/toSuper" method="post" >
            <div class="form-head">
                <h2>登录</h2>
                <p>还没有账号？<a href="${website}/user/toAdd">立即注册</a></p>
            </div>
            <div class="form-body">
                <div class=ui-input>
                    <input type="text" name="username" placeholder="昵称">
                </div>
                <div class=ui-input>
                    <input type="password" name="password" placeholder="密码">
                </div>
                <p class="forget-password">
                        <a href="reset.html">忘记密码？</a>
                </p>
                <button class="ui-button ui-button--primary"  type="submit" id="login">登录</button>
            </div>
        </form>
        <div class="if_sure"><h3>${msg}</h3></div>
    </div>
</div>
</body>
</html>




