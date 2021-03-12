package edu.nenu.onlineExam.adminuser.service;

import org.springframework.transaction.annotation.Transactional;

import edu.nenu.onlineExam.adminuser.dao.AdminUserDao;
import edu.nenu.onlineExam.adminuser.entity.AdminUser;
import edu.nenu.onlineExam.teacheruser.entity.Teacher;

@Transactional
public class AdminUserService {
	
	private AdminUserDao adminUserDao;

	public void setAdminUserDao(AdminUserDao adminUserDao) {
		this.adminUserDao = adminUserDao;
	}
	
	//管理员登录验证
	public AdminUser login(AdminUser admin) {
		return adminUserDao.login(admin);
	}

	public void updatePW(Integer uid, String npw) {
		adminUserDao.updatePW(uid,npw);
	}

}
