<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/fmt" prefix="fmt" %>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>城市建筑</title>
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
                <li><a href="${website}/nature/list">自然风光</a></li>
                <li><a href="${website}/user/toPerson">人像写真</a></li>
                <li id="nav_01"><a href="${website}/user/toCity">城市建筑</a></li>
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
            <p>frankleesz</p>
            <p>居住地</br>江苏-苏州</p>
            <p>常用标签</br>#索尼 #后期 #苏州 #色彩 #风光 #城市 #建筑 #上海 #卡色第7期“现金大奖”风光摄影月赛 #广角</p>
            <ol>
                <li>机身</br>SONY ILCE-7RM</li>
                <li>镜头</br>FE 16-35mm F4 ZA</li>
                <li>手机</br>Apple iPhone X</li>
            </ol>
        </div>
    </div>


    <!--  浮动框   end-->

    <!--  第一张图  start-->
    <div class="index_right fr">
        <div class="banner"><img src="../../../img/city/1.jpg" /></div>
        <div>
            <button class="love_button"  ></button>
            <input class="love_value" type="text" value="0" style="display:none ">
        </div>
        <div class="Introduce">
            <div class="title">作品简介 / Introduction of works</div>
            <div class="Introduce_con">
      						这时，天色已经暗了下来，我们这排高高地俯瞰着城市的灯火通明的窗户，一定让街头偶尔抬头眺望的人感到了，人类的秘密也有其一份在这里吧，我也是这样的一个过路人，举头望着诧异着。我既在事内又在事外，几杯永无枯竭的五彩纷呈的生活所吸引，同时又被其排斥着。
      					</div>
        </div>
    </div>
    <!--  第一张图  end-->

    <!--  第二张图  start-->
    <div class="index_right fr">
        <div class="banner"><img src="../../../img/city/2.jpg" /></div>
        <div>
            <button class="love_button"  ></button>
            <input class="love_value" type="text" value="0" style="display:none ">
        </div>
        <div class="Introduce">
            <div class="title">作品简介 / Introduction of works</div>
            <div class="Introduce_con">
      						人一生最孤独的时刻就是看着他们的世界土崩瓦解，而自己只能茫然无力地看着。
      					</div>
        </div>
    </div>
    <!--  第二张图  end-->


    <!--  第三张图  start-->
    <div class="index_right fr">
        <div class="banner"><img src="../../../img/city/3.jpg" /></div>
        <div>
            <button class="love_button"  ></button>
            <input class="love_value" type="text" value="0" style="display:none ">
        </div>
        <div class="Introduce">
            <div class="title">作品简介 / Introduction of works</div>
            <div class="Introduce_con">
      						世界上只有被追求者和追求者忙碌者和疲惫者。
      					</div>
        </div>
    </div>
    <!--  第三张图  end-->

    <!--  第四张图  start-->
    <div class="index_right fr">
        <div class="banner"><img src="../../../img/city/4.jpg" /></div>
        <div>
            <button class="love_button"  ></button>
            <input class="love_value" type="text" value="0" style="display:none ">
        </div>
        <div class="Introduce">
            <div class="title">作品简介 / Introduction of works</div>
            <div class="Introduce_con">
      						我整夜没睡;雾笛声劲儿桑德海湾上凄恻地鸣响我辗转反侧像生了病样理清哪些狰狞现实哪些怕梦魇 。
      					</div>
        </div>
    </div>
    <!--  第四张图  end-->

    <!--  第五张图  start-->
    <div class="index_right fr">
        <div class="banner"><img src="../../../img/city/5.jpg" /></div>
        <div>
            <button class="love_button"  ></button>
            <input class="love_value" type="text" value="0" style="display:none ">
        </div>
        <div class="Introduce">
            <div class="title">作品简介 / Introduction of works</div>
            <div class="Introduce_con">
      						情况真实时定感觉了已失去了原来温馨世界感觉了长时间只活梦里所付出高昂代价时定举头望过 令人恐怖叶片看了陌生天宇定由得颤栗了当发现玫瑰原来长得奇形怪状照疏疏落落草叶上阳光粗鄙没 有真实物新世界里怜鬼魂们四处随风飘荡们像呼吸空气样吮吸着梦幻。
      					</div>
        </div>
    </div>
    <!--  第五张图  end-->

    <!--  第六张图  start-->
    <div class="index_right fr">
        <div class="banner"><img src="../../../img/city/6.jpg" /></div>
        <div>
            <button class="love_button"  ></button>
            <input class="love_value" type="text" value="0" style="display:none ">
        </div>
        <div class="Introduce">
            <div class="title">作品简介 / Introduction of works</div>
            <div class="Introduce_con">
      						月光渐渐升高显得渺小房屋开始融入溶溶月色去此时我眼前逐渐浮现出座古老岛屿当年荷兰航海者眼种妖娆风姿--新世界翠绿 欲滴胸膛现复存林木(修造盖茨比住过座别墅被砍伐掉了)曾经温馨地煽起人类也伟大梦想;短暂神奇时刻里人类定 片大陆前屏住了呼吸情自禁地耽入既理解也没希冀过美享受之历史上次面对面地欣赏着与感受惊奇力量相称景观。
      					</div>
        </div>
    </div>
    <!--  第六张图  end-->

    <!--  第七张图  start-->
    <div class="index_right fr">
        <div class="banner"><img src="../../../img/city/7.jpg" /></div>
        <div>
            <button class="love_button"  ></button>
            <input class="love_value" type="text" value="0" style="display:none ">
        </div>
        <div class="Introduce">
            <div class="title">作品简介 / Introduction of works</div>
            <div class="Introduce_con">
      						经过慢慢追索才来了片蓝色草地上梦想定已经离得此之近至于几乎会抓了知道梦想已经被甩了身已经隐藏了城市外冥蒙之里共和国黑暗土地黑夜延伸着……
      					</div>
        </div>
    </div>
    <!--  第七张图  end-->

    <!--  第八张图  start-->
    <div class="index_right fr">
        <div class="banner"><img src="../../../img/city/8.jpg" /></div>
        <div>
            <button class="love_button"  ></button>
            <input class="love_value" type="text" value="0" style="display:none ">
        </div>
        <div class="Introduce">
            <div class="title">作品简介 / Introduction of works</div>
            <div class="Introduce_con">
      						消逝了奢华房子里消逝了富裕充实生活。
      					</div>
        </div>
    </div>
    <!--  第八张图  end-->

</div>
</body>
</html>
