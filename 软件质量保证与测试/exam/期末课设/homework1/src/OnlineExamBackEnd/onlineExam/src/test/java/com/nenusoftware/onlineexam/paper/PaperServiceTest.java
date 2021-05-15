//package com.nenusoftware.onlineexam.paper;
//
//import com.nenusoftware.onlineexam.entity.paper.Paper;
//import com.nenusoftware.onlineexam.service.paper.PaperService;
//import org.junit.Test;
//import org.junit.runner.RunWith;
//import org.springframework.beans.factory.annotation.Autowired;
//import org.springframework.boot.test.context.SpringBootTest;
//import org.springframework.test.context.junit4.SpringRunner;
//
///**
// * @Author:Liangll
// * @Description: 测试PaperService的各类方法
// * @Date: 12:21 2020/6/21
// */
//@RunWith(SpringRunner.class)
//@SpringBootTest
//public class PaperServiceTest {
//
//    @Autowired
//    PaperService paperService;
//
//    @Test
//    public void testListAllPaper() throws Exception{
//        System.out.println(paperService.listAllPaper());
//    }
//
//    @Test
//    public void testListPublishPaper() throws Exception{
//        System.out.println(paperService.listPublishPaper(1));
//    }
//
//    @Test
//    public void testAddPaper() throws Exception {
//        String paperName = "新增一张试卷";
//        Paper paper = new Paper();
//        paper.setPaperName(paperName);
//        paper.setStatus(0);
//        paper.setBeginTime(null);
//        paper.setDuration(null);
//        paperService.addPaper(paper);
//        System.out.println(paperService.queryPaperIdByName(paperName).getPaperId());
//    }
//
//    @Test
//    public void testDeletePaper() throws Exception{
//        paperService.deletePaper(1);
//    }
//
//    @Test
//    public void testUpdatePaper() throws Exception{
//        Paper paper = new Paper();
//        paper.setPaperId(3);
//        paper.setPaperName("测试修改试卷");
//        paperService.updatePaper(paper);
//    }
//
//    @Test
//    public void testQueryPaperName() throws Exception{
//        String keyWord = "试卷";
//        System.out.println(paperService.queryPaperName(keyWord));
//    }
//
//    @Test
//    public void testQueryPaperNameById() throws Exception{
//        int paperId = 2;
//        System.out.println(paperService.queryPaperNameById(paperId).getPaperName());
//    }
//
//    @Test
//    public void testQueryPaperIdByName() throws Exception{
//        String paperName = "2020年春季学期软件质量保证与测试期末考试";
//        System.out.println(paperService.queryPaperIdByName(paperName).getPaperId());
//    }
//
//    @Test
//    public void testPublishPaper() throws Exception{
//        Paper paper = new Paper();
//        paper.setPaperId(2);
//        paper.setStatus(1);
//        paper.setBeginTime("开始:2020年6月8日15时0分0秒");
//        paper.setDuration("120");
//        paper.setEndTime("结束:2020年6月30日23时59分59秒");
//        paperService.publishPaper(paper);
//    }
//
////    @Test
////    public void testConvertTime() throws Exception{
////        String str = "开始:1999年10月21日7时32分20秒";
////        int time[] = new int[6];
////        time = paperService.extractTime(str);
////        for(int i=0;i<6;i++){
////            System.out.println(time[i]);
////        }
////    }
//}
