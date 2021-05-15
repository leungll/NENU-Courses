//package com.nenusoftware.onlineexam.connect;
//
//import com.nenusoftware.onlineexam.entity.connect.Connect;
//import com.nenusoftware.onlineexam.service.connect.ConnectService;
//import org.junit.Test;
//import org.junit.runner.RunWith;
//import org.springframework.beans.factory.annotation.Autowired;
//import org.springframework.boot.test.context.SpringBootTest;
//import org.springframework.test.context.junit4.SpringRunner;
//
//import java.util.List;
//
///**
// * @Author:Liangll
// * @Description: 测试 ConnectService的各类方法
// * @Date: 11:53 2020/6/20
// */
//@RunWith(SpringRunner.class)
//@SpringBootTest
//public class ConnectServiceTest {
//
//    @Autowired
//    ConnectService connectService;
//
//    @Test
//    public void testListAllConnect() throws Exception{
//        int paperId = 1;
//        String choiceType = "选择题";
//        String judgeType = "判断题";
//        List<Connect> choiceList = null;
//        List<Connect> judgeList = null;
//        System.out.println(connectService.listAllConnect(paperId, choiceType));
//        System.out.println(connectService.listAllConnect(paperId, judgeType));
//        choiceList = connectService.listAllConnect(paperId, choiceType);
//        judgeList = connectService.listAllConnect(paperId, judgeType);
//        choiceList.addAll(judgeList);
//        System.out.println(choiceList);
//    }
//
//    @Test
//    public void testAddConnect() throws Exception {
//        int paperId = 1, paperDetailId = 10;
//        Connect connect = new Connect();
//        connect.setPaperId(paperId);
//        connect.setPaperDetailId(paperDetailId);
//        connectService.addConnect(connect);
//    }
//
//    @Test
//    public void testInTime() throws Exception{
////        String str1 = "开始:1999年10月21日7时32分20秒";
////        String str2 = "开始:2020年10月21日7时32分20秒";
//        System.out.println(connectService.isInTheTime(2));
//    }
//
//    @Test
//    public void testLeftover() throws Exception{
//        System.out.println(connectService.leftoverTime(2));
//    }
//}
