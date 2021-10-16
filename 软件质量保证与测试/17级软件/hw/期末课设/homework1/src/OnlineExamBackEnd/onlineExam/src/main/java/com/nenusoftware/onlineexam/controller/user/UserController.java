package com.nenusoftware.onlineexam.controller.user;

import com.nenusoftware.onlineexam.entity.user.User;
import com.nenusoftware.onlineexam.md5util.MD5Util;
import com.nenusoftware.onlineexam.service.user.UserService;
import io.swagger.annotations.Api;
import io.swagger.annotations.ApiImplicitParam;
import io.swagger.annotations.ApiOperation;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.multipart.MultipartFile;

import javax.annotation.Resource;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;
import java.io.File;
import java.util.ArrayList;
import java.util.Objects;

/**
 * @Author:Liangll
 * @Description: UserController层（与前端页面进行交互）
 * @Date: 10:54 2020/6/15
 */
@CrossOrigin(allowCredentials = "true")
@Controller
@RequestMapping("/user")
@Api(value = "UserController|用户控制器")
public class UserController {

    @Resource
    UserService userService;

    boolean flag = false;

    /**
     * 用户登录
     * @param username 用户名
     * @param password 用户密码
     * @param request Http请求（需登录）
     * @return 用户名
     * @throws Exception 报错信息
     */
    @ResponseBody
    @RequestMapping("/login")
    @ApiOperation(value="登录", notes="返回username")
    @ApiImplicitParam(paramType="login", name = "username", value = "用户名", required = true, dataType = "String")
    public String login(String username, String password, HttpServletRequest request) throws Exception {
        if(userService.queryByName(username) != null){
            String pwd = MD5Util.string2MD5(password);
            if(userService.checkPassword(username, pwd).size() != 0){
                HttpSession session = request.getSession();
                session.setAttribute("usernameSession",username);
                System.out.println("登录成功！");
            }else {
                username = "您的密码有误！";
            }
        }else{
            username = "用户名不存在，请去注册！";
        }
        return username;
    }

    @RequestMapping("/toRegister")
    public String toRegister(){
        return "/register";
    }

    /**
     * 用户注册
     * @param username 用户名
     * @param password 用户密码
     * @return 用户名
     * @throws Exception 报错信息
     */
    @ResponseBody
    @RequestMapping("/register")
    public String register (String username, String password) throws Exception{
        if(userService.queryByName(username) == null){
            User user = new User();
            String pwd = MD5Util.string2MD5(password);
            user.setUsername(username);
            user.setPassword(pwd);
            user.setPower(0);
            if(userService.addUser(user)){
                System.out.println("注册成功！");
            }
        }else{
            username = "用户名已存在，请直接登录！";
        }
        return username;
    }

    /**
     * 列出所有用户信息
     * @param request Http请求
     * @return 返回List形式的用户信息
     */
    @ResponseBody
    @RequestMapping("listAllUser")
    public ArrayList<User> listAllUser(HttpServletRequest request){
        ArrayList<User> userList = new ArrayList<>();
        User user = new User();
        try {
            int result = judgePower(request);
            if(result == 2){
                userList = userService.listAllUser();
                for (User value : userList) {
                    User user1 = new User();
                    user1 = value;
                    if (user1.getPower() == 0) {
                        user1.setPowerS("学生");
                    } else if (user1.getPower() == 1) {
                        user1.setPowerS("教师");
                    } else if (user1.getPower() == 2) {
                        user1.setPowerS("管理员");
                    }
                }
            }
            else{
                user.setUsername("您未登录或没有权限");
                userList.add(0, user);
            }
        }catch (Exception e){
            e.printStackTrace();
        }
        return userList;
    }

    /**
     * 根据用户编号列出用户所有信息
     * @param request Http请求（需登录）
     * @return 用户列表
     * @throws Exception 报错信息
     */
    @ResponseBody
    @RequestMapping("/listUserById")
    public ArrayList<User> listUserById(HttpServletRequest request) throws Exception {
        ArrayList<User> userList = new ArrayList<>();
        HttpSession session = request.getSession(flag);
        if(session != null){
            String username = String.valueOf(session.getAttribute("usernameSession"));
            int userId = userService.queryIdByUsername(username).getUserId();
            userList = userService.listUserById(userId);
        }
        else{
            User user = new User();
            user.setUsername("请先登录");
            userList.add(user);
        }
        return userList;
    }

    /**
     * 用户注销
     * @param request Http请求（需登录）
     */
    @RequestMapping("/exit")
    @ResponseBody
    public void exit(HttpServletRequest request){
        HttpSession session = request.getSession(flag);
        session.removeAttribute("usernameSession");
        System.out.println("退出成功");
    }

//    /**
//     * 删除用户
//     * @param userIdStr 用户编号
//     * @throws Exception
//     */
//    @RequestMapping("/deleteUser")
//    @ResponseBody
//    public void deleteUser(String userIdStr) throws Exception{
//        int userId = Integer.parseInt(userIdStr);
//        userService.deleteUser(userId);
//        System.out.println("删除成功");
//    }

    @RequestMapping("file")
    public String file(){
        return "test";
    }

    /**
     * 修改用户信息
     * @param birthday 生日
     * @param sex 性别
     * @param request Http请求（需登录）
     * @param file 头像
     * @throws Exception 报错信息
     */
    @ResponseBody
    @RequestMapping("/updateUser")
    public void updateUser(String birthday, String sex, HttpServletRequest request, @RequestParam("fileName") MultipartFile file) throws Exception{
        if(file.isEmpty()){
            System.out.println("文件不存在!");
        }else{
            String fileName = file.getOriginalFilename();
            int size = (int) file.getSize();
            System.out.println(fileName + "-->" + size);

            //上传之后文件置于的路径
            String url = Objects.requireNonNull(this.getClass().getClassLoader().getResource("")).toString();
            url = url.replace("file:/","");
            System.out.println(url);
            String path = url;

            File dest = new File(path + "/" + fileName);
            //判断文件父目录是否存在
            if(!dest.getParentFile().exists()){
                dest.getParentFile().mkdir();
            }
            try{
                //保存文件
                file.transferTo(dest);
                HttpSession session = request.getSession();
                String username = String.valueOf(session.getAttribute("usernameSession"));
                int userId = userService.queryIdByUsername(username).getUserId();
                User user = new User();
                user.setUserId(userId);
                user.setBirthday(birthday);
                user.setSex(sex);
                user.setImage("http://120.26.186.88:8080/" + fileName);
                userService.updateUser(user);
                System.out.println("Success");
            } catch (IllegalStateException e) {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }
        }
    }

    /**
     * 判断用户是否有权限
     * @param request Http请求
     * @return 结果
     */
    @ResponseBody
    @RequestMapping("/JudgePower")
    public int judgePower(HttpServletRequest request){
        int result = 0;
        try{
            HttpSession session = request.getSession(flag);
            if(session == null){
                result = -1;
                return result;
            }
            else{
                String username = String.valueOf(session.getAttribute("usernameSession"));
                int power = userService.queryByName(username).getPower();
                if(power == 1){
                    result = 1;
                }
                else if(power == 2){
                    result = 2;
                }
                else if(power == 0){
                    result = 0;
                }
            }
        }catch (Exception e){
            e.printStackTrace();
        }
        return result;
    }

//    /**
//     * 修改用户权限
//     * @param userIdStr 用户编号
//     * @throws Exception
//     */
//    @RequestMapping("/updatePower")
//    @ResponseBody
//    public void updatePower(String userIdStr) throws Exception {
//        int userId = Integer.parseInt(userIdStr);
//        userService.updatePower(userId);
//        System.out.println("修改成功!");
//    }
}
