<!--
 * @Author: 吴婷婷、屈英杰
 * @Date: 2020-06-01 13:02:54
 * @LastEditTime: 2020-07-01 11:09:16
 * @LastEditors: Please set LastEditors
 * @Description: 学生端页面
 * @FilePath: \onlineexamLLL\src\pages\Profile\Profile.vue
--> 
<template>
  <div class="profile">
    <section class="profile-number">
      <div id="title">
        <a href="http://localhost:8090/#/home">
          <h1>在线考试系统</h1>
          <span>TESTONLINE</span>
        </a>
      </div>
      <a href="javascript:void(0)" class="profile-link" @click="personInfor=true">
        <div class="user-info">
          <p class="user-info-top" >{{userInfor.username}}</p>
        </div>
        <div class="profile_image">
          <img :src="require('../../assets/Student.jpg')" alt="学生头像">
          <!--<img src="../../common/imgs/profile.jpg" alt="头像" v-else>-->
        </div>
      </a>
    </section>

    <div id="navigation">
      <el-menu
      default-active="1"
      class="el-menu-vertical-demo"
      background-color="#f5f5f5"
      active-text-color="#4ab8a1">
        <el-menu-item index="1">
          <i class="el-icon-menu"></i>
          <span slot="title" @click="isTest=true; myScore=false;sureTest=false; mistake=false;noticeShow=false">我的考试</span>
        </el-menu-item>
        <el-menu-item index="2" @click="isTest=false; myScore=true; sureTest=false; mistake=false;noticeShow=false">
          <i class="el-icon-document"></i>
          <span slot="title">查看成绩</span>
        </el-menu-item>
        <el-menu-item index="3" @click="isTest=false; myScore=false; sureTest=false; mistake=true;noticeShow=false">
          <i class="el-icon-document"></i>
          <span slot="title">错题集</span>
        </el-menu-item>
        <el-menu-item index="4" @click="isTest=false; myScore=false; sureTest=false; mistake=false;noticeShow=true">
          <i class="el-icon-document"></i>
          <span slot="title">我的公告</span>
        </el-menu-item>
      </el-menu>
    </div>

    <!-- 考试 -->
    <!-- 提示 -->
    <el-card v-show="isTest" id="testOrNot">
      <div slot="header" class="clearfix" style="text-align:center">
        <span>考试通知</span>
      </div>
      <div>
        <p>
          {{userInfor.username}}同学：你好！
        </p>
        <br>
        <p style="line-height: 20px">
          &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;考试通道已开启，请合理安排时间完成考试！
        </p>
        <br>
      </div>
      <div style="text-align: center">
        <el-button type="success" plain @click="isTest=false;sureTest=true">选择试卷</el-button>
      </div>
    </el-card>

    <!-- 试卷列表 -->
    <el-card v-show="sureTest" id="testYes">
      <el-table :data="tableData2.slice((currentPage2-1)*pagesize,currentPage2*pagesize)" style="width: 100%">
          <el-table-column align="center" type="index" label="序号" width="50"></el-table-column>
          <!-- <el-table-column align="center" prop="paperId" label="试卷编号"></el-table-column> -->
          <el-table-column align="center" prop="paperName" label="试卷名称"></el-table-column>
          <el-table-column align="center" prop="operation" label="操作">
            <template slot-scope="scope">
              <el-button type="success" 
                icon="el-icon-edit" 
                title="开始考试" 
                circle 
                plain
                @click="beginTest(scope.$index, scope.row)"></el-button>
          </template>
                        <!-- <el-button type="danger" icon="el-icon-delete" title="删除" @click="dele" plain>删除</el-button> -->
                    </el-table-column>
      </el-table>
      <div class="pagination">
        <el-pagination background layout="prev, pager, next" :total="total2" @current-change="current_change2" class="paginate"></el-pagination>
      </div>
    </el-card>

    <!-- 考试页面 -->
    <el-card id="answer" v-show="testing">
      <div slot="header" class="clearfix" style="text-align:center">
        <span>答题卡</span>
        <br><br>
        <p>用时：{{str}}</p>
        <el-button type="success" 
                  icon="el-icon-check" 
                  style="text-align: right"
                  size="small"
                  plain 
                  @click="submiteAnwser()">确认提交</el-button>
      </div>
      <!-- 单选 -->
      <div v-for="(item, index) in questionDanxuan" :key="item.index" v-show="danxuanShow">
        <template v-if="index<questionDanxuan.length-1">
          <p style="margin-top: 10px; margin-down: 5px;">
            <!-- <span>{{item.index}}. </span> -->
            <span>{{item.content}}</span>
          </p>
          <el-radio-group v-model="item.solution" >
            <el-radio label="A">A.{{item.typeA}}</el-radio>
            <el-radio label="B">B.{{item.typeB}}</el-radio>
            <el-radio label="C">C.{{item.typeC}}</el-radio>
            <el-radio label="D">D.{{item.typeD}}</el-radio>
          </el-radio-group>
        </template>
      </div>
      <!-- 判断 -->
      <div v-for="(item, index) in questionPanduan" :key="item.index" v-show="panduanShow">
        <template v-if="index<questionPanduan.length-1">
          <p style="margin-top: 10px; margin-down: 5px;">
            <!-- <span>{{item.index}}. </span> -->
            <span>{{item.content}}</span>
          </p>
          <el-radio-group v-model="item.solution" >
            <el-radio label="A">A.{{item.typeA}}</el-radio>
            <el-radio label="B">B.{{item.typeB}}</el-radio>
          </el-radio-group>
        </template>
      </div>
      <!-- 填空 -->
      <div v-for="(item, index) in questionTiankong" v-bind:key="item.index" v-show="tiankongShow">
        <template v-if="index<questionTiankong.length-1">
          <p style="margin-top: 10px; margin-down: 5px;">
            <!-- <span>{{item.index}}. </span> -->
            <span>{{item.content}}</span>
          </p>
          <el-input type="text" placeholder="请输入答案" v-model="item.solution"></el-input>
        </template>
      </div>
      <!-- 问答 -->
        <div v-for="(item, index) in questionWenda" v-bind:key="item.index" v-show="wendaShow">
          <template v-if="index<questionWenda.length-1">
            <p style="margin-top: 10px; margin-down: 5px;">
              <!-- <span>{{item.index}}. </span> -->
              <span>{{item.content}}</span>
            </p>
            <el-input type="textarea" placeholder="请输入答案" v-model="item.solution"></el-input>
          </template>
      </div>
    </el-card>
    
    <!-- 查看成绩 -->
    <el-card v-show="myScore" id="score">
      <el-table :data="tableData1.slice((currentPage1-1)*pagesize,currentPage1*pagesize)" style="width: 100%" id="peoTable">
          <el-table-column align="center" type="index" label="序号" width="50"></el-table-column>
          <!-- <el-table-column align="center" prop="paperId" label="试卷编号"></el-table-column> -->
          <el-table-column align="center" prop="paperName" label="试卷名称"></el-table-column>
          <el-table-column align="center" prop="mark" label="得分"></el-table-column>
      </el-table>
      <div class="pagination">
            <el-pagination background layout="prev, pager, next" :total="total1" @current-change="current_change1" class="paginate"></el-pagination>
      </div>
    </el-card>

    <!-- 错题集 -->
    <el-card v-show="mistake" id="mis">
      <el-table :data="tableData3.slice((currentPage3-1)*pagesize,currentPage3*pagesize)" style="width: 100% ">
          <el-table-column align="center" prop="wrongId" label="错误编号"></el-table-column>
          <el-table-column align="center" prop="paperId" label="试卷编号"></el-table-column>
          <el-table-column align="center" prop="paperDetailId" label="题目编号"></el-table-column>
          <el-table-column align="center" prop="answer" label="所选答案"></el-table-column>
          <el-table-column align="center" prop="right" label="正确答案"></el-table-column>
          <el-table-column align="center" prop="score" label="满分"></el-table-column>
          <el-table-column align="center" prop="nowScore" label="得分"></el-table-column>
          <el-table-column align="center" prop="operation" label="操作">
            <template slot-scope="scope">
              <el-button type="danger" 
                icon="el-icon-delete" 
                title="删除错题" 
                circle 
                plain
                @click="deleteWrongQuestion(scope.$index, scope.row)"></el-button>
            </template>
                        <!-- <el-button type="danger" icon="el-icon-delete" title="删除" @click="dele" plain>删除</el-button> -->
          </el-table-column>
      </el-table>
      <div class="pagination">
            <el-pagination background layout="prev, pager, next" :total="total3" @current-change="current_change3" class="paginate"></el-pagination>
      </div>
    </el-card>

    <!-- 公告管理 -->
    <el-card v-show="noticeShow" id="noti">
        <el-table :data="tableData4.slice((currentPage4-1)*pagesize,currentPage4*pagesize)" style="width: 100%" id="peoTable">
          <el-table-column align="center" type="index" label="序号" width="50"></el-table-column>
          <!-- <el-table-column width="80px" align="center" prop="noticeId" label="公告编号"></el-table-column> -->
          <el-table-column width="80px" align="center" prop="userId" label="发布者ID"></el-table-column>
          <el-table-column align="center" prop="title" label="标题"></el-table-column>
          <el-table-column align="center" prop="content" label="内容"></el-table-column>
          <el-table-column align="center" prop="createTime" label="发布时间"></el-table-column>
        </el-table>
        <div class="pagination">
          <el-pagination background layout="prev, pager, next" :total="total4" @current-change="current_change4" class="paginate"></el-pagination>
        </div>
    </el-card>
          
    <el-dialog title="个人信息" v-model="userInfor" :visible.sync="personInfor" :close-on-click-modal="false">
      <img id="userHead" src="../../assets/Student.jpg" width="100px" height="100px" style="border-radius: 50px" />
      <el-form  ref="userInfor" label-width="150px">
        <el-form-item label="用户ID：">
          <el-col :span="8">
             <span>{{userInfor.userId}}</span>
          </el-col>
        </el-form-item>
        <el-form-item label="用户名：">
          <el-col :span="8">
            <span>{{userInfor.username}}</span>
          </el-col>
        </el-form-item>
        <el-form-item label="性别：">
          <el-col :span="8">
            <span>{{userInfor.sex}}</span>
          </el-col>
        </el-form-item>
        <el-form-item label="生日：">
          <el-col :span="8">
            <span>{{userInfor.birthday}}</span>
          </el-col>
        </el-form-item>
        <el-form-item label="权限：">
          <el-col :span="8">
            <span>{{this.userPower}}</span>
          </el-col>
        </el-form-item>
      </el-form>
    </el-dialog>
  </div>
</template>

<script>
  import HeaderTop from '../../components/HeaderTop/HeaderTop.vue'
  import ProfileItem from '../../components/ProfileItem/ProfileItem.vue'
  import { mapState, mapGetters } from 'vuex'
  import { MessageBox, Toast } from 'mint-ui';
  import {reqUpdateFeedbackStatus, reqFeedbackInfo} from '../../api'
  export default {
    name: "",
    data() {
      return {
        sno:this.$store.state.userInfo.sno,
        isSelect:false,
        
        //在线考试
        //试卷id
        questionDanxuan: [],
        questionTiankong: [],
        questionPanduan: [],
        questionWenda: [],
        danxuanShow: false,
        panduanShow: false,
        tiankongShow: false,
        wendaShow: false,

        paperID: '',
        isTest: true,
        sureTest: false,
        tableData2: [],
        // radioAnswer: [],
        question: [],
        currentPage2: 1,
        total2: 0,
        h: 0,
        m: 0,
        s: 0,
        time: 0,
        str: '00:00:00',
        duration: '',
        radio: '',
        radioShow: true,
        checkShow: false,
        testing: false,

        //暂存做题答案数据
        solutionList: [],

        //分页
        pagesize: 10,
        //查看成绩
        myScore: false,
        tableData1: [],
        currentPage1: 1,
        total1: 0,
        
        //错题集
        mistake: false,
        tableData3: [],
        currentPage3: 1,
        total3: 0,

        //公告
        noticeShow: false,
        tableData4: [],
        currentPage4: 1,
        total4: 0,

        //personInfor
        personInfor: false,

        //公告
        title: '',
        content: '',

        //用户信息
        userInfor: [],
        userPower: "",
      }
    },
    computed:{
      ...mapState(['userInfo']),
      ...mapGetters(['unreadMsgCount'])
    },
    
    created(){
      //请求用户信息
      this.$ajax({
          method: "post",
          url: "http://120.26.186.88:8080/user/listUserById",
          dataType: "json",
          crossDomain: true,
          cache: false,
      }).then(resolve => {
        console.log(resolve.data[0]);
        this.userInfor = resolve.data[0];
        if(this.userInfor.power == 0)
          this.userPower = "学生";
        else if(this.userInfor.power == 1)
          this.userPower = "教师";
        else 
          this.userPower = "管理员";
      }, reject => {
          // this.peoLoading = true;
          console.log(reject);
      });

      //所有试卷加载
      this.$ajax({
          method: "post",
          url: "http://120.26.186.88:8080/paper/listPublishPaper",
          dataType: "json",
          crossDomain: true,
          cache: false,
      }).then(resolve => {
          this.tableData2 = resolve.data;
          //获取数组长度赋值给total
          this.total2 = resolve.data.length;
          // this.peoLoading = false;
          console.log(this.total2);
          console.log(resolve.data);
          
      }, reject => {
          // this.peoLoading = true;
          console.log(reject);
      });

      //公告管理
        this.$ajax({
            method: "post",
            url: "http://120.26.186.88:8080/notice/listAllNotice",
            dataType: "json",
            crossDomain: true,
            cache: false,
        }).then(resolve => {
            this.tableData4 = resolve.data;
            //获取数组长度赋值给total
            this.total4 = resolve.data.length;
            console.log(this.tota3);
            // console.log(resolve.data);
        }, reject => {
            console.log(reject);
        });
      
      //个人成绩
      this.$ajax({
          method: "post",
          url: "http://120.26.186.88:8080/score/queryScoreByUser",
          dataType: "json",
          crossDomain: true,
          cache: false,
      }).then(resolve => {
          this.tableData1 = resolve.data;
          //获取数组长度赋值给total
          this.total1 = resolve.data.length;
          // this.peoLoading = false;
          console.log(resolve.data);
      }, reject => {
          // this.peoLoading = true;
          console.log(reject);
      });

      //请求错题
      this.$ajax({
          method: "post",
          url: "http://120.26.186.88:8080/wrong/listWrongById",
          dataType: "json",
          crossDomain: true,
          cache: false,
          transformRequest(obj){
                    var str = [];
                    for(var p in obj){
                        str.push(encodeURIComponent(p) + "=" + encodeURIComponent(obj[p]));
                    }
                    return str.join("&");
                },
      }).then(resolve => {
          this.tableData3 = resolve.data;
          //获取数组长度赋值给total
          this.total3 = resolve.data.length;
          // this.peoLoading = false;
          console.log(resolve.data);
      }, reject => {
          // this.peoLoading = true;
          console.log(reject);
      });
    },
    methods: {
      //删除错题
      /**
       * 删除错题集中的错题
       * @date 2020-06-30
       * @param {number} index
       * @param {number} row
       * @returns 返回删除后的剩余错题列表
       */
      deleteWrongQuestion(index,row){
        this.$ajax({
                method: "post",
                url: "http://120.26.186.88:8080/wrong/deleteWrong",
                data:{
                    wrongIdStr:row.wrongId,
                },
                dataType: "json",
                crossDomain: true,
                cache: false,
                transformRequest(obj){
                    var str = [];
                    for(var p in obj){
                        str.push(encodeURIComponent(p) + "=" + encodeURIComponent(obj[p]));
                    }
                    return str.join("&");
                },
            }).then(resolve => {
               this.$ajax({
                    method: "post",
                    url: "http://120.26.186.88:8080/wrong/listWrongById",
                    dataType: "json",
                    crossDomain: true,
                    cache: false,
                    transformRequest(obj){
                    var str = [];
                    for(var p in obj){
                        str.push(encodeURIComponent(p) + "=" + encodeURIComponent(obj[p]));
                    }
                    return str.join("&");
                },
                }).then(resolve => {
                    this.tableData3 = resolve.data;
                    //获取数组长度赋值给total
                    this.total3 = resolve.data.length;
                    // this.peoLoading = false;
                    console.log(this.total1);
                    // console.log(resolve.data);
                }, reject => {
                    // this.peoLoading = true;
                    console.log(reject);
                });
            }, reject => {
                console.log(reject);
            });
      },

      //开始考试
      /**
       * 在线考试列出试卷题目
       * @date 2020-06-30
       * @param {number} index
       * @param {number} row
       * @returns 返回对应的试题到页面
       */
      beginTest(index, row) {
        this. sureTest = false;
        this.paperID = row.paperId;
        console.log(row.paperId);
        //单选
        this.$ajax({
          method: "post",
          // method: "get",
          // url: "../../../static/testJSONdanxuan.json",
          url: "http://120.26.186.88:8080/connect/listAllConnect",
          dataType: "json",
          data: {
            paperIdStr: row.paperId,
            exerciseTypeStr: 0,
          },
          crossDomain: true,
          cache: false,
          transformRequest(obj){
            var str = [];
            for(var p in obj){
              str.push(encodeURIComponent(p) + "=" + encodeURIComponent(obj[p]));
            }
            return str.join("&");
          },
        }).then(resolve => {
          //题目渲染至页面之中
          // console.log("单选");
          // console.log(resolve);
          var dataLength = resolve.data.length;
          //考试时间没有到
          if(resolve.data[dataLength-1].log != null) {
            console.log(resolve.data[dataLength-1].log);
            this.$alert('考试时间未到或您已过了考试时间！', '注意', {
              confirmButtonText: '确定',
              callback: action => {
                this. sureTest = true;
              }
            });
          }
          else {
            this.testing = true;
            this.duration = resolve.data[dataLength-1].leftover
            console.log(this.duration);
            this.start();
            this.$ajax({
              method: "post",
              // method: "get",
              // url: "../../../static/testJSONdanxuan.json",
              url: "http://120.26.186.88:8080/connect/listAllConnect",
              dataType: "json",
              data: {
                paperIdStr: row.paperId,
                exerciseTypeStr: 0,
              },
              crossDomain: true,
              cache: false,
              transformRequest(obj){
                var str = [];
                for(var p in obj){
                  str.push(encodeURIComponent(p) + "=" + encodeURIComponent(obj[p]));
                }
                return str.join("&");
              },
            }).then(resolve => {
              //题目渲染至页面之中
              // this.question = resolve.data;
              this.questionDanxuan = resolve.data;
              if(this.questionDanxuan != null)
                this.danxuanShow = true;
              console.log(resolve);
              // this.showPaper(pid);
            }, reject => {
              console.log("题目获取失败！");
            });
            
            //判断
              this.$ajax({
              method: "post",
              // method: "get",
              // url: "../../../static/testJSONdanxuan.json",
              url: "http://120.26.186.88:8080/connect/listAllConnect",
              dataType: "json",
              data: {
                paperIdStr: row.paperId,
                exerciseTypeStr: 1,
              },
              crossDomain: true,
              cache: false,
              transformRequest(obj){
                var str = [];
                for(var p in obj){
                  str.push(encodeURIComponent(p) + "=" + encodeURIComponent(obj[p]));
                }
                return str.join("&");
              },
            }).then(resolve => {
              //题目渲染至页面之中
              // this.question = resolve.data;
              this.questionPanduan = resolve.data;
              if(this.questionPanduan != null)
                this.panduanShow = true;
              console.log(resolve);
              // this.showPaper(pid);
            }, reject => {
              console.log("题目获取失败！");
            });
            //填空
            this.$ajax({
              method: "post",
              // method: "get",
              // url: "../../../static/testJSONdanxuan.json",
              url: "http://120.26.186.88:8080/connect/listAllConnect",
              dataType: "json",
              data: {
                paperIdStr: row.paperId,
                exerciseTypeStr: 2,
              },
              crossDomain: true,
              cache: false,
              transformRequest(obj){
                var str = [];
                for(var p in obj){
                  str.push(encodeURIComponent(p) + "=" + encodeURIComponent(obj[p]));
                }
                return str.join("&");
              },
            }).then(resolve => {
              //题目渲染至页面之中
              // this.question = resolve.data;
              this.questionTiankong = resolve.data;
              if(this.questionTiankong != null)
                this.tiankongShow = true;
              console.log(resolve);
              // this.showPaper(pid);
            }, reject => {
              console.log("题目获取失败！");
            });
            //问答
            this.$ajax({
              method: "post",
              // method: "get",
              // url: "../../../static/testJSONdanxuan.json",
              url: "http://120.26.186.88:8080/connect/listAllConnect",
              dataType: "json",
              data: {
                paperIdStr: row.paperId,
                exerciseTypeStr: 3,            
              },
              crossDomain: true,
              cache: false,
              transformRequest(obj){
                var str = [];
                for(var p in obj){
                  str.push(encodeURIComponent(p) + "=" + encodeURIComponent(obj[p]));
                }
                return str.join("&");
              },
            }).then(resolve => {
              //题目渲染至页面之中
              // this.question = resolve.data;
              this.questionWenda = resolve.data;
              if(this.questionWenda != null)
                this.wendaShow = true;
              console.log(resolve);
              // this.showPaper(pid);
            }, reject => {
              console.log("题目获取失败！");
            });

          }
          // this.showPaper(pid);
        }, reject => {
          console.log("题目获取失败！");
        });
      },

      /**
       * 分页
       * @date 2020-06-30
       * @param {number} currentPage
       * @returns no return
       */
      //查看成绩
      current_change1(currentPage) {
        this.currentPage1 = currentPage;
      },
      //考试
      current_change2(currentPage) {
        this.currentPage2 = currentPage;
      },
      //错题集
      current_change3(currentPage) {
        this.currentPage3 = currentPage;
      },
      //公告
      current_change4(currentPage) {
        this.currentPage4 = currentPage;
      },

      //交卷
      /**
       * 点击提交试卷调用的函数
       * @date 2020-06-30
       * @returns 返回该生该卷的最终成绩[改卷由后端完成]，并显示成绩页面供学生查询其考试成绩
       */
      submiteAnwser() {
        clearInterval(this.time);
        this.$alert('请前往“我的成绩”中查询你的成绩', '提交成功！', {
            confirmButtonText: '确定',
            callback: action => {
              this.testing = false;
              this.myScore = true;
              this.$ajax({
                method: "post",
                url: "http://120.26.186.88:8080/score/queryScoreByUser",
                dataType: "json",
                crossDomain: true,
                cache: false,
            }).then(resolve => {
                this.tableData1 = resolve.data;
                //获取数组长度赋值给total
                this.total1 = resolve.data.length;
                // this.peoLoading = false;
                console.log(resolve.data);

                for(var i = 0; i < this.questionDanxuan.length-1; i++) {
                  const objEle = {'paperId': this.questionDanxuan[i].paperId,
                                'paperDetailId': this.questionDanxuan[i].paperDetailId, 
                                'solution': this.questionDanxuan[i].solution};
                  this.solutionList.push(objEle);
                }
                for(var i = 0; i < this.questionPanduan.length-1; i++) {
                  const objEle = {'paperId': this.questionPanduan[i].paperId,
                                'paperDetailId': this.questionPanduan[i].paperDetailId, 
                                'solution': this.questionPanduan[i].solution};
                  this.solutionList.push(objEle);
                }
                for(var i = 0; i < this.questionTiankong.length-1; i++) {
                  const objEle = {'paperId': this.questionTiankong[i].paperId,
                                'paperDetailId': this.questionTiankong[i].paperDetailId, 
                                'solution': this.questionTiankong[i].solution};
                  this.solutionList.push(objEle);
                }
                for(var i = 0; i < this.questionWenda.length-1; i++) {
                  const objEle = {'paperId': this.questionWenda[i].paperId,
                                'paperDetailId': this.questionWenda[i].paperDetailId, 
                                'solution': this.questionWenda[i].solution};
                  this.solutionList.push(objEle);
                }
                // console.log(this.solutionList);
                var list = JSON.stringify(this.solutionList);
                console.log(list);

                this.$ajax({
                  method: "post",
                  url: "http://120.26.186.88:8080/paperDetail/judgeQuestion",
                  contentType : 'application/json',
                  data: {
                    // jsonString: this.solutionList,
                    jsonString: list,
                  },
                  // dataType: "json",
                  crossDomain: true,
                  cache: false,
                  transformRequest(obj){
                    var str = [];
                    for(var p in obj){
                      str.push(encodeURIComponent(p) + "=" + encodeURIComponent(obj[p]));
                    }
                    return str.join("&");
                  },
                }).then(resolve => {
                  console.log("成绩为:");
                  console.log(resolve);
	  this.solutionList = [];
                  //请求成绩数据
                  this.$ajax({
                    method: "post",
                    url: "http://120.26.186.88:8080/score/queryScoreByUser",
                    dataType: "json",
                    crossDomain: true,
                    cache: false,
                }).then(resolve => {
                    this.tableData1 = resolve.data;
                    //获取数组长度赋值给total
                    this.total1 = resolve.data.length;
                    // this.peoLoading = false;
                    console.log(resolve.data);
                }, reject => {
                    // this.peoLoading = true;
                    console.log(reject);
                });

                //请求错题
                this.$ajax({
                  method: "post",
                  url: "http://120.26.186.88:8080/wrong/listWrongById",
                  dataType: "json",
                  crossDomain: true,
                  cache: false,
                  transformRequest(obj){
                    var str = [];
                    for(var p in obj){
                      str.push(encodeURIComponent(p) + "=" + encodeURIComponent(obj[p]));
                    }
                    return str.join("&");
                  },
                }).then(resolve => {
                    this.tableData3 = resolve.data;
                    //获取数组长度赋值给total
                    this.total3 = resolve.data.length;
                    // this.peoLoading = false;
                    console.log(resolve.data);
                }, reject => {
                    // this.peoLoading = true;
                    console.log(reject);
                });
                
                }, reject => {
                  //上传失败
                  console.log("上传失败");
                });
                // console.log(this.solutionList);
              }, reject => {
                // this.peoLoading = true;
                console.log(reject);
              });
            }
        });
      },

      //计时
      /**
       * 计时功能，根据后端提供的考试时长来计时
       * @date 2020-06-30
       * @returns 返回“答题卡”顶部的时间
       */
      timer() {
        //秒针走动
        this.s=this.s+1;
        //秒进位分，秒归零
        if(this.s>=60){
          this.m=this.m+1;
          this.s=0;
        }
        //分进位时，分归零
        if(this.m>=60){
          this.h=this.h+1;
          this.m=0;
        }
        this.str=this.addZero(this.h)+":"+this.addZero(this.m)+":"+this.addZero(this.s);
        // console.log(this.str);

        
        // var dur = 10;
        var hour = "0";
        var min = "0";
        var sec = "0";
        //是整数
        if(this.duration % 60 == 0) {
          var dur = this.duration / 60;
          if(dur % 60 == 0) {
            hour = this.addZero((dur/60));
            min = this.addZero(0);
            sec = this.addZero(0);
          }
          else {
            if((dur / 60) >= 1 && (dur / 60) < 2) {
              hour = this.addZero(parseInt(dur / 60));
              var mid = dur - parseInt(dur / 60)*60;
              min = this.addZero(mid);
              sec = this.addZero(0);
            }
            else if(dur / 60 >= 2) {
              hour = this.addZero(2);
              var mid = dur - 120;
              min = this.addZero(mid);
              sec = this.addZero(0);
            }
            else {
              hour = this.addZero(0);
              min = this.addZero(dur);
              sec = this.addZero(0);
            }
          }
        }
        //不是整数
        else {
          //保留1位小数
          var dur = this.duration / 60;
          var durNoInt, durInt,  durFlo;
          durNoInt = parseFloat(dur).toFixed(1);
          //整数部分
          durInt = parseInt(durNoInt);
          //小数部分
          durFlo = parseFloat(durNoInt - durInt).toFixed(1);
          console.log(durNoInt);
          console.log(durInt+"   :   "+durFlo);
          if((durInt / 60) >= 1 && (durInt / 60) < 2) {
              hour = this.addZero(1);
              var mid = durInt - 60;
              min = this.addZero(mid);
              var secMid = durFlo * 60;
              sec = this.addZero(secMid);
            }
            else if(durInt / 60 >= 2) {
              hour = this.addZero(parseInt(durInt / 60));
              var mid = durInt - parseInt(durInt / 60)*60;
              min = this.addZero(mid);
              var secMid = durFlo * 60;
              sec = this.addZero(secMid);
            }
            else {
              hour = this.addZero(0);
              min = this.addZero(durInt);
              var secMid = durFlo * 60;
              sec = this.addZero(secMid);
            }
        }
        
        console.log(hour+":"+min+":"+sec);
      
        if(this.str == hour+":"+min+":"+sec){
          this.$confirm('请停止答题，前往“我的成绩”中查询你的成绩', '考试时间到！', {
            confirmButtonText: '确定',
            // cancelButtonText: '取消',
            type: 'warning'
          }).then(() => {
            // this.$message({
            //   type: 'success',
            //   message: '删除成功!'
            // });
            //强制交卷
              this.submiteAnwser();
              this.testing = false;
              this.myScore = true;
              this.s = 0;
              this.m = 0;
              this.h = 0;
          }).catch(() => {
            // this.$message({
            //   type: 'info',
            //   message: '已取消删除'
            // });       
            //强制交卷
              this.submiteAnwser();
              this.testing = false;
              this.myScore = true;
              this.s = 0;
              this.m = 0;
              this.h = 0;   
          });
          // this.$alert('请停止答题，前往“我的成绩”中查询你的成绩', '考试时间到！', {
          //   confirmButtonText: '确定',
          //   callback: action => {
          //     //强制交卷
          //     this.submiteAnwser();
          //     this.testing = false;
          //     this.myScore = true;
          //     this.s = 0;
          //     this.m = 0;
          //     this.h = 0;
          //   }
          // });
          clearInterval(this.time);
        }
      },
      
      //补零
      /**
       * 用于显示的时间动画的补零效果
       * @date 2020-06-30
       * @param {number} t
       * @returns 返回补零之后的数值
       */
      addZero(t){
        if(t<10){
          return ("0"+t);
        }
        else{
          return t;
        }
      },

      //开始计时
      /**
       * 动画，使得时间能够在视觉上“动”
       * @date 2020-06-30
       * @returns no return
       */
      start(){
        //1秒=1000毫秒
        this.time=setInterval(this.timer,1000);
      },
    },
    components:{
      HeaderTop,
      ProfileItem
    }
  }
</script>

<style lang="stylus" type="text/stylus" rel="stylesheet/stylus" scoped>
  @import "../../common/stylus/mixins.styl"
  .profile
    width 100%
    overflow hidden
    padding-bottom 56px
    .profile-number
      // margin-top 45.5px
      &:active
        opacity 0.8
      .profile-link
        clearFix()
        position relative
        display block
        background lightslategrey
        padding 20px 10px
        .profile_image
          float right
          width 60px
          height 60px
          border-radius 50%
          overflow hidden
          vertical-align top
          img
            height 100%
            width 100%
          .icon-yonghuming
            background #e4e4e4
            font-size 62px
        .user-info
          float right
          margin-top 23px
          margin-left 15px
          p
            font-weight: 700
            font-size 18px
            color #fff
            &.user-info-top
              padding-bottom 8px
            .icon-msnui-tel
              font-size 14px
              color #fff
        .arrow
          position absolute
          right 15px
          top 40%
          .iconjiantou
            color #fff
            font-size 30px
    .profile-items
      .login_out
        height 50px
        display flex
        justify-content center
        align-items center
        background-color lightslategrey
        margin-top 6px
        color #fff
        //box-shadow 0px 0px 1px rgba(0,0,0,.5)
        &.opacity
          opacity 0.4
          background lightslategrey
     
  #title
    position absolute 
    // border 1px solid red
    z-index 1000
    left 2%
    top 4.5%
    line-height 25px
    text-align center
  #title a {
    color white
    font-weight 300
  }
  #title h1 {
    font-size 20px
  }
  #navigation {
    margin-top 1%
    width 13%
    background-color rgba(255,255,255,0)
  }

  //考试
  #testOrNot {
    width 50%;
    position absolute 
    top 150px
    left 27%
  }
  #testYes
    position absolute 
    width 83%
    top 112px
    left 15%
  #answer
    position absolute 
    width 83%
    top 112px
    left 15%
  // 查看成绩
  #score {
    position absolute 
    width 83%
    top 112px
    left 15%
  }
  #mis{
    position absolute 
    width 83%
    top 112px
    left 15%
  }
  #noti{
    position absolute 
    width 83%
    top 112px
    left 15%
  }
  //头像
  #userHead {
    position absolute
    top 12%
    right 15%;
  }
  .pagination {
      text-align: center;
  }
</style>
