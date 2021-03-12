package com.nenusoftware.onlineexam.service.impl;

import com.nenusoftware.onlineexam.entity.User;
import com.nenusoftware.onlineexam.mapper.UserMapper;
import com.nenusoftware.onlineexam.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

/**
 * @Author:Liangll
 * @Description: UserService的底层实现方法
 * @Date: 10:53 2019/5/3
 */
@Service
public class UserServiceImpl implements UserService {

    @Autowired
    UserMapper userMapper;

    /**
     * 根据用户名查询数据信息
     * @param username 用户名
     * @return 返回根据用户名查询后的信息
     * @throws Exception
     */
    @Override
    public User selectByName(String username) throws Exception {
        return userMapper.selectByName(username);
    }

    /**
     * 判断用户输入密码是否正确
     * @param username 用户名
     * @param password 用户密码
     * @return 回根据用户名与用户密码查询后的信息
     * @throws Exception
     */
    @Override
    public List<User> checkPassword(String username, String password) throws Exception{
        boolean flag = true;
        List<User> list = userMapper.checkPassword(username,password);
        return list;
    }

    /**
     * 增加用户（注册方法）
     * @param user 用户实体
     * @return 注册成功返回true，注册失败返回false
     * @throws Exception
     */
    @Override
    public boolean addUser(User user) throws Exception {
        if(userMapper.addUser(user)){
            return true;
        }else {
            return false;
        }
    }
}
