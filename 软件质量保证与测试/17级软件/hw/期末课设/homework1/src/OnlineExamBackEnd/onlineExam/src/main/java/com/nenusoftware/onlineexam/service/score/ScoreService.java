package com.nenusoftware.onlineexam.service.score;

import com.nenusoftware.onlineexam.entity.score.Score;

import java.util.List;

/**
 * @Author:Liangll
 * @Description: ScoreService的接口层
 * @Date: 10:52 2020/6/16
 */
public interface ScoreService {

    /**
     * 增加成绩信息
     * @param score 成绩信息实体
     * @return 增加成功返回true，增加失败返回false
     * @throws Exception 抛出错误类型
     */
    public boolean addScore(Score score) throws Exception;

    /**
     * 删除成绩
     * @param scoreId 成绩编号
     * @return 删除成功返回true，删除失败返回false
     * @throws Exception 抛出错误类型
     */
    public boolean deleteScore(int scoreId) throws Exception;

    /**
     * 根据用户编号列出该用户对应的成绩
     * @param userId 用户编号
     * @return 返回List形式的成绩信息
     * @throws Exception 抛出错误类型
     */
    public List<Score> queryScoreByUser(int userId) throws Exception;

    /**
     * 根据试卷编号列出所有学生做该试卷的成绩
     * @param paperId 试卷编号
     * @return 返回List形式的成绩信息
     * @throws Exception 抛出错误类型
     */
    public List<Score> queryScoreByPaper(int paperId) throws Exception;

    /**
     * 根据试卷编号列出该试卷所有成绩在60分及以上的学生
     * @param paperId 试卷的id
     * @return 返回一个list（成绩在60分以上的信息）
     * @throws Exception 抛出错误类型
     */
    public List<Score> listScoreByMark1(int paperId) throws Exception;

    /**
     * 根据试卷编号列出该试卷所有成绩在60分以下的学生
     * @param paperId 试卷id
     * @return 返回一个list（成绩在60分以下的信息）
     * @throws Exception 抛出错误类型
     */
    public List<Score> listScoreByMark2(int paperId) throws Exception;

}
