package com.nenusoftware.onlineexam.service.wrong.impl;

import com.nenusoftware.onlineexam.entity.wrong.Wrong;
import com.nenusoftware.onlineexam.mapper.wrong.WrongMapper;
import com.nenusoftware.onlineexam.service.wrong.WrongService;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.util.LinkedList;
import java.util.List;

/**
 * @Author:kongyy
 * @Description: WrongService的底层实现方法
 * @Date: 23:49 2020/6/16
 */
@Service
public class WrongServiceImpl implements WrongService {

    @Resource
    WrongMapper wrongMapper;

    /**
     * 添加错题
     * @param wrong 要添加的wrong对象
     * @throws Exception 抛出错误类型
     */
    @Override
    public void addWrong(Wrong wrong) throws Exception{
        wrongMapper.addWrong(wrong);
    }

    /**
     * 列出用户错题
     * @param userId 用户id
     * @return 列出这个用户的错题
     * @throws Exception 抛出错误类型
     */
    @Override
    public List<Wrong> listWrongByUserId(int userId) throws Exception{
        List<Wrong> wrongList = new LinkedList<>();
        wrongList = wrongMapper.listWrongByUserId(userId);
        return  wrongList;
    }

    /**
     * 删除错题
     * @param wrongId 错题id
     * @return 如果删除成功，则返回true，否则返回false
     * @throws Exception 抛出错误类型
     */
    @Override
    public boolean deleteWrong(int wrongId) throws Exception{
        return wrongMapper.deleteWrong(wrongId);
    }
}
