package com.nenusoftware.onlineexam.mapper.paperdetail;

import com.nenusoftware.onlineexam.entity.paperdetail.PaperDetail;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.springframework.stereotype.Repository;

import java.util.List;

/**
 * @Author:Liangll
 * @Description: PaperDetailMapper的接口层
 * @Date: 11:29 2020/6/18
 */
@Mapper
@Repository
public interface PaperDetailMapper {

    /**
     * 列出所有试卷详细信息
     * @return 返回List形式的试卷详细信息
     * @throws Exception 报错信息
     */
    public List<PaperDetail> listAllPaperDetail() throws Exception;

    /**
     * 根据试卷编号列出试卷详细信息
     * @param paperId 试卷编号
     * @return 返回List形式的试卷详细信息
     * @throws Exception 报错信息
     */
    public List<PaperDetail> listPaperDetailByPaperId(@Param("paperId") int paperId) throws Exception;

    /**
     * 增加试卷详细信息
     * @param paperDetail 试卷详细信息实体
     * @throws Exception 报错信息
     */
    public void addPaperDetail(@Param("paperDetail") PaperDetail paperDetail) throws Exception;

    /**
     * 删除试卷详细信息
     * @param paperDetailId 试卷详细信息编号
     * @return 删除成功返回true，删除失败返回false
     * @throws Exception 报错信息
     */
    public boolean deletePaperDetail(@Param("paperDetailId") int paperDetailId) throws Exception;

    /**
     * 修改试卷详细信息
     * @param paperDetail 试卷详细信息实体
     * @throws Exception 报错信息
     */
    public void updatePaperDetail(@Param("paperDetail") PaperDetail paperDetail) throws Exception;

    /**
     * 模糊查询（查询试卷题目的内容或类型）
     * @param keyWord 输入查询的关键字
     * @return 返回List形式的试卷详细信息
     * @throws Exception 报错信息
     */
    public List<PaperDetail> queryPaperDetail(@Param("keyWord") String keyWord) throws Exception;

    /**
     * 根据题目类型列出试卷详细信息
     * @param exerciseType 题目类型
     * @return 返回List形式的试卷详细信息
     * @throws Exception 报错信息
     */
    public List<PaperDetail> queryExerciseByTypes(@Param("exerciseType") String exerciseType) throws Exception;

    /**
     * 根据试卷Id查询题目选项
     * @param paperDetailId 试卷详细信息编号
     * @return 返回List形式的试卷详细信息
     * @throws Exception 报错信息
     */
    public List<PaperDetail> queryExerciseItemsById(@Param("paperDetailId") int paperDetailId) throws Exception;

    /**
     * 根据试题内容获取题目编号
     * @param content 试题内容
     * @return 题目编号
     * @throws Exception 报错信息
     */
    public PaperDetail queryIdByContent(@Param("content") String content) throws Exception;

    /**
     * 根据题目id查找某道题的答案以及分值
     * @param paperDetailId 题目id
     * @return 某道题的答案以及分值
     * @throws Exception 报错信息
     */
    public List<PaperDetail> queryQuestion(@Param("paperDetailId") int paperDetailId) throws Exception;

}
