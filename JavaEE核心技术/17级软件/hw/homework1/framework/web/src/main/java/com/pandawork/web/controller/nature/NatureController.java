package com.pandawork.web.controller.nature;

import com.pandawork.common.entity.nature.Nature;
import com.pandawork.core.common.exception.SSException;
import com.pandawork.core.common.log.LogClerk;
import com.pandawork.core.common.util.Assert;
import com.pandawork.service.nature.NatureService;
import com.pandawork.web.spring.AbstractController;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.servlet.mvc.support.RedirectAttributes;
import org.springframework.web.multipart.MultipartFile;
import javax.script.ScriptContext;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.RequestDispatcher;
import javax.servlet.http.HttpSession;
import java.io.File;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Collections;
import java.util.List;
import java.util.Date;
/**
 * @author : kongyy
 * @time : 2018/12/23 23:51
 */
@Controller
@RequestMapping("/nature")
public class NatureController extends AbstractController {

    ScriptContext response;

    @Autowired
    NatureService natureService;

    @RequestMapping(value = "/list", method = RequestMethod.GET)
    public String NatureList(Model model) {
        try {
            List<Nature> list = Collections.emptyList();
            list = natureService.listAll();
            model.addAttribute("natureList", list);
            return "outer/nature";
        } catch (SSException e) {
            LogClerk.errLog.error(e);
            sendErrMsg(e.getMessage());
            return ADMIN_SYS_ERR_PAGE;
        }
    }

    @RequestMapping(value = "/list2", method = RequestMethod.GET)
    public String NatureList2(Model model) {
        try {
            List<Nature> list2 = Collections.emptyList();
            list2 = natureService.listAll2();
            model.addAttribute("natureList2", list2);
            return "user/person";
        } catch (SSException e) {
            LogClerk.errLog.error(e);
            sendErrMsg(e.getMessage());
            return ADMIN_SYS_ERR_PAGE;
        }
    }

    @RequestMapping(value = "/add1", method = RequestMethod.POST)
    public String addNature(Nature nature, HttpSession session, MultipartFile uploadFile2, RedirectAttributes redirectAttributes, Model model) throws SSException {
        Date date = new Date();
        SimpleDateFormat sdf = new SimpleDateFormat("yyyyMMddhhmmss");
        String date1 = sdf.format(date);
        String filename = date1 + uploadFile2.getOriginalFilename();
        String leftPath = session.getServletContext().getRealPath("images");
        File file = new File(leftPath, filename);
        nature.setPath("/images/" + filename);
        try {
            uploadFile2.transferTo(file);
            natureService.addNature(nature);
            redirectAttributes.addFlashAttribute("message", "添加成功！");
            return "redirect:/carousel/list";
        } catch (SSException e) {
            LogClerk.errLog.error(e);
            sendErrMsg(e.getMessage());
            return ADMIN_SYS_ERR_PAGE;
        }catch (IOException e) {
            e.printStackTrace();
        }
        return "carousel/home_carousel";
    }

    @RequestMapping(value = "update2/{id}", method = RequestMethod.POST)
    public String update(Nature nature, @PathVariable("id") int id) {
        try {
            if (Assert.isNull(nature)) {
                return null;
            }
            natureService.update(nature);
            return "redirect:/nature/list";
        } catch (SSException e) {
            LogClerk.errLog.error(e);
            sendErrMsg(e.getMessage());
            return ADMIN_SYS_ERR_PAGE;
        }
    }

    @RequestMapping(value = "update2/{id}", method = RequestMethod.GET)
    public String update2(@PathVariable("id") int id) {
        try {
            natureService.update2(id);
            return "redirect:/nature/list";
        } catch (SSException e) {
            LogClerk.errLog.error(e);
            sendErrMsg(e.getMessage());
            return ADMIN_SYS_ERR_PAGE;
        }
    }

    @RequestMapping(value = "update3/{id}", method = RequestMethod.GET)
    public String update3(@PathVariable("id") int id) {
        try {
            natureService.update3(id);
            return "redirect:/nature/list2";
        } catch (SSException e) {
            LogClerk.errLog.error(e);
            sendErrMsg(e.getMessage());
            return ADMIN_SYS_ERR_PAGE;
        }
    }

        @RequestMapping(value = "del/{id}", method = RequestMethod.GET)
    public String delete( @PathVariable("id") int id) {
        try {
            natureService.delById(id);
            return "redirect:/carousel/list";
        } catch (SSException e) {
            LogClerk.errLog.error(e);
            sendErrMsg(e.getMessage());
            return ADMIN_SYS_ERR_PAGE;
        }
    }

}
