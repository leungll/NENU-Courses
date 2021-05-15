package com.nenusoftware.onlineexam.service.paper;

import com.nenusoftware.onlineexam.entity.paper.Paper;

import java.util.ArrayList;
import java.util.List;

/**
 * @Author:Liangll
 * @Description: PaperService的接口层
 * @Date: 10:52 2020/6/15
 */
public interface PaperService {

    /**
     * 列出所有试卷
     * @return 返回 List形式的试卷信息
     * @throws Exception
     */
    public ArrayList<Paper> listAllPaper() throws Exception;

    /**
     * 列出所有已发布试卷
     * @param status 1：发布；0：不发布
     * @return 返回 List形式的试卷信息
     * @throws Exception 抛出错误类型
     */
    public ArrayList<Paper> listPublishPaper(int status) throws Exception;

    /**
     * 增加试卷
     * @param paper 试卷实体
     * @throws Exception 抛出错误类型
     */
    public void addPaper(Paper paper) throws Exception;

    /**
     * 删除试卷
     * @param paperId 试卷编号
     * @throws Exception 抛出错误类型
     */
    public void deletePaper(int paperId) throws Exception;

    /**
     * 修改试卷
     * @param paper 试卷实体
     * @throws Exception 抛出错误类型
     */
    public void updatePaper(Paper paper) throws Exception;

    /**
     * 模糊查询（查询试卷名称）
     * @param keyWord 输入查询的关键字
     * @return 返回 List形式的试卷信息
     * @throws Exception 抛出错误类型
     */
    public List<Paper> queryPaperName(String keyWord) throws Exception;

    /**
     * 根据Id查询试卷名称
     * @param paperId 试卷编号
     * @return 返回 Paper形式的试卷信息
     * @throws Exception 抛出错误类型
     */
    public Paper queryPaperNameById(int paperId) throws Exception;

    /**
     * 根据试卷名称查询试卷编号
     * @param paperName 试卷名称
     * @return 返回 Paper形式的试卷信息
     * @throws Exception 抛出错误类型
     */
    public Paper queryPaperIdByName(String paperName) throws Exception;

    /**
     * 发布试卷
     * @param paper 试卷实体
     * @throws Exception 抛出错误类型
     */
    public void publishPaper(Paper paper) throws Exception;

    /**
     * 提取字符串中的年月日时分秒并存入数组
     * @param time 待提取的时间字符串
     * @return 返回一个长度为6的string类型数组，里面的值分别是年月日时分秒
     * @throws Exception 抛出错误类型
     */
    public String[] extractTime(String time) throws Exception;

}
