package com.nenusoftware.onlineexam.service.paper.impl;

import com.nenusoftware.onlineexam.entity.paper.Paper;
import com.nenusoftware.onlineexam.mapper.paper.PaperMapper;
import com.nenusoftware.onlineexam.service.paper.PaperService;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

/**
 * @Author:Liangll
 * @Description: PaperService的底层实现方法
 * @Date: 10:53 2020/6/15
 */
@Service
public class PaperServiceImpl implements PaperService {

    @Resource
    PaperMapper paperMapper;

    /**
     * 列出所有试卷
     * @return 返回List形式的试卷信息
     * @throws Exception 抛出错误类型
     */
    @Override
    public ArrayList<Paper> listAllPaper() throws Exception{
        ArrayList<Paper> paperList = new ArrayList<>();
        paperList = paperMapper.listAllPaper();
        return paperList;
    }

    /**
     * 列出所有已发布试卷
     * @param status 1：发布；0：不发布
     * @return 返回 List形式的试卷信息
     * @throws Exception 抛出错误类型
     */
    @Override
    public ArrayList<Paper> listPublishPaper(int status) throws Exception{
        return paperMapper.listPublishPaper(status);
    }

    /**
     * 增加试卷
     * @param paper 试卷实体
     * @throws Exception 抛出错误类型
     */
    @Override
    public void addPaper(Paper paper) throws Exception {
        paperMapper.addPaper(paper);
    }

    /**
     * 删除试卷
     * @param paperId 试卷编号
     * @throws Exception 抛出错误类型
     */
    @Override
    public void deletePaper(int paperId) throws Exception{
        paperMapper.deletePaper(paperId);
    }

    /**
     * 修改试卷
     * @param paper 试卷实体
     * @throws Exception 抛出错误类型
     */
    @Override
    public void updatePaper(Paper paper) throws Exception{
        paperMapper.updatePaper(paper);
    }

    /**
     * 模糊查询（查询试卷名称）
     * @param keyWord 输入查询的关键字
     * @return 返回List形式的试卷信息
     * @throws Exception 抛出错误类型
     */
    @Override
    public List<Paper> queryPaperName(String keyWord) throws Exception{
        List<Paper> paperlist = Collections.emptyList();
        keyWord = "%" + keyWord + "%";
        paperlist = paperMapper.queryPaperName(keyWord);
        return paperlist;
    }

    /**
     * 根据Id查询试卷名称
     * @param paperId 试卷编号
     * @return 返回Paper形式的试卷信息
     * @throws Exception 抛出错误类型
     */
    @Override
    public Paper queryPaperNameById(int paperId) throws Exception{
        return paperMapper.queryPaperNameById(paperId);
    }

    /**
     * 根据试卷名称查询试卷编号
     * @param paperName 试卷名称
     * @return 返回 Paper形式的试卷信息
     * @throws Exception 抛出错误类型
     */
    @Override
    public Paper queryPaperIdByName(String paperName) throws Exception{
        return paperMapper.queryPaperIdByName(paperName);
    }

    /**
     * 发布试卷
     * @param paper 试卷实体
     * @throws Exception 抛出错误类型
     */
    @Override
    public void publishPaper(Paper paper) throws Exception{
        paperMapper.publishPaper(paper);
    }

    /**
     * 从字符串中提取时间
     * @param str 待提取的字符串
     * @return 返回一个长度为6的string类型数组，里面的值分别是年月日时分秒
     * @throws Exception 抛出错误类型
     */
    @Override
    public String[] extractTime(String str) throws Exception{
        String[] time = new String[6];
        time[0] = str.substring(str.indexOf(":")+1, str.lastIndexOf("年"));
        time[1] = str.substring(str.indexOf("年")+1, str.lastIndexOf("月"));
        time[2] = str.substring(str.indexOf("月")+1, str.lastIndexOf("日"));
        time[3] = str.substring(str.indexOf("日")+1, str.lastIndexOf("时"));
        time[4] = str.substring(str.indexOf("时")+1, str.lastIndexOf("分"));
        time[5] = str.substring(str.indexOf("分")+1, str.lastIndexOf("秒"));
        return time;
    }
}
