package edu.nenu.onlineExam.questionpaper.entity;

import java.util.Date;
import java.util.HashSet;
import java.util.Set;

import edu.nenu.onlineExam.qprelationq.entity.QpRelationq;
import edu.nenu.onlineExam.teacheruser.entity.Teacher;
import edu.nenu.onlineExam.testcontrol.entity.TestControl;
import edu.nenu.onlineExam.testnote.entity.TestNote;

public class QuestionPaper {
	private Integer qpid;	//试卷id
	private Date qpdate;	//出卷时间
	private Integer time;	//考试时长
	private Teacher teacher; 
	//配置试卷与试题关系的集合
	private Set<QpRelationq> qpRelationq = new HashSet<QpRelationq> ();
	private Set<TestControl> testControl = new HashSet<TestControl>();
	private Set<TestNote> testNote = new HashSet<TestNote>();
	
	public Set<TestNote> getTestNote() {
		return testNote;
	}
	public void setTestNote(Set<TestNote> testNote) {
		this.testNote = testNote;
	}
	public Set<TestControl> getTestControl() {
		return testControl;
	}
	public void setTestControl(Set<TestControl> testControl) {
		this.testControl = testControl;
	}
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
