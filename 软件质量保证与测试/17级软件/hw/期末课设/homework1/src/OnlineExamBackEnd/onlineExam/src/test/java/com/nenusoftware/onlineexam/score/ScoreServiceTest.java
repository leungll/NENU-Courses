//package com.nenusoftware.onlineexam.score;
//
//import com.nenusoftware.onlineexam.entity.score.Score;
//import com.nenusoftware.onlineexam.service.score.ScoreService;
//import org.junit.Test;
//import org.junit.runner.RunWith;
//import org.springframework.beans.factory.annotation.Autowired;
//import org.springframework.boot.test.context.SpringBootTest;
//import org.springframework.test.context.junit4.SpringRunner;
//
///**
// * @Author:Liangll
// * @Description: 测试NoticeService的各类方法
// * @Date: 09:34 2020/6/23
// */
//@RunWith(SpringRunner.class)
//@SpringBootTest
//public class ScoreServiceTest {
//
//    @Autowired
//    ScoreService scoreService;
//
//    @Test
//    public void testAddScore() throws Exception {
//        Score score = new Score();
//        score.setUserId(2);
//        score.setPaperId(1);
//        score.setMark(99);
//        score.setPaperName("测试增加试卷名称addScore");
//        System.out.println(scoreService.addScore(score));
//    }
//
//    @Test
//    public void testDeleteScore() throws Exception{
//        System.out.println(scoreService.deleteScore(2));
//    }
//
//    @Test
//    public void testQueryScoreByUser() throws Exception{
//        int userId = 1;
//        System.out.println(scoreService.queryScoreByUser(userId));
//    }
//
//    @Test
//    public void testQueryScoreByPaper() throws Exception{
//        int paperId = 2;
//        System.out.println(scoreService.queryScoreByPaper(paperId));
//    }
//
//    @Test
//    public void testListScoreByMark1() throws Exception{
//        int paperId = 1;
//        System.out.println(scoreService.listScoreByMark1(paperId));
//    }
//
//    @Test
//    public void testListScoreByMark2() throws Exception{
//        int paperId = 1;
//        System.out.println(scoreService.listScoreByMark2(paperId));
//    }
//}
