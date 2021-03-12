package edu.nenu.onlineExam.adminuser.dao;

import java.util.List;

import org.springframework.orm.hibernate5.support.HibernateDaoSupport;

import edu.nenu.onlineExam.adminuser.entity.AdminUser;
import edu.nenu.onlineExam.teacheruser.entity.Teacher;

public class AdminUserDao extends HibernateDaoSupport{
	
	//管理员登录验证
	public AdminUser login(AdminUser admin) {
		String hql = "from AdminUser where uid = ? and password = ?";
		List<AdminUser> list = (List<AdminUser>) this.getHibernateTemplate().find(hql, admin.getUid(),admin.getPassword());
		if(list != null && list.size() > 0){
			return list.get(0);
		}
		return null;
	}

	public void updatePW(Integer uid, String npw) {
		String hql = "from AdminUser where uid =? ";
		AdminUser admin = null;
		List<AdminUser> list = (List<AdminUser>) this.getHibernateTemplate().find(hql, uid);
		if(list != null && list.size()>0){
			admin = (AdminUser)list.get(0);
		}
		admin.setPassword(npw);
		this.getHibernateTemplate().save(admin);
	}
}
