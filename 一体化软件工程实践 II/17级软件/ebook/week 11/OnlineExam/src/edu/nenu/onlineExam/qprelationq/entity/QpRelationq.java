package edu.nenu.onlineExam.qprelationq.entity;
/**
 * 试卷与试题的对应关系
 */
import edu.nenu.onlineExam.question.entity.Question;
import edu.nenu.onlineExam.questionpaper.entity.QuestionPaper;

public class QpRelationq {
	private Integer rid;	//试卷与试题对应关系id
	private Integer num;	//试卷中试题的序号
	//试卷外键对象
	private QuestionPaper questionPaper;
	//试题外键对象
	private Question question;
	public Integer getRid() {
		return rid;
	}
	public void setRid(Integer rid) {
		this.rid = rid;
	}
	public Integer getNum() {
		return num;
	}
	public void setNum(Integer num) {
		this.num = num;
	}
	public QuestionPaper getQuestionPaper() {
		return questionPaper;
	}
	public void setQuestionPaper(QuestionPaper questionPaper) {
		this.questionPaper = questionPaper;
	}
	public Question getQuestion() {
		return question;
	}
	public void setQuestion(Question question) {
		this.question = question;
	}
}
