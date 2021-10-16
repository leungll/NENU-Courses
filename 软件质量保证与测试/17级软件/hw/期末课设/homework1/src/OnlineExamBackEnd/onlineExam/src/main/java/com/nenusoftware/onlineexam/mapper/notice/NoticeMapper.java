package com.nenusoftware.onlineexam.mapper.notice;

import com.nenusoftware.onlineexam.entity.notice.Notice;
import org.apache.ibatis.annotations.Mapper;
import org.apache.ibatis.annotations.Param;
import org.springframework.stereotype.Repository;

import java.util.List;

/**
 * @Author:Kongyy
 * @Description: NoticeMapper的接口层
 * @Date: 22:08 2020/6/19
 */
@Mapper
@Repository
public interface NoticeMapper {

    /**
     * 列出所有公告信息
     * @return 返回List形式的公告信息
     * @throws Exception 报错信息
     */
    public List<Notice> listAllNotice() throws Exception;

    /**
     * 增加公告
     * @param notice 公告实体
     * @return 增加成功返回true，增加失败返回false
     * @throws Exception 报错信息
     */
    public boolean addNotice(@Param("notice") Notice notice) throws Exception;

    /**
     * 删除公告
     * @param noticeId 公告编号
     * @return 删除成功返回true，删除失败返回false
     * @throws Exception 报错信息
     */
    public boolean deleteNotice(@Param("noticeId") int noticeId) throws Exception;

    /**
     * 修改公告
     * @param notice 公告实体
     * @return 修改成功返回true，修改失败返回false
     * @throws Exception 报错信息
     */
    public boolean updateNotice(@Param("notice") Notice notice) throws Exception;

    /**
     * 公告的模糊查询（可查询公告标题和公告内容）
     * @param keyWord 输入查询的关键字
     * @return 返回List形式的公告信息
     * @throws Exception 报错信息
     */
    public List<Notice> queryNotice(@Param("keyWord") String keyWord) throws Exception;

}
