package com.nenusoftware.onlineexam;

import com.nenusoftware.onlineexam.entity.User;
import com.nenusoftware.onlineexam.service.UserService;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;

/**
 * @Author:Liangll
 * @Description: 测试UserService的各类方法
 * @Date: 11:44 2019/5/3
 */
@RunWith(SpringRunner.class)
@SpringBootTest
public class UserServiceTest {

    @Autowired
    UserService userService;

    @Test
    public void testSelectByName() throws Exception {
        User user = new User();
        user.setUsername("45");
        System.out.println(userService.selectByName(user.getUsername()));
    }

    @Test
    public void testCheckPassword() throws Exception {
        User user = new User();
        user.setUsername("45");
        user.setPassword("45");
        System.out.println(userService.checkPassword(user.getUsername(),user.getPassword()));
    }

    @Test
    public void testAddUser() throws Exception {
        User user = new User();
        user.setId(88);
        user.setUsername("admin");
        user.setPassword("123");
        System.out.println(userService.addUser(user));
    }
}
