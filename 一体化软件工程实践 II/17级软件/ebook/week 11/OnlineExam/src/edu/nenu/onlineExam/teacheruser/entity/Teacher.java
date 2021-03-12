package edu.nenu.onlineExam.teacheruser.entity;

import java.util.HashSet;
import java.util.Set;

import edu.nenu.onlineExam.bj.entity.BJ;
import edu.nenu.onlineExam.question.entity.Question;

/**
 * 教师实体类
 * @author xxn
 *
 */
public class Teacher {
	private Integer tid;		//教师编号
	private String password;	//密码
	private String tname;		//教师姓名	
	private String phone;		//教师电话
	private String email;		//邮箱
	private Set<BJ> bjs = new HashSet<BJ>();
	private Set<Question> questions = new HashSet<Question>();
	
	public Set<Question> getQuestions() {
		return questions;
	}
	public void setQuestions(Set<Question> questions) {
		this.questions = questions;
	}
	public Set<BJ> getBjs() {
		return bjs;
	}
	public void setBjs(Set<BJ> bjs) {
		this.bjs = bjs;
	}
	public Integer getTid() {
		return tid;
	}
	public void setTid(Integer tid) {
		this.tid = tid;
	}
	public String getPassword() {
		return password;
	}
	public void setPassword(String password) {
		this.password = password;
	}
	public String getTname() {
		return tname;
	}
	public void setTname(String tname) {
		this.tname = tname;
	}
	public String getPhone() {
		return phone;
	}
	public void setPhone(String phone) {
		this.phone = phone;
	}
	public String getEmail() {
		return email;
	}
	public void setEmail(String email) {
		this.email = email;
	}
	
}
