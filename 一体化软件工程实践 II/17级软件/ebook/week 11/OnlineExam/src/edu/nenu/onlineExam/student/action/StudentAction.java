package edu.nenu.onlineExam.student.action;

import java.io.IOException;
import java.util.List;
import java.util.Map;

import javax.servlet.http.HttpServletResponse;

import org.apache.struts2.ServletActionContext;
import org.apache.struts2.interceptor.SessionAware;

import com.opensymphony.xwork2.ActionContext;
import com.opensymphony.xwork2.ActionSupport;
import com.opensymphony.xwork2.ModelDriven;

import edu.nenu.onlineExam.answerstate.entity.AnswerState;
import edu.nenu.onlineExam.bj.entity.BJ;
import edu.nenu.onlineExam.bj.service.BJService;
import edu.nenu.onlineExam.student.entity.Students;
import edu.nenu.onlineExam.student.service.StudentService;
import edu.nenu.onlineExam.teacheruser.entity.Teacher;
import edu.nenu.onlineExam.testnote.entity.TestNote;
import edu.nenu.onlineExam.utils.PageBean;

public class StudentAction extends ActionSupport implements ModelDriven<Students>,SessionAware{
	
	private Students student = new Students();
	
	public Students getModel() {
		return student;
	}
	
	private StudentService studentService;

	public void setStudentService(StudentService studentService) {
		this.studentService = studentService;
	}
	
	//接收当前页数
	private int page;
	
	public void setPage(int page) {
		this.page = page;
	}
	//接收班级编号
	private Integer bjid;
	
	public void setStudent(Students student) {
		this.student = student;
	}

	public void setBjid(Integer bjid) {
		this.bjid = bjid;
	}
	private Integer tnid;

	public void setTnid(Integer tnid) {
		this.tnid = tnid;
	}

	//接收教师编号
	private Integer tid;

	public void setTid(Integer tid) {
		this.tid = tid;
	}
	private String npw;
	
	public void setNpw(String npw) {
		this.npw = npw;
	}

	public String slogin(){
		return "loginStudent";
	}
	//验证学号和密码是否正确
	public String login(){
		Students existStudent = studentService.login(student);
		//判断用户是否存在
		if(existStudent == null){
			this.addActionError("学号或密码错误");
			return "loginFailStudent";
		}else{
			ServletActionContext.getRequest().getSession().setAttribute("existStudent", existStudent);
				return "loginSuccessStudent";	
		}		
	}
	//安全退出清除session
	public String sessionDestory(){
		ServletActionContext.getRequest().getSession().invalidate();
		return "sessionDestory";
	}
	//修改密码
	public String upw(){
		return "upwStudent";
	}
	//修改密码实现
	public String updatePW(){
		studentService.updatePW(student.getSid(),npw);
		return "updatePWStudent";
	}
	//查询所有学生信息
	public String ckAllStudent(){
		PageBean<Students> pageBean = studentService.ckStudent(tid,page);
		//将PageBean存入值栈中
		ActionContext.getContext().getValueStack().set("pageBean", pageBean);		
		return "ckAllStudent";
	}
	public String ckAllStudentAdmin(){
		PageBean<Students> pageBean = studentService.ckStudentAdmin(page);
		//将PageBean存入值栈中
		ActionContext.getContext().getValueStack().set("pageBean", pageBean);
		return "ckAllStudentAdmin";
	}
	//根据学号删除学生信息
	public String deleteStudent(){
		studentService.deleteStudent(student.getSid());
		PageBean<Students> pageBean = studentService.ckStudent(tid,page);
		//将PageBean存入值栈中
		ActionContext.getContext().getValueStack().set("pageBean", pageBean);		
		return "ckAllStudent";
	}
	public String deleteStudentAdmin(){
		studentService.deleteStudent(student.getSid());
		PageBean<Students> pageBean = studentService.ckStudentAdmin(page);
		//将PageBean存入值栈中
		ActionContext.getContext().getValueStack().set("pageBean", pageBean);	
		return "ckAllStudentAdmin";
	}
	//添加学生信息
	public String addStudent(){
		List<BJ> list =studentService.ckbj(tid);
		//通过值栈保存返回的list集合
		ActionContext.getContext().getValueStack().set("listbj", list);
		return "addStudent";
	}
	public String addStudentAdmin(){
		List<BJ> list =studentService.ckbjAdmin();
		//通过值栈保存返回的list集合
		ActionContext.getContext().getValueStack().set("listbj", list);
		return "addStudentAdmint";
	}
	//完善学生信息
	public String wsStudent(){
		Students stu = studentService.cxStudent(student.getSid());
		ActionContext.getContext().getValueStack().set("stu", stu);
		return "wsStudent";
	}
	//完善学生信息
	public String wsStudentSX(){
		studentService.wsStudentSX(student);
		return "wsStudentSX";
	}
	//查询学生信息
	public String myBJ(){
		BJ bj = studentService.myBJ(student.getSid());
		ActionContext.getContext().getValueStack().set("bj", bj);
		return "myBJ";
	}

	/**
	 * AJAX进行异步校验班级名的执行方法
	 * @return
	 * @throws IOException 
	 */
	public String findBySid() throws IOException{
		Students existStudent = studentService.findBySid(student.getSid());
		//获得response对象，向页面输出
		HttpServletResponse response = ServletActionContext.getResponse();
		response.setContentType("text/html;charset=UTF-8");
		//判断
		if(existStudent != null){
			//查询到班级：班级名存在
			response.getWriter().print("t");
		}else{
			//没有查到该班级：班级名不存在，可以使用
			response.getWriter().print("f");
		}
		return NONE;
	}
	//添加学生信息实现
	public String addStudentSX(){
		studentService.addStudentSX(student,bjid);
		return "addStudentSX";
	}
	//查看考试记录
	public String ckTestNote(){
		List<TestNote> testNotes = studentService.ckTestNote(student.getSid());
		ActionContext.getContext().getValueStack().set("testNotes", testNotes);
		return "ckTestNote";
	}
	//查看试卷答题情况
	public String ckAnswerState(){
		//查看选择题
		List<AnswerState> answerStatesxz = studentService.ckAnswerStatexz(tnid);
		//查看判断题
		List<AnswerState> answerStatespd = studentService.ckAnswerStatepd(tnid);
		//查看填空题
		List<AnswerState> answerStatestk = studentService.ckAnswerStatetk(tnid);
		ActionContext.getContext().getValueStack().set("answerStatesxz", answerStatesxz);
		ActionContext.getContext().getValueStack().set("answerStatespd", answerStatespd);
		ActionContext.getContext().getValueStack().set("answerStatestk", answerStatestk);
		return "ckAnswerState";
	}
	//查看学生信息
	public String ckStudentXX(){
		Students stu = studentService.ckStudentXX(student.getSid());
		ActionContext.getContext().getValueStack().set("stu", stu);
		return "ckStudentXX";
	}
	public void setSession(Map<String, Object> arg0) {
	
	}
}
