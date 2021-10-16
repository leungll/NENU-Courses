<!--
 * @Author: 吴婷婷、屈英杰
 * @Date: 2020-06-01 13:02:54
 * @LastEditTime: 2020-07-01 19:21:18
 * @LastEditors: Please set LastEditors
 * @Description: 管理员端页面
 * @FilePath: \onlineexamLLL\src\pages\Admin\admin.vue
--> 
<template>
    <div class="profile">
        <!-- header -->
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
                <img :src="require('../../assets/admin.jpg')" alt="学生头像">
                <!--<img src="../../common/imgs/profile.jpg" alt="头像" v-else>-->
                </div>
            </a>
        </section>

        <el-dialog title="个人信息" v-model="userInfor" :visible.sync="personInfor" :close-on-click-modal="false">
            <img id="userHead" src="../../assets/admin.jpg" width="100px" height="100px" style="border-radius: 50px" />
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

        <!-- 侧边栏(导航) -->
        <div id="aside">
            <!-- <el-aside id="el_aside"> -->
                <el-row>
                    <el-col :span="24">
                        <el-menu default-active="1" background-color="#f5f5f5" active-text-color="#4ab8a1">
                            <el-menu-item index="1" @click="allPaper = true; 
                                                            questionShow = false; 
                                                            noticeShow = false;
                                                            allScore = false;
                                                            allUser = false;
                                                            allStudentScore = false">
                                <i class="el-icon-user"></i>
                                <span slot="title">试卷管理</span>
                            </el-menu-item>
                            <el-menu-item index="2" @click="allPaper = false; 
                                                            questionShow = true; 
                                                            noticeShow = false;
                                                            allScore = false;
                                                            allUser = false;
                                                            allStudentScore = false">
                                <i class="el-icon-tickets"></i>
                                <span slot="title">题库管理</span>
                            </el-menu-item>
                            <el-menu-item index="3" @click="allPaper = false; 
                                                            questionShow = false; 
                                                            noticeShow = true;
                                                            allScore = false;
                                                            allUser = false;
                                                            allStudentScore = false">
                                <i class="el-icon-school"></i>
                                <span slot="title">公告管理</span>
                            </el-menu-item>
                            <el-menu-item index="4" @click="allPaper = false; 
                                                            questionShow = false; 
                                                            noticeShow = false;
                                                            allScore = true;
                                                            allStudentScore = false;
                                                            allUser = false">
                                <i class="el-icon-school"></i>
                                <span slot="title">成绩管理</span>
                            </el-menu-item>
                            <el-menu-item index="5" @click="allPaper = false; 
                                                            questionShow = false; 
                                                            noticeShow = false;
                                                            allScore = false;
                                                            allStudentScore = false;
                                                            allUser = true">
                                <i class="el-icon-school"></i>
                                <span slot="title">人员管理</span>
                            </el-menu-item>
                        </el-menu>
                    </el-col>
                </el-row>
            <!-- </el-aside> -->
        </div>

        <!-- List -->
        <el-main id="List">
            <!-- 试卷 -->
            <el-card v-show="allPaper" id="testYes">
                <div slot="header" class="clearfix">
                    <el-row :gutter="10">
                        <el-col :span="8">
                            <el-input v-model="searchPaper" placeholder="请输入需要搜索的试卷名称"></el-input>
                        </el-col>
                        <el-col :span="5">
                            <el-button type="success" plain @click="searchPapers()">搜索</el-button>
                        </el-col>
                    </el-row>
                </div>
                <el-table :data="tableData1.slice((currentPage1-1)*pagesize,currentPage1*pagesize)" style="width: 100%">
                    <el-table-column align="center" type="index" label="序号" width="50"></el-table-column>
                    <!-- <el-table-column align="center" prop="paperId" label="试卷编号"></el-table-column> -->
                    <el-table-column align="center" prop="paperName" label="试卷名称"></el-table-column>    
                </el-table>
                <div class="pagination">
                        <el-pagination background layout="prev, pager, next" :total="total1" @current-change="current_change1" class="paginate"></el-pagination>
                </div>
            </el-card>
            <!-- 题库管理 -->
            <el-card v-show="questionShow">
                <el-table :data="tableData2.slice((currentPage2-1)*pagesize,currentPage2*pagesize)" style="width: 100%" id="peoTable">
                    <el-table-column align="center" type="index" label="序号" width="50"></el-table-column>
                    <!-- <el-table-column align="center" prop="exerciseId" label="题目编号"></el-table-column> -->
                    <el-table-column align="center" prop="content" label="题目"></el-table-column>
                    <el-table-column align="center" prop="exerciseType" label="题型"></el-table-column>
                    <el-table-column align="center" prop="paperDetailId" label="所在试卷编号"></el-table-column>
                    <el-table-column align="center" prop="answer" label="正确答案"></el-table-column>
                    <el-table-column align="center" prop="score" label="分值"></el-table-column>
                </el-table>
                <div class="pagination">
                    <el-pagination background layout="prev, pager, next" :total="total2" @current-change="current_change2" class="paginate"></el-pagination>
                </div>
            </el-card>
            <!-- 公告管理 -->
            <el-card v-show="noticeShow">
                <div slot="header" class="clearfix" style="text-align: right">
                    <el-button type="success" plain @click="addNoticeShow=true">新增公告</el-button>
                </div>
                <el-table :data="tableData3.slice((currentPage3-1)*pagesize,currentPage3*pagesize)" style="width: 100%" id="peoTable">
                    <el-table-column align="center" type="index" label="序号" width="50"></el-table-column>
                    <!-- <el-table-column width="80px" align="center" prop="noticeId" label="公告编号"></el-table-column> -->
                    <el-table-column width="80px" align="center" prop="userId" label="发布者ID"></el-table-column>
                    <el-table-column align="center" prop="title" label="标题"></el-table-column>
                    <el-table-column align="center" prop="content" label="内容"></el-table-column>
                    <el-table-column align="center" prop="createTime" label="发布时间"></el-table-column>
                </el-table>
                <div class="pagination">
                    <el-pagination background layout="prev, pager, next" :total="total3" @current-change="current_change3" class="paginate"></el-pagination>
                </div>
            </el-card>

            <!-- 成绩 -->
            <el-card v-show="allScore">
                <el-table :data="tableData4.slice((currentPage4-1)*pagesize,currentPage4*pagesize)" style="width: 100%">
                    <el-table-column align="center" type="index" label="序号" width="50"></el-table-column>
                    <!-- <el-table-column align="center" prop="paperId" label="试卷编号"></el-table-column> -->
                    <el-table-column align="center" prop="paperName" label="试卷名称"></el-table-column>
                    <el-table-column align="center" prop="operation" label="所有考生成绩" width="120">
                        <template slot-scope="scope">
                            <el-button type="success" 
                                icon="el-icon-search" 
                                title="查看本卷所有考生成绩" 
                                circle 
                                plain
                                @click="showAllScore(scope.$index, scope.row);"></el-button>
                        </template>
                        <!-- <el-button type="danger" icon="el-icon-delete" title="删除" @click="dele" plain>删除</el-button> -->
                    </el-table-column> 
                    <el-table-column align="center" prop="operation" label="不及格考生成绩" width="120">
                        <template slot-scope="scope">
                            <el-button type="success" 
                                icon="el-icon-search" 
                                title="查看本卷不及格考生成绩" 
                                circle 
                                plain
                                @click="searchfailScores(scope.$index, scope.row);"></el-button>
                        </template>
                        <!-- <el-button type="danger" icon="el-icon-delete" title="删除" @click="dele" plain>删除</el-button> -->
                    </el-table-column>
                    <el-table-column align="center" prop="operation" label="及格考生成绩" width="120">
                        <template slot-scope="scope">
                            <el-button type="success" 
                                icon="el-icon-search" 
                                title="查看本卷及格考生成绩" 
                                circle 
                                plain
                                @click="searchScores(scope.$index, scope.row);"></el-button>
                        </template>
                        <!-- <el-button type="danger" icon="el-icon-delete" title="删除" @click="dele" plain>删除</el-button> -->
                    </el-table-column>
                </el-table>
                <div class="pagination">
                    <el-pagination background layout="prev, pager, next" :total="total4" @current-change="current_change4" class="paginate"></el-pagination>
                </div>
            </el-card>

            <!-- 根据试卷列出考生成绩信息 -->
            <el-card v-show="allStudentScore">
                <el-table :data="tableData5.slice((currentPage5-1)*pagesize,currentPage5*pagesize)" style="width: 100%">
                    <el-table-column align="center" type="index" label="序号" width="50"></el-table-column>
                    <el-table-column align="center" prop="userId" label="学生学号"></el-table-column>
                    <el-table-column align="center" prop="username" label="学生姓名"></el-table-column>
                    <el-table-column align="center" prop="mark" label="学生成绩"></el-table-column>    
                </el-table>
                <div class="pagination">
                        <el-pagination background layout="prev, pager, next" :total="total5" @current-change="current_change5" class="paginate"></el-pagination>
                    </div>
            </el-card>
            
            <!-- 列出所有用户信息 -->
            <el-card v-show="allUser">
                <el-table :data="tableData6.slice((currentPage6-1)*pagesize,currentPage6*pagesize)" style="width: 100%">
                    <el-table-column align="center" type="index" label="序号" width="50"></el-table-column>
                    <el-table-column align="center" prop="userId" label="用户ID"></el-table-column>
                    <el-table-column align="center" prop="username" label="用户名"></el-table-column>
                    <el-table-column align="center" prop="birthday" label="生日"></el-table-column>
                    <el-table-column align="center" prop="sex" label="性别"></el-table-column>
                    <el-table-column align="center" prop="power" label="权限"></el-table-column>
                    <el-table-column align="center" prop="operation" label="操作">
                        <template slot-scope="scope">
                            <el-col :span="13">
                                <el-button type="danger" 
                                icon="el-icon-delete" 
                                title="删除" 
                                circle 
                                plain
                                @click="deleteUser(scope.$index, scope.row);"></el-button>
                            </el-col>
                            <el-col :span="8">
                                <el-button type="success" 
                                    icon="el-icon-edit" 
                                    title="修改用户限权" 
                                    circle 
                                    plain
                                    @click="updateUserPower(scope.$index, scope.row);"></el-button>
                            </el-col>
                        </template>
                    </el-table-column>    
                </el-table>
                <div class="pagination">
                        <el-pagination background layout="prev, pager, next" :total="total6" @current-change="current_change6" class="paginate"></el-pagination>
                </div>
            </el-card>
        </el-main>

        <!-- 新增公告 -->
        <el-dialog id="addNotice" :visible="addNoticeShow" @close="addNoticeShow=false;reset('addNoticeInfor')">
            <el-form :model="addNoticeInfor" ref="addNoticeInfor" label-width="150px">
                <el-form-item label="标题：" prop="title">
                    <el-col :span="8">
                        <el-input v-model="addNoticeInfor.title" placeholder="请输入标题" autocomplete="off"></el-input>
                    </el-col>
                </el-form-item>
                <el-form-item label="内容：" prop="content">
                    <el-col :span="20">
                        <el-input 
                            v-model="addNoticeInfor.content" 
                            type="textarea" 
                            placeholder="请编辑公告内容"
                            size="medium">
                        </el-input>
                    </el-col>
                </el-form-item>
                <el-form-item id="slotBtn">
                    <el-button type="success" icon="el-icon-check" @click="addNoticeShow=false; submiaddNotice()">确认发布</el-button>
                    <el-button type="primary" icon="el-icon-refresh-right" @click="reset('addNoticeInfor')">重置</el-button>
                    <el-button type="danger" icon="el-icon-close" @click="addNoticeShow=false; reset('addNoticeInfor')">取消</el-button>
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
    data() {
        return {
            sno:this.$store.state.userInfo.sno,
            isSelect:false,
            personInfor: false,
            //一页表中的数据记录条数
            pagesize: 10,
            //试卷管理
            tableData1: [],
            allPaper: true,
            //分页
            currentPage1: 1,
            total1: 0,
            //查询
            searchPaper: '',

            //题库管理
            tableData2: [],
            questionShow: false,
            //分页
            currentPage2: 1,
            total2: 0,
            
            //公告管理
            tableData3: [],
            noticeShow: false,
            //新增
            addNoticeShow: false,
            addNoticeInfor: [{
                title: '',
                content: '',
            }],
            //分页
            currentPage3: 1,
            total3: 0,

            //成绩管理
            allScore: false,
            tableData4: [],
            //分页
            currentPage4: 1,
            total4: 0,
            allStudentScore: false,
            tableData5: [],
            //分页
            currentPage5: 1,
            total5: 0,

            //用户管理
            allUser: false,
            tableData6: [],
            currentPage6: 1,
            total6: 0,
            //用户信息
            userInfor: [],
            userPower: "",

        }
    },
    components:{
      HeaderTop,
      ProfileItem
    },
    computed:{
      ...mapState(['userInfo']),
      ...mapGetters(['unreadMsgCount'])
    },
    methods: {
        /**
         * 重置
         * @date 2020-06-30
         * @param {object} refname
         * @returns no reuturns
         */
        reset(refname) {
            this.$refs[refname].resetFields()
        },

        /**
         * 页面分页
         * @date 2020-06-30
         * @param {number} currentPage
         * @returns {any} no return
         */
        current_change1(currentPage) {
            this.currentPage1 = currentPage;
        },
        current_change2(currentPage) {
            this.currentPage2 = currentPage;
        },
        current_change3(currentPage) {
            this.currentPage3 = currentPage;
        },
        current_change4(currentPage) {
            this.currentPage4 = currentPage;
        },
        current_change5(currentPage) {
            this.currentPage5 = currentPage;
        },
        current_change6(currentPage) {
            this.currentPage6 = currentPage;
        },

        //搜索试卷
        /**
         * 对列出的所有试卷进行搜索，利用axios
         * @date 2020-06-30
         * @returns 后端返回的搜索结果[list]
         */
        searchPapers() {
            this.$ajax({
                method: "post",
                url: "http://120.26.186.88:8080/paper/queryPaperName",
                data: {
                    keyStr: this.searchPaper,
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
                this.tableData1 = resolve.data;
                //获取数组长度赋值给total
                this.total1 = resolve.data.length;
                // console.log(resolve.data);
            }, reject => {
                    // this.peoLoading = true;
                    console.log(reject);
            });
        },

        //提交新增公告
        /**
         * 管理员添加公告
         * @date 2020-06-30
         * @returns 返回新增后的所以公告列表[list]
         */
        submiaddNotice() {
            this.$ajax({
                method: "post",
                url: "http://120.26.186.88:8080/notice/addNotice",
                dataType: "json",
                data: {
                    title: this.addNoticeInfor.title,
                    content: this.addNoticeInfor.content,
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
                this.$ajax({
                    method: "post",
                    url: "http://120.26.186.88:8080/notice/listAllNotice",
                    dataType: "json",
                    crossDomain: true,
                    cache: false,
                }).then(resolve => {
                    this.tableData3 = resolve.data;
                    //获取数组长度赋值给total
                    this.total3 = resolve.data.length;
                    console.log(this.tota3);
                    // console.log(resolve.data);
                }, reject => {
                    console.log(reject);
                });
            }, reject => {
                console.log("failed request!");
            });
        },

        //查看试卷对应的所有考生成绩
        /**
         * 查看试卷对应的所有考生成绩
         * @date 2020-06-30
         * @param {number} index
         * @param {number} row
         * @returns 返回对应的所有成绩列表
         */
        showAllScore(index, row) {
            this.allStudentScore = true;
            this.allScore = false;
            console.log(row.paperId);
            this.$ajax({
                method: "post",
                url: "http://120.26.186.88:8080/score/queryScoreByPaper",
                data: {
                    paperIdStr: row.paperId,
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
                this.tableData5 = resolve.data;
                //获取数组长度赋值给total
                this.total5 = resolve.data.length;
                // console.log(resolve.data);
            }, reject => {
                    // this.peoLoading = true;
                    console.log(reject);
            });
        },

        //查看不及格成绩信息
        /**
         * 查看不及格成绩信息
         * @date 2020-06-30
         * @param {number} index
         * @param {number} row
         * @returns 返回对应的成绩列表
         */
        searchfailScores(index,row){
            this.allStudentScore = true;
            this.allScore = false;
            console.log(row.paperId);
            this.$ajax({
                method: "post",
                url: "http://120.26.186.88:8080/score/listScoreByMark2",
                data: {
                    paperIdStr: row.paperId,
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
                this.tableData5 = resolve.data;
                //获取数组长度赋值给total
                this.total5 = resolve.data.length;
                // console.log(resolve.data);
            }, reject => {
                    // this.peoLoading = true;
                    console.log(reject);
            });
        },

        //查看及格成绩信息
        /**
         * 查看及格成绩信息
         * @date 2020-06-30
         * @param {number} index
         * @param {number} row
         * @returns 返回对应的成绩列表
         */
        searchScores(index,row){
            this.allStudentScore = true;
            this.allScore = false;
            console.log(row.paperId);
            this.$ajax({
                method: "post",
                url: "http://120.26.186.88:8080/score/listScoreByMark1",
                data: {
                    paperIdStr: row.paperId,
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
                this.tableData5 = resolve.data;
                //获取数组长度赋值给total
                this.total5 = resolve.data.length;
                // console.log(resolve.data);
            }, reject => {
                    // this.peoLoading = true;
                    console.log(reject);
            });
        },

        //删除用户
        /**
         * 删除对应用户
         * @date 2020-06-30
         * @param {number} index
         * @param {number} row
         * @returns 删除后所有用户列表
         */
        deleteUser(index, row) {
            this.$ajax({
                method: "post",
                url: "http://120.26.186.88:8080/superUser/deleteUser",
                data: {
                    userIdStr: row.userId,
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
                    url: "http://120.26.186.88:8080/user/listAllUser",
                    dataType: "json",
                    crossDomain: true,
                    cache: false,
                }).then(resolve => {
                    this.tableData6 = resolve.data;
                    //获取数组长度赋值给total
                    this.total6 = resolve.data.length;
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

        //修改用户权限
        /**
         * 修改对应用户权限
         * @date 2020-06-30
         * @param {number} index
         * @param {number} row
         * @returns 修改权限后的用户列表
         */
        updateUserPower(index, row) {
            this.$ajax({
                method: "post",
                url: "http://120.26.186.88:8080/superUser/updateUserPower",
                data: {
                    userIdStr: row.userId,
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
                    url: "http://120.26.186.88:8080/user/listAllUser",
                    dataType: "json",
                    crossDomain: true,
                    cache: false,
                }).then(resolve => {
                    this.tableData6 = resolve.data;
                    //获取数组长度赋值给total
                    this.total6 = resolve.data.length;
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
        }
    },

    created() {
        //获取用户信息
        this.$ajax({
          method: "post",
          url: "http://120.26.186.88:8080/user/listUserById",
          dataType: "json",
          crossDomain: true,
          cache: false,
        }).then(resolve => {
            console.log(resolve);
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
        //试卷管理
        this.$ajax({
            method: "post",
            url: "http://120.26.186.88:8080/paper/listAllPaper",
            dataType: "json",
            crossDomain: true,
            cache: false,
        }).then(resolve => {
            this.tableData1 = resolve.data;
            //获取数组长度赋值给total
            this.total1 = resolve.data.length;
            // this.peoLoading = false;
            console.log(this.total1);
            // console.log(resolve.data);
        }, reject => {
            // this.peoLoading = true;
            console.log(reject);
        });
        //题库管理
        this.$ajax({
            method: "post",
            url: "http://120.26.186.88:8080/paperDetail/listAllPaperDetail",
            dataType: "json",
            crossDomain: true,
            cache: false,
        }).then(resolve => {
            this.tableData2 = resolve.data;
            //获取数组长度赋值给total
            this.total2 = resolve.data.length;
            // this.peoLoading = false;
            console.log(this.total2);
            // console.log(resolve.data);
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
            this.tableData3 = resolve.data;
            //获取数组长度赋值给total
            this.total3 = resolve.data.length;
            console.log(this.tota3);
            // console.log(resolve.data);
        }, reject => {
            console.log(reject);
        });
        //成绩管理
        this.$ajax({
            method: "post",
            url: "http://120.26.186.88:8080/paper/listAllPaper",
            dataType: "json",
            crossDomain: true,
            cache: false,
        }).then(resolve => {
            this.tableData4 = resolve.data;
            //获取数组长度赋值给total
            this.total4 = resolve.data.length;
            // this.peoLoading = false;
            console.log(this.total4);
            // console.log(resolve.data);
        }, reject => {
            // this.peoLoading = true;
            console.log(reject);
        });
        //用户管理
        this.$ajax({
            method: "post",
            url: "http://120.26.186.88:8080/user/listAllUser",
            dataType: "json",
            crossDomain: true,
            cache: false,
        }).then(resolve => {
            this.tableData6 = resolve.data;
            //获取数组长度赋值给total
            this.total6 = resolve.data.length;
            // this.peoLoading = false;
            console.log(this.total1);
            // console.log(resolve.data);
        }, reject => {
            // this.peoLoading = true;
            console.log(reject);
        });
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
  /* header */
    #header {
        /* border: 1px solid #879b6f; */
        padding: 0;
    }
    #header_inner {
        text-align: center;
        background-color: #879b6f;
        padding: 0.6%;
    }
    #header_inner_text h1 {
        font-size: 24px;
        color: white;
    }
    #header_inner_text span {
        font-size: 15px;
    }
    #header_inner_text {
        width: 18%;
        line-height: 75%;
        /* border: 1px solid red; */
    }
    #header_inner_text a {
        color: white;
        text-decoration: none;
    }
    //头像
    #userHead {
        position absolute
        top 12%
        right 15%;
    }
    /* 侧边栏 */
    #aside {
        width: 13%;
        /* border: 1px solid; */
        margin-top: 1%;
    }

    /* 各个List */
    #List {
        width: 83%;
        position: absolute;
        top 112px
        left 15%
    }

    /* 分页 */
    .pagination {
        text-align: center;
    }
    /* 背景颜色 */
    /* .el-pagination .el-pager li {
        background-color: #879b6f;
    } */
</style>
