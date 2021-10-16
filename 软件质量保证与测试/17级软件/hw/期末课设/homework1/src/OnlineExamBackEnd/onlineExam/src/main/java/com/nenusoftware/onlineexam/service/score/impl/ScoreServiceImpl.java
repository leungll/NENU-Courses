package com.nenusoftware.onlineexam.service.score.impl;

import com.nenusoftware.onlineexam.entity.score.Score;
import com.nenusoftware.onlineexam.mapper.score.ScoreMapper;
import com.nenusoftware.onlineexam.service.score.ScoreService;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.util.List;

/**
 * @Author:Liangll
 * @Description: ScoreService的底层实现方法
 * @Date: 10:53 2020/6/16
 */
@Service
public class ScoreServiceImpl implements ScoreService {

    @Resource
    ScoreMapper scoreMapper;

    /**
     * 增加成绩信息
     * @param score 成绩信息实体
     * @return 增加成功返回true，增加失败返回false
     * @throws Exception 抛出错误类型
     */
    @Override
    public boolean addScore(Score score) throws Exception {
        return scoreMapper.addScore(score);
    }

    /**
     * 删除成绩
     * @param scoreId 成绩编号
     * @return 删除成功返回true，删除失败返回false
     * @throws Exception 抛出错误类型
     */
    @Override
    public boolean deleteScore(int scoreId) throws Exception{
        return scoreMapper.deleteScore(scoreId);
    }

    /**
     * 根据用户编号列出该用户对应的成绩
     * @param userId 用户编号
     * @return 返回List形式的成绩信息
     * @throws Exception 抛出错误类型
     */
    @Override
    public List<Score> queryScoreByUser(int userId) throws Exception{
        return scoreMapper.queryScoreByUser(userId);
    }

    /**
     * 根据试卷编号列出所有学生做该试卷的成绩
     * @param paperId 试卷编号
     * @return 返回List形式的成绩信息
     * @throws Exception 抛出错误类型
     */
    @Override
    public List<Score> queryScoreByPaper(int paperId) throws Exception{
        return scoreMapper.queryScoreByPaper(paperId);
    }

    /**
     * 根据试卷编号列出该试卷所有成绩在60分及以上的学生
     * @param paperId 试卷的id
     * @return 返回一个list（成绩在60分以上的信息）
     * @throws Exception 抛出错误类型
     */
    @Override
    public List<Score> listScoreByMark1(int paperId) throws Exception{
        return scoreMapper.listScoreByMark1(paperId);

    }

    /**
     * 根据试卷编号列出该试卷所有成绩在60分以下的学生
     * @param paperId 试卷id
     * @return 返回一个list（成绩在60分以下的信息）
     * @throws Exception 抛出错误类型
     */
    @Override
    public List<Score> listScoreByMark2(int paperId) throws Exception{
        return scoreMapper.listScoreByMark2(paperId);
    }

}
