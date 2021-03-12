package edu.nenu.onlineExam.adminuser.action;

import java.util.Map;

import org.apache.struts2.ServletActionContext;
import org.apache.struts2.interceptor.SessionAware;

import edu.nenu.onlineExam.adminuser.entity.AdminUser;
import edu.nenu.onlineExam.adminuser.service.AdminUserService;
import edu.nenu.onlineExam.teacheruser.entity.Teacher;

import com.opensymphony.xwork2.ActionSupport;
import com.opensymphony.xwork2.ModelDriven;

public class AdminUserAction extends ActionSupport implements ModelDriven<AdminUser> ,SessionAware{
	private AdminUser admin = new AdminUser();
	private AdminUserService adminUserService;
	
	public void setAdminUserService(AdminUserService adminUserService) {
		this.adminUserService = adminUserService;
	}

	public AdminUser getModel() {
		return admin;
	}
	
	private String npw;
	public void setNpw(String npw) {
		this.npw = npw;
	}

	//管理员登录
	public String alogin(){
		return "alogin";
	}
	
	//验证管理员编号和密码是否正确
	public String login(){
		//接收从数据库中查询的信息
		AdminUser existAdmin = adminUserService.login(admin);
		//判断用户是否存在
		if(existAdmin == null){
			this.addActionError("管理员编号或密码错误");
			return "loginFailadmin";
		}else{
			//如果用户存在，将用户信息存到session中
			ServletActionContext.getRequest().getSession().setAttribute("existAdmin", existAdmin);
			return "loginSuccessadmin";	
		}		
	}
	//查看管理员信息
	public String ckxx(){
		return "ckxxadmin";
	}
	//修改密码
	public String upw(){
		return "upwadmin";
	}
	public String updatePW(){
		adminUserService.updatePW(admin.getUid(),npw);
		return "updateadminPW";
	}
	//安全退出清除session
	public String sessionDestory(){
		ServletActionContext.getRequest().getSession().invalidate();
		return "sessionDestoryadmin";
	}

	public void setSession(Map<String, Object> arg0) {
	}
}
