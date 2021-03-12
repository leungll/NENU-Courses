<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/core" prefix="c" %>
<%@ taglib uri="http://java.sun.com/jsp/jstl/fmt" prefix="fmt" %>
<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>人像写真</title>
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

                b--;
            }else{
                $(".love_button").css("background-image","url(../../../img/bigheart2.jpg)");

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
                <li id="nav_01"><a href="${website}/user/toPerson">人像写真</a></li>
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
            <p>沐沐打晕的狼</p>
            <p>居住地</br>江苏-苏州</p>
            <p>常用标签</br>#佳能 #儿童 #人像 #小清新 #上海 #日系 #苏州 #图虫封面你做主 #孩子，不想让你长大 #35mm</p>
            <ol>
                <li>机身</br>Canon EOS 6D</li>
                <li>镜头</br>Canon EF 24-70mm f/2.8L II USM</li>
                <li>手机</br>Apple iPhone 8 Puls</li>
            </ol>
        </div>
    </div>


    <!--  浮动框   end-->

    <!--  第一张图  start-->
    <div class="index_right fr">
        <div class="banner"><img src="../../../img/person/1.jpg" /></div>
        <div>
            <button class="love_button"  ></button>
            <input class="love_value" type="text" value="0" style="display:none ">
        </div>
        <div class="Introduce">
            <div class="title">作品简介 / Introduction of works</div>
            <div class="Introduce_con">
							对我而言，你只是一个小男孩，和其他成千上万的小男孩没有什么不同。我不需要你。你也不需要我。对你而言，我也和其它成千上万的狐狸并没有差别。但是，假如你驯服了我，我们就彼此需要了。对我而言，你就是举世无双的;对你而言，我也是独一无二的……
      					</div>
        </div>
    </div>
    <!--  第一张图  end-->

    <!--  第二张图  start-->
    <div class="index_right fr">
        <div class="banner"><img src="../../../img/person/2.jpg" /></div>
        <div>
            <button class="love_button"  ></button>
            <input class="love_value" type="text" value="0" style="display:none ">
        </div>
        <div class="Introduce">
            <div class="title">作品简介 / Introduction of works</div>
            <div class="Introduce_con">
      						每一个人都有自己的星星，但其中的含意却因人而异。对旅人而言，星星是向导;对其他人而言，它们只不过是天际中闪闪发光的小东西而已;对学者而言，星星则是一门待解的难题;对我那位商人来说，它们就是财富。不过，星星本身是沉默的你只有你——了解这些星星与众不同的含义……
      					</div>
        </div>
    </div>
    <!--  第二张图  end-->


    <!--  第三张图  start-->
    <div class="index_right fr">
        <div class="banner"><img src="../../../img/person/3.jpg" /></div>
        <div>
            <button class="love_button"  ></button>
            <input class="love_value" type="text" value="0" style="display:none ">
        </div>
        <div class="Introduce">
            <div class="title">作品简介 / Introduction of works</div>
            <div class="Introduce_con">
      						你所居住的星球上的人们，在同一座花园培育了五千朵玫瑰——却无法从中找到他们所要寻找的东西。但是，他们所寻找的，其实是可以从一朵玫瑰花或一滴水中找到的。然而眼睛往往是盲从的。人还是必须用心去看……
      					</div>
        </div>
    </div>
    <!--  第三张图  end-->

    <!--  第四张图  start-->
    <div class="index_right fr">
        <div class="banner"><img src="../../../img/person/4.jpg" /></div>
        <div>
            <button class="love_button"  ></button>
            <input class="love_value" type="text" value="0" style="display:none ">
        </div>
        <div class="Introduce">
            <div class="title">作品简介 / Introduction of works</div>
            <div class="Introduce_con">
      						当你不再感到伤心的时候,时间会冲淡一切伤痛，你就会因认识我而感到心满意足。你是我永远的朋友。将会和我一起欢笑。为了欢乐，你会经常打开窗子……当你的朋友看到你因仰望天空而大笑时，一定会感到莫名其妙!到时候，你可以对他们说：“是的，星星总让我开心而笑!”
      					</div>
        </div>
    </div>
    <!--  第四张图  end-->

    <!--  第五张图  start-->
    <div class="index_right fr">
        <div class="banner"><img src="../../../img/person/5.jpg" /></div>
        <div>
            <button class="love_button"  ></button>
            <input class="love_value" type="text" value="0" style="display:none ">
        </div>
        <div class="Introduce">
            <div class="title">作品简介 / Introduction of works</div>
            <div class="Introduce_con">
      						倘若一个人对一朵花情有独钟，而那花在浩瀚的星河中，是独一无二的，那么，他只要仰望繁星点点，就心满意足了。他会喃喃自语：“我的花就在星河的某个角落……”可是，这花一旦被羊吃掉了，一瞬间，所有星星都将随之黯淡无光……那你也认为这不重要吗?
      					</div>
        </div>
    </div>
    <!--  第五张图  end-->

    <!--  第六张图  start-->
    <div class="index_right fr">
        <div class="banner"><img src="../../../img/person/6.jpg" /></div>
        <div>
            <button class="love_button"  ></button>
            <input class="love_value" type="text" value="0" style="display:none ">
        </div>
        <div class="Introduce">
            <div class="title">作品简介 / Introduction of works</div>
            <div class="Introduce_con">
      						麦田和我没有任何关联，真令人沮丧。不过，你有金黄色的头发。想想看，如果你驯服了我，那该有多好啊!小麦也是金黄色的，那会使我想起你。我会喜欢听麦田里的风声……
      					</div>
        </div>
    </div>
    <!--  第六张图  end-->

    <!--  第七张图  start-->
    <div class="index_right fr">
        <div class="banner"><img src="../../../img/person/7.jpg" /></div>
        <div>
            <button class="love_button"  ></button>
            <input class="love_value" type="text" value="0" style="display:none ">
        </div>
        <div class="Introduce">
            <div class="title">作品简介 / Introduction of works</div>
            <div class="Introduce_con">
      						驯服对我是有好处的——因为麦田的颜色。再回头看那些玫瑰花吧!到时你就明白你的玫瑰花仍是举世无双的一朵花。
      					</div>
        </div>
    </div>
    <!--  第七张图  end-->

    <!--  第八张图  start-->
    <div class="index_right fr">
        <div class="banner"><img src="../../../img/person/8.jpg" /></div>
        <div>
            <button class="love_button"  ></button>
            <input class="love_value" type="text" value="0" style="display:none ">
        </div>
        <div class="Introduce">
            <div class="title">作品简介 / Introduction of works</div>
            <div class="Introduce_con">
      						我就在繁星中的一颗上生活。我会站在其中的一颗星星上微笑。当你在夜间仰望天际时，就仿佛每一颗星星都在笑……你——只有你——才能拥有会笑的星星……
      					</div>
        </div>
    </div>
    <!--  第八张图  end-->

</div>
</body>
</html>
