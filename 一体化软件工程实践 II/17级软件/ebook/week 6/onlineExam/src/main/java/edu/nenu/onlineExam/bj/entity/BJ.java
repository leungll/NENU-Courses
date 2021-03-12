package edu.nenu.onlineExam.bj.entity;

import edu.nenu.onlineExam.adminuser.entity.Teacher;
public class BJ {
	private Integer bjid;
	   private String bjname;
	   private Teacher teacher;
		
   public Integer getBjid() {
		return bjid;
	}
	public void setBjid(Integer bjid) {
		this.bjid = bjid;
	}
	public String getBjname() {
		return bjname;
	}
	public void setBjname(String bjname) {
		this.bjname = bjname;
	}
	public Teacher getTeacher() {
		return teacher;
	}
	public void setTeacher(Teacher teacher) {
		this.teacher = teacher;
	}

}
