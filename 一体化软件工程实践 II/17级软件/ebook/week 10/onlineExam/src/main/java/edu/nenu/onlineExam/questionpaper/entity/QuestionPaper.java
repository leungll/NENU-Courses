package edu.nenu.onlineExam.questionpaper.entity;

import java.util.Date;
import java.util.HashSet;
import java.util.Set;

import edu.nenu.onlineExam.qprelationq.entity.QpRelationq;
import edu.nenu.onlineExam.teacheruser.entity.Teacher;
import edu.nenu.onlineExam.testcontrol.entity.TestControl;
import edu.nenu.onlineExam.testnote.entity.TestNote;

public class QuestionPaper {
	private Integer qpid;	//试卷内容
	private Date qpdate;	//试卷生成日期
	private Integer time;	//考试时长
	private Teacher teacher; //教师

	private Set<QpRelationq> qpRelationq = new HashSet<QpRelationq> ();
	
	
	public Teacher getTeacher() {
		return teacher;
	}
	public void setTeacher(Teacher teacher) {
		this.teacher = teacher;
	}
	
	public Integer getQpid() {
		return qpid;
	}
	public void setQpid(Integer qpid) {
		this.qpid = qpid;
	}
	public Date getQpdate() {
		return qpdate;
	}
	public void setQpdate(Date qpdate) {
		this.qpdate = qpdate;
	}
	public Integer getTime() {
		return time;
	}
	public void setTime(Integer time) {
		this.time = time;
	}
	
	public Set<QpRelationq> getQpRelationq() {
		return qpRelationq;
	}
	public void setQpRelationq(Set<QpRelationq> qpRelationq) {
		this.qpRelationq = qpRelationq;
	}
	
}
