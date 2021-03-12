package edu.nenu.onlineExam.teacheruser.dao;

import java.util.List;

import org.springframework.orm.hibernate5.support.HibernateDaoSupport;

import edu.nenu.onlineExam.teacheruser.entity.Teacher;


public class TeacherUserDao extends HibernateDaoSupport{
	
	//����Ա��¼��֤
	public Teacher login(Teacher teacher) {
		String hql = "from Teacher where tid = ? and password = ?";
		List<Teacher> list = (List<Teacher>) this.getHibernateTemplate().find(hql, teacher.getTid(),teacher.getPassword());
		if(list != null && list.size() > 0){
			return list.get(0);
		}
		return null;
	}

	public void updatePW(Integer tid, String npw) {
		String hql = "from Teacher where tid =? ";
		Teacher teacher = null;
		List<Teacher> list = (List<Teacher>) this.getHibernateTemplate().find(hql, tid);
		if(list != null && list.size()>0){
			teacher = (Teacher)list.get(0);
		}
		teacher.setPassword(npw);
		this.getHibernateTemplate().save(teacher);
	}
	
	public void addTeacher(Teacher teacher)
	{
		this.getHibernateTemplate().save(teacher);
	}
	public void deleteTeacher(Integer tid )
	{		
		String hql = "from Teacher where tid =? ";
	    Teacher teacher = null;
	   List<Teacher> list = (List<Teacher>) this.getHibernateTemplate().find(hql, tid);
	    if(list != null && list.size()>0){
		 this.getHibernateTemplate().delete(list.get(0));
     	}
		
	}
}
