package com.nenusoftware.onlineexam.service.answer;

import com.nenusoftware.onlineexam.entity.answer.Answer;

import java.util.List;

/**
 * @Author:kongyy
 * @Description: AnswerService的接口层
 * @Date: 20:06 2020/6/15
 */
public interface AnswerService {

    /**
     * 列出所有答题信息
     * @return 返回List形式的答题信息
     * @throws Exception 抛出错误类型
     */
    public List<Answer> listAllAnswer() throws Exception;


    /**
     * 添加答题信息
     * @param answer answer实体
     * @return 添加成功，返回true，添加失败则返回false
     * @throws Exception 抛出错误类型
     */
    public boolean addAnswer(Answer answer) throws Exception;


    /**
     * 删除某条答题信息
     * @param answerId 答案的id
     * @return 删除成功返回true，删除失败返回false
     * @throws Exception 抛出错误类型
     */
    public boolean deleteAnswer(int answerId) throws Exception;

}
