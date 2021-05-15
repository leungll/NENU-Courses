<!--
 * @Author: 吴婷婷、屈英杰
 * @Date: 2020-06-01 13:02:54
 * @LastEditTime: 2020-07-05 00:59:07
 * @LastEditors: Please set LastEditors
 * @Description: 教师端页面
 * @FilePath: \onlineexamLLL\src\pages\Teacher\Teacher.vue
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
                <img :src="require('../../assets/Teacher.jpg')" alt="学生头像">
                <!--<img src="../../common/imgs/profile.jpg" alt="头像" v-else>-->
                </div>
            </a>
        </section>

        <el-dialog title="个人信息" v-model="userInfor" :visible.sync="personInfor" :close-on-click-modal="false">
            <img id="userHead" src="../../assets/Teacher.jpg" width="100px" height="100px" style="border-radius: 50px" />
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
                                                        allStudentScore = false">
                            <i class="el-icon-user"></i>
                            <span slot="title">试卷管理</span>
                        </el-menu-item>
                        <el-menu-item index="2" @click="allPaper = false; 
                                                        questionShow = true; 
                                                        noticeShow = false;
                                                        allScore = false;
                                                        allStudentScore = false">
                            <i class="el-icon-tickets"></i>
                            <span slot="title">题库管理</span>
                        </el-menu-item>
                        <el-menu-item index="3" @click="allPaper = false; 
                                                        questionShow = false; 
                                                        noticeShow = true;
                                                        allScore = false;
                                                        allStudentScore = false">
                            <i class="el-icon-school"></i>
                            <span slot="title">公告管理</span>
                        </el-menu-item>
                        <el-menu-item index="4" @click="allPaper = false; 
                                                        questionShow = false; 
                                                        noticeShow = false;
                                                        allScore = true;
                                                        allStudentScore = false">
                            <i class="el-icon-school"></i>
                            <span slot="title">成绩管理</span>
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
                        <el-col :span="9" style="text-align:right">
                            <el-button type="success" plain @click="addPaperShow=true">新增试卷 </el-button>
                        </el-col>
                    </el-row>
                </div>
                <el-table :data="tableData1.slice((currentPage1-1)*pagesize,currentPage1*pagesize)" style="width: 100%">
                    <el-table-column align="center" type="index" label="序号"></el-table-column>
                    <!-- 不显示ID -->
                    <!-- <el-table-column align="center" prop="paperId" label="试卷编号"></el-table-column> -->
                    <el-table-column align="center" prop="paperName" label="试卷名称"></el-table-column>
                    <el-table-column align="center" prop="operation" label="操作">
                        <template slot-scope="scope">
                            <el-col :span="11" style="text-align: right">
                                <el-button type="success" 
                                    icon="el-icon-edit" 
                                    title="修改试卷名称" 
                                    circle 
                                    plain
                                    @click="changePaperName(scope.$index, scope.row);"></el-button>
                            </el-col>
                            <el-col :span="5">
                                <el-button type="danger" 
                                icon="el-icon-delete" 
                                title="删除" 
                                circle 
                                plain
                                @click="deletePaperName(scope.$index, scope.row);"></el-button>
                            </el-col>
                        </template>
                        <!-- <el-button type="danger" icon="el-icon-delete" title="删除" @click="dele" plain>删除</el-button> -->
                    </el-table-column>
                </el-table>
                <div class="pagination">
                    <el-pagination background layout="prev, pager, next" :total="total1" @current-change="current_change1" class="paginate"></el-pagination>
                </div>
            </el-card>

            <!-- 题库管理 -->
            <el-card v-show="questionShow">
                <div slot="header" class="clearfix">
                    <el-row :gutter="10">
                        <el-col :span="8">
                            <el-input v-model="searchQuestion" placeholder="请输入需要搜索的试卷名称"></el-input>
                        </el-col>
                        <el-col :span="5">
                            <el-button type="success" plain @click="searchQuestionBtn()">搜索</el-button>
                        </el-col>
                        <el-col :span="9" style="text-align:right">
                            <el-button type="success" plain @click="addQuestionShow=true">新增题目</el-button>
                        </el-col>
                    </el-row>
                </div>
                <el-table :data="tableData2.slice((currentPage2-1)*pagesize,currentPage2*pagesize)" style="width: 100%" class="peoTable">
                    <el-table-column align="center" prop="operation" label="操作">
                        <template slot-scope="scope">    
                            <el-button type="danger" 
                                icon="el-icon-delete" 
                                title="删除" 
                                circle 
                                plain
                                @click="deleteQuestion(scope.$index, scope.row);"></el-button>
                        </template>
                    </el-table-column>
                    <el-table-column align="center" type="index" label="序号" width="50"></el-table-column>
                    <!-- 不显示ID -->
                    <!-- <el-table-column align="center" prop="paperDetailId" label="题目编号"></el-table-column> -->
                    <el-table-column align="center" prop="exerciseType" label="类型" width="70"></el-table-column>
                    <el-table-column align="center" prop="content" label="内容" width="300"></el-table-column>
                    <el-table-column align="center" prop="typeA" label="选项A" width="105"></el-table-column>
                    <el-table-column align="center" prop="typeB" label="选项B" width="105"></el-table-column>
                    <el-table-column align="center" prop="typeC" label="选项C" width="105"></el-table-column>
                    <el-table-column align="center" prop="typeD" label="选项D" width="105"></el-table-column>
                    <el-table-column align="center" prop="answer" label="答案/采分点1" width="105"></el-table-column>
                    <el-table-column align="center" prop="answer2" label="采分点2" width="105"></el-table-column>
                    <el-table-column align="center" prop="answer3" label="采分点3" width="105"></el-table-column>
                    <el-table-column align="center" prop="score" label="分值" width="50"></el-table-column>
                </el-table>
                <div class="pagination">
                    <el-pagination background layout="prev, pager, next" :total="total2" @current-change="current_change2" class="paginate"></el-pagination>
                </div>
            </el-card>

            <!-- addQuestion -->
            <el-dialog :visible.sync="addQuestionShow" title="输入题目内容" center>
                <el-form :model="handQuestionInput" ref="handQuestionInput">
                    <el-form-item label="题目类型" prop="questionType">
                        <el-select v-model="handQuestionInput.questionType">
                            <el-option label="单选题" value="0"></el-option>
                            <el-option label="判断题" value="1"></el-option>
                            <el-option label="填空题" value="2"></el-option>
                            <el-option label="主观问答题" value="3"></el-option>
                        </el-select>
                    </el-form-item>
                    <el-form-item label="题目内容" prop="questionContext">
                        <el-input type="textarea" placeholder="请输入题目内容" v-model="handQuestionInput.questionContext"></el-input>
                    </el-form-item>
                    <el-form-item label="选项A" prop="choiceA">
                        <el-col :span="10">
                            <el-input v-model="handQuestionInput.choiceA" placeholder="请输入A选项"></el-input>
                        </el-col>
                    </el-form-item>
                    <el-form-item label="选项B" prop="choiceB">
                        <el-col :span="10">
                            <el-input v-model="handQuestionInput.choiceB" placeholder="请输入B选项"></el-input>
                        </el-col>
                    </el-form-item>
                    <el-form-item label="选项C" prop="choiceC">
                        <el-col :span="10">
                            <el-input v-model="handQuestionInput.choiceC" placeholder="请输入C选项"></el-input>
                        </el-col>
                    </el-form-item>
                    <el-form-item label="选项D" prop="choiceD">
                        <el-col :span="10">
                            <el-input v-model="handQuestionInput.choiceD" placeholder="请输入D选项"></el-input>
                        </el-col>
                    </el-form-item>
                    <el-form-item label="客观题正确答案" prop="questionAnswerKeguan">
                        <el-col :span="7">
                            <el-input v-model="handQuestionInput.questionAnswerKeguan" placeholder="请输入正确答案"></el-input>
                        </el-col>
                    </el-form-item>
                    <el-form-item label="主观题采分点" prop="questionAnswerZhuguan1">
                        <el-col :span="7">
                            <el-input v-model="handQuestionInput.questionAnswerZhuguan1" placeholder="采分点1"></el-input>
                        </el-col>
                    </el-form-item>
                    <el-form-item label="主观题采分点" prop="questionAnswerZhuguan2">
                        <el-col :span="7">
                            <el-input v-model="handQuestionInput.questionAnswerZhuguan2" placeholder="采分点2"></el-input>
                        </el-col>
                    </el-form-item>
                    <el-form-item label="主观题采分点" prop="questionAnswerZhuguan3">
                        <el-col :span="7">
                            <el-input v-model="handQuestionInput.questionAnswerZhuguan3" placeholder="采分点3"></el-input>
                        </el-col>
                    </el-form-item>
                    <el-form-item prop="questionCount">
                        <span>分值</span>
                        <el-slider v-model="handQuestionInput.questionCount" :max="100"></el-slider>
                    </el-form-item>
                    <el-form-item>
                        <el-col :span="24" style="text-align:right">
                            <el-button type="success" icon="el-icon-check" @click="addQuestionShow=false; addQuestion()">确认添加</el-button>
                            <el-button type="primary" icon="el-icon-refresh-right" @click="reset('handQuestionInput')">重置</el-button>
                            <el-button type="danger" icon="el-icon-close" @click="addQuestionShow=false; reset('handQuestionInput')">取消</el-button>
                        </el-col>
                    </el-form-item>
                </el-form>
            </el-dialog>

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

            <!-- 题库选题 用表格列出来所有的题目 进行选择-->
            <el-card v-show="selectQuestion" title="选择题目">
                <el-table :data="tableData7.slice((currentPage7-1)*pagesize,currentPage7*pagesize)" style="width: 100%" class="peoTable">
                    <el-table-column align="center" prop="operation" label="操作">
                        <template slot-scope="scope">    
                            <el-button type="primary" 
                                icon="el-icon-plus" 
                                title="添加"  
                                plain
                                @click="sureAddQuestion(scope.$index, scope.row);"></el-button>
                        </template>
                    </el-table-column>
                    <el-table-column align="center" type="index" label="序号" width="50"></el-table-column>
                    <!-- 不显示ID -->
                    <!-- <el-table-column align="center" prop="paperDetailId" label="ID" width="45"></el-table-column> -->
                    <el-table-column align="center" prop="exerciseType" label="类型" width="50"></el-table-column>
                    <el-table-column align="center" prop="content" label="内容" width="300"></el-table-column>
                    <el-table-column align="center" prop="typeA" label="选项A"></el-table-column>
                    <el-table-column align="center" prop="typeB" label="选项B"></el-table-column>
                    <el-table-column align="center" prop="typeC" label="选项C"></el-table-column>
                    <el-table-column align="center" prop="typeD" label="选项D"></el-table-column>
                    <el-table-column align="center" prop="answer" label="答案/采分点1"></el-table-column>
                    <el-table-column align="center" prop="answer2" label="采分点2"></el-table-column>
                    <el-table-column align="center" prop="answer3" label="采分点3"></el-table-column>
                    <el-table-column align="center" prop="score" label="分值"></el-table-column>
                </el-table>
                <div class="pagination">
                    <el-pagination background layout="prev, pager, next" :total="total7" @current-change="current_change7" class="paginate"></el-pagination>
                </div>
                <div style="text-align: right">
                    <el-button type="primary" @click="selectQuestion=false;
                                                        allPaper = true;
                                                        selectShow=true;">添加完成</el-button>
                </div>
            </el-card>

        </el-main>

    
       <!-- 新增试卷 -->
        <el-dialog id="addPaper" title="请选择出题方式" :visible.sync="addPaperShow" width="20%" center>
            <div>
                <el-row>
                    <el-col :span="24" style="text-align:center">
                        <el-button type="info" plain icon="el-icon-thumb" @click="handInputName=true;
                                addPaperShow=false">手动录入</el-button>
                    </el-col>
                </el-row>
                <el-row style="top:10px">
                    <el-col :span="24" style="text-align:center">
                    <el-button type="info" plain icon="el-icon-check" @click="selectInputName=true;
                            addPaperShow=false">题库选题</el-button>
                    </el-col>
                </el-row>
            </div>
            <span slot="footer" class="dialog-footer"></span>
        </el-dialog>

        <!-- 手动录入 -->
            <!-- 输入试卷名 -->
        <el-dialog class="nameInput" :visible.sync="handInputName">
            <el-form :model="handPaperName" ref="handPaperName" label-width="150px">
                <el-form-item label="试卷名称：" prop="paperNameHand">
                    <el-col :span="17">
                        <el-input v-model="handPaperName.paperNameHand" placeholder="请输入试卷名称"></el-input>
                    </el-col>
                </el-form-item>
                <el-form-item>
                    <el-button type="success" icon="el-icon-check" @click="handInputName=false;handInputShow=true;subPaperName1();">确认增加</el-button>
                    <el-button type="primary" icon="el-icon-refresh-right" @click="reset('handPaperName')">重置</el-button>
                    <el-button type="danger" icon="el-icon-close" @click="handInputName=false; addPaperShow=true; reset('handPaperName')">取消</el-button>
                </el-form-item>
            </el-form>
        </el-dialog>
            <!-- 显示试卷 -->
        <el-dialog :visible.sync="handInputShow" width="60%">
            <el-row>
                <el-col :span="24" style="text-align:center">
                    <!-- <span>hhhhhhh</span> -->
                    <span>{{this.handPaperName.paperNameHand}}</span>
                </el-col>
            </el-row>
            <el-row>
                <el-col :span="24" style="text-align:right">
                    <el-button type="success" class="inputQue" @click="handQuestion=true">录入题目</el-button>
                </el-col>
            </el-row>
            <!-- 单选 -->
            <div v-for="item in questionDanxuan" :key="item.id">
                 <p style="margin-top: 10px; margin-down: 5px;">
                     <!-- <span>{{item.index}}. </span> -->
                     <span>{{item.content}}</span>
                </p>
                <el-radio-group 
                    v-model="item.id"
                    @change="handleRadioChange(item.index,item.paperDetailId)">
                    <el-radio label="A">A.{{item.typeA}}</el-radio>
                    <el-radio label="B">B.{{item.typeB}}</el-radio>
                    <el-radio label="C">C.{{item.typeC}}</el-radio>
                    <el-radio label="D">D.{{item.typeD}}</el-radio>
                </el-radio-group>
            </div>
            <!-- 判断 -->
            <div v-for="item in questionPanduan" :key="item.id">
                <p style="margin-top: 10px; margin-down: 5px;">
                     <!-- <span>{{item.index}}. </span> -->
                     <span>{{item.content}}</span>
                </p>
                <el-radio-group 
                    v-model="item.id"
                    @change="handleRadioChange(item.index,item.paperDetailId)">
                    <el-radio label="A">A.{{item.typeA}}</el-radio>
                    <el-radio label="B">B.{{item.typeB}}</el-radio>
                </el-radio-group>
            </div>
            <!-- 填空 -->
            <div v-for="item in questionTiankong" v-bind:key="item.id">
                <p style="margin-top: 10px; margin-down: 5px;">
                     <!-- <span>{{item.index}}. </span> -->
                     <span>{{item.content}}</span>
                </p>
                <el-input type="text" placeholder="请输入答案" v-model="answerTiankong"></el-input>
            </div>
            <!-- 问答 -->
            <div v-for="item in questionWenda" v-bind:key="item.id">
                <p style="margin-top: 10px; margin-down: 5px;">
                     <!-- <span>{{item.index}}. </span> -->
                     <span>{{item.content}}</span>
                </p>
                <el-input type="textarea" placeholder="请输入答案" v-model="answerWenda"></el-input>
            </div>
            <span slot="footer">
                <el-button type="primary" @click="outputPaper=true; handInputShow=false">发布试卷</el-button>
            </span>
        </el-dialog>
        <!-- 设定考试时长 -->
        <el-dialog :visible.sync="outputPaper" width="50%">
            <el-form :model="outputTime" ref="outputTime">
                <el-form-item label="试卷有效时间[起始]:">
                    <el-col :span="6" style="text-align: center;">
                        <el-date-picker type="date" placeholder="选择日期" 
                                        value-format="yyyy年MM月dd日"
                                        v-model="outputTime.beginDate" 
                                        style="width: 100%;"></el-date-picker>
                    </el-col>
                    <el-col class="line" :span="2" style="text-align: center;">-</el-col>
                    <el-col :span="6">
                        <el-time-picker placeholder="选择时间" 
                                        value-format="hh时mm分ss秒"
                                        v-model="outputTime.beginTime" 
                                        style="width: 100%;"></el-time-picker>
                    </el-col>
                </el-form-item>
                <el-form-item label="试卷有效时间[截至]:">
                    <el-col :span="6" style="text-align: center;">
                        <el-date-picker type="date" placeholder="选择日期" 
                                        value-format="yyyy年MM月dd日"
                                        v-model="outputTime.endDate" 
                                        style="width: 100%;"></el-date-picker>
                    </el-col>
                    <el-col class="line" :span="2" style="text-align: center;">-</el-col>
                    <el-col :span="6">
                        <el-time-picker placeholder="选择时间" 
                                    value-format="hh时mm分ss秒"
                                    v-model="outputTime.endTime" 
                                    style="width: 100%;"></el-time-picker>
                    </el-col>
                </el-form-item>
                <el-form-item label="考试时长" prop="duration" :rules="[{ required: true, message: '考试时长不能为空'}]">
                    <el-col :span="6">
                        <el-input type="number" v-model="outputTime.duration" placeholder="输入时长" ></el-input>
                    </el-col>
                    <el-col :span="2" style="text-align: center;">
                        <span>分钟</span>
                    </el-col>
                </el-form-item>
                <el-form-item>
                    <el-col :span="24" style="text-align:right">
                        <el-button type="success" icon="el-icon-check" @click="sureSubmit()">确认发布</el-button>
                        <el-button type="danger" icon="el-icon-close" @click="outputPaper=false">取消</el-button>
                    </el-col>
                </el-form-item>
            </el-form>
        </el-dialog>
            <!-- 手动输入题目 -->
        <el-dialog :visible.sync="handQuestion" title="输入题目内容" center>
            <el-form :model="handQuestionInput" ref="handQuestionInput">
                <el-form-item label="题目类型" prop="questionType">
                    <el-select v-model="handQuestionInput.questionType">
                        <el-option label="单选题" value="0"></el-option>
                        <el-option label="判断题" value="1"></el-option>
                        <el-option label="填空题" value="2"></el-option>
                        <el-option label="主观问答题" value="3"></el-option>
                    </el-select>
                </el-form-item>
                <el-form-item label="题目内容" prop="questionContext">
                    <el-input type="textarea" placeholder="请输入题目内容" v-model="handQuestionInput.questionContext"></el-input>
                </el-form-item>
                <el-form-item label="选项A" prop="choiceA">
                    <el-col :span="10">
                        <el-input v-model="handQuestionInput.choiceA" placeholder="请输入A选项"></el-input>
                    </el-col>
                </el-form-item>
                <el-form-item label="选项B" prop="choiceB">
                    <el-col :span="10">
                        <el-input v-model="handQuestionInput.choiceB" placeholder="请输入B选项"></el-input>
                    </el-col>
                </el-form-item>
                <el-form-item label="选项C" prop="choiceC">
                    <el-col :span="10">
                        <el-input v-model="handQuestionInput.choiceC" placeholder="请输入C选项"></el-input>
                    </el-col>
                </el-form-item>
                <el-form-item label="选项D" prop="choiceD">
                    <el-col :span="10">
                        <el-input v-model="handQuestionInput.choiceD" placeholder="请输入D选项"></el-input>
                    </el-col>
                </el-form-item>
                <el-form-item label="客观题正确答案" prop="questionAnswerKeguan">
                    <el-col :span="7">
                        <el-input v-model="handQuestionInput.questionAnswerKeguan" placeholder="请输入正确答案"></el-input>
                    </el-col>
                </el-form-item>
                <el-form-item label="主观题采分点" prop="questionAnswerZhuguan1">
                    <el-col :span="7">
                        <el-input v-model="handQuestionInput.questionAnswerZhuguan1" placeholder="采分点1"></el-input>
                    </el-col>
                </el-form-item>
                <el-form-item label="主观题采分点" prop="questionAnswerZhuguan2">
                    <el-col :span="7">
                        <el-input v-model="handQuestionInput.questionAnswerZhuguan2" placeholder="采分点2"></el-input>
                    </el-col>
                </el-form-item>
                <el-form-item label="主观题采分点" prop="questionAnswerZhuguan3">
                    <el-col :span="7">
                        <el-input v-model="handQuestionInput.questionAnswerZhuguan3" placeholder="采分点3"></el-input>
                    </el-col>
                </el-form-item>
                <el-form-item prop="questionCount">
                    <span>分值</span>
                    <el-slider v-model="handQuestionInput.questionCount" :max="100"></el-slider>
                </el-form-item>
                <el-form-item>
                    <el-col :span="24" style="text-align:right">
                        <el-button type="success" icon="el-icon-check" @click="handQuestion=false; submihandQuestion()">确认录入</el-button>
                        <el-button type="primary" icon="el-icon-refresh-right" @click="reset('handQuestionInput')">重置</el-button>
                        <el-button type="danger" icon="el-icon-close" @click="handQuestion=false; reset('handQuestionInput')">取消</el-button>
                    </el-col>
                </el-form-item>
            </el-form>
        </el-dialog>


        <!-- 题库选题 -->
        <el-dialog id="selectInput" :visible.sync="selectInputName">
            <el-form :model="selectPaperName" ref="selectPaperName" label-width="150px">
                <el-form-item label="试卷名称：" prop="paperNameSelect">
                    <el-col :span="17">
                        <el-input v-model="selectPaperName.paperNameSelect" placeholder="请输入试卷名称"></el-input>
                    </el-col>
                </el-form-item>
                <el-form-item>
                    <el-button type="success" icon="el-icon-check" @click="selectInputName=false;selectShow=true;subPaperName2()">确认增加</el-button>
                    <el-button type="primary" icon="el-icon-refresh-right" @click="reset('selectPaperName')">重置</el-button>
                    <el-button type="danger" icon="el-icon-close" @click="selectInputName=false; addPaperShow=true; reset('selectPaperName')">取消</el-button>
                </el-form-item>
            </el-form>
        </el-dialog>
        <!-- 显示试卷 -->
        <el-dialog :visible.sync="selectShow" width="60%">
            <el-row>
                <el-col :span="24" style="text-align:center">
                    <!-- <span>hhhhhhh</span> -->
                    <span>{{this.selectPaperName.paperNameSelect}}</span>
                </el-col>
            </el-row>
            <el-row>
                <el-col :span="24" style="text-align:right">
                    <el-button type="success" class="inputQue" @click="selectQuestion=true; 
                                                                        selectShow=false;
                                                                        allPaper=false;
                                                                        getAllQuestion()">题库选题</el-button>
                </el-col>
            </el-row>
            <!-- 单选 -->
            <div v-for="item in questionDanxuan" :key="item.id" class="showPaper">
                <p style="margin-top: 10px; margin-down: 5px;">
                    <!-- <span>{{item.id}}. </span> -->
                    <span>{{item.content}}</span>
                </p>
                <el-radio-group 
                    v-model="item.id"
                    @change="handleRadioChange(item.index,item.paperDetailId)">
                    <el-radio label="A">A.{{item.typeA}}</el-radio>
                    <el-radio label="B">B.{{item.typeB}}</el-radio>
                    <el-radio label="C">C.{{item.typeC}}</el-radio>
                    <el-radio label="D">D.{{item.typeD}}</el-radio>
                </el-radio-group>
            </div>
            <!-- 判断 -->
            <div v-for="item in questionPanduan" :key="item.id" class="showPaper">
                <p style="margin-top: 10px; margin-down: 5px;">
                    <!-- <span>{{item.id}}. </span> -->
                    <span>{{item.content}}</span>
                </p>
                <el-radio-group 
                    v-model="item.id"
                    @change="handleRadioChange(item.index,item.paperDetailId)">
                    <el-radio label="A">A.{{item.typeA}}</el-radio>
                    <el-radio label="B">B.{{item.typeB}}</el-radio>
                </el-radio-group>
            </div>
            <!-- 填空 -->
            <div v-for="item in questionTiankong" v-bind:key="item.id">
                <p style="margin-top: 10px; margin-down: 5px;">
                    <!-- <span>{{item.id}}. </span> -->
                    <span>{{item.content}}</span>
                </p>
                <el-input type="text" placeholder="请输入答案" v-model="answerTiankong"></el-input>
            </div>
            <!-- 问答 -->
            <div v-for="item in questionWenda" v-bind:key="item.id" class="showPaper">
                <p style="margin-top: 10px; margin-down: 5px;">
                    <!-- <span>{{item.id}}. </span> -->
                    <span>{{item.content}}</span>
                </p>
                <el-input type="textarea" placeholder="请输入答案" v-model="answerWenda"></el-input>
            </div>
            <span slot="footer">
                <el-button type="primary" @click="outputPaper=true; selectShow=false; handInputShow=false">发布试卷</el-button>
            </span>
        </el-dialog>
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
            //新增试卷
            addPaperShow: false,
            handInputShow: false,
            handInputName: false,
            handPaperName: [{
                paperNameHand: ''
            }],
            handQuestion: false,
            handQuestionInput: [{
                questionType: "",
                questionContext: "",
                choiceA: "",
                choiceB: "",
                choiceC: "",
                choiceD: "",
                questionAnswerKeguan: "",
                questionAnswerZhuguan1: "",
                questionAnswerZhuguan2: "",
                questionAnswerZhuguan3: "",
                questionCount: ''
            }],
            questionDanxuan: [],
            questionTiankong: [],
            questionPanduan: [],
            questionWenda: [],
            outputPaper: false,
            outputTime: [{
                beginDate: '',
                endDate: '',
                beginTime: '',
                endTime: '',
                duration: '',
            }],            
        
            selectShow: false,
            selectInputName: false,
            selectQuestion: false,
            selectPaperName: [{
                paperNameSelect: ''
            }],

            paperIDback: 100000,
            questionDetail: 100000,

            //题库管理
            tableData2: [],
            tableData7: [],
            questionShow: false,
            //分页
            currentPage2: 1,
            total2: 0,
            currentPage7: 1,
            total7: 0,
            searchQuestion: '',
            //新增题目
            addQuestionShow: false,
            addQuestionInfor: [{
                    paperIdStr: '',
                    exerciseTypeStr: '',
                    exerciseIdStr: '',
                    contentStr: '',
                    typeAStr: '',
                    typeBStr: '',
                    typeCStr: '',
                    typeDStr: '',
                    answerStr: '',
                    scoreStr: '',
                }],

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
        //重置
        /**
         * 表单重置
         * @date 2020-06-30
         * @param {object} refname
         * @returns no return
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
        //分页
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
        current_change7(currentPage) {
            this.currentPage7 = currentPage;
        },

        /**
         * 对列出的所有试卷进行搜索，利用axios
         * @date 2020-06-30
         * @returns 后端返回的搜索结果[list]
         */
        //搜索试卷
        searchPapers() {
            // console.log(this.searchPaper);
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

        //删除试卷
        /**
         * 删除对应的试卷
         * @date 2020-06-30
         * @param {number} index
         * @param {number} row
         * @returns 返回剩余试卷列表
         */
        deletePaperName(index, row) {
            this.$ajax({
                method: "post",
                // url: "http://120.26.186.88:8080/paper/deletePaper?paperldStr="+row.paperId,
                url: "http://120.26.186.88:8080/paper/deletePaper",
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
                    // console.log(resolve.data);
                }, reject => {
                    // this.peoLoading = true;
                    console.log(reject);
                });
            }, reject => {
                // this.peoLoading = true;
                console.log(reject);
            });
        },

        //修改试卷名
        /**
         * 修改对应试卷名称
         * @date 2020-06-30
         * @param {number} index
         * @param {number} row
         * @returns 返回修改后的试卷[以所有试卷的形式]
         */
        changePaperName(index, row) {
            this.$prompt('请输入新的试卷名称', '修改试卷名称', {
                confirmButtonText: '确定',
                cancelButtonText: '取消',
            }).then(({ value }) => {
                // console.log(value);
                this.$ajax({
                    method: "post",
                    url: "http://120.26.186.88:8080/paper/updatePaper",
                    data: {
                        paperIdStr: row.paperId,
                        paperName: value,
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
                        url: "http://120.26.186.88:8080/paper/listAllPaper",
                        dataType: "json",
                        crossDomain: true,
                        cache: false,
                    }).then(resolve => {
                        this.tableData1 = resolve.data;
                        //获取数组长度赋值给total
                        this.total1 = resolve.data.length;
                        // console.log(resolve.data);
                    }, reject => {
                        // this.peoLoading = true;
                        console.log(reject);
                    });
                }, reject => {
                    // this.peoLoading = true;
                    console.log(reject);
                });
            }).catch(() => {
                this.$message({
                    type: 'info',
                    message: '取消输入'
                });       
            });
        },

        //提交试卷名 手动录入
        /**
         * 手动录题创建试卷
         * @date 2020-06-30
         * @returns 返回试卷的ID[paperID]
         */
        subPaperName1() {
            console.log(this.handPaperName);
            console.log(this.handPaperName.paperNameHand);
            this.$ajax({
                method: "post",
                url: "http://120.26.186.88:8080/paper/addPaper",
                dataType: "json",
                data: {
                    paperName: this.handPaperName.paperNameHand,
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
                console.log(resolve);
                this.paperIDback = resolve.data;
                //调用显示试卷
                this.showPaper(this.paperIDback);
            }, reject => {
                console.log("提交失败!");
            });
        },

        //将当前已有题目显示在试卷之中
        /**
         * 显示当前试卷中所包含的题目[录题阶段]，以实现录一个题显示一个题的效果
         * @date 2020-06-30
         * @param {number} PID
         * @returns 返回题目
         */
        showPaper(PID) {
            const pid = PID;
            //单选
            this.$ajax({
                method: "post",
                // method: "get",
                // url: "../../../static/testJSONdanxuan.json",
                url: "http://120.26.186.88:8080/connect/listAllConnect",
                dataType: "json",
                data: {
                    paperIdStr: pid,
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
                console.log(resolve.data);
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
                    paperIdStr: pid,
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
                console.log(this.questionPanduan);
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
                    paperIdStr: pid,
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
                console.log(this.questionTiankong);
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
                    paperIdStr: pid,
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
                console.log(this.questionWenda);
                // this.showPaper(pid);
            }, reject => {
                console.log("题目获取失败！");
            });
        },

        //录入题目上传 
        /**
         * 上传手动输入的题目到数据库[利用axios，通过后端]
         * @date 2020-06-30
         * @returns 返回试题ID
         */
        submihandQuestion() {
            console.log(this.handQuestionInput);
            if((this.handQuestionInput.questionType)=="3") {
                //只有一个
                if(this.handQuestionInput.questionAnswerZhuguan1 != undefined && this.handQuestionInput.questionAnswerZhuguan2 == undefined && this.handQuestionInput.questionAnswerZhuguan3 == undefined) {
                    console.log(1);
                    this.$ajax({
                        method: "post",
                        url: "http://120.26.186.88:8080/paperDetail/addPaperDetail",
                        data: {
                            paperIdStr: this.paperIDback,
                            exerciseTypeStr: this.handQuestionInput.questionType,
                            contentStr: this.handQuestionInput.questionContext,
                            typeAStr: "",
                            typeBStr: "",
                            typeCStr: "",
                            typeDStr: "",
                            answerStr: this.handQuestionInput.questionAnswerZhuguan1,
                            answer2: "这个字段为空",
                            answer3: "这个字段为空",
                            scoreStr: this.handQuestionInput.questionCount,
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
                        this.questionDetail = resolve.data;
                        console.log("当前试卷编号为：");
                        console.log(this.paperIDback);
                        console.log(this.questionDetail);
                        this.$ajax({
                            method: "post",
                            // url: "http://120.26.186.88:8080/connect/addConnect?paperIdStr="+this.paperIDback+"&exerciseTypeStr="+this.questionDetail,
                            url: "http://120.26.186.88:8080/connect/addConnect",
                            dataType: "json",
                            data: {
                                paperIdStr: this.paperIDback,
                                paperDetailIdStr: this.questionDetail,
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
                            //调用显示试卷
                            this.showPaper(this.paperIDback);
                            //提交之后 表单清空
                            this.handQuestionInput = {brand_right: 0};
                            console.log("绑定成功");
                        }, reject => {
                            console.log("题目创建失败！");
                        });
                    }, reject => {
                        console.log("题目创建失败了！");
                    });
                }
                else if(this.handQuestionInput.questionAnswerZhuguan1 != undefined && this.handQuestionInput.questionAnswerZhuguan2 != undefined && this.handQuestionInput.questionAnswerZhuguan3 == undefined) {
                    console.log(2);
                    this.$ajax({
                        method: "post",
                        url: "http://120.26.186.88:8080/paperDetail/addPaperDetail",
                        data: {
                            paperIdStr: this.paperIDback,
                            exerciseTypeStr: this.handQuestionInput.questionType,
                            contentStr: this.handQuestionInput.questionContext,
                            typeAStr: "",
                            typeBStr: "",
                            typeCStr: "",
                            typeDStr: "",
                            answerStr: this.handQuestionInput.questionAnswerZhuguan1,
                            answer2: this.handQuestionInput.questionAnswerZhuguan2,
                            answer3: "这个字段为空",
                            scoreStr: this.handQuestionInput.questionCount,
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
                        this.questionDetail = resolve.data;
                        console.log("当前试卷编号为：");
                        console.log(this.paperIDback);
                        console.log(this.questionDetail);
                        this.$ajax({
                            method: "post",
                            // url: "http://120.26.186.88:8080/connect/addConnect?paperIdStr="+this.paperIDback+"&exerciseTypeStr="+this.questionDetail,
                            url: "http://120.26.186.88:8080/connect/addConnect",
                            dataType: "json",
                            data: {
                                paperIdStr: this.paperIDback,
                                paperDetailIdStr: this.questionDetail,
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
                            //调用显示试卷
                            this.showPaper(this.paperIDback);
                            //提交之后 表单清空
                            this.handQuestionInput = {brand_right: 0};
                            console.log("绑定成功");
                        }, reject => {
                            console.log("题目创建失败！");
                        });
                    }, reject => {
                        console.log("题目创建失败了！");
                    });
                }
                else if(this.handQuestionInput.questionAnswerZhuguan1 != undefined && this.handQuestionInput.questionAnswerZhuguan2 != undefined && this.handQuestionInput.questionAnswerZhuguan3 != undefined) {
                    console.log(3);
                    this.$ajax({
                        method: "post",
                        url: "http://120.26.186.88:8080/paperDetail/addPaperDetail",
                        data: {
                            paperIdStr: this.paperIDback,
                            exerciseTypeStr: this.handQuestionInput.questionType,
                            contentStr: this.handQuestionInput.questionContext,
                            typeAStr: "",
                            typeBStr: "",
                            typeCStr: "",
                            typeDStr: "",
                            answerStr: this.handQuestionInput.questionAnswerZhuguan1,
                            answer2: this.handQuestionInput.questionAnswerZhuguan2,
                            answer3: this.handQuestionInput.questionAnswerZhuguan3,
                            scoreStr: this.handQuestionInput.questionCount,
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
                        this.questionDetail = resolve.data;
                        console.log("当前试卷编号为：");
                        console.log(this.paperIDback);
                        console.log(this.questionDetail);
                        this.$ajax({
                            method: "post",
                            // url: "http://120.26.186.88:8080/connect/addConnect?paperIdStr="+this.paperIDback+"&exerciseTypeStr="+this.questionDetail,
                            url: "http://120.26.186.88:8080/connect/addConnect",
                            dataType: "json",
                            data: {
                                paperIdStr: this.paperIDback,
                                paperDetailIdStr: this.questionDetail,
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
                            //调用显示试卷
                            this.showPaper(this.paperIDback);
                            //提交之后 表单清空
                            this.handQuestionInput = {brand_right: 0};
                            console.log("绑定成功");
                        }, reject => {
                            console.log("题目创建失败！");
                        });
                    }, reject => {
                        console.log("题目创建失败了！");
                    });
                }
                console.log(this.handQuestionInput.questionType);
            }
            // 判断
            else {
                this.$ajax({
                    method: "post",
                    url: "http://120.26.186.88:8080/paperDetail/addPaperDetail",
                    data: {
                        paperIdStr: this.paperIDback,
                        exerciseTypeStr: this.handQuestionInput.questionType,
                        contentStr: this.handQuestionInput.questionContext,
                        typeAStr: this.handQuestionInput.choiceA,
                        typeBStr: this.handQuestionInput.choiceB,
                        typeCStr: this.handQuestionInput.choiceC,
                        typeDStr: this.handQuestionInput.choiceD,
                        answerStr: this.handQuestionInput.questionAnswerKeguan,
                        answer2: "这个字段为空",
                        answer3: "这个字段为空",
                        scoreStr: this.handQuestionInput.questionCount,
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
                    this.questionDetail = resolve.data;
                    console.log(this.paperIDback);
                    console.log(this.questionDetail);
                    this.$ajax({
                        method: "post",
                        // url: "http://120.26.186.88:8080/connect/addConnect?paperIdStr="+this.paperIDback+"&exerciseTypeStr="+this.questionDetail,
                        url: "http://120.26.186.88:8080/connect/addConnect",
                        dataType: "json",
                        data: {
                            paperIdStr: this.paperIDback,
                            paperDetailIdStr: this.questionDetail,
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
                        //调用显示试卷
                        this.showPaper(this.paperIDback);
                        // this.reset('handQuestionInput');
                        this.handQuestionInput = {brand_right: 0};
                        console.log("绑定成功");
                    }, reject => {
                        console.log("题目创建失败！");
                    });
                }, reject => {
                    console.log("题目创建失败了！");
                });
            }
        },

        //发布考试时间
        /**
         * 创建完试卷之后，发布考试的时间[即试卷显示给学生的时间段]以及做题时长
         * @date 2020-06-30
         * @returns no return
         */
        sureSubmit() {
            if(this.outputTime.duration <= 0) {
                this.$message.error("考试时长非法!");
                return;
            }
            this.outputPaper=false;
            console.log(this.outputTime);
            let testBegin = "开始:"+this.outputTime.beginDate+this.outputTime.beginTime;
            let testEnd = "结束:"+this.outputTime.endDate+this.outputTime.endTime;
            console.log(testBegin);
            console.log(testEnd);
            console.log(this.paperIDback);
            console.log(this.outputTime.duration);
            this.$ajax({
                method: "post",
                url: "http://120.26.186.88:8080/paper/publishPaper?paperIdStr="+this.paperIDback
                                                                            +"&beginTime="+testBegin
                                                                            +"&endTime="+testEnd
                                                                            +"&duration="+this.outputTime.duration,
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
                console.log("上传时间成功！");
                // 发布试卷后 填写试卷名称清空
                this.selectPaperName = {brand_right: 0};
                this.handPaperName = {brand_right: 0};
                this.questionDanxuan = [];
                this.questionTiankong = [];
                this.questionPanduan = [];
                this.questionWenda = [];
                //题库更新
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
                    console.log(resolve);
                    // console.log(resolve.data);
                }, reject => {
                    // this.peoLoading = true;
                    console.log(reject);
                });
                //试卷更新
                this.$ajax({
                    method: "post",
                    url: "http://120.26.186.88:8080/paper/listAllPaper",
                    dataType: "json",
                    crossDomain: true,
                    cache: false,
                }).then(resolve => {
                    this.tableData1 = resolve.data;
                    console.log(resolve.data);
                    //获取数组长度赋值给total
                    this.total1 = resolve.data.length;
                    // this.peoLoading = false;
                    console.log(this.total1);
                    // console.log(resolve.data);
                }, reject => {
                    // this.peoLoading = true;
                    console.log(reject);
                });
            }, reject => {
                console.log("未能上传数据");
            });
        },

        //提交试卷名 题库选题
        /**
         * 题库选题题创建试卷
         * @date 2020-06-30
         * @returns 返回试卷的ID[paperID]
         */
        subPaperName2() {
            this.$ajax({
                method: "post",
                url: "http://120.26.186.88:8080/paper/addPaper",
                dataType: "json",
                data: {
                    paperName: this.selectPaperName.paperNameSelect,
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
                this.paperIDback = resolve.data;
            }, reject => {
                console.log("提交失败!");
            });
        },

        //获得所有题目 列在题库表中
        /**
         * 获取数据库中所有的题目供用户参考，选择其心仪的题目并添加
         * @date 2020-06-30
         * @returns no return
         */
        getAllQuestion() {
            this.$ajax({
                method: "post",
                url: "http://120.26.186.88:8080/paperDetail/listAllPaperDetail",
                dataType: "json",
                crossDomain: true,
                cache: false,
            }).then(resolve => {
                 console.log(resolve);
                this.tableData7 = resolve.data;
                //获取数组长度赋值给total
                this.total7 = resolve.data.length;
                // this.peoLoading = false;
                console.log(this.total7);
                // console.log(resolve.data);
            }, reject => {
                // this.peoLoading = true;
                console.log(reject);
            });
        },

        //点击题目添加
        /**
         * 创建一个绑定——试卷与题目的绑定
         * @date 2020-06-30
         * @param {number} index
         * @param {number} row
         * @returns no return
         */
        sureAddQuestion(index, row) {
            console.log("当前试卷编号为：");
            console.log(this.paperIDback);
            console.log(row.paperDetailId);
            this.$ajax({
                method: "post",
                // url: "http://120.26.186.88:8080/connect/addConnect?paperIdStr="+this.paperIDback+"&exerciseTypeStr="+this.questionDetail,
                url: "http://120.26.186.88:8080/connect/addConnect",
                dataType: "json",
                data: {
                    paperIdStr: this.paperIDback,
                    paperDetailIdStr: row.paperDetailId,
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
                //调用显示试卷
                // this.showPaper(this.paperIDback);
                this.showPaper(this.paperIDback)
                console.log("绑定成功");
            }, reject => {
                console.log("题目创建失败！");
            });
        },
       
        //提交新增公告
        /**
         * 教师添加公告
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
         * @param numbery} row
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

        //搜索题目
        /**
         * 依输入的字段对题目进行模糊查询
         * @date 2020-06-30
         * @returns 返回查询到的所有题目列表
         */
        searchQuestionBtn() {
            console.log(this.searchQuestion);
            this.$ajax({
                method: "post",
                url: "http://120.26.186.88:8080/paperDetail/queryPaperDetail",
                data: {
                    keyStr: this.searchQuestion,
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
                this.tableData2 = resolve.data;
                //获取数组长度赋值给total
                this.total2 = resolve.data.length;
                // this.peoLoading = false;
                console.log(this.total2);
                // console.log(resolve.data);
            }, reject => {
                console.log(reject);
            });
        },

        //删除题目
        /**
         * 删除对应的题目
         * @date 2020-06-30
         * @param {number} index
         * @param {number} row
         * @returns 返回删除后的所有剩余题目
         */
        deleteQuestion(index, row) {
            // console.log(row.exerciseId);
            this.$ajax({
                method: "post",
                // url: "http://120.26.186.88:8080/paper/deletePaper?paperldStr="+row.paperId,
                url: "http://120.26.186.88:8080/paperDetail/deletePaperDetail",
                data: {
                    paperIdStr: row.paperDetailId,
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
                    console.log(reject);
                });
            }, reject => {
                console.log("删除失败");
            });
        },

        //新增题目
        /**
         * 新增题目
         * @date 2020-06-30
         * @returns 返回新增后的所有题目
         */
        addQuestion() {
            console.log(this.handQuestionInput);
            if((this.handQuestionInput.questionType)=="3") {
                console.log(this.handQuestionInput.questionAnswerZhuguan1);
                console.log(this.handQuestionInput.questionAnswerZhuguan2);
                console.log(this.handQuestionInput.questionAnswerZhuguan3);
                //只有一个
                if(this.handQuestionInput.questionAnswerZhuguan1 != undefined && this.handQuestionInput.questionAnswerZhuguan2 == undefined && this.handQuestionInput.questionAnswerZhuguan3 == undefined) {
                    console.log(1);
                    this.$ajax({
                        method: "post",
                        url: "http://120.26.186.88:8080/paperDetail/addPaperDetail",
                        data: {
                            // paperIdStr: this.paperIDback,
                            exerciseTypeStr: this.handQuestionInput.questionType,
                            contentStr: this.handQuestionInput.questionContext,
                            typeAStr: "",
                            typeBStr: "",
                            typeCStr: "",
                            typeDStr: "",
                            answerStr: this.handQuestionInput.questionAnswerZhuguan1,
                            answer2: "这个字段为空",
                            answer3: "这个字段为空",
                            scoreStr: this.handQuestionInput.questionCount,
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
                        this.questionDetail = resolve.data;
                        console.log(resolve.data);
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
                            //提交之后 表单清空
                            this.handQuestionInput = {brand_right: 0};
                        }, reject => {
                            console.log(reject);
                        });
                    }, reject => {
                        console.log("题目创建失败了！");
                    });
                }
                else if(this.handQuestionInput.questionAnswerZhuguan1 != undefined && this.handQuestionInput.questionAnswerZhuguan2 != undefined && this.handQuestionInput.questionAnswerZhuguan3 == undefined) {
                    console.log(2);
                    this.$ajax({
                        method: "post",
                        url: "http://120.26.186.88:8080/paperDetail/addPaperDetail",
                        data: {
                            // paperIdStr: this.paperIDback,
                            exerciseTypeStr: this.handQuestionInput.questionType,
                            contentStr: this.handQuestionInput.questionContext,
                            typeAStr: "",
                            typeBStr: "",
                            typeCStr: "",
                            typeDStr: "",
                            answerStr: this.handQuestionInput.questionAnswerZhuguan1,
                            answer2: this.handQuestionInput.questionAnswerZhuguan2,
                            answer3: "这个字段为空",
                            scoreStr: this.handQuestionInput.questionCount,
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
                        this.questionDetail = resolve.data;
                        console.log(resolve.data);
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
                            //提交之后 表单清空
                            this.handQuestionInput = {brand_right: 0};
                        }, reject => {
                            console.log(reject);
                        });
                    }, reject => {
                        console.log("题目创建失败了！");
                    });
                }
                else if(this.handQuestionInput.questionAnswerZhuguan1 != undefined && this.handQuestionInput.questionAnswerZhuguan2 != undefined && this.handQuestionInput.questionAnswerZhuguan3 != undefined) {
                    console.log(3);
                    this.$ajax({
                        method: "post",
                        url: "http://120.26.186.88:8080/paperDetail/addPaperDetail",
                        data: {
                            // paperIdStr: this.paperIDback,
                            exerciseTypeStr: this.handQuestionInput.questionType,
                            contentStr: this.handQuestionInput.questionContext,
                            typeAStr: "",
                            typeBStr: "",
                            typeCStr: "",
                            typeDStr: "",
                            answerStr: this.handQuestionInput.questionAnswerZhuguan1,
                            answer2: this.handQuestionInput.questionAnswerZhuguan2,
                            answer3: this.handQuestionInput.questionAnswerZhuguan3,
                            scoreStr: this.handQuestionInput.questionCount,
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
                        this.questionDetail = resolve.data;
                        console.log(resolve.data);
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
                            //提交之后 表单清空
                            this.handQuestionInput = {brand_right: 0};
                        }, reject => {
                            console.log(reject);
                        });
                    }, reject => {
                        console.log("题目创建失败了！");
                    });
                }
                console.log(this.handQuestionInput.questionType);
            }
            //判断
            else {
                this.$ajax({
                    method: "post",
                    url: "http://120.26.186.88:8080/paperDetail/addPaperDetail",
                    data: {
                        // paperIdStr: this.paperIDback,
                        exerciseTypeStr: this.handQuestionInput.questionType,
                        contentStr: this.handQuestionInput.questionContext,
                        typeAStr: this.handQuestionInput.choiceA,
                        typeBStr: this.handQuestionInput.choiceB,
                        typeCStr: this.handQuestionInput.choiceC,
                        typeDStr: this.handQuestionInput.choiceD,
                        answerStr: this.handQuestionInput.questionAnswerKeguan,
                        answer2: "这个字段为空",
                        answer3: "这个字段为空",
                        scoreStr: this.handQuestionInput.questionCount,
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
                    this.questionDetail = resolve.data;
                    console.log(resolve.data);
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
                        //提交之后 表单清空
                        this.handQuestionInput = {brand_right: 0};
                    }, reject => {
                        console.log(reject);
                    });
                }, reject => {
                    console.log("题目创建失败了！");
                });
            }
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
            console.log(resolve.data);
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
            console.log(resolve);
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
