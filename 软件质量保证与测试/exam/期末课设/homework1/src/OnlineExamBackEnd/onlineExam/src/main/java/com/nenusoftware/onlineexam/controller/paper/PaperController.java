package com.nenusoftware.onlineexam.controller.paper;

import com.nenusoftware.onlineexam.controller.user.UserController;
import com.nenusoftware.onlineexam.entity.connect.Connect;
import com.nenusoftware.onlineexam.entity.paper.Paper;
import com.nenusoftware.onlineexam.service.connect.ConnectService;
import com.nenusoftware.onlineexam.service.paper.PaperService;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

import javax.annotation.Resource;
import javax.servlet.http.HttpServletRequest;
import java.util.ArrayList;
import java.util.List;

/**
 * @Author:Liangll
 * @Description: PaperController层（与前端页面进行交互）
 * @Date: 15:54 2020/6/15
 */
@CrossOrigin(allowCredentials = "true")
@Controller
@RequestMapping("/paper")
public class PaperController {

    @Resource
    PaperService paperService;

    @Resource
    ConnectService connectService;

    @Resource
    UserController userController;

    /**
     * 列出所有试卷
     * @param request Http请求
     * @return 返回 List形式的试卷信息
     */
    @RequestMapping("/listAllPaper")
    @ResponseBody
    public ArrayList<Paper> listAllPaper(HttpServletRequest request){
        ArrayList<Paper> paperList = new ArrayList<>();
        int result = userController.judgePower(request);
        if(result == 1 || result == 2){
            try {
                paperList = paperService.listAllPaper();
            }catch (Exception e){
                e.printStackTrace();
            }
        }
        else{
            Paper paper = new Paper();
            paper.setPaperName("您未登录或没有权限");
            paperList.add(paper);
        }
        return paperList;
    }

    /**
     * 列出所有已发布试卷 (1：发布；0：不发布)
     * @param request HTTP请求头
     * @return 返回 List形式的试卷信息
     */
    @RequestMapping("/listPublishPaper")
    @ResponseBody
    public List<Paper> listPublishPaper(HttpServletRequest request){
        int result = userController.judgePower(request);
        ArrayList<Paper> paperList = new ArrayList<>();
        if(result != -1){
            try {
                paperList = paperService.listPublishPaper(1);
            }catch (Exception e){
                e.printStackTrace();
            }
        }
        else{
            Paper paper = new Paper();
            paper.setPaperName("您未登录!");
            paperList.add(paper);
        }
        return paperList;
    }

    /**
     * 增加试卷
     * @param paperName 试卷名称
     * @param request HTTP请求头
     * @return 试卷编号
     */
    @ResponseBody
    @RequestMapping("/addPaper")
    public int addPaper(String paperName, HttpServletRequest request){
        int result = userController.judgePower(request);
        int paperId = -1;
        if(result == 1){
            try {
                Paper paper = new Paper();
                paper.setPaperName(paperName);
                paper.setStatus(0);
                paper.setBeginTime(null);
                paper.setDuration(null);
                paperService.addPaper(paper);
                paperId = paperService.queryPaperIdByName(paperName).getPaperId();
                Connect connect = new Connect();
                System.out.println(paperId);
                connect.setPaperId(paperId);
                connect.setPaperDetailId(0);
                connectService.addConnect(connect);
            }catch (Exception e){
                e.printStackTrace();
                System.out.println("增加试卷失败！");
            }
        }
        else{
            System.out.println("您未登录或没有权限");
        }
        return paperId;
    }

    /**
     * 删除试卷
     * @param paperIdStr 试卷编号
     * @param request HTTP请求头
     * @return 报错信息
     */
    @ResponseBody
    @RequestMapping("/deletePaper")
    public String deletePaper(String paperIdStr, HttpServletRequest request) {
        int result = userController.judgePower(request);
        int paperId = Integer.parseInt(paperIdStr);
        if(result == 1){
            try {
                paperService.deletePaper(paperId);
                System.out.println("删除试卷成功！");
                return "删除成功！";
            }catch (Exception e){
                e.printStackTrace();
                System.out.println("删除试卷失败！");
            }

        }
        return "您未登录或没有权限！";
    }

    /**
     * 修改试卷
     * @param paperIdStr 试卷编号
     * @param paperName 试卷名称
     */
    @ResponseBody
    @RequestMapping("/updatePaper")
    public void updatePaper(String paperIdStr, String paperName) {
        int paperId = Integer.parseInt(paperIdStr);
        try {
            Paper paper = new Paper();
            paper.setPaperId(paperId);
            paper.setPaperName(paperName);
            paperService.updatePaper(paper);
            System.out.println("修改试卷成功！");
        }catch (Exception e){
            e.printStackTrace();
            System.out.println("修改试卷失败！");
        }
    }

    /**
     * 模糊查询（查询试卷名称）
     * @param keyStr 输入查询的关键字
     * @return 返回试卷信息
     */
    @ResponseBody
    @RequestMapping("/queryPaperName")
    public List<Paper> queryPaperName(String keyStr){
        List<Paper> paperList = null;
        try {
            paperList = paperService.queryPaperName(keyStr);
        }catch (Exception e){
            e.printStackTrace();
        }
        return paperList;
    }

    /**
     * 发布试卷
     * @param paperIdStr 试卷编号
     * @param beginTime 开始时间
     * @param duration 做题时长
     * @param endTime 截止时间
     */
    @ResponseBody
    @RequestMapping("/publishPaper")
    public void publishPaper(String paperIdStr, String beginTime, String duration, String endTime) {
        int paperId = Integer.parseInt(paperIdStr);
        try {
            Paper paper = new Paper();
            paper.setPaperId(paperId);
            paper.setStatus(1);
            paper.setBeginTime(beginTime);
            paper.setDuration(duration);
            paper.setEndTime(endTime);
            paperService.publishPaper(paper);
            System.out.println("发布试卷成功！");
        }catch (Exception e){
            e.printStackTrace();
            System.out.println("发布试卷失败！");
        }
    }
}
