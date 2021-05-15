package com.nenusoftware.onlineexam.service.user.impl;

import com.nenusoftware.onlineexam.entity.user.User;
import com.nenusoftware.onlineexam.mapper.user.UserMapper;
import com.nenusoftware.onlineexam.service.user.UserService;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * @Author:Liangll
 * @Description: UserService的底层实现方法
 * @Date: 11:53 2020/6/13
 */
@Service
public class UserServiceImpl implements UserService {

    @Resource
    UserMapper userMapper;

    /**
     * 判断用户输入密码是否正确
     * @param username 用户名
     * @param password 用户密码
     * @return 回根据用户名与用户密码查询后的信息
     * @throws Exception 抛出错误类型
     */
    @Override
    public List<User> checkPassword(String username, String password) throws Exception{
        boolean flag = true;
        return userMapper.checkPassword(username,password);
    }

    /**
     * 列出所有用户信息
     * @return 返回List形式的用户信息
     * @throws Exception 抛出错误类型
     */
    @Override
    public ArrayList<User> listAllUser() throws Exception{
        ArrayList<User> userList = new ArrayList<>();
        userList = userMapper.listAllUser();
        return userList;
    }

    /**
     * 增加用户（注册方法）
     * @param user 用户实体
     * @return 注册成功返回true，注册失败返回false
     * @throws Exception 抛出错误类型
     */
    @Override
    public boolean addUser(User user) throws Exception {
        return userMapper.addUser(user);

    }

//    /**
//     * 删除用户
//     * @param userId 用户编号
//     * @return 删除成功返回true，删除失败返回false
//     * @throws Exception
//     */
//    @Override
//    public boolean deleteUser(int userId) throws Exception{
//        return userMapper.deleteUser(userId);
//    }

    /**
     * 修改用户
     * @param user 用户实体
     * @return 修改成功返回true，修改失败返回false
     * @throws Exception 抛出错误类型
     */
    @Override
    public boolean updateUser(User user) throws Exception{
        return userMapper.updateUser(user);
    }

//    /**
//     * 修改用户权限（用于后台管理）
//     * @param userId 用户编号
//     * @return 修改成功返回true，修改失败返回false
//     * @throws Exception
//     */
//    @Override
//    public boolean updatePower(int userId) throws Exception{
//        return userMapper.updatePower(userId);
//    }

    /**
     * 根据用户名查询数据信息
     * @param username 用户名
     * @return 返回根据用户名查询后的信息
     * @throws Exception 抛出错误类型
     */
    @Override
    public User queryByName(String username) throws Exception {
        return userMapper.querytByName(username);
    }

    /**
     * 根据用户名得到用户唯一编号
     * @param username 用户名
     * @return 返回User实体
     * @throws Exception 抛出错误类型
     */
    @Override
    public User queryIdByUsername(String username) throws Exception {
        return userMapper.queryIdByUsername(username);
    }

    /**
     * 根据用户编号列出用户所有信息
     * @param userId 用户编号
     * @return 返回List形式的用户信息
     * @throws Exception 抛出错误类型
     */
    @Override
    public ArrayList<User> listUserById(int userId) throws Exception{
        ArrayList<User> userList = new ArrayList<>();
        userList = userMapper.listUserById(userId);
        return userList;
    }
}
