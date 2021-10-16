package com.nenusoftware.onlineexam.controller.notice;

import com.nenusoftware.onlineexam.entity.notice.Notice;
import com.nenusoftware.onlineexam.service.notice.NoticeService;
import com.nenusoftware.onlineexam.service.user.UserService;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

import javax.annotation.Resource;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;
import java.util.Date;
import java.util.List;

/**
 * @Author:Kongyy
 * @Description: NoticeController层（与前端页面进行交互）
 * @Date: 15:54 2020/6/11
 */
@CrossOrigin(allowCredentials = "true")
@Controller
@RequestMapping("/notice")
public class NoticeController {

    @Resource
    NoticeService noticeService;

    @Resource
    UserService userService;

    /**
     * 列出所有公告信息
     * @return 返回List形式的公告信息
     */
    @ResponseBody
    @RequestMapping("/listAllNotice")
    public List<Notice> listAllNotice(){
        List<Notice> noticeList = null;
        try {
            noticeList = noticeService.listAllNotice();
        }catch (Exception e){
            e.printStackTrace();
        }
        return noticeList;
    }

    /**
     * 增加公告
     * @param title 公告标题
     * @param content 公告内容
     * @param request Http请求
     */
    @ResponseBody
    @RequestMapping("/addNotice")
    public void addNotice(String title, String content, HttpServletRequest request){
        try {
            HttpSession session = request.getSession();
            String username = String.valueOf(session.getAttribute("usernameSession"));
            int userId = userService.queryIdByUsername(username).getUserId();

            Notice notice = new Notice();

            notice.setUserId(userId);
            notice.setTitle(title);
            notice.setContent(content);
            Date date = new Date();
            String createTimeStr = date.toString();
            notice.setCreateTime(createTimeStr);

            noticeService.addNotice(notice);
        }catch (Exception e){
            e.printStackTrace();
            System.out.println("增加公告失败！");
        }
    }

    /**
     * 删除公告
     * @param noticeIdStr 公告编号
     */
    @ResponseBody
    @RequestMapping("/deleteNotice")
    public void deleteNotice(String noticeIdStr) {
        int noticeId = Integer.parseInt(noticeIdStr);
        try {
            noticeService.deleteNotice(noticeId);
        }catch (Exception e){
            e.printStackTrace();
            System.out.println("删除公告失败！");
        }
    }

    /**
     * 修改公告
     * @param noticeIdStr 公告编号
     * @param title 公告标题
     * @param content 公告内容
     * @param request Http请求
     */
    @ResponseBody
    @RequestMapping("/updateNotice")
    public void updateNotice(String noticeIdStr, String title, String content, HttpServletRequest request) {
        int noticeId = Integer.parseInt(noticeIdStr);
        try {
            HttpSession session = request.getSession();
            String username = String.valueOf(session.getAttribute("usernameSession"));
            int userId = userService.queryIdByUsername(username).getUserId();

            Notice notice = new Notice();

            notice.setNoticeId(noticeId);
            notice.setUserId(userId);
            notice.setTitle(title);
            notice.setContent(content);
            Date date = new Date();
            String createTimeStr = date.toString();
            notice.setCreateTime(createTimeStr);
            noticeService.updateNotice(notice);
        }catch (Exception e){
            e.printStackTrace();
            System.out.println("修改公告失败！");
        }
    }

    /**
     * 公告的模糊查询（可查询公告标题和公告内容）
     * @param keyStr 输入查询的关键字
     * @return 返回公告完整信息
     */
    @ResponseBody
    @RequestMapping("/queryNotice")
    public List<Notice> queryNotice(String keyStr){
        List<Notice> noticeList = null;
        try {
            noticeList = noticeService.queryNotice(keyStr);
        }catch (Exception e){
            e.printStackTrace();
        }
        return noticeList;
    }
}
