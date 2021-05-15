package com.nenusoftware.onlineexam.controller.superuser;

import com.nenusoftware.onlineexam.controller.user.UserController;
import com.nenusoftware.onlineexam.service.superuser.SuperUserService;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

import javax.annotation.Resource;
import javax.servlet.http.HttpServletRequest;

/**
 * @Author:Kongyy
 * @Description: SuperUserController层（与前端页面进行交互）
 * @Date: 15:14 2020/6/19
 */
@CrossOrigin(allowCredentials = "true")
@Controller
@RequestMapping("/superUser")
public class SuperUserController {

    @Resource
    SuperUserService superUserService;

    @Resource
    UserController userController;


    /**
     * 根据用户id删除用户
     * @param userIdStr 用户编号
     * @param request Http请求
     * @return 报错信息
     */
    @ResponseBody
    @RequestMapping("/deleteUser")
    public String  deleteUser(String userIdStr, HttpServletRequest request){
        int result = userController.judgePower(request);
        if(result == 2){
            int userId = Integer.parseInt(userIdStr);
            try {
                superUserService.deleteUser(userId);
                return "删除成功！";
            }catch (Exception e){
                e.printStackTrace();
                System.out.println("删除失败！");
            }
        }
        return "您未登录或没有权限";
    }

    /**
     * 据用户id更改用户权限，如果为教师，则更改为管理员，如果是管理员，则改为教师，学生权限不能改变
     * @param userIdStr 用户编号
     * @param request Http请求
     * @return 报错信息
     */
    @ResponseBody
    @RequestMapping("/updateUserPower")
    public String updateUserPower(String userIdStr, HttpServletRequest request){
        int result = userController.judgePower(request);
        int userId = Integer.parseInt(userIdStr);
        if(result == 2){
            try {
                superUserService.updateUserPower(userId);
                return "修改成功";
            }catch (Exception e){
                e.printStackTrace();
                System.out.println("更新失败！");
            }
        }
        return "您未登录或没有权限";
    }
}
