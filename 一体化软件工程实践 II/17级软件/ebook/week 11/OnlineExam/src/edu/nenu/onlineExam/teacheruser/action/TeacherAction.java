package edu.nenu.onlineExam.teacheruser.action;

import java.io.IOException;
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletResponse;

import org.apache.struts2.ServletActionContext;
import org.apache.struts2.interceptor.SessionAware;

import edu.nenu.onlineExam.student.entity.Students;
import edu.nenu.onlineExam.teacheruser.entity.Teacher;
import edu.nenu.onlineExam.teacheruser.service.TeacherService;

import com.opensymphony.xwork2.ActionContext;
import com.opensymphony.xwork2.ActionSupport;
import com.opensymphony.xwork2.ModelDriven;

public class TeacherAction extends ActionSupport implements ModelDriven<Teacher>,SessionAware{
	//模型驱动使用的对象
	private Teacher teacher = new Teacher();
	
	public Teacher getModel() {
		return teacher;
	}
	
	//注入TeacherService
	private TeacherService teacherService;

	public void setTeacherService(TeacherService teacherService) {
		this.teacherService = teacherService;
	}
	//获取新密码
	private String npw ;

	public void setTeacher(Teacher teacher) {
		this.teacher = teacher;
	}

	public void setNpw(String npw) {
		this.npw = npw;
	}

	public String tlogin(){
		return "login";
	}
	
	//验证教师编号和密码是否正确
	public String login(){
		Teacher existTeacher = teacherService.login(teacher);
		//判断用户是否存在
		if(existTeacher == null){
			this.addActionError("教师编号或密码错误");
			return "loginFail";
		}else{
			ServletActionContext.getRequest().getSession().setAttribute("existTeacher", existTeacher);
				return "loginSuccess";	
		}		
	}
	//安全退出清除session
	public String sessionDestory(){
		ServletActionContext.getRequest().getSession().invalidate();
		return "sessionDestoryteacher";
	}
	//查看教师信息
	public String ckxx(){
		return "ckxx";
	}
	//查看所有教师
	public String ckAllTeacherAdmin(){
		List<Teacher>  list = teacherService.ckAllTeacher();
		ActionContext.getContext().getValueStack().set("list", list);
		return "ckAllTeacherAdmin";
	}
	//根据教师编号查询教师信息
	public String ckTeacherXX(){
		Teacher t = teacherService.ckTeacherXX(teacher.getTid());
		ActionContext.getContext().getValueStack().set("t", t);
		return "ckTeacherXX";
	}
	//根据教师编号删除教师
	public String deleteTeacherAdmin(){
		teacherService.deleteTeacherAdmin(teacher.getTid());
		List<Teacher>  list = teacherService.ckAllTeacher();
		ActionContext.getContext().getValueStack().set("list", list);
		return "ckAllTeacherAdmin";
	}
	//校验教师编号是否被使用
	public String findByTid() throws IOException{
		Teacher existTeacher = teacherService.ckTeacherXX(teacher.getTid());
		//获得response对象，向页面输出
		HttpServletResponse response = ServletActionContext.getResponse();
		response.setContentType("text/html;charset=UTF-8");
		//判断
		if(existTeacher != null){
			//查询到教师，存在
			response.getWriter().print("t");
		}else{
			//没有查到该教师：教师不存在，可以使用
			response.getWriter().print("f");
		}
		return NONE;
	}
	//添加教师
	public String addTeacherAdmin(){
		return "addTeacherAdmin";
	}
	//添加教师实现
	public String addTeacherSX(){
		teacherService.addTeacherSX(teacher);
		return "addTeacherSX";
	}
	//修改密码
	public String upw(){
		return "upw";
	}
	//修改密码实现
	public String updatePW(){
		teacherService.updatePW(teacher.getTid(),npw);
		return "updatePW";
	}
	@Override
	public String execute() throws Exception {
		// TODO Auto-generated method stub
		return "NONE";
	}

	public void setSession(Map<String, Object> arg0) {
	}
}
