<template>
  <div class="home">
    <div id="TITLE">
      <div id="title">
        <a href="http://localhost:8090/#/home">
          <h1>在线考试系统</h1>
          <span>TESTONLINE</span>
        </a>
        <div id="operation">
          <router-link class="header_login" slot="right" :to="userInfo.sno ? '/profile/info' : '/login'">
            <span class="header_login_text" v-if="!userInfo.sno">
              登录 | 注册
            </span>
          </router-link>
        </div>
      </div>
    </div>
    
    <!-- <HeaderTop title="在线考试系统">
      <router-link class="header_login" slot="right" :to="userInfo.sno ? '/profile/info' : '/login'">
        <span class="header_login_text" v-if="!userInfo.sno">
          登录|注册
        </span>
        <span class="header_login_text" v-else>
          <img :src="userInfo.stuImgSrc ? userInfo.stuImgSrc : require('../../common/imgs/profile.jpg')" class="profile_img">
        </span>
        
      </router-link>
    </HeaderTop> -->
    <div id="move">
            <!-- <img src="../../assets/banner3.jpg" width="100%" height="100%;" id="backimg" /> -->
            <el-carousel height="460px" type="card" :autoplay="true" >
                <el-carousel-item v-for="item in dataimg" v-bind:key="item.index">
                    <div id="playCard">
                        <img :src="item.src" />
                        <!-- <div id="cardText">
                            <h1>{{ item.msg2 }}</h1>
                            <span>{{ item.msg3 }}</span>
                        </div> -->
                        <!-- <div id="detail">
                            <h1>{{ item.msg1 }}</h1>
                        </div> -->
                    </div>
                </el-carousel-item>
            </el-carousel>
        </div>
  </div>
</template>

<script>
  import {Toast} from 'mint-ui'
  import HeaderTop from '../../components/HeaderTop/HeaderTop.vue'
  import Swiper from '../../components/Swiper/Swiper.vue'
  import {mapState} from 'vuex'

  export default {
    name: "",
    created(){
      this.$store.dispatch('getRotationImages');
      // this.$store.dispatch('getExamCalendar');
      this.$store.dispatch('getLanguagesInfo');
    },
    data() {
      return {
        currentDate:new Date(),
        curSelect:null,
        alreadyClock: false,
        dataimg :[
          {
            src: require('../../assets/1.jpg'),
          },
          {
            src: require('../../assets/2.jpg'),
          },
          {
            src: require('../../assets/3.jpg'),
          },
          {
            src: require('../../assets/4.jpg'),
          }
        ],
      }
    },
    computed:{
      //轮播图的数组
      ...mapState(['examCalendar','rotationImages','userInfo','languagesInfo'])
    },
    methods:{
    },
    components:{
      HeaderTop,
    } 
  }
</script>

<style lang="stylus" type="text/stylus" rel="stylesheet/stylus" scoped>
    //  #move {
    //     margin-top: 5%;
    //   }
      #TITLE {
        width 100%
        padding 1%
      }
      #title{
        width: 10%;
        line-height: 150%;
        color: black;
        text-align: center;
      }
      #title a {
        color: black;
        text-decoration: none;
      }
      #title h1 {
        font-size 20px
      }
      #operation {
        position: absolute;
        right: 3%;
        top: 3%;
      }
</style>

