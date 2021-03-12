package edu.nenu.onlineExam.teacheruser.action;

import java.util.Map;

import org.apache.struts2.ServletActionContext;
import org.apache.struts2.interceptor.SessionAware;

import edu.nenu.onlineExam.teacheruser.entity.Teacher;
import edu.nenu.onlineExam.teacheruser.service.TeacherService;
 

import com.opensymphony.xwork2.ActionSupport;
import com.opensymphony.xwork2.ModelDriven;

public class TeacherAction extends ActionSupport implements ModelDriven<Teacher> ,SessionAware{
	private Teacher teacher = new Teacher();
	private TeacherService teacherService;
	
	public void seTeacherService(TeacherService teacherService) {
		this.teacherService = teacherService;
	}

	public Teacher getModel() {
		return teacher;
	}
	
	private String npw;
	public void setNpw(String npw) {
		this.npw = npw;
	}


	public String alogin(){
		return "alogin";
	}
	

	public String login(){
	
		Teacher existTeacher = teacherService.login(teacher);
		if(existTeacher == null){
			this.addActionError("ΩÃ ¶±‡∫≈ªÚ√‹¬Î¥ÌŒÛ");
			return "loginFail";
		}else{
			
			ServletActionContext.getRequest().getSession().setAttribute("existTeacher", existTeacher);
			return "loginSuccess";	
		}		
	}

	public String ckxx(){
		return "ckxxteacher";
	}

	public String upw(){
		return "upwteacher";
	}
	public String updatePW(){
		teacherService.updatePW(teacher.getTid(),npw);
		return "updateteacherPW";
	}
	
	public void addTeacher()  {
		
		teacherService.addTeacher(teacher);
	}
	
	public void deleteTeacher(Integer tid)
	{
		teacherService.deleteTeacher(tid);
	}
	
	public String sessionDestory(){
		ServletActionContext.getRequest().getSession().invalidate();
		return "sessionDestoryteacher";
	}

	public void setSession(Map<String, Object> arg0) {
	}
}
