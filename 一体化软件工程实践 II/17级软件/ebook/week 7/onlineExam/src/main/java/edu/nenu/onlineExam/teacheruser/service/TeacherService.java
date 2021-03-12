package edu.nenu.onlineExam.adminuser.service;

import org.springframework.transaction.annotation.Transactional;

import edu.nenu.onlineExam.teacheruser.dao.TeacherDao;
import edu.nenu.onlineExam.Teacheruser.entity.Teacher;

@Transactional
public class TeacherService {
	
	private TeacherDao teacherUserDao;

	public void setTeacherDao(TeacherDao teacherDao) {
		this.teacherDao = teacherDao;
	}
	
	//����Ա��¼��֤
	public Teacher login(Teacher teacher) {
		return teacherDao.login(teacher);
	}

	public void updatePW(Integer tid, String npw) {
		teacherDao.updatePW(tid,npw);
	}

	public void deleteTeacher(Integer tid)
	{
		teacherDao.deleteTeacher(tid);
	}
	
	public void addTeacher(Teacher teacher)
	{
		teacherDao.addTeacher(teacher);
	}
}
