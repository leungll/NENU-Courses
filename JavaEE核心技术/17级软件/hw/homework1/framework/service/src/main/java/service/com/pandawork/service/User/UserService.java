package com.pandawork.service.User;

import com.pandawork.common.entity.user.User;
import com.pandawork.core.common.exception.SSException;

import java.util.List;

/**
 * @author : kongyy
 * @time : 2018/12/19 10:38
 */

public interface UserService {

    public List<User> listAll( ) throws SSException;

    public boolean addUser(User user) throws SSException;

    public boolean update(User user) throws SSException;

    public boolean update2(int id) throws SSException;

    public User selectByName(String username) throws SSException;

    public boolean delById(int id) throws SSException;

    public boolean pswIsTrue(String username, String password) throws Exception;
}
