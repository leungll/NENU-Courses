package com.nenusoftware.onlineexam.service.paperdetail;

import com.alibaba.fastjson.JSONArray;
import com.nenusoftware.onlineexam.entity.paperdetail.PaperDetail;
import org.apache.ibatis.annotations.Param;

import java.util.List;

/**
 * @Author:kongyy
 * @Description: PaperDetailService的接口层
 * @Date: 10:02 2020/6/16
 */
public interface PaperDetailService {

    /**
     * 列出所有试卷详细信息
     * @return 返回List形式的试卷详细信息
     * @throws Exception 抛出错误类型
     */
    public List<PaperDetail> listAllPaperDetail() throws Exception;

    /**
     * 根据试卷编号列出试卷详细信息
     * @param paperId 试卷编号
     * @return 返回List形式的试卷详细信息
     * @throws Exception 抛出错误类型
     */
    public List<PaperDetail> listPaperDetailByPaperId(int paperId) throws Exception;

    /**
     * 增加试卷详细信息
     * @param paperDetail 试卷详细信息实体
     * @throws Exception 抛出错误类型
     */
    public void addPaperDetail(PaperDetail paperDetail) throws Exception;

    /**
     * 删除试卷详细信息
     * @param paperDetailId 试卷详细信息编号
     * @return 删除成功返回true，删除失败返回false
     * @throws Exception 抛出错误类型
     */
    public boolean deletePaperDetail(int paperDetailId) throws Exception;

    /**
     * 修改试卷详细信息
     * @param paperDetail 试卷详细信息实体
     * @throws Exception 抛出错误类型
     */
    public void updatePaperDetail(PaperDetail paperDetail) throws Exception;

    /**
     * 模糊查询（查询试卷题目的内容或类型）
     * @param keyWord 输入查询的关键字
     * @return 返回List形式的试卷详细信息
     * @throws Exception 抛出错误类型
     */
    public List<PaperDetail> queryPaperDetail(String keyWord) throws Exception;

    /**
     * 根据题目类型列出试卷详细信息
     * @param exerciseType 题目类型
     * @return 返回List形式的试卷详细信息
     * @throws Exception 抛出错误类型
     */
    public List<PaperDetail> queryExerciseByTypes(String exerciseType) throws Exception;

    /**
     * 根据试卷Id查询题目选项
     * @param paperDetailId 试卷详细信息编号
     * @return 返回List形式的试卷详细信息
     * @throws Exception 抛出错误类型
     */
    public List<PaperDetail> queryExerciseItemsById(int paperDetailId) throws Exception;

    /**
     * 根据题目id查找某道题的答案以及分值
     * @param paperDetailId 题目id
     * @return 某道题的答案以及分值
     * @throws Exception 抛出错误类型
     */
    public PaperDetail queryQuestion(int paperDetailId) throws Exception;

    /**
     * 前端传回做题信息，进行判分，并将错误的题目存入错题集中
     * @param jsonArray 学生做题信息，其中包含两项信息，学生答案：answer和这道题目的id：paperDetailId
     * @param userId 学生的id
     * @return 返回学生的分数
     * @throws Exception 抛出错误类型
     */
    public int judgeQuestion(JSONArray jsonArray, int userId) throws Exception;

    /**
     * 根据试题内容获取题目编号
     * @param content 试题内容
     * @return 题目编号
     * @throws Exception 抛出错误类型
     */
    public PaperDetail queryIdByContent(@Param("content") String content) throws Exception;

//    /**
//     * 根据试卷编号列出已发布试卷详细信息
//     * @param paperId 试卷编号
//     * @param status 是否发布
//     * @return 返回 List形式的试卷详细信息
//     * @throws Exception
//     */
//    public List<PaperDetail> listPublishPaperByPaperId(int paperId, int status) throws Exception;

}
