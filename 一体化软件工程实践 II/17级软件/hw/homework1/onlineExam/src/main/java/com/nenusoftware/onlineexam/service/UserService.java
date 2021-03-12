package com.nenusoftware.onlineexam.service;

import com.nenusoftware.onlineexam.entity.User;

import java.util.List;

/**
 * @Author:Liangll
 * @Description: UserService的接口层
 * @Date: 10:52 2019/5/3
 */
public interface UserService {

    /**
     * 根据用户名查询数据信息
     * @param username 用户名
     * @return 返回根据用户名查询后的信息
     * @throws Exception
     */
    public User selectByName(String username) throws Exception;

    /**
     * 判断用户输入密码是否正确
     * @param username 用户名
     * @param password 用户密码
     * @return 返回根据用户名与用户密码查询后的信息
     * @throws Exception
     */
    public List<User> checkPassword(String username, String password) throws Exception;

    /**
     * 增加用户（注册方法）
     * @param user 用户实体
     * @throws Exception
     */
    public boolean addUser(User user) throws Exception;
}
