package com.nenusoftware.onlineexam.controller.answer;

import com.nenusoftware.onlineexam.service.answer.AnswerService;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.RequestMapping;

import javax.annotation.Resource;

/**
 * @Author:Liangll
 * @Description: AnswerController层（与前端页面进行交互）
 * @Date: 10:54 2020/6/13
 */
@CrossOrigin(allowCredentials = "true")
@Controller
@RequestMapping("/answer")
public class AnswerController {

    @Resource
    AnswerService answerService;

}
