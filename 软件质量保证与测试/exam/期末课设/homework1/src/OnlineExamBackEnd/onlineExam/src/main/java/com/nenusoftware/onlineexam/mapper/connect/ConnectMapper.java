package com.nenusoftware.onlineexam.mapper.connect;

import com.nenusoftware.onlineexam.entity.connect.Connect;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.springframework.stereotype.Repository;

import java.util.List;

/**
 * @Author: Liangll
 * @Description: ConnectMapper的接口层
 * @Date: 23:03 2020/6/17
 */
@Mapper
@Repository
public interface ConnectMapper {

    /**
     * 通过试卷编号列出试卷详细信息
     * @param paperId 试卷编号
     * @param exerciseType 试题类型
     * @return 返回 List形式的试卷详细信息
     * @throws Exception 报错信息
     */
    public List<Connect> listAllConnect(@Param("paperId") int paperId, @Param("exerciseType") String exerciseType) throws Exception;

    /**
     * 增加试卷详细信息
     * @param connect 试卷详细信息实体
     * @return 增加成功返回true，增加失败返回false
     * @throws Exception 报错信息
     */
    public boolean addConnect(@Param("connect") Connect connect) throws Exception;

}
