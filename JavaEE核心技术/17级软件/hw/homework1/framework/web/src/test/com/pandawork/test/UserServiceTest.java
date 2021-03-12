package com.pandawork.test;

import com.pandawork.common.entity.user.User;
import com.pandawork.core.common.exception.SSException;
import com.pandawork.service.User.UserService;
import org.junit.Test;
import org.springframework.beans.factory.annotation.Autowired;

/**
 * 学生管理系统
 * 测试service页面
 * studentService
 * Created by fujia on 2016/3/26.
 */
public class UserServiceTest extends AbstractTestCase {

    @Autowired
    UserService userService;

    //测试新增学生信息
    @Test
    public void testAddUser() throws SSException {
        User user = new User();
        user.setUsername("hai");
        user.setPassword("12312312");
        user.setSig("2420hhjkds");
        userService.addUser(user);
        System.out.println("添加成功");
    }

    //测试查询学生信息列表
    @Test
    public void testListAll() throws SSException{
        System.out.print(userService.listAll());
    }

    //测试删除学生信息
    @Test
    public void testDelById() throws SSException{
        User user = new User();
        user.setId(80);
        userService.delById(user.getId());
        System.out.println("16");
    }

    //测试更新学生信息
    @Test
    public void testUpdate() throws SSException{
        User user = new User();
        user.setId(3);
        user.setUsername("ahe");
        user.setPassword("邱兰");
        user.setSig("ahfjdhkfjh");
        userService.update(user);
        System.out.println("12");
    }

    //测试更新学生信息
    @Test
    public void testUpdate2() throws SSException{
        userService.update2(83);
        System.out.println("12");
    }

    //测试根据姓名查询学生信息
    @Test
    public void testSelectByName() throws SSException{
        User user = new User();
        User u = new User();
        user.setUsername("ha");
        u = userService.selectByName(user.getUsername());
        System.out.println(u);
    }

}
