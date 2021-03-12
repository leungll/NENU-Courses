package edu.nenu.onlineExam.question.action;

import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.List;

import javax.servlet.http.HttpServletResponse;

import org.apache.struts2.ServletActionContext;

import edu.nenu.onlineExam.bj.entity.BJ;
import edu.nenu.onlineExam.question.entity.Question;
import edu.nenu.onlineExam.question.service.QuestionService;
import edu.nenu.onlineExam.questiontype.entity.QuestionType;
import edu.nenu.onlineExam.utils.PageBean;

import com.opensymphony.xwork2.ActionContext;
import com.opensymphony.xwork2.ActionSupport;
import com.opensymphony.xwork2.ModelDriven;

public class QuestionAction extends ActionSupport implements ModelDriven<Question>{
	
	private Question question = new Question();
	
	public Question getModel() {
		return question;
	}
	private QuestionService questionService;

	public void setQuestionService(QuestionService questionService) {
		this.questionService = questionService;
	}
	private Integer tid;
	
	public void setTid(Integer tid) {
		this.tid = tid;
	}
	private Integer qtid;
	public void setQtid(Integer qtid) {
		this.qtid = qtid;
	}
	private int page;
	public void setPage(int page) {
		this.page = page;
	}
	//选择查找试题的试题类型
	public String ckQuestionAndXZQT(){
		List<QuestionType> listqt = questionService.ckQuestionAndXZQT();
		ActionContext.getContext().getValueStack().set("listqt", listqt);
		return "ckQuestionAndXZQT";
	}
	//选择查找试题的试题类型
	public String ckAdminQuestionAndXZQT(){
		List<QuestionType> listqt = questionService.ckQuestionAndXZQT();
		ActionContext.getContext().getValueStack().set("listqt", listqt);
		return "ckAdminQuestionAndXZQT";
	}
	//查找试题
	public String ckQuestion() throws UnsupportedEncodingException{
		if(question.getQid()!=null){
			question = questionService.selectQuestion(question.getQid());
		}
		PageBean<Question> pageBean = questionService.ckQuestion(question,tid,qtid,page);
		ActionContext.getContext().getValueStack().set("pageBean", pageBean);
		List<QuestionType> listqt = questionService.ckQuestionAndXZQT();
		ActionContext.getContext().getValueStack().set("listqt", listqt);
		ActionContext.getContext().getValueStack().set("pageqtid", qtid);
		return "ckQuestion";
	}
	//管理员查找试题
	public String ckAdminQuestion() throws UnsupportedEncodingException{
		if(question.getQid()!=null){
			//根据试题编号，获取试题详细信息
			question = questionService.selectQuestion(question.getQid());
		}
		//获取符合条件的试题
		PageBean<Question> pageBean = questionService.ckAdminQuestion(question,qtid,page);
		//将符合符合条件的数据存放到值栈中，出入到显示界面
		ActionContext.getContext().getValueStack().set("pageBean", pageBean);
		List<QuestionType> listqt = questionService.ckQuestionAndXZQT();
		ActionContext.getContext().getValueStack().set("listqt", listqt);
		ActionContext.getContext().getValueStack().set("pageqtid", qtid);
		return "ckAdminQuestion";
	}
	//查看相似选择试题
	public String ckXSXZQuestion(){
		List<Question> listxs = questionService.findByOword(question.getOword(), question.getQscope(), question.getQdifficulty(), qtid);
		ActionContext.getContext().getValueStack().set("question", question);
		ActionContext.getContext().getValueStack().set("listxs", listxs);
		return "ckXSXZQuestion";
	}
	public String ckXSXZAdminQuestion(){
		List<Question> listxs = questionService.findByOword(question.getOword(), question.getQscope(), question.getQdifficulty(), qtid);
		ActionContext.getContext().getValueStack().set("question", question);
		ActionContext.getContext().getValueStack().set("listxs", listxs);
		return"ckXSXZAdminQuestion";
	}
	//添加选择题
	public String addQuestionXZ(){
		return "addQuestionXZ";
	}
	public String addAdminQuestionXZ(){
		return "addAdminQuestionXZ";
	}
	//添加选择实现
	public String addQuestionXZSX(){
		Date date = new Date();
		question.setQdate(date);
		questionService.addQuestionXZSX(question,qtid,tid);
		return "addQuestionXZSX";
	}
	public String addAdminQuestionXZSX(){
		Date date = new Date();
		question.setQdate(date);
		questionService.addAdminQuestionXZSX(question,qtid);
		return "addQuestionXZSX";
	}
	//查看相似填空题
	public String ckXSTKQuestion(){
		List<Question> listxs = questionService.findByOword(question.getOword(), question.getQscope(), question.getQdifficulty(), qtid);
		ActionContext.getContext().getValueStack().set("question", question);
		ActionContext.getContext().getValueStack().set("listxs", listxs);
		return"ckXSTKQuestion";
	}
	public String ckXSTKAdminQuestion(){
		List<Question> listxs = questionService.findByOword(question.getOword(), question.getQscope(), question.getQdifficulty(), qtid);
		ActionContext.getContext().getValueStack().set("question", question);
		ActionContext.getContext().getValueStack().set("listxs", listxs);
		return "ckXSTKAdminQuestion";
	}
	//添加填空题
	public String addQuestionTK(){
		return "addQuestionTK";
	}
	public String addAdminQuestionTK(){
		return "addAdminQuestionTK";
	}
	//添加填空实现
	public String addQuestionTKSX(){
		Date date = new Date();
		question.setQdate(date);
		questionService.addQuestionXZSX(question,qtid,tid);
		return "addQuestionTKSX";
	}
	public String addAdminQuestionTKSX(){
		Date date = new Date();
		question.setQdate(date);
		questionService.addAdminQuestionXZSX(question,qtid);
		return "addQuestionXZSX";
	}
	//查看相似判断题
	public String ckXSPDQuestion(){
		List<Question> listxs = questionService.findByOword(question.getOword(), question.getQscope(), question.getQdifficulty(), qtid);
		ActionContext.getContext().getValueStack().set("question", question);
		ActionContext.getContext().getValueStack().set("listxs", listxs);
		return "ckXSPDQuestion";
	}
	public String ckXSPDAdminQuestion(){
		List<Question> listxs = questionService.findByOword(question.getOword(), question.getQscope(), question.getQdifficulty(), qtid);
		ActionContext.getContext().getValueStack().set("question", question);
		ActionContext.getContext().getValueStack().set("listxs", listxs);
		return "ckXSPDAdminQuestion";
	}
	//添加判断题
	public String addQuestionPD(){
		return "addQuestionPD";
	}
	public String addAdminQuestionPD(){
		return "addAdminQuestionPD";
	}
	
	//添加判断题实现
	public String addQuestionPDSX(){
		Date date = new Date();
		question.setQdate(date);
		questionService.addQuestionXZSX(question,qtid,tid);
		return"addQuestionPDSX";
	}
	public String addAdminQuestionPDSX(){
		Date date = new Date();
		question.setQdate(date);
		questionService.addAdminQuestionXZSX(question,qtid);
		return"addQuestionPDSX";
	}
	//查看选择题
	public String ckQuestionXX(){
		System.out.println("试题编号="+question.getQid());
		Question questionxx = questionService.ckQuestionXX(question.getQid());
		ActionContext.getContext().getValueStack().set("questionxx", questionxx);
		if(questionxx.getQuestionType().getQtid() == 1){
			return "ckXZQuestion";
		}else if(questionxx.getQuestionType().getQtid() == 2){
			return "ckPDQuestion";
		}else{
			return "ckTKQuestion";
		}	
	}
	//根据试题编号删除试题
	public String delQuestion(){
		questionService.delQuestion(question.getQid());
		List<QuestionType> listqt = questionService.ckQuestionAndXZQT();
		ActionContext.getContext().getValueStack().set("listqt", listqt);
		return "ckQuestionAndXZQT";
	}
	public String delAdminQuestion(){
		questionService.delQuestion(question.getQid());
		List<QuestionType> listqt = questionService.ckQuestionAndXZQT();
		ActionContext.getContext().getValueStack().set("listqt", listqt);
		return "ckAdminQuestionAndXZQT";
	}

}
