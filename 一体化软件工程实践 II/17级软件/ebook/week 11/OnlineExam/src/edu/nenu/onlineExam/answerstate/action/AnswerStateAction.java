package edu.nenu.onlineExam.answerstate.action;

import java.io.IOException;
import java.net.URLDecoder;

import javax.servlet.http.HttpServletResponse;

import org.apache.struts2.ServletActionContext;

import edu.nenu.onlineExam.answerstate.entity.AnswerState;
import edu.nenu.onlineExam.answerstate.service.AnswerStateService;

import com.opensymphony.xwork2.ActionSupport;
import com.opensymphony.xwork2.ModelDriven;

public class AnswerStateAction extends ActionSupport implements ModelDriven<AnswerState>{
	private AnswerState answerState = new AnswerState();
	public AnswerState getModel() {
		return answerState;
	}
	private AnswerStateService asService;
	public void setAsService(AnswerStateService asService) {
		this.asService = asService;
	}
	private Integer qid;
	
	public void setQid(Integer qid) {
		this.qid = qid;
	}
	private Integer tnid;

	public void setTnid(Integer tnid) {
		this.tnid = tnid;
	}
	private String qanswer;

	public void setQanswer(String qanswer) {
		this.qanswer = qanswer;
	}
	//根据试题编号，记录编号 进行将试题答案保存
	public String saveAnswerState() throws IOException{
		String qas = java.net.URLDecoder.decode(qanswer, "UTF-8");
		asService.saveAnswerState(tnid,qid,qas);
		return NONE;
	}

}
