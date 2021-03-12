package edu.nenu.onlineExam.testcontrol.entity;
/**
 * 考场控制
 */
import java.util.Date;

import edu.nenu.onlineExam.questionpaper.entity.QuestionPaper;

public class TestControl {
	private Integer tcid;	//考场控制id
	private Integer state;	//考场状态0(考场关闭)/1(考场打开)
	private Integer mode;	//考试方式2(随机抽取试卷)/3(指定试卷)
	private String tname;	//考试名称
	private Date tdate;		//考试时间
	private QuestionPaper questionPaper;
	
	public QuestionPaper getQuestionPaper() {
		return questionPaper;
	}
	public void setQuestionPaper(QuestionPaper questionPaper) {
		this.questionPaper = questionPaper;
	}
	public Integer getTcid() {
		return tcid;
	}
	public void setTcid(Integer tcid) {
		this.tcid = tcid;
	}
	public Integer getState() {
		return state;
	}
	public void setState(Integer state) {
		this.state = state;
	}
	public Integer getMode() {
		return mode;
	}
	public void setMode(Integer mode) {
		this.mode = mode;
	}
	public String getTname() {
		return tname;
	}
	public void setTname(String tname) {
		this.tname = tname;
	}
	public Date getTdate() {
		return tdate;
	}
	public void setTdate(Date tdate) {
		this.tdate = tdate;
	}
	
}
