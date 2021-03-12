package edu.nenu.onlineExam.student.entity;

import java.util.HashSet;
import java.util.Set;

import edu.nenu.onlineExam.bj.entity.BJ;
import edu.nenu.onlineExam.testnote.entity.TestNote;

public class Students {
	private Integer sid;
	private String password;
	private String name;
	private String phone;
	private String email;
	private BJ bj;
	private Set<TestNote> testNote = new HashSet<TestNote>();
	
	public Set<TestNote> getTestNote() {
		return testNote;
	}
	public void setTestNote(Set<TestNote> testNote) {
		this.testNote = testNote;
	}
	public Integer getSid() {
		return sid;
	}
	public void setSid(Integer sid) {
		this.sid = sid;
	}
	public String getPassword() {
		return password;
	}
	public void setPassword(String password) {
		this.password = password;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
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
	public BJ getBj() {
		return bj;
	}
	public void setBj(BJ bj) {
		this.bj = bj;
	}
}
