package edu.nenu.onlineExam.adminuser.action;

import java.util.Map;

import org.apache.struts2.ServletActionContext;
import org.apache.struts2.interceptor.SessionAware;

import edu.nenu.onlineExam.adminuser.entity.AdminUser;
import edu.nenu.onlineExam.adminuser.service.AdminUserService;
 

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

	//����Ա��¼
	public String alogin(){
		return "alogin";
	}
	
	//��֤����Ա��ź������Ƿ���ȷ
	public String login(){
		//���մ����ݿ��в�ѯ����Ϣ
		AdminUser existAdmin = adminUserService.login(admin);
		//�ж��û��Ƿ����
		if(existAdmin == null){
			this.addActionError("����Ա��Ż��������");
			return "loginFailadmin";
		}else{
			//����û����ڣ����û���Ϣ�浽session��
			ServletActionContext.getRequest().getSession().setAttribute("existAdmin", existAdmin);
			return "loginSuccessadmin";	
		}		
	}
	//�鿴����Ա��Ϣ
	public String ckxx(){
		return "ckxxadmin";
	}
	//�޸�����
	public String upw(){
		return "upwadmin";
	}
	public String updatePW(){
		adminUserService.updatePW(admin.getUid(),npw);
		return "updateadminPW";
	}
	//��ȫ�˳����session
	public String sessionDestory(){
		ServletActionContext.getRequest().getSession().invalidate();
		return "sessionDestoryadmin";
	}

	public void setSession(Map<String, Object> arg0) {
	}
}
