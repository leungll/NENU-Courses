package com.nenusoftware.onlineexam.mapper.paper;

import com.nenusoftware.onlineexam.entity.paper.Paper;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.springframework.stereotype.Repository;

import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.List;

/**
 * @Author:Liangll
 * @Description: PaperMapper的接口层
 * @Date: 17:29 2020/6/15
 */
@Mapper
@Repository
public interface PaperMapper {

    /**
     * 列出所有试卷
     * @return 返回List形式的试卷信息
     * @throws Exception 报错信息
     */
    public ArrayList<Paper> listAllPaper() throws Exception;

    /**
     * 列出所有已发布试卷
     * @param status 1：发布；0：不发布
     * @return 返回 List形式的试卷信息
     * @throws Exception 报错信息
     */
    public ArrayList<Paper> listPublishPaper(@Param("status") int status) throws Exception;

    /**
     * 增加试卷
     * @param paper 试卷实体
     * @return 增加成功返回 true，增加失败返回 false
     * @throws Exception 报错信息
     */
    public boolean addPaper(@Param("paper") Paper paper) throws Exception;

    /**
     * 删除试卷
     * @param paperId 试卷编号
     * @return 删除成功返回true，删除失败返回false
     * @throws Exception 报错信息
     */
    public boolean deletePaper(@Param("paperId") int paperId) throws Exception;

    /**
     * 修改试卷
     * @param paper 试卷实体
     * @return 修改成功返回true，修改失败返回false
     * @throws Exception 报错信息
     */
    public boolean updatePaper(@Param("paper") Paper paper) throws Exception;

    /**
     * 模糊查询（查询试卷名称）
     * @param keyWord 输入查询的关键字
     * @return 返回List形式的试卷信息
     * @throws Exception 报错信息
     */
    public List<Paper> queryPaperName(@Param("keyWord") String keyWord) throws Exception;

    /**
     * 根据 Id查询试卷名称
     * @param paperId 试卷编号
     * @return 返回Paper形式的试卷信息
     * @throws Exception 报错信息
     */
    public Paper queryPaperNameById(@Param("paperId") int paperId) throws Exception;

    /**
     * 根据试卷名称查询试卷编号
     * @param paperName 试卷名称
     * @return 返回 Paper形式的试卷信息
     * @throws Exception 报错信息
     */
    public Paper queryPaperIdByName(@Param("paperName") String paperName) throws Exception;

    /**
     * 发布试卷
     * @param paper 试卷实体
     * @return 发布成功返回true，发布失败返回false
     * @throws Exception 报错信息
     */
    public boolean publishPaper(@Param("paper") Paper paper) throws Exception;

}
