package com.nenusoftware.onlineexam.service.notice.impl;

import com.nenusoftware.onlineexam.entity.notice.Notice;
import com.nenusoftware.onlineexam.mapper.notice.NoticeMapper;
import com.nenusoftware.onlineexam.service.notice.NoticeService;
import org.springframework.stereotype.Service;

import javax.annotation.Resource;
import java.util.Collections;
import java.util.List;

/**
 * @Author:Liangll
 * @Description: NoticeService的底层实现方法
 * @Date: 20:30 2020/6/15
 */
@Service
public class NoticeServiceImpl implements NoticeService {

    @Resource
    NoticeMapper noticeMapper;

    /**
     * 列出所有公告信息
     * @return 返回List形式的公告信息
     * @throws Exception 抛出错误类型
     */
    @Override
    public List<Notice> listAllNotice() throws Exception{
        List<Notice> noticeList = Collections.emptyList();
        noticeList = noticeMapper.listAllNotice();
        return noticeList;
    }

    /**
     * 增加公告
     * @param notice 公告实体
     * @throws Exception 抛出错误类型
     */
    @Override
    public void addNotice(Notice notice) throws Exception {
        noticeMapper.addNotice(notice);
    }

    /**
     * 删除公告
     * @param noticeId 公告编号
     * @return 删除成功返回true，删除失败返回false
     * @throws Exception 抛出错误类型
     */
    @Override
    public boolean deleteNotice(int noticeId) throws Exception{
        return noticeMapper.deleteNotice(noticeId);
    }

    /**
     * 修改公告
     * @param notice 公告实体
     * @throws Exception 抛出错误类型
     */
    @Override
    public void updateNotice(Notice notice) throws Exception{
        noticeMapper.updateNotice(notice);
    }

    /**
     * 公告的模糊查询（可查询公告标题和公告内容）
     * @param keyWord 输入查询的关键字
     * @return 返回List形式的公告信息
     * @throws Exception 抛出错误类型
     */
    @Override
    public List<Notice> queryNotice(String keyWord) throws Exception{
        List<Notice> noticelist = Collections.emptyList();
        keyWord = "%" + keyWord + "%";
        noticelist = noticeMapper.queryNotice(keyWord);
        return noticelist;
    }

}
