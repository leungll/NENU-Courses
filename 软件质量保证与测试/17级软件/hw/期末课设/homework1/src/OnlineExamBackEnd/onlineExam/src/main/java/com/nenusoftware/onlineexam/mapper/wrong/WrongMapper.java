package com.nenusoftware.onlineexam.mapper.wrong;

import com.nenusoftware.onlineexam.entity.wrong.Wrong;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.springframework.stereotype.Repository;

import java.util.List;

/**
 * @Author:Kongyy
 * @Description: WrongMapper的接口层
 * @Date: 18:40 2020/6/16
 */
@Mapper
@Repository
public interface WrongMapper {

    /**
     * 添加错题
     * @param wrong 错题信息
     * @return 是否添加成功
     * @throws Exception 报错信息
     */
    public boolean addWrong(@Param("wrong")Wrong wrong) throws Exception;

    /**
     * 列出用户错题
     * @param userId 用户编号
     * @return 错题信息
     * @throws Exception 报错信息
     */
    public List<Wrong> listWrongByUserId(@Param("userId") int userId) throws Exception;

    /**
     * 删除错题
     * @param wrongId 错题编号
     * @return 是否删除成功
     * @throws Exception 报错信息
     */
    public boolean deleteWrong(@Param("wrongId") int wrongId) throws Exception;
}
