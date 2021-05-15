package com.nenusoftware.onlineexam.mapper.answer;

import com.nenusoftware.onlineexam.entity.answer.Answer;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.springframework.stereotype.Repository;

import java.util.List;

/**
 * @Author:Liangll
 * @Description: AnswerMapper的接口层
 * @Date: 22:08 2020/6/18
 */
@Mapper
@Repository
public interface AnswerMapper {

    /**
     * 列出所有答题信息
     * @return 返回List形式的答题信息
     * @throws Exception 报错信息
     */
    public List<Answer> listAllAnswer() throws Exception;

    /**
     * 增加答题信息
     * @param answer 答题信息实体
     * @return 增加成功返回true，增加失败返回false
     * @throws Exception 报错信息
     */
    public boolean addAnswer(@Param("answer") Answer answer) throws Exception;

    /**
     * 删除某条答题信息
     * @param answerId 答案编号
     * @return 删除成功返回true，删除失败返回false
     * @throws Exception 报错信息
     */
    public boolean deleteAnswer(@Param("answerId") int answerId) throws Exception;

}
