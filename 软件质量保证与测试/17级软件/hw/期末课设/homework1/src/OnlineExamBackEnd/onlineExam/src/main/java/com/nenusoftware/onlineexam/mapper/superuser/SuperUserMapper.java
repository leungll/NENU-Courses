package com.nenusoftware.onlineexam.mapper.superuser;

import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.springframework.stereotype.Repository;

/**
 * @Author:Kongyy
 * @Description: ScoreMapper的接口层
 * @Date: 12:40 2020/6/16
 */
@Mapper
@Repository
public interface SuperUserMapper {

    /**
     * 修改用户权限
     * @param userId 用户编号
     * @return 是否修改成功
     * @throws Exception 报错信息
     */
    public boolean updateUserPower(@Param("userId") int userId) throws Exception;

    /**
     * 删除用户
     * @param userId 用户编号
     * @return 是否修改成功
     * @throws Exception 报错信息
     */
    public boolean deleteUser(@Param("userId") int userId) throws Exception;

}
