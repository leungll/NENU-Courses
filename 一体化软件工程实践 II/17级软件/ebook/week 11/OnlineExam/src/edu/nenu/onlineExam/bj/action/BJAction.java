package edu.nenu.onlineExam.bj.action;

import java.io.IOException;
import java.util.Iterator;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts2.ServletActionContext;

import edu.nenu.onlineExam.bj.entity.BJ;
import edu.nenu.onlineExam.bj.service.BJService;
import edu.nenu.onlineExam.student.entity.Students;
import edu.nenu.onlineExam.teacheruser.entity.Teacher;

import com.opensymphony.xwork2.ActionContext;
import com.opensymphony.xwork2.ActionSupport;
import com.opensymphony.xwork2.ModelDriven;

public class BJAction extends ActionSupport implements ModelDriven<BJ>{
	
	private BJ bj = new BJ();
	public BJ getModel() {
		return bj;
	}
	private Integer sid;
	public void setSid(Integer sid) {
		this.sid = sid;
	}
	private Integer tid;
	public void setTid(Integer tid) {
		this.tid = tid;
	}
	
	private BJService bjService;

	public void setBjService(BJService bjService) {
		this.bjService = bjService;
	}
	
	/**
	 * 查看班级
	 * @return
	 */
	public String ckbj(){
		Teacher teacher = (Teacher) ServletActionContext.getRequest().getSession().getAttribute("existTeacher");
		List<BJ> listbj = bjService.ckbj(teacher.getTid());
		//通过值栈保存返回的list集合
		ActionContext.getContext().getValueStack().set("listbj", listbj);
		return "ckbj";
	}
	public String ckbjAdmin(){
		List<BJ> listbj = bjService.ckbjAdmin();
		//通过值栈保存返回的list集合
		ActionContext.getContext().getValueStack().set("listbj", listbj);
		return "ckbjAdmin";
	}
	/**
	 * 跳转到添加班级页面
	 * @return
	 */
	public String addbj(){	
		return "addbj";
	}
	public String addbjAdmin(){
		return "addbjAdmin";
	}
	/**
	 * AJAX进行异步校验用户名的执行方法
	 * @return
	 * @throws IOException 
	 */
	public String findByName() throws IOException{
		BJ existBJ = bjService.findByName(java.net.URLDecoder.decode(bj.getBjname(), "UTF-8"));
		//获得response对象，向页面输出
		HttpServletResponse response = ServletActionContext.getResponse();
		response.setContentType("text/html;charset=UTF-8");
		//判断
		if(existBJ != null){
			//查询到班级：班级名存在
			response.getWriter().print("t");
		}else{
			//没有查到该班级：班级名不存在，可以使用
			response.getWriter().print("f");
		}
		return NONE;
	}
	/**
	 * 添加班级实现
	 * @return
	 */
	public String addbjsx(){
		bjService.addbjsx(bj,tid);
		return "addbjsx";
	}
	
	public String deleteBJ(){
		bjService.deleteBJ(bj.getBjid());
		return "deleteBJ";
	}
	public String deleteBJAdmin(){
		bjService.deleteBJ(bj.getBjid());
		return "deleteBJAdmin";
	}
	//根据班级id查看班级信息
	public String ckBJStudents(){
		List<Students> liststu = bjService.ckBJStudents(bj.getBjid());
		ActionContext.getContext().getValueStack().set("liststu", liststu);
		ActionContext.getContext().getValueStack().set("bjid", bj.getBjid());
		return "ckBJStudents";
	}
	//根据学号删除学生信息
	public String deleteBJStudent(){
		bjService.deleteBJStudent(sid);
		List<Students> liststu = bjService.ckBJStudents(bj.getBjid());
		ActionContext.getContext().getValueStack().set("liststu", liststu);
		ActionContext.getContext().getValueStack().set("bjid", bj.getBjid());
		return "ckBJStudents";
	}
	@Override
	public String execute() throws Exception {
		// TODO Auto-generated method stub
		return super.execute();
	}

}
