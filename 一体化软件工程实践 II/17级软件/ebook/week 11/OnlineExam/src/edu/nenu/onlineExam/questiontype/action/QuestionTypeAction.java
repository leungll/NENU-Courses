package edu.nenu.onlineExam.questiontype.action;

import edu.nenu.onlineExam.questiontype.entity.QuestionType;
import edu.nenu.onlineExam.questiontype.service.QuestionTypeService;

import com.opensymphony.xwork2.ActionSupport;
import com.opensymphony.xwork2.ModelDriven;

public class QuestionTypeAction extends ActionSupport implements ModelDriven<QuestionType>{
	
	private QuestionType questionType = new QuestionType();
	public QuestionType getModel() {
		return questionType;
	}
	
	private QuestionTypeService qtService;
	public void setQtService(QuestionTypeService qtService) {
		this.qtService = qtService;
	}

}
