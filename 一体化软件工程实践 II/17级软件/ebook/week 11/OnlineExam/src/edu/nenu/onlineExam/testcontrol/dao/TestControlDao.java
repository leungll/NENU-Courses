package edu.nenu.onlineExam.testcontrol.dao;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

import org.springframework.orm.hibernate5.support.HibernateDaoSupport;

import edu.nenu.onlineExam.answerstate.entity.AnswerState;
import edu.nenu.onlineExam.qprelationq.entity.QpRelationq;
import edu.nenu.onlineExam.question.entity.Question;
import edu.nenu.onlineExam.questionpaper.entity.QuestionPaper;
import edu.nenu.onlineExam.student.entity.Students;
import edu.nenu.onlineExam.testcontrol.entity.TestControl;
import edu.nenu.onlineExam.testnote.entity.TestNote;

public class TestControlDao extends HibernateDaoSupport {
	
	//查询所有试卷
	public List<QuestionPaper> ckQuestionPaper() {
		String hql = "from QuestionPaper";
		List<QuestionPaper> list = (List<QuestionPaper>) this.getHibernateTemplate().find(hql, null);
		if(list != null && list.size() > 0 ){
			return list;
		}
		return null;
	}
	//添加考试信息
	public void addTestControl(TestControl testControl, Integer qpid) {
		String hql = "from QuestionPaper where qpid = ?";
		//根据试卷id查询试卷信息
		List<QuestionPaper> list = (List<QuestionPaper>) this.getHibernateTemplate().find(hql, qpid);
		if(list != null && list.size() > 0){
			//如果是指定试卷考试方式将试卷信息添加到考场控制对象中
			testControl.setQuestionPaper(list.get(0));
		}
		//保存考场控制对象
		this.getHibernateTemplate().save(testControl);
	}
	//打开考场
	public void openTest() {
		String hql = "from TestControl tc order by tc.tdate desc";
		List<TestControl> list = (List<TestControl>) this.getHibernateTemplate().find(hql, null);
		if(list != null && list.size() > 0){
			TestControl tc = list.get(0);
			tc.setState(1);
			this.getHibernateTemplate().save(tc);
		}
	}
	//关闭考场
	public void closeTest() {
		String hql = "from TestControl tc order by tc.tdate desc";
		List<TestControl> list = (List<TestControl>) this.getHibernateTemplate().find(hql, null);
		if(list != null && list.size() > 0){
			TestControl tc = list.get(0);
			tc.setState(0);
			this.getHibernateTemplate().save(tc);
		}
	}
	//查看考场信息
	public TestControl ckTestControl() {
		String hql = "from TestControl tc order by tc.tdate desc";
		List<TestControl> list = (List<TestControl>) this.getHibernateTemplate().find(hql, null);
		if(list != null && list.size() > 0){
			return list.get(0);
		}
		return null;
	}
	//根据学号查询考试记录
	public TestNote ckTestNote(Integer sid) {
		String hql = "from TestNote t where t.students.sid = ? order by t.tdate desc";
		List<TestNote> list = (List<TestNote>) this.getHibernateTemplate().find(hql, sid);
		if(list != null && list.size() >0){
			return list.get(0);
		}
		return null;
	}
	//随机抽取试卷
	public QuestionPaper cqQuestionPaper() {
		String hql = "from QuestionPaper";
		List<QuestionPaper> list = (List<QuestionPaper>) this.getHibernateTemplate().find(hql, null);
		if(list != null && list.size() > 0){
			Random rand = new Random();
			
			int randNum = rand.nextInt(list.size());
			System.out.println("产生的随机数为==================================================="+randNum);
			return list.get(randNum);
		}
		return null;
	}
	//根据学号查询学生
	public Students ckStudents(Integer sid) {
		String hql = "from Students where sid = ?";
		List<Students> list = (List<Students>) this.getHibernateTemplate().find(hql, sid);
		if(list != null && list.size() > 0){
			return list.get(0);
		}
		return null;
	}
	//保存考试记录
	public void saveTestNote(TestNote tn1) {
		this.getHibernateTemplate().save(tn1);
	}
	//根据试卷id查询试卷信息
	public QuestionPaper hqQuestionPaper(Integer qpid) {
		String hql = "from QuestionPaper where qpid = ?";
		List<QuestionPaper> list = (List<QuestionPaper>) this.getHibernateTemplate().find(hql, qpid);
		if(list != null && list.size() > 0){
			return list.get(0);
		}
		return null;
	}
	//根据试卷id查询选择题
	public List<QpRelationq> ckxzQpRelationq(Integer qpid) {
		String hql = "from QpRelationq  qpq where qpq.questionPaper.qpid = ? and qpq.question.questionType.qtid = ? order by qpq.num asc";
		List<QpRelationq> listqpq = (List<QpRelationq>) this.getHibernateTemplate().find(hql, qpid,1);
		List<QpRelationq> list = new ArrayList<QpRelationq>();
		String hql2 = null;
		for(int i=0; i<listqpq.size(); i++){
			QpRelationq qpq = listqpq.get(i);
			Question q = new Question();
			hql2 = "from Question where qid = ?";
			List<Question> listq = (List<Question>) this.getHibernateTemplate().find(hql2, listqpq.get(i).getQuestion().getQid());
			q = listq.get(0);
			qpq.setQuestion(q);
			list.add(qpq); 
		}
		return list;
	}
	//根据试卷id查询判断题
	public List<QpRelationq> ckpdQpRelationq(Integer qpid) {
		String hql = "from QpRelationq  qpq where qpq.questionPaper.qpid = ? and qpq.question.questionType.qtid = ? order by qpq.num asc";
		List<QpRelationq> listqpq = (List<QpRelationq>) this.getHibernateTemplate().find(hql, qpid,2);
		List<QpRelationq> list = new ArrayList<QpRelationq>();
		String hql2 = null;
		for(int i=0; i<listqpq.size(); i++){
			QpRelationq qpq = listqpq.get(i);
			Question q = new Question();
			hql2 = "from Question where qid = ?";
			List<Question> listq = (List<Question>) this.getHibernateTemplate().find(hql2, listqpq.get(i).getQuestion().getQid());
			q = listq.get(0);
			qpq.setQuestion(q);
			list.add(qpq); 
		}
		return list;
	}
	//根据试卷id查询填空题
	public List<QpRelationq> cktkQpRelationq(Integer qpid) {
		String hql = "from QpRelationq  qpq where qpq.questionPaper.qpid = ? and qpq.question.questionType.qtid = ? order by qpq.num asc";
		List<QpRelationq> listqpq = (List<QpRelationq>) this.getHibernateTemplate().find(hql, qpid,3);
		List<QpRelationq> list = new ArrayList<QpRelationq>();
		String hql2 = null;
		for(int i=0; i<listqpq.size(); i++){
			QpRelationq qpq = listqpq.get(i);
			Question q = new Question();
			hql2 = "from Question where qid = ?";
			List<Question> listq = (List<Question>) this.getHibernateTemplate().find(hql2, listqpq.get(i).getQuestion().getQid());
			q = listq.get(0);
			qpq.setQuestion(q);
			list.add(qpq); 
		}
		return list;
	}
	//根据试卷id查询试题与试卷的对应关系
	public List<QpRelationq> getQpq(Integer qpid) {
		String hql = "from QpRelationq qpq where qpq.questionPaper.qpid = ? order by qpq.num asc";
		List<QpRelationq> listqpq = (List<QpRelationq>) this.getHibernateTemplate().find(hql, qpid);
		return listqpq;
	}
	//根据试题id查询试题对象
	public Question czQuestion(Integer qid){
		String hql = "from Question where qid = ?";
		List<Question> q = (List<Question>) this.getHibernateTemplate().find(hql, qid);
		if(q != null && q.size() > 0){
			return q.get(0);
		}
		return null;
	}
	//将试题与考试记录保存到answerState中
	public void saveAnswerState(AnswerState a) {
		this.getHibernateTemplate().save(a);
	}
	
	

}
