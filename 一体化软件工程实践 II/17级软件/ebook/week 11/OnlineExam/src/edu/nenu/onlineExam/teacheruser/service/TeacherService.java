package edu.nenu.onlineExam.teacheruser.service;

import java.util.List;

import org.springframework.transaction.annotation.Transactional;

import edu.nenu.onlineExam.teacheruser.dao.TeacherDao;
import edu.nenu.onlineExam.teacheruser.entity.Teacher;

@Transactional
public class TeacherService {
	//注入TeacherDao
	private TeacherDao teacherDao;

	public void setTeacherDao(TeacherDao teacherDao) {
		this.teacherDao = teacherDao;
	}

	public Teacher login(Teacher teacher) {
		
		return teacherDao.login(teacher);
	}

	public void updatePW(Integer tid, String npw) {
		teacherDao.updatePW(tid,npw);
	}
	//查询所有教师信息
	public List<Teacher> ckAllTeacher() {
		return teacherDao.ckAllTeacher();
	}
	//根据教师编号查询教师信息
	public Teacher ckTeacherXX(Integer tid) {
		return teacherDao.ckTeacherXX(tid);
	}
	//根据教师编号删除教师
	public void deleteTeacherAdmin(Integer tid) {
		teacherDao.deleteTeacherAdmin(tid);
	}
	//添加教师
	public void addTeacherSX(Teacher teacher) {
		teacherDao.addTeacherSX(teacher);
	}
}
