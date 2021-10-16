package com.nenusoftware.onlineexam.mapper.score;

import com.nenusoftware.onlineexam.entity.score.Score;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.springframework.stereotype.Repository;

import java.util.List;

/**
 * @Author:Kongyy
 * @Description: ScoreMapper的接口层
 * @Date: 12:08 2020/6/16
 */
@Mapper
@Repository
public interface ScoreMapper {

    /**
     * 增加成绩信息
     * @param score 成绩信息实体
     * @return 增加成功返回true，增加失败返回false
     * @throws Exception 报错信息
     */
    public boolean addScore(@Param("score") Score score) throws Exception;

    /**
     * 删除成绩
     * @param scoreId 成绩编号
     * @return 删除成功返回true，删除失败返回false
     * @throws Exception 报错信息
     */
    public boolean deleteScore(@Param("scoreId") int scoreId) throws Exception;

    /**
     * 根据用户编号列出该用户对应的成绩
     * @param userId 用户编号
     * @return 返回List形式的成绩信息
     * @throws Exception 报错信息
     */
    public List<Score> queryScoreByUser(@Param("userId") int userId) throws Exception;

    /**
     * 根据试卷编号列出所有学生做该试卷的成绩
     * @param paperId 试卷编号
     * @return 返回List形式的成绩信息
     * @throws Exception 报错信息
     */
    public List<Score> queryScoreByPaper(@Param("paperId") int paperId) throws Exception;

    /**
     * 列出某张卷子及格的学生
     * @param paperId 试卷编号
     * @return 成绩信息
     * @throws Exception 报错信息
     */
    public List<Score> listScoreByMark1(@Param("paperId") int paperId) throws Exception;

    /**
     * 列出某张卷子未及格的学生
     * @param paperId 时间编号
     * @return 成绩信息
     * @throws Exception 报错信息
     */
    public List<Score> listScoreByMark2(@Param("paperId") int paperId) throws Exception;

}
