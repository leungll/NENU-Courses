<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/fmt" prefix="fmt" %>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<!DOCTYPE html>
<html>
<head>
    <meta charset="utf-8"/>
    <title><%=session.getAttribute("username")%>的空间</title>
    <link rel="stylesheet" type="text/css" href="../../../css/base/aboutus.css">
    <script type="text/javascript" src="../../../js/jquery.js" ></script>
</head>
<body>
<div class="index_left fl">
    <div class="logo"><img src="../../../img/icon/loga.jpg"></div>
    <div class="nav">
        <ul>
            <li><a href="${website}/carousel/list2">网站首页</a></li>
            <li><a href="${website}/nature/list">风景赏析</a></li>
            <li><a href="${website}/user/toPerson">人物风情</a></li>
            <li><a href="${website}/user/toCity">城市纵览</a></li>
            <li>个人主页</li>
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

<div id="right">
    <div class="infor">
        <img src="../../../img/aboutUs/1.jpg">
        <div class="text">
            <input id=“get_value” value="<%=session.getAttribute("id")%>" hidden />
            <div><h2 class="id">昵称：</h2>&emsp;<span><%=session.getAttribute("username")%></span></div>
            <div><h3>个性签名:&emsp;</h3><span class="description"><%=session.getAttribute("sig")%></span></div>
        </div>
    </div>
    <div class="re_text">
        <button id="re_text">编辑</button>
    </div>
    <div class="rewrite">
        <h4>修改信息</h4>
        <form action="/user/update" method="post">
            <input type="text"  id="set_value" name="id"  />
            <div>
                <span>昵称：&emsp;&emsp;</span><input type="text" id="rename" name="username">
            </div>
            <div>
                <span>密码：&emsp;&emsp;<input type="text " id="repassword" name="password"></span>
            </div>
            <div>
                <span>个性签名：<input type="text " id="reword" name="sig"></span>
            </div>
            <button id="re_sure" type="submit" >确认修改</button>
        </form>
    </div>
    <script language="JavaScript">
        $(document).ready(function(){

            $("#re_text").click(function(){
                $(".rewrite").toggle();
                var need=$("#“get_value”").val();
                $("#set_value").val(need);
            });
            $("#re_sure").click(function(){
                $(".rewrite").toggle();
            })
        });
    </script>
    <div class="infor_love">
        <h3>我的收藏</h3>
        <div id="love">
            <form action="/nature/list2" method="post">
                <c:forEach items="${natureList2}" var="nature" varStatus="status">
                    <div class="love_div">
                        <td><img id="love_img" src="${nature.path}"/></td>
                        <a href="${website}/nature/update3/${nature.id}"><div class="BUTTOM">
                           <img id="delete_img" src="../../../img/delete.jpg"/>
                        </div></a>
                            <%--<button class="set_love"><a href="${website}/nature/update3/${nature.id}">删除</a></button>--%>
                    </div>
                </c:forEach>
            </form>
        </div>
    </div>
</div>
</body>
</html>


