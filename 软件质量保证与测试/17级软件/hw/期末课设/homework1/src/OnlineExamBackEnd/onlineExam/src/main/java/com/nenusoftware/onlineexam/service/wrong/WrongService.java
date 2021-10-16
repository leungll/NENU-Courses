package com.nenusoftware.onlineexam.service.wrong;

import com.nenusoftware.onlineexam.entity.wrong.Wrong;

import java.util.List;

/**
 * @Author:kongyy
 * @Description: WrongService的接口层
 * @Date: 23:49 2020/6/16
 */
public interface WrongService {

    /**
     * 添加错题
     * @param wrong 要添加的wrong对象
     * @throws Exception 抛出错误类型
     */
    public void addWrong(Wrong wrong) throws Exception;

    /**
     * 列出用户错题
     * @param userId 用户id
     * @return 返回通过用户id查找对应该用户的错题
     * @throws Exception 抛出错误类型
     */
    public List<Wrong> listWrongByUserId(int userId) throws Exception;

    /**
     * 删除错题
     * @param wrongId 错题id
     * @return 如果删除成功，则返回true，否则返回false
     * @throws Exception 抛出错误类型
     */
    public boolean deleteWrong(int wrongId) throws Exception;
}
