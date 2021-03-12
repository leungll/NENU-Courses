package edu.nenu.onlineExam.testcontrol.action;

import java.util.Date;
import java.util.List;

import edu.nenu.onlineExam.qprelationq.entity.QpRelationq;
import edu.nenu.onlineExam.questionpaper.entity.QuestionPaper;
import edu.nenu.onlineExam.student.entity.Students;
import edu.nenu.onlineExam.testcontrol.entity.TestControl;
import edu.nenu.onlineExam.testcontrol.service.TestControlService;
import edu.nenu.onlineExam.testnote.entity.TestNote;

import com.opensymphony.xwork2.ActionContext;
import com.opensymphony.xwork2.ActionSupport;
import com.opensymphony.xwork2.ModelDriven;

public class TestControlAction extends ActionSupport implements ModelDriven<TestControl>{
	private TestControl testControl = new TestControl();
	public TestControl getModel() {
		return testControl;
	}
	private TestControlService tcService;
	public void setTcService(TestControlService tcService) {
		this.tcService = tcService;
	}
	private Integer qpid;
	public void setQpid(Integer qpid) {
		this.qpid = qpid;
	}
	private Integer sid;
	
	public void setSid(Integer sid) {
		this.sid = sid;
	}
	//进入设置考试信息页面
	public String szTest(){
		List<QuestionPaper> list = tcService.ckQuestionPaper();
		ActionContext.getContext().getValueStack().set("list", list);
		return "szTest";
	}
	//添加考试信息
	public String addTestControl(){
		Date date = new Date();
		testControl.setTdate(date);
		tcService.addTestControl(testControl,qpid);
		return "addTestControl";
	}
	//查看考场信息
	public String ckTestControl(){
		TestControl tc = tcService.ckTestControl();
		if(tc.getState()==0){
			return "closeTestControl";
		}else{
			ActionContext.getContext().getValueStack().set("tc", tc);
			return "openTestControl";
		}
	}
	//打开考场
	public String openTest(){
		tcService.openTest();
		return "openTest";
	}
	//关闭考场
	public String closeTest(){
		tcService.closeTest();
		return "closeTest";
	}
	//查询考试方式
	public String ckTestControlMode(){
		TestControl tc = tcService.ckTestControl();
		TestNote tn = tcService.ckTestNote(sid);
		Students stu = tcService.ckStudents(sid);
		ActionContext.getContext().getValueStack().set("stu", stu);
		TestNote tn1 = new TestNote();
		tn1.setStudents(stu);
		tn1.setTdate(tc.getTdate());
		tn1.setTname(tc.getTname());
		if(tn != null && tn.getTname().equals(tc.getTname()) && tn.getTdate().equals(tc.getTdate())){
			return "testend";
		}else{
			//tc.getMode() == 2 表示随机抽取试卷
			if(tc.getMode() == 2){					
				//随机抽取试卷
				QuestionPaper qp = tcService.cqQuestionPaper();
				ActionContext.getContext().getValueStack().set("qp", qp);
				Date stime = new Date();
				tn1.setQuestionPaper(qp);
				tn1.setStime(stime);
				//保存考试记录
				tcService.saveTestNote(tn1);
				TestNote tn2 = tcService.ckTestNote(sid);
				//将试题和考试记录id保存到AnswerState表中
				tcService.saveQuestionTN(qp,tn2); 
				List<QpRelationq> listxzqpq = tcService.ckxzQpRelationq(qp.getQpid());
				List<QpRelationq> listpdqpq = tcService.ckpdQpRelationq(qp.getQpid());
				List<QpRelationq> listtkqpq = tcService.cktkQpRelationq(qp.getQpid());
				ActionContext.getContext().getValueStack().set("listxzqpq", listxzqpq);
				ActionContext.getContext().getValueStack().set("listpdqpq", listpdqpq);
				ActionContext.getContext().getValueStack().set("listtkqpq", listtkqpq);
				ActionContext.getContext().getValueStack().set("tn", tn2);
				return "StartTest";
			}else{	
				//指定试卷进行考试
				QuestionPaper qp = tcService.hqQuestionPaper(tc.getQuestionPaper().getQpid());
				ActionContext.getContext().getValueStack().set("qp", qp);
				Date stime = new Date();
				tn1.setQuestionPaper(qp);
				tn1.setStime(stime);
				//保存考试记录
				tcService.saveTestNote(tn1);
				TestNote tn2 = tcService.ckTestNote(sid);
				//将试题和考试记录id保存到AnswerState表中
				tcService.saveQuestionTN(qp,tn2); 
				List<QpRelationq> listxzqpq = tcService.ckxzQpRelationq(qp.getQpid());
				List<QpRelationq> listpdqpq = tcService.ckpdQpRelationq(qp.getQpid());
				List<QpRelationq> listtkqpq = tcService.cktkQpRelationq(qp.getQpid());
				ActionContext.getContext().getValueStack().set("listxzqpq", listxzqpq);
				ActionContext.getContext().getValueStack().set("listpdqpq", listpdqpq);
				ActionContext.getContext().getValueStack().set("listtkqpq", listtkqpq);
				ActionContext.getContext().getValueStack().set("tn", tn2);
				return "StartTest";
			}
		}
	}
}
