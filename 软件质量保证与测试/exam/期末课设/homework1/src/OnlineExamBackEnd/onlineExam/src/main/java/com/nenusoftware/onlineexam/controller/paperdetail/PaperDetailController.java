package com.nenusoftware.onlineexam.controller.paperdetail;

import com.alibaba.fastjson.JSONArray;
import com.nenusoftware.onlineexam.entity.paperdetail.PaperDetail;
import com.nenusoftware.onlineexam.service.paperdetail.PaperDetailService;
import com.nenusoftware.onlineexam.service.user.UserService;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.CrossOrigin;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

import javax.annotation.Resource;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;
import java.util.ArrayList;
import java.util.List;

/**
 * @Author:Liangll
 * @Description: PaperDetailController层（与前端页面进行交互）
 * @Date: 10:54 2020/6/16
 */
@CrossOrigin(allowCredentials = "true")
@Controller
@RequestMapping("/paperDetail")
public class PaperDetailController {

    @Resource
    PaperDetailService paperDetailService;

    @Resource
    UserService userService;

    /**
     * 列出试题库所有试题详细信息
     * @return 返回 List形式的试卷详细信息
     */
    @ResponseBody
    @RequestMapping("/listAllPaperDetail")
    public List<PaperDetail> listAllPaperDetail(){
        List<PaperDetail> paperDetailList = null;
        try {
            paperDetailList = paperDetailService.listAllPaperDetail();
        }catch (Exception e){
            e.printStackTrace();
        }
        return paperDetailList;
    }

    /**
     * 增加试题详细信息
     * @param contentStr 题目内容
     * @param typeAStr 选项 A
     * @param typeBStr 选项 B
     * @param typeCStr 选项 C
     * @param typeDStr 选项 D
     * @param answerStr 题目答案
     * @param answer2 得分点 2
     * @param answer3 得分点 3
     * @param exerciseTypeStr 题目类型(0:选择题，1：判断题，2：填空题：3：简答题 )
     * @param scoreStr 题目分值
     * @return 试题库题目编号
     * @throws Exception 报错信息
     */
    @ResponseBody
    @RequestMapping("/addPaperDetail")
    public int addPaperDetail(String contentStr, String typeAStr, String typeBStr, String typeCStr, String typeDStr, String answerStr, String answer2, String answer3, String exerciseTypeStr, String scoreStr) throws Exception{
        PaperDetail paperDetail = new PaperDetail();

        int exerciseType = Integer.parseInt(exerciseTypeStr);
        int score = Integer.parseInt(scoreStr);

        paperDetail.setContent(contentStr);
        if(exerciseType == 0){
            paperDetail.setTypeA(typeAStr);
            paperDetail.setTypeB(typeBStr);
            paperDetail.setTypeC(typeCStr);
            paperDetail.setTypeD(typeDStr);
            paperDetail.setExerciseType("选择题");
        }else if(exerciseType == 1){
            paperDetail.setTypeA(typeAStr);
            paperDetail.setTypeB(typeBStr);
            paperDetail.setExerciseType("判断题");
        }else if(exerciseType == 2){
            paperDetail.setTypeA(typeAStr);
            paperDetail.setExerciseType("填空题");
        }else if(exerciseType == 3){
            paperDetail.setTypeA(typeAStr);
            paperDetail.setExerciseType("简答题");
        }
        paperDetail.setAnswer(answerStr);
        if("这个字段为空".equals(answer2)){
            answer2 = "";
        }
        if("这个字段为空".equals(answer3)){
            answer3 = "";
        }
        paperDetail.setAnswer2(answer2);
        paperDetail.setAnswer3(answer3);
        paperDetail.setScore(score);
        paperDetailService.addPaperDetail(paperDetail);
        int paperDetailId = paperDetailService.queryIdByContent(contentStr).getPaperDetailId();
        System.out.println("增加试题成功！");
        return paperDetailId;
    }

    /**
     * 删除题目
     * @param paperIdStr 题目编号
     */
    @ResponseBody
    @RequestMapping("/deletePaperDetail")
    public void deletePaperDetail(String paperIdStr){
        int paperId = Integer.parseInt(paperIdStr);
        try {
            paperDetailService.deletePaperDetail(paperId);
            System.out.println("删除题目信息失败!");
        }catch (Exception e){
            e.printStackTrace();
            System.out.println("删除题目信息失败!");
        }
    }

    /**
     * 根据试题编号修改试题详细信息
     * @param paperDetailIdStr 试题编号
     * @param contentStr 题目内容
     * @param typeAStr 选项 A
     * @param typeBStr 选项 B
     * @param typeCStr 选项 C
     * @param typeDStr 选项 D
     * @param answerStr 题目答案
     * @param answerStr2 得分点 2
     * @param answerStr3 得分点 3
     * @param scoreStr 题目分值
     */
    @ResponseBody
    @RequestMapping("/updatePaperDetail")
    public void updatePaperDetail(String paperDetailIdStr, String contentStr, String typeAStr, String typeBStr, String typeCStr, String typeDStr, String answerStr, String answerStr2, String answerStr3, String scoreStr){
        int paperDetailId = Integer.parseInt(paperDetailIdStr);
        int score = Integer.parseInt(scoreStr);
        try {
            PaperDetail paperDetail = new PaperDetail();
            paperDetail.setPaperDetailId(paperDetailId);
            paperDetail.setContent(contentStr);
            paperDetail.setTypeA(typeAStr);
            paperDetail.setTypeB(typeBStr);
            paperDetail.setTypeC(typeCStr);
            paperDetail.setTypeD(typeDStr);
            paperDetail.setAnswer(answerStr);
            paperDetail.setAnswer2(answerStr2);
            paperDetail.setAnswer3(answerStr3);
            paperDetail.setScore(score);
            paperDetailService.updatePaperDetail(paperDetail);
            System.out.println("修改题目信息成功!");
        }catch (Exception e){
            e.printStackTrace();
            System.out.println("修改题目信息失败!");
        }
    }

    /**
     * 模糊查询（查询题目内容或类型）
     * @param keyStr 输入查询的关键字
     * @return 返回List形式的题目详细信息
     * @throws Exception 报错信息
     */
    @ResponseBody
    @RequestMapping("queryPaperDetail")
    public List<PaperDetail> queryPaperDetail(String keyStr) throws Exception {
        List<PaperDetail> paperDetailList = new ArrayList<>();
        paperDetailList = paperDetailService.queryPaperDetail(keyStr);
        return paperDetailList;
    }

    /**
     * 根据题目类型列出试卷详细信息
     * @param exerciseTypeStr 题目类型
     */
    @ResponseBody
    @RequestMapping("/queryExerciseByTypes")
    public void queryExerciseByTypes(String exerciseTypeStr){
        try {
            paperDetailService.queryExerciseByTypes(exerciseTypeStr);
        }catch (Exception e){
            e.printStackTrace();
            System.out.println("根据题目类型列出题目信息失败!");
        }
    }

    /**
     * 前端传回做题信息，进行判分，并将错误的题目存入错题集中
     * @param jsonString 答题数据
     * @return 结果
     */
    @ResponseBody
    @RequestMapping("/judgeQuestion")
    public int judgeQuestion(String jsonString,HttpServletRequest request){
        HttpSession session = request.getSession();
        String username = String.valueOf(session.getAttribute("usernameSession"));
        int result = 0;
        //String jsonString = "[{\"answer\":\"后置双摄\",\"paperDetailId\":\"24\"}, {\"answer\":\"A\",\"paperDetailId\":\"11\"},{\"answer\":\"错\",\"paperDetailId\":\"3\"}]";
        try{
            int userId = userService.queryIdByUsername(username).getUserId();
            JSONArray jsonArray = JSONArray.parseArray(jsonString);
            result = paperDetailService.judgeQuestion(jsonArray, userId);
        }catch (Exception e){
            e.printStackTrace();
            System.out.println("得出成绩失败");
        }
        return result;
    }
}
