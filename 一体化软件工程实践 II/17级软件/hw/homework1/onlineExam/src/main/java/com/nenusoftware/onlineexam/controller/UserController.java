package com.nenusoftware.onlineexam.controller;

import com.nenusoftware.onlineexam.entity.User;
import com.nenusoftware.onlineexam.service.UserService;
import org.springframework.stereotype.Controller;
import org.springframework.ui.ModelMap;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;

import javax.annotation.Resource;

/**
 * @Author:Liangll
 * @Description: UserController层（与前端页面进行交互）
 * @Date: 10:54 2019/5/3
 */
@Controller
public class UserController {
    @Resource
    UserService userService;

    @RequestMapping("/toLogin")
    public String toLogin(){
        return "/index";
    }

    @RequestMapping("/login")
    public String login(@RequestParam("username")String username, @RequestParam("password")String password, ModelMap map) throws Exception {
        if(userService.selectByName(username) != null){
            if(userService.checkPassword(username,password).size() != 0){
                System.out.println("登录成功！");
                map.addAttribute("msg", "登录成功！");
                return "index";
//                return "登录成功！";
            }else {
                System.out.println("您的密码有误！");
                map.addAttribute("msg", "您的密码有误！请重新输入密码");
                return "index";
//                return "您的密码有误！";
            }
        }else{
            System.out.println("用户名不存在，请去注册！");
            map.addAttribute("msg", "用户名不存在，请去注册！");
            return "index";
//            return "用户名不存在，请去注册！";
        }
    }

    @RequestMapping("/toRegister")
    public String toRegister(){
        return "/register";
    }

    @RequestMapping("/register")
    public String register (@RequestParam("username")String username, @RequestParam("password")String password, ModelMap map) throws Exception{
        if(userService.selectByName(username) == null){
            User user = new User();
            user.setUsername(username);
            user.setPassword(password);
            if(userService.addUser(user)){
                System.out.println("注册成功！");
                map.addAttribute("msg", "注册成功！");
                return "index";
            }
        }else{
            System.out.println("用户名不存在，请去注册！");
            map.addAttribute("msg", "用户名已存在，请重新输入！");
        }
        return "register";
    }
}
