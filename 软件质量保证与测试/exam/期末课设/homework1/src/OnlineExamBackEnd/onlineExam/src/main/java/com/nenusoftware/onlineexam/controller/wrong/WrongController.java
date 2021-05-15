package com.nenusoftware.onlineexam.controller.wrong;

import com.nenusoftware.onlineexam.entity.wrong.Wrong;
import com.nenusoftware.onlineexam.service.user.UserService;
import com.nenusoftware.onlineexam.service.wrong.WrongService;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

import javax.annotation.Resource;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;
import java.util.Collections;
import java.util.List;

/**
 * @Author:Kongyy
 * @Description: WrongController层（与前端页面进行交互）
 * @Date: 10:38 2020/6/16
 */
@CrossOrigin(allowCredentials = "true")
@Controller
@RequestMapping("/wrong")
public class WrongController {

    @Resource
    WrongService wrongService;

    @Resource
    UserService userService;

    /**
     * 根据Id列出错题本
     * @param request Http请求
     * @return 错题信息
     */
    @ResponseBody
    @RequestMapping("/listWrongById")
    public List<Wrong> listWrongById(HttpServletRequest request){
        HttpSession session = request.getSession();
        String username = String.valueOf(session.getAttribute("usernameSession"));
        List<Wrong> wrongList = Collections.emptyList();
        try{
            int userId = userService.queryIdByUsername(username).getUserId();
            wrongList = wrongService.listWrongByUserId(userId);
        }catch (Exception e){
            e.printStackTrace();
        }
        return wrongList;
    }

    /**
     * 删除错题
     * @param wrongIdStr 错题编号
     */
    @ResponseBody
    @RequestMapping("/deleteWrong")
    public void deleteWrong(String wrongIdStr){
        int wrongId = Integer.parseInt(wrongIdStr);
        try {
            wrongService.deleteWrong(wrongId);
            System.out.println("删除错题成功");
        }catch (Exception e){
            e.printStackTrace();
            System.out.println("删除错题失败");
        }
    }
}
