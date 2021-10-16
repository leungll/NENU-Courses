package com.nenusoftware.onlineexam.controller.connect;

import com.nenusoftware.onlineexam.controller.user.UserController;
import com.nenusoftware.onlineexam.entity.connect.Connect;
import com.nenusoftware.onlineexam.service.connect.ConnectService;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

import javax.annotation.Resource;
import javax.servlet.http.HttpServletRequest;
import java.util.LinkedList;
import java.util.List;

/**
 * @Author:Liangll
 * @Description: ConnectController层（与前端页面进行交互）
 * @Date: 15:54 2020/6/18
 */
@CrossOrigin(allowCredentials = "true")
@Controller
@RequestMapping("/connect")
public class ConnectController {

    @Resource
    ConnectService connectService;

    @Resource
    UserController userController;

    /**
     * 通过试卷编号列出试卷详细信息
     * @param paperIdStr 试卷编号
     * @param exerciseTypeStr 题目类型
     * @param request HTTP请求
     * @return 返回 List形式的试卷详细信息
     */
    @RequestMapping("/listAllConnect")
    @ResponseBody
    public List<Connect> listAllConnect(String paperIdStr, String exerciseTypeStr, HttpServletRequest request){
        int result = userController.judgePower(request);
        int paperId = Integer.parseInt(paperIdStr);
        String exerciseType = null;
        if("0".equals(exerciseTypeStr)){
            exerciseType = "选择题";
        }else if("1".equals(exerciseTypeStr)){
            exerciseType = "判断题";
        }else if("2".equals(exerciseTypeStr)){
            exerciseType = "填空题";
        }else if("3".equals(exerciseTypeStr)){
            exerciseType = "简答题";
        }
        List<Connect> connectList = new LinkedList<>();
        if(result == 1){
            try {
                connectList = connectService.listAllConnect(paperId, exerciseType);
                return connectList;
            }catch (Exception e){
                e.printStackTrace();
            }
        }
        else if(result != -1){
            try {
                if(connectService.isInTheTime(paperId)){
                    connectList = connectService.listAllConnect(paperId, exerciseType);
                    long leftover = connectService.leftoverTime(paperId);
                    Connect connect = new Connect();
                    connect.setLeftover(leftover);
                    connectList.add(connect);
                    System.out.println("通过试卷编号列出试卷详细信息成功！");
                }else{
                    Connect connect = new Connect();
                    connect.setLog("考试时间未到或您已过了考试时间");
                    connectList.add(connect);
                }
            }catch (Exception e){
                e.printStackTrace();
            }
        }
        return connectList;
    }

    /**
     * 增加试卷详细信息
     * @param paperIdStr 试卷编号
     * @param paperDetailIdStr 试题编号
     */
    @ResponseBody
    @RequestMapping("/addConnect")
    public void addConnect(String paperIdStr, String paperDetailIdStr){
        int paperId = Integer.parseInt(paperIdStr);
        int paperDetailId = Integer.parseInt(paperDetailIdStr);
        try {
            Connect connect = new Connect();
            connect.setPaperId(paperId);
            connect.setPaperDetailId(paperDetailId);
            connectService.addConnect(connect);
            System.out.println("增加试卷详细信息成功！");
        }catch (Exception e){
            e.printStackTrace();
            System.out.println("增加试卷详细信息！");
        }
    }
}
