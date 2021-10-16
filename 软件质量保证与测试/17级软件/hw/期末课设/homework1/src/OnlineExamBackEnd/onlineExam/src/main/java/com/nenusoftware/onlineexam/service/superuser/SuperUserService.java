package com.nenusoftware.onlineexam.service.superuser;

/**
 * @Author:kongyy
 * @Description: SuperUserService的接口层
 * @Date: 21:39 2020/6/16
 */
public interface SuperUserService {

    /**
     * 修改用户权限
     * @param userId 用户id
     * @throws Exception 抛出错误类型
     */
    public void updateUserPower(int userId) throws Exception;

    /**
     * 删除用户
     * @param userId 用户id
     * @return 如果删除成功，则返回true，否则返回false
     * @throws Exception 抛出错误类型
     */
    public boolean deleteUser(int userId) throws Exception;
}
