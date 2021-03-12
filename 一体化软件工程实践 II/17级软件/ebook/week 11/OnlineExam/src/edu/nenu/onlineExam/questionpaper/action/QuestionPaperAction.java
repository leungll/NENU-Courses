package edu.nenu.onlineExam.questionpaper.action;

import java.util.Date;
import java.util.List;

import edu.nenu.onlineExam.qprelationq.entity.QpRelationq;
import edu.nenu.onlineExam.question.entity.Question;
import edu.nenu.onlineExam.questionpaper.entity.QuestionPaper;
import edu.nenu.onlineExam.questionpaper.service.QuestionPaperService;
import edu.nenu.onlineExam.questiontype.entity.QuestionType;
import edu.nenu.onlineExam.utils.PageBean;

import com.opensymphony.xwork2.ActionContext;
import com.opensymphony.xwork2.ActionSupport;
import com.opensymphony.xwork2.ModelDriven;

public class QuestionPaperAction extends ActionSupport implements ModelDriven<QuestionPaper>{
	
	private QuestionPaper questionPaper = new QuestionPaper();
	public QuestionPaper getModel() {
		return questionPaper;
	}
	private QuestionPaperService qpService;
	
	public void setQpService(QuestionPaperService qpService) {
		this.qpService = qpService;
	}
	public Question question;
	public Question getQuestion() {
		return question;
	}
	public void setQuestion(Question question) {
		this.question = question;
	}
	private Integer tid;
	
	public void setTid(Integer tid) {
		this.tid = tid;
	}
	private Integer qtid;
	public void setQtid(Integer qtid) {
		this.qtid = qtid;
	}
	private Integer qid;
	public Integer getQid() {
		return qid;
	}
	public void setQid(Integer qid) {
		this.qid = qid;
	}
	private int page;
	public void setPage(int page) {
		this.page = page;
	}
	private Integer num;
	public void setNum(Integer num) {
		this.num = num;
	}
	//设置试卷
	public String szQuestionPaper(){	
		return "szQuestionPaper";
	}
	public String szAdminQuestionPaper(){
		return "szAdminQuestionPaper";
	}
	//添加试卷
	public String tjQuestionPaper(){
		Date qpdate = new Date();
		questionPaper.setQpdate(qpdate);
		qpService.szQuestionPaper(questionPaper,tid);
		List<QuestionType> listqt = qpService.allQT();
		questionPaper = qpService.getQuestionPaper();  //查询试卷获取试卷id
		ActionContext.getContext().getValueStack().set("listqt", listqt);
		ActionContext.getContext().getValueStack().set("questionPaper", questionPaper);
		return "tjQuestionPaper";
	}
	public String tjAdminQuestionPaper(){
		Date qpdate = new Date();
		questionPaper.setQpdate(qpdate);
		qpService.szAdminQuestionPaper(questionPaper);
		List<QuestionType> listqt = qpService.allQT();
		questionPaper = qpService.getQuestionPaper();  //查询试卷获取试卷id
		ActionContext.getContext().getValueStack().set("listqt", listqt);
		ActionContext.getContext().getValueStack().set("questionPaper", questionPaper);
		return "tjAdminQuestionPaper";
	}
	//为试卷添加试题
	public String tjQuestion(){
		if(qid!=null){
			question = qpService.selectQuestion(qid);
		}
		
		PageBean<Question> pageBean = qpService.ckQuestion(question,tid,qtid,page);
		ActionContext.getContext().getValueStack().set("pageBean", pageBean);
		List<QpRelationq> listqpq = qpService.qpQuestion(questionPaper.getQpid()); //查找试卷中已有的试题
		List<QuestionType> listqt = qpService.allQT();
		ActionContext.getContext().getValueStack().set("questionPaper", questionPaper);
		ActionContext.getContext().getValueStack().set("listqt", listqt);
		ActionContext.getContext().getValueStack().set("pageqtid", qtid);
		ActionContext.getContext().getValueStack().set("listqpq", listqpq);
		
		return "tjQuestion";
	}
	public String tjAdminQuestion(){
		if(qid!=null){
			question = qpService.selectQuestion(qid);
		}
		
		PageBean<Question> pageBean = qpService.ckAdminQuestion(question,qtid,page);
		ActionContext.getContext().getValueStack().set("pageBean", pageBean);
		List<QpRelationq> listqpq = qpService.qpQuestion(questionPaper.getQpid()); //查找试卷中已有的试题
		List<QuestionType> listqt = qpService.allQT();
		ActionContext.getContext().getValueStack().set("questionPaper", questionPaper);
		ActionContext.getContext().getValueStack().set("listqt", listqt);
		ActionContext.getContext().getValueStack().set("pageqtid", qtid);
		ActionContext.getContext().getValueStack().set("listqpq", listqpq);
		return "tjAdminQuestion";
	}
	//为试卷添加试题实现
	public String tjQuestionSX(){
		qpService.tiQuestionSX(questionPaper.getQpid(),qid,num);
		List<QpRelationq> listqpq = qpService.qpQuestion(questionPaper.getQpid()); //查找试卷中已有的试题
		List<QuestionType> listqt = qpService.allQT();
		ActionContext.getContext().getValueStack().set("listqt", listqt);
		ActionContext.getContext().getValueStack().set("questionPaper", questionPaper);
		ActionContext.getContext().getValueStack().set("listqpq", listqpq);
		return "tjQuestionSX";
	}
	public String tjAdminQuestionSX(){
		qpService.tiQuestionSX(questionPaper.getQpid(),qid,num);
		List<QpRelationq> listqpq = qpService.qpQuestion(questionPaper.getQpid()); //查找试卷中已有的试题
		List<QuestionType> listqt = qpService.allQT();
		ActionContext.getContext().getValueStack().set("listqt", listqt);
		ActionContext.getContext().getValueStack().set("questionPaper", questionPaper);
		ActionContext.getContext().getValueStack().set("listqpq", listqpq);
		return "tjAdminQuestionSX";
	}
	//查看试卷
	public String ckQuestionPaper(){
		List<QuestionPaper> list = qpService.ckQuestionPaper(tid);
		ActionContext.getContext().getValueStack().set("list", list);
		return "ckQuestionPaper";
	}
	public String ckAdminQuestionPaper(){
		List<QuestionPaper> list = qpService.ckAdminQuestionPaper();
		ActionContext.getContext().getValueStack().set("list", list);
		return "ckAdminQuestionPaper";
	}
	//查看试卷中的试题
	public String ckQPQuestion(){
		//查看试卷中的试题
		List<QpRelationq> listqpq = qpService.qpQuestion(questionPaper.getQpid()); 
		ActionContext.getContext().getValueStack().set("listqpq", listqpq);
		return "ckQPQuestion";
	}

}
