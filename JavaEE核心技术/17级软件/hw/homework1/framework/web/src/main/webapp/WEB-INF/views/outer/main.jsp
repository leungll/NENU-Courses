<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/fmt" prefix="fmt" %>
<!doctype html>
<html>
<head>
    <meta charset="utf-8">
    <link rel="stylesheet" type="text/css" href="../../../css/base/yishuguan.css">
    <script src="../../../js/jquery.min.js"></script>
    <title>现代摄影艺术馆</title>
</head>

<body>
<div id="top">
    <div id="title">
        <h1><a href="#frame">现代摄影艺术馆</a></h1>
        <h2><a href="#frame">The Modern Art Museum of Photography</a></h2>
    </div>
    <div id="nav">
        <nav>
            <ul id="firul">
                <li><a href="${website}/nature/list">自然风光</a>
                    <audio id="beep-one" preload="auto">
                        <source src="../audio/beep.mp3"></source>
                        <source src="../audio/beep.ogg"></source>
                        Your browser isn&#39;t invited for super fun time.
                    </audio>
                </li>
                <li><a href="${website}/user/toCity">城市建筑</a></li>
                <li><a href="${website}/user/toPerson">人像写真</a></li>
                <li><a href="${website}/user/toLogin">登录注册</a></li>
                <li ><a href="#foot">了解更多</a></li>
            </ul>
        </nav>
    </div>
</div>
<!--以上内容是导航栏--><!--所用div为top、title、nav-->
<!--以下内容是轮播图-->
<div id="frame" >
    <a id="a1" class="num">1</a>
    <a id="a2" class="num">2</a>
    <a id="a3" class="num">3</a>
    <a id="a4" class="num">4</a>
    <a id="a5" class="num">5</a>
    <div id="photos" class="play">
        <c:forEach items="${carouselList2}"  var="carousel" varStatus="status">
                    <img src="${carousel.path}">
        </c:forEach>
    </div>
</div>
<!--以上内容是轮播图-->
<!--以下内容是第一段文本-->
<div id="text">
    <div id="textbody">
        <h1>Daily Photo recommendation</h1>
        <h2> Night City</h2>
        <span>There is no night in this city, the noise of vehicles and the dazzling streetlights have forgotten the memories of the night in the countryside. Raising the head, the moon in the sky is roughly half of the perfect time. The dim light and the light from the neon light on the ground echo the loneliness of the sky palace and the prosperity of the world. The dim moonlight lined the sky. Because of the influence of vision, I felt that the sky was the highest in the sky. The sky in the distance disappeared on the horizon. The sky was delusions of the sky like a huge Mongolia bag. The mountains in the distance were also hidden in the night, and the dots of lights on the mountain were outlined as stars in the sky.</span>
        <a href="#trans"><img src="../../../img/icon/down.jpg"></a>
    </div>
</div>
<!--以上内容是第一段文本-->
<!--以下内容是透明框-->
<div id="trans">

</div>
<!--以上内容是透明框-->
<!--以下内容是画廊一-->
<div id="gallery2">
    <h1>每日画廊推荐</h1>
    <h2><a href="http://www.360doc.com/content/16/0610/09/178233_566430862.shtml">肖全</a>：「我们这一代」，正无可挽回地老去</h2>
    <br/>
    <span>肖全被称为“中国最好的人像摄影师”。<br/>肖全在摄影圈内外的知名度，靠的是《我们这一代》的大型摄影集，这本出版于1996年的画册几乎囊括了1980、1990年代文学艺术界风云一时的各色知名人物，<br/>其中有、张艺谋、陈凯歌、姜文、何训田、谭盾、北岛、王安忆、史铁生、陈村、崔健等人。<br/>为了拍摄这本画册，肖全走南闯北，用了将近10年时间才告完成。肖全也因此有了“中国最好的人像摄影师”的美誉</span>
    <div id="content">
        <div class="imgs2"><a class="example2" href="../../../img/womenzheyidai/yizhinan.jpg"><img src="../../../img/womenzheyidai/yizhinan.jpg"></a></div>
        <div class="imgs2"><a class="example2" href="../../../img/womenzheyidai/cuijian.jpg"><img src="../../../img/womenzheyidai/cuijian.jpg"></a></div>
        <div class="imgs2"><a class="example2" href="../../../img/womenzheyidai/douwei.jpg"><img src="../../../img/womenzheyidai/douwei.jpg"></a></div>
        <div class="imgs2"><a class="example2" href="../../../img/womenzheyidai/jiangwen.jpg"><img src="../../../img/womenzheyidai/jiangwen.jpg"></a></div>
        <div class="imgs2"><a class="example2" href="../../../img/womenzheyidai/sanmao.jpg"><img src="../../../img/womenzheyidai/sanmao.jpg"></a></div>
        <div class="imgs2"><a class="example2" href="../../../img/womenzheyidai/yuhua.jpg"><img src="../../../img/womenzheyidai/yuhua.jpg"></a></div>
    </div>
</div>

<script src="../../../js/jqueryLibrary.min.js"></script>
<script src="../../../js/jquery.imgbox.pack.js"></script>
<script>
    $(function(){
//	$(".example1").imgbox();
        $(".example2").imgbox({
            'speedIn'		: 0,
            'speedOut'		: 0,
            'alignment'		: 'center',
            'overlayShow'	: true,
            'allowMultiple'	: false
        });
    });
</script>
<!--以上内容是画廊一-->
<!--以下内容是画廊二-->
<div id="gallery">
    <h1>每日画廊推荐</h1>
    <h2><a href="http://www.lwlm.com/sixiangzhexue/201603/809297.htm">金我他</a>：韩国人的东方哲学思想</h2>
    <br/>
    <span>金我他（Atta Kim）是备受西方瞩目的韩国摄影师，作品以拥有浓厚东方哲学意味著称。他善于使用影像作为媒介来表达自己的哲学观念，并借助照片拓展到更广阔的艺术领域。<br/>《解构主义》（ Deconstruction）、《博物馆》（The Museum Project）、《空气之上》（ON-AIR Project）、《自然涂写》（Drawing of Nature）是金我他最重要的几部摄影作品。</span>
    <div id="content">
        <div class="imgs"><a class="example2" href="../../../img/hualang/1.jpg"><img src="../../../img/hualang/1.jpg"></a></div>
        <div class="imgs"><a class="example2" href="../../../img/hualang/2.jpg"><img src="../../../img/hualang/2.jpg"></a></div>
        <div class="imgs"><a class="example2" href="../../../img/hualang/3.jpg"><img src="../../../img/hualang/3.jpg"></a></div>
        <div class="imgs"><a class="example2" href="../../../img/hualang/4.jpg"><img src="../../../img/hualang/4.jpg"></a></div>
        <div class="imgs"><a class="example2" href="../../../img/hualang/5.jpg"><img src="../../../img/hualang/5.jpg"></a></div>
        <div class="imgs"><a class="example2" href="../../../img/hualang/6.jpg"><img src="../../../img/hualang/6.jpg"></a></div>
        <div class="imgs"><a class="example2" href="../../../img/hualang/7.jpg"><img src="../../../img/hualang/7.jpg"></a></div>
        <div class="imgs"><a class="example2" href="../../../img/hualang/8.jpg"><img src="../../../img/hualang/8.jpg"></a></div>
    </div>
</div>

<script src="../../../js/jqueryLibrary.min.js"></script>
<script src="../../../js/jquery.imgbox.pack.js"></script>
<script>
    $(function(){
        $(".example1").imgbox();
        $(".example2").imgbox({
            'speedIn'		: 0,
            'speedOut'		: 0,
            'alignment'		: 'center',
            'overlayShow'	: true,
            'allowMultiple'	: false
        });
    });
</script>
<!--以上内容是画廊二-->
<!--以下内容是末尾-->
<div id="foot">
    <div class="footbody">
        <h1>版权声明</h1>
        <p>所有照片来源于网络，主要素材来源<a href="https://tuchong.com/">图虫网</a>。</p>
        <p>本网站仅用于比赛学习，不做任何商业用途。</p>
    </div>
    <div class="light"></div>
    <div class="footbody">
        <h1>相关链接</h1>
        <p><a href=""http://www.lwlm.com/sixiangzhexue/201603/809297.htm"" target="_blank">金我他：韩国人的东方哲学</a>|<a href="http://www.360doc.com/content/16/0610/09/178233_566430862.shtml" target="_blank">摄影师肖全：《我们这一代》</a></p>
        <p><a href="#" target="_blank">链接三</a>|<a href="#" target="_blank">链接四</a></p>
        <p><a href="#" target="_blank">链接五</a>|<a href="#" target="_blank">链接六</a></p>
    </div>
    <div class="light"></div>
    <div class="footbody">
        <h1>联系我们</h1>
        <p>设计：<a href="mailto:1324816813@qq.com?subject=Hello%20again">李娜</a></p>
        <p>内容：<a href="mailto:1324816813@qq.com?subject=Hello%20again">张芸嘉</a></p>
        <p>功能：<a href="mailto:1324816813@qq.com?subject=Hello%20again">孔一言</a></p>
        <p>维护：<a href="mailto:1324816813@qq.com?subject=Hello%20again">梁莉莉</a></p>
    </div>
</div>
<script>var beepOne = $("#beep-one")[0];
$("#firul a")
    .mouseenter(function() {
        beepOne.play();
    });</script>
</body>
</html>
