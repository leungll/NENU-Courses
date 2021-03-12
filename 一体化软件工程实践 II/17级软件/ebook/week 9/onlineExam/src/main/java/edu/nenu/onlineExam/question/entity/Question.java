package edu.nenu.onlineExam.question.entity;

import java.util.Date;
import java.util.HashSet;
import java.util.Set;

import edu.nenu.onlineExam.answerstate.entity.AnswerState;
import edu.nenu.onlineExam.qprelationq.entity.QpRelationq;
import edu.nenu.onlineExam.questiontype.entity.QuestionType;
import edu.nenu.onlineExam.teacheruser.entity.Teacher;

public class Question {
	private Integer qid;		//试题id
	private String qcontent;	//试题内容
	private String aoption;		//选项a
	private String boption;		//选项b
	private String coption;		//选项c
	private String doption;		//选项d
	private String qanswer;		//答案
	private String qanalysis;	//解析
	private String oword;		//关键字
	private String qscope;		//试题范围
	private String qdifficulty; //试题难度
	private Date qdate;			//试题添加日期
	private QuestionType questionType;	//试题类型
	private Teacher teacher;	//添加教师
	private Set<QpRelationq> qpRelationq = new HashSet<QpRelationq>(); //试卷与试题之间的关系
	private Set<AnswerState> answerState = new HashSet<AnswerState>();
	public Set<AnswerState> getAnswerState() {
		return answerState;
	}
	public void setAnswerState(Set<AnswerState> answerState) {
		this.answerState = answerState;
	}
	public Set<QpRelationq> getQpRelationq() {
		return qpRelationq;
	}
	public void setQpRelationq(Set<QpRelationq> qpRelationq) {
		this.qpRelationq = qpRelationq;
	}
	public Integer getQid() {
		return qid;
	}
	public void setQid(Integer qid) {
		this.qid = qid;
	}
	public String getQcontent() {
		return qcontent;
	}
	public void setQcontent(String qcontent) {
		this.qcontent = qcontent;
	}
	public String getAoption() {
		return aoption;
	}
	public void setAoption(String aoption) {
		this.aoption = aoption;
	}
	public String getBoption() {
		return boption;
	}
	public void setBoption(String boption) {
		this.boption = boption;
	}
	public String getCoption() {
		return coption;
	}
	public void setCoption(String coption) {
		this.coption = coption;
	}
	public String getDoption() {
		return doption;
	}
	public void setDoption(String doption) {
		this.doption = doption;
	}
	public String getQanswer() {
		return qanswer;
	}
	public void setQanswer(String qanswer) {
		this.qanswer = qanswer;
	}
	public String getQanalysis() {
		return qanalysis;
	}
	public void setQanalysis(String qanalysis) {
		this.qanalysis = qanalysis;
	}
	public String getOword() {
		return oword;
	}
	public void setOword(String oword) {
		this.oword = oword;
	}
	public String getQscope() {
		return qscope;
	}
	public void setQscope(String qscope) {
		this.qscope = qscope;
	}
	public String getQdifficulty() {
		return qdifficulty;
	}
	public void setQdifficulty(String qdifficulty) {
		this.qdifficulty = qdifficulty;
	}
	public Date getQdate() {
		return qdate;
	}
	public void setQdate(Date qdate) {
		this.qdate = qdate;
	}
	public QuestionType getQuestionType() {
		return questionType;
	}
	public void setQuestionType(QuestionType questionType) {
		this.questionType = questionType;
	}
	public Teacher getTeacher() {
		return teacher;
	}
	public void setTeacher(Teacher teacher) {
		this.teacher = teacher;
	}
	
	
}
