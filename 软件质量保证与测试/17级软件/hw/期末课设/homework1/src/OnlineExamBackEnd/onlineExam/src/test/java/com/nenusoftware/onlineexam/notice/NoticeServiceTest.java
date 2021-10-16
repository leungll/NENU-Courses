//package com.nenusoftware.onlineexam.notice;
//
//import com.nenusoftware.onlineexam.entity.notice.Notice;
//import com.nenusoftware.onlineexam.service.notice.NoticeService;
//import org.junit.Test;
//import org.junit.runner.RunWith;
//import org.springframework.beans.factory.annotation.Autowired;
//import org.springframework.boot.test.context.SpringBootTest;
//import org.springframework.test.context.junit4.SpringRunner;
//
//import java.util.Date;
//
///**
// * @Author:Liangll
// * @Description: 测试NoticeService的各类方法
// * @Date: 13:44 2020/6/20
// */
//@RunWith(SpringRunner.class)
//@SpringBootTest
//public class NoticeServiceTest {
//
//    @Autowired
//    NoticeService noticeService;
//
//    @Test
//    public void testListAllNotice() throws Exception{
//        System.out.println(noticeService.listAllNotice());
//    }
//
//    @Test
//    public void testAddNotice() throws Exception {
//        Notice notice = new Notice();
//
//        notice.setUserId(2);
//        notice.setTitle("测试增加通告标题");
//        notice.setContent("测试增加通告内容");
//        Date date = new Date();
//        String createTimeStr = date.toString();
//        notice.setCreateTime(createTimeStr);
//
//        noticeService.addNotice(notice);
//    }
//
//    @Test
//    public void testDeleteNotice() throws Exception{
//        System.out.println(noticeService.deleteNotice(2));
//    }
//
//    @Test
//    public void testUpdateNotice() throws Exception{
//        Notice notice = new Notice();
//        notice.setNoticeId(1);
//
//        notice.setUserId(2);
//        notice.setTitle("测试修改通告标题");
//        notice.setContent("测试修改通告内容");
//        Date date = new Date();
//        String createTimeStr = date.toString();
//        notice.setCreateTime(createTimeStr);
//        noticeService.updateNotice(notice);
//    }
//
//    @Test
//    public void testQueryNotice() throws Exception{
//        String keyWord = "增加";
//        System.out.println(noticeService.queryNotice(keyWord));
//    }
//
//}
