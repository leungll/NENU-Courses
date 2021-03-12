package com.pandawork.service.User.impl;

import com.pandawork.common.entity.user.User;
import com.pandawork.common.utils.NFException;
import com.pandawork.core.common.exception.SSException;
import com.pandawork.core.common.log.LogClerk;
import com.pandawork.core.common.util.Assert;
import com.pandawork.core.framework.dao.CommonDao;
import com.pandawork.mapper.user.UserMapper;
import com.pandawork.service.User.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.transaction.annotation.Propagation;
import org.springframework.transaction.annotation.Transactional;

import java.util.Collections;
import java.util.List;

/**
 * @author : kongyy
 * @time : 2018/12/19 10:38
 */
@Service("userService")
public class UserServiceImpl implements UserService {

    @Autowired
    UserMapper userMapper;

    @Autowired
    protected CommonDao commonDao;


    @Override
    public List<User> listAll() throws SSException {
        List<User> userList = Collections.emptyList();
        try {
            userList = userMapper.listAll();
        } catch (Exception e) {
            LogClerk.errLog.error(e);
            throw SSException.get(NFException.SystemException, e);
        }
        return userList;
    }

    @Override
    public boolean addUser(User user) throws SSException {
        try {
            return userMapper.addUser(user);
        } catch (Exception e) {
            LogClerk.errLog.error(e);
            throw SSException.get(NFException.SystemException, e);
        }
    }

    @Override
    public boolean update(User user) throws SSException {
        try {
            return userMapper.update(user);
        } catch (Exception e) {
            LogClerk.errLog.error(e);
            throw SSException.get(NFException.SystemException, e);
        }
    }

    @Override
    public boolean update2(int id) throws SSException {
        try {
            return userMapper.update2(id);
        } catch (Exception e) {
            LogClerk.errLog.error(e);
            throw SSException.get(NFException.SystemException, e);
        }
    }

    @Override
    @Transactional(propagation = Propagation.REQUIRED, rollbackFor = {SSException.class, Exception.class, RuntimeException.class})
    public User selectByName(String username)throws SSException{
        if (Assert.isNull(username)) {
            return null;
        }
        try {
            return userMapper.selectByName(username);
        } catch (Exception e){
            LogClerk.errLog.error(e);
            throw SSException.get(NFException.QueryByNameFailed, e);
        }
    }

    @Override
    public boolean delById(int id) throws SSException {
        if (Assert.lessOrEqualZero(id)) {
            return false;
        }
        try {
            return userMapper.delById(id);
        } catch (Exception e) {
            LogClerk.errLog.error(e);
            throw SSException.get(NFException.DelStudentNull, e);
        }
    }

    @Override
    @Transactional(propagation = Propagation.REQUIRED, rollbackFor = {SSException.class, Exception.class, RuntimeException.class})
    public boolean pswIsTrue(String username,String password)throws SSException{
        boolean flag = false;
        try {
            List<User> list = userMapper.pswIsTrue(username,password);
            if(list.size()!=0){
                flag = true;
            }
        }catch (Exception e){
            LogClerk.errLog.error(e);
            throw SSException.get(NFException.PasswordIsWrong,e);
        }
        return flag;
    }
}

