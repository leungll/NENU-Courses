package com.nenusoftware.onlineexam.mapper;

import com.nenusoftware.onlineexam.entity.User;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.springframework.stereotype.Repository;

import java.util.List;


/**
 * @Author:Liangll
 * @Description: UserMapper的接口层
 * @Date: 22:08 2019/4/28
 */
@Mapper
@Repository
public interface UserMapper {

    /**
     * 根据用户名查询数据信息
     * @param username 用户名
     * @return 返回根据用户名查询后的信息
     * @throws Exception
     */
    public User selectByName(@Param("username")String username) throws Exception;

    /**
     * 判断用户输入密码是否正确
     * @param username 用户名
     * @param password 用户密码
     * @return 返回根据用户名与用户密码查询后的信息
     * @throws Exception
     */
    public List<User> checkPassword(@Param("username")String username, @Param("password")String password) throws Exception;

    /**
     * 增加用户（注册方法）
     * @param user 用户实体
     * @return 注册成功返回true，注册失败返回false
     * @throws Exception
     */
    public boolean addUser(@Param("user") User user) throws Exception;

}
