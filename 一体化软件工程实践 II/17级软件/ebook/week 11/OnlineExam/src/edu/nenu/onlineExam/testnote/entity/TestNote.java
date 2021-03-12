package edu.nenu.onlineExam.testnote.entity;

import java.util.Date;
import java.util.HashSet;
import java.util.Set;

import edu.nenu.onlineExam.answerstate.entity.AnswerState;
import edu.nenu.onlineExam.questionpaper.entity.QuestionPaper;
import edu.nenu.onlineExam.student.entity.Students;

public class TestNote {
	private Integer tnid;	//考试记录id
	private String tname;	//考试名称
	private Date tdate;		//考试日期
	private Date stime;		//开始答题时间
	private Date etime;		//交卷时间
	private Integer score;	//考试成绩
	private Students students;
	private QuestionPaper questionPaper;
	private Set<AnswerState> answerState = new HashSet<AnswerState>();
	
	public Set<AnswerState> getAnswerState() {
		return answerState;
	}
	public void setAnswerState(Set<AnswerState> answerState) {
		this.answerState = answerState;
	}
	public Integer getTnid() {
		return tnid;
	}
	public void setTnid(Integer tnid) {
		this.tnid = tnid;
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
	public Date getStime() {
		return stime;
	}
	public void setStime(Date stime) {
		this.stime = stime;
	}
	public Date getEtime() {
		return etime;
	}
	public void setEtime(Date etime) {
		this.etime = etime;
	}
	public Integer getScore() {
		return score;
	}
	public void setScore(Integer score) {
		this.score = score;
	}
	public Students getStudents() {
		return students;
	}
	public void setStudents(Students students) {
		this.students = students;
	}
	public QuestionPaper getQuestionPaper() {
		return questionPaper;
	}
	public void setQuestionPaper(QuestionPaper questionPaper) {
		this.questionPaper = questionPaper;
	}
}
