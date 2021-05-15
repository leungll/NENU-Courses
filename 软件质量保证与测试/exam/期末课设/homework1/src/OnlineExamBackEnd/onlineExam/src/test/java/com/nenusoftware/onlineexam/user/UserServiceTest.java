//package com.nenusoftware.onlineexam.user;
//
//import com.nenusoftware.onlineexam.entity.user.User;
//import com.nenusoftware.onlineexam.service.user.UserService;
//import org.junit.Test;
//import org.junit.runner.RunWith;
//import org.springframework.beans.factory.annotation.Autowired;
//import org.springframework.boot.test.context.SpringBootTest;
//import org.springframework.test.context.junit4.SpringRunner;
//
///**
// * @Author:Liangll
// * @Description: 测试UserService的各类方法
// * @Date: 16:49 2020/6/23
// */
//@RunWith(SpringRunner.class)
//@SpringBootTest
//public class UserServiceTest {
//
//    @Autowired
//    UserService userService;
//
//    @Test
//    public void testCheckPassword() throws Exception {
//        User user = new User();
//        user.setUsername("admin");
//        user.setPassword("123");
//        System.out.println(userService.checkPassword(user.getUsername(),user.getPassword()));
//    }
//
//    @Test
//    public void testListAllUser() throws Exception{
//        System.out.println(userService.listAllUser());
//    }
//
//    @Test
//    public void testAddUser() throws Exception {
//        User user = new User();
//        user.setUsername("测试注册");
//        user.setPassword("123");
//        user.setBirthday("19991021");
//        user.setSex("女");
//        user.setPower(1);
//        user.setImage("img.jpg");
//        userService.addUser(user);
//    }
//
////    @Test
////    public void testDeleteUser() throws Exception{
////        System.out.println(userService.deleteUser(1));
////    }
//
//    @Test
//    public void testUpdateUser() throws Exception{
//        User user = new User();
//        user.setUserId(2);
//        user.setUsername("hello");
//        user.setPassword("123");
//        user.setBirthday("19990901");
//        user.setSex("女");
//        user.setPower(1);
//        user.setImage("img.jpg");
//        System.out.println(userService.updateUser(user));
//    }
//
////    @Test
////    public void testUpdatePower() throws Exception{
////        int id = 2;
////        System.out.println(userService.updatePower(id));
////    }
//
//    @Test
//    public void testQueryByName() throws Exception {
//        User user = new User();
//        user.setUsername("admin");
//        System.out.println(userService.queryByName(user.getUsername()));
//    }
//
//    @Test
//    public void testQueryIdByUsername() throws Exception{
//        String username = "teacher";
//        System.out.println(userService.queryIdByUsername(username).getUserId());
//    }
//
//    @Test
//    public void testListUserById() throws Exception{
//        System.out.println(userService.listUserById(2));
//    }
//}
