//package com.nenusoftware.onlineexam.wrong;
//
//import com.nenusoftware.onlineexam.entity.wrong.Wrong;
//import com.nenusoftware.onlineexam.service.wrong.WrongService;
//import org.junit.Test;
//import org.junit.runner.RunWith;
//import org.springframework.beans.factory.annotation.Autowired;
//import org.springframework.boot.test.context.SpringBootTest;
//import org.springframework.test.context.junit4.SpringRunner;
//
//import java.util.Calendar;
//import java.util.Date;
//import java.util.LinkedList;
//import java.util.List;
//
///**
// * @Author:Liangll
// * @Description: 测试WrongService的各类方法
// * @Date: 16:25 2020/6/22
// */
//@RunWith(SpringRunner.class)
//@SpringBootTest
//public class WrongServiceTest {
//
//    @Autowired
//    WrongService wrongService;
//
//    @Test
//    public void testListWrongById() throws Exception{
//        System.out.println(wrongService.listWrongByUserId(1));
//    }
//
//    @Test
//    public void testDeleteWrong() throws Exception{
//        System.out.println(wrongService.deleteWrong(4));
//    }
//
//    @Test
//    public void testFunc(){
//        Calendar calendar=Calendar.getInstance();
//        System.out.println(calendar.get(Calendar.YEAR));
//        System.out.println(calendar.get(Calendar.MONTH) + 1);
//        System.out.println(calendar.get(Calendar.DATE));
//        System.out.println(calendar.get(Calendar.HOUR_OF_DAY));
//        System.out.println(calendar.get(Calendar.MINUTE));
//        System.out.println(calendar.get(Calendar.SECOND));
//    }
//
//    @Test
//    public void testSplitData(){
////        String str = "开始:1999年10月21日7时32分20秒";
////        String year = str.substring(str.indexOf(":")+1, str.lastIndexOf("年"));
////        System.out.println(year);
////        String month = str.substring(str.indexOf("年")+1, str.lastIndexOf("月"));
////        System.out.println(month);
////        String day = str.substring(str.indexOf("月")+1, str.lastIndexOf("日"));
////        System.out.println(day);
////        String hour = str.substring(str.indexOf("日")+1, str.lastIndexOf("时"));
////        System.out.println(hour);
////        String minute = str.substring(str.indexOf("时")+1, str.lastIndexOf("分"));
////        System.out.println(minute);
////        String second = str.substring(str.indexOf("分")+1, str.lastIndexOf("秒"));
////        System.out.println(second);
//        Date date = new Date();
//        System.out.println(date);
//    }
//
//    @Test
//    public void testList(){
//        List<Wrong> wrongList = new LinkedList<>();
//        Wrong wrong = new Wrong();
//        wrong.setRight("a");
//        wrongList.add(wrong);
//        System.out.println(wrongList);
//    }
//}
