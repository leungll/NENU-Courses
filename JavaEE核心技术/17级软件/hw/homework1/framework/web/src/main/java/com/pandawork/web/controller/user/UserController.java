package com.pandawork.web.controller.user;

import com.pandawork.common.entity.user.User;
import com.pandawork.core.common.exception.SSException;
import com.pandawork.core.common.log.LogClerk;
import com.pandawork.core.common.util.Assert;
import com.pandawork.service.User.UserService;
import com.pandawork.web.spring.AbstractController;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.mvc.support.RedirectAttributes;

import javax.script.ScriptContext;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.util.Collections;
import java.util.List;

/**
 * @author : kongyy
 * @time : 2018/12/23 11:33
 */

@Controller
@RequestMapping("/user")
public class UserController extends AbstractController{

    ScriptContext response;

    @Autowired
    UserService userService;

    @RequestMapping(value = "/list", method = RequestMethod.GET)
    public String UserList(Model model) {
        try {
            List<User> list = Collections.emptyList();
            list = userService.listAll();
            model.addAttribute("userList", list);
            return "user/userlist";
        } catch (SSException e) {
            LogClerk.errLog.error(e);
            sendErrMsg(e.getMessage());
            return ADMIN_SYS_ERR_PAGE;
        }
    }

    @RequestMapping(value = "del/{id}", method = RequestMethod.GET)
    public String delete(@PathVariable("id") int id) {
        try {
            userService.delById(id);
            return "redirect:/carousel/list";
        } catch (SSException e) {
            LogClerk.errLog.error(e);
            sendErrMsg(e.getMessage());
            return ADMIN_SYS_ERR_PAGE;
        }
    }

    @RequestMapping(value = "/update", method = RequestMethod.POST)
    public String update(User user, @RequestParam("id") Integer id, Model model, HttpServletRequest req,String username, String sig) {
        try {
            if(Assert.isNull(user)){
                return "user/person";
            }
            user.setId(id);
            model.addAttribute("user",user);
            userService.update(user);
            HttpSession session = req.getSession();
            session.setAttribute("user", user);
            username = user.getUsername();
            sig = user.getSig();
            id = user.getId();
            session.setAttribute("username",username );
            session.setAttribute("sig", sig);
            session.setAttribute("id", id);
            return "redirect:/nature/list2";
        } catch (SSException e){
            LogClerk.errLog.error(e);
            sendErrMsg(e.getMessage());
            return ADMIN_SYS_ERR_PAGE;
        }
    }


    @RequestMapping(value = "update2/{id}", method = RequestMethod.GET)
    public String update2( @PathVariable("id") int id) {
        try {
            userService.update2(id);
            return "redirect:/carousel/list";
        } catch (SSException e){
            LogClerk.errLog.error(e);
            sendErrMsg(e.getMessage());
            return ADMIN_SYS_ERR_PAGE;
        }
    }

    @RequestMapping(value ="/add", method = RequestMethod.POST)
    public String addUser(User user,@RequestParam("username") String username, RedirectAttributes redirectAttributes) throws Exception{
       if(!Assert.isNotNull(user)){
           return"redirect:/user/alert4";
       }
       else if(userService.selectByName(username) != null){
           return "redirect:/user/alert3";
       }
       else{
            try {
                userService.addUser(user);
                redirectAttributes.addFlashAttribute("message", "添加成功！");
                return "redirect:/user/toLogin";
            } catch (SSException e){
                LogClerk.errLog.error(e);
                sendErrMsg(e.getMessage());
                return ADMIN_SYS_ERR_PAGE;
            }
        }

    }


    @RequestMapping(value = "/toAdd", method = RequestMethod.GET)
    public String toNewStudent(){
        return "user/add";
    }

    @RequestMapping(value = "/toLogin", method = RequestMethod.GET)
    public String toLogin(){
        return "user/login";
    }

    @RequestMapping(value ="login/{id}",method = RequestMethod.GET)
    public String login(@RequestParam("username") String username) {
        try {
            userService.selectByName(username);
            return "redirect:/user/toMain";
        } catch (SSException e ){
            LogClerk.errLog.error(e);
            sendErrMsg(e.getMessage());
            return ADMIN_SYS_ERR_PAGE;
        }
    }

    @RequestMapping(value = "/toSuper", method = RequestMethod.POST)
    public String Super(@RequestParam("username") String username,@RequestParam("password") String password,String sig, Integer id,  HttpServletRequest req, HttpServletResponse resp)throws Exception {
        if (userService.selectByName(username) != null) {
            if (userService.pswIsTrue(username, password)) {
                User user = userService.selectByName(username);
                HttpSession session = req.getSession();
                sig = user.getSig();
                id = user.getId();
                session.setAttribute("user", user);
                session.setAttribute("username", username);
                session.setAttribute("sig", sig);
                session.setAttribute("id", id);
                if (user.getPower() == 0) {
                    return "redirect:/nature/list2";
                } else {
                    return "redirect:/carousel/list";
                }
            } else {
                  return "redirect:/user/alert1";
            }
        }
        else {
            return "redirect:/user/alert2";
        }
    }

    @RequestMapping(value = "/alert1", method = RequestMethod.GET)
    public String alert1(Model model){

        model.addAttribute("msg","密码错误");
        return "user/login";
    }

    @RequestMapping(value = "/alert2", method = RequestMethod.GET)
    public String alert2(Model model){

        model.addAttribute("msg","没有账号？请先注册");
        return "user/login";
    }

    @RequestMapping(value = "/alert3", method = RequestMethod.GET)
    public String alert3(Model model){

        model.addAttribute("msg","该用户名已存在，请重新输入");
        return "user/add";
    }

    @RequestMapping(value = "/alert4", method = RequestMethod.GET)
    public String alert4(Model model){
        model.addAttribute("msg","请输入有效信息");
        return "user/add";
    }

    @RequestMapping(value = "/toNature", method = RequestMethod.GET)
    public String toNature(){
        return "outer/nature";
    }

    @RequestMapping(value = "/toCity", method = RequestMethod.GET)
    public String toCity(){
        return "outer/city";
    }

    @RequestMapping(value = "/toMain", method = RequestMethod.GET)
    public String toMain(){
        return "outer/main";
    }

    @RequestMapping(value = "/toPerson", method = RequestMethod.GET)
    public String toPerson(){
        return "outer/person";
    }


}
    