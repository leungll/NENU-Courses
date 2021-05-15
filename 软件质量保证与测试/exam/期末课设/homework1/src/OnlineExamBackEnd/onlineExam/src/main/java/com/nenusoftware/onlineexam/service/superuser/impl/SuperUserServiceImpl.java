package com.nenusoftware.onlineexam.service.superuser.impl;

import com.nenusoftware.onlineexam.mapper.superuser.SuperUserMapper;
import com.nenusoftware.onlineexam.mapper.user.UserMapper;
import com.nenusoftware.onlineexam.service.superuser.SuperUserService;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;

/**
 * @Author:kongyy
 * @Description: SuperUserService的底层实现方法
 * @Date: 21:40 2020/6/16
 */
@Service
public class SuperUserServiceImpl implements SuperUserService {

    @Resource
    SuperUserMapper superUserMapper;

    /**
     * 修改用户权限
     * @param userId 用户id
     * @throws Exception 抛出错误类型
     */
    @Override
    public void updateUserPower(int userId) throws Exception{
        superUserMapper.updateUserPower(userId);
    }

    /**
     * 删除用户
     * @param userId 用户id
     * @return 如果删除成功，则返回true，否则返回false
     * @throws Exception 抛出错误类型
     */
    @Override
    public boolean deleteUser(int userId) throws Exception{
        return superUserMapper.deleteUser(userId);
    }

}
