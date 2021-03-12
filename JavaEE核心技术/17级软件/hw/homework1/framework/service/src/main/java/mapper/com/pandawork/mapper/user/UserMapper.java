package com.pandawork.mapper.user;

import com.pandawork.common.entity.user.User;
import org.apache.ibatis.annotations.Param;

import java.util.List;

/**
 * @author : kongyy
 * @time : 2018/12/19 10:27
 */
public interface UserMapper {

    public boolean addUser(@Param("user") User user) throws Exception;

    public boolean update(@Param("user") User user) throws Exception;

    public boolean update2(@Param("id") int id) throws Exception;

    public boolean delById(@Param("id") int id) throws Exception;

    public User selectByName(@Param("username") String username) throws Exception;

    public List<User> listAll() throws Exception;

    public List<User>pswIsTrue(@Param("username") String username, @Param("password") String password) throws Exception;


}
