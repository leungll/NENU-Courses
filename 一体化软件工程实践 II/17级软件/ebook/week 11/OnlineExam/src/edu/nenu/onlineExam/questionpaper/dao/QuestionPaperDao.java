package edu.nenu.onlineExam.questionpaper.dao;

import java.util.ArrayList;
import java.util.List;

import org.springframework.orm.hibernate5.support.HibernateDaoSupport;

import edu.nenu.onlineExam.qprelationq.entity.QpRelationq;
import edu.nenu.onlineExam.question.entity.Question;
import edu.nenu.onlineExam.questionpaper.entity.QuestionPaper;
import edu.nenu.onlineExam.questiontype.entity.QuestionType;
import edu.nenu.onlineExam.teacheruser.entity.Teacher;
import edu.nenu.onlineExam.utils.PageHibernateCallback;

public class QuestionPaperDao extends HibernateDaoSupport{
	
	//设置试卷基本信息
	public void szQuestionPaper(QuestionPaper questionPaper, Integer tid) {
		String hql = "from Teacher where tid = ?";
		List<Teacher> listt = (List<Teacher>) this.getHibernateTemplate().find(hql, tid);
		if(listt!=null && listt.size()>0){
			questionPaper.setTeacher(listt.get(0));
		}
		
	}
	public void szAdminQuestionPaper(QuestionPaper questionPaper) {
		this.getHibernateTemplate().save(questionPaper);
	}
	//查询所有试题类型
	public List<QuestionType> allQT() {
		String hql = "from QuestionType";
		List<QuestionType> listqt = (List<QuestionType>) this.getHibernateTemplate().find(hql);
		return listqt;
	}
	public Question selectQuestion(Integer qid) {
		String hql = "from Question where qid = ?";
		List<Question> list = (List<Question>) this.getHibernateTemplate().find(hql, qid);
		if(list != null && list.size()>0){
			return list.get(0);
		}
		return null;
	}
	//获取符合条件的试题总数
	public int findCount(Question question, Integer tid, Integer qtid) {
		String hql = "select count(*) from Question q where q.teacher.tid = ? and q.questionType.qtid = ? and  q.qscope = ? and q.qdifficulty = ? ";
		List<Long> list = (List<Long>) this.getHibernateTemplate().find(hql, tid,qtid,question.getQscope(),question.getQdifficulty());
		if(list != null && list.size()>0){
			return list.get(0).intValue();
		}
		return 0;	
	}
	public int findCountAdmin(Question question, Integer qtid) {
		String hql = "select count(*) from Question q where q.questionType.qtid = ? and  q.qscope = ? and q.qdifficulty = ? ";
		List<Long> list = (List<Long>) this.getHibernateTemplate().find(hql,qtid,question.getQscope(),question.getQdifficulty());
		if(list != null && list.size()>0){
			return list.get(0).intValue();
		}
		return 0;	
	}
	//根据条件获取试题集合
	public List<Question> findQuestion(Question question, Integer tid,
			Integer qtid, int begin, int limit) {
		//String hql = "select s from Students s join s.bj b join b.teacher t where t.tid = ? order by s.sid";
		String hql = "select q from Question q join q.teacher t join q.questionType qt where t.tid = ? and qt.qtid = ? and q.qscope = ? and q.qdifficulty = ? order by q.qid";
		//分页实现
		List<Question> list = this.getHibernateTemplate().execute(new PageHibernateCallback<Question>(hql, new Object[]{tid,qtid,question.getQscope(),question.getQdifficulty()}, begin, limit));
		if(list != null && list.size()>0){
			return list;
		}
		return null;
	}
	public List<Question> findQuestionAdmin(Question question, Integer qtid,
			int begin, int limit) {
		String hql = "select q from Question q join q.questionType qt where qt.qtid = ? and q.qscope = ? and q.qdifficulty = ? order by q.qid";
		//分页实现
		List<Question> list = this.getHibernateTemplate().execute(new PageHibernateCallback<Question>(hql, new Object[]{qtid,question.getQscope(),question.getQdifficulty()}, begin, limit));
		if(list != null && list.size()>0){
			return list;
		}
		return null;
	}

	public QuestionPaper getQuestionPaper() {
		String hql = "from QuestionPaper qp order by qp.qpid desc";
		List<QuestionPaper> list = (List<QuestionPaper>) this.getHibernateTemplate().find(hql, null);
		if(list!=null && list.size()>0){
			return list.get(0);
		}
		return null;
	}
	//为试卷添加试题实现
	public void tjQuestionSX(Integer qpid, Integer qid, Integer num) {
		QpRelationq qpq = new QpRelationq();
		String hql = "from QuestionPaper where qpid = ?";
		//根据试卷id查询出该出卷
		List<QuestionPaper> listqp = (List<QuestionPaper>) this.getHibernateTemplate().find(hql, qpid);
		if(listqp != null && listqp.size() > 0){
			//将试卷信息添加到试题与试卷的对应关系表中
			qpq.setQuestionPaper(listqp.get(0));
		}
		String hql2 = "from Question where qid = ?";
		//根据试题id查询出要插入试题信息
		List<Question> listq = (List<Question>) this.getHibernateTemplate().find(hql2, qid);
		if(listq != null && listq.size() > 0){
			//将试题信息添加到试卷中
			qpq.setQuestion(listq.get(0));
		}
		qpq.setNum(num);
		//保存试题与试卷对应关系对象
		this.getHibernateTemplate().save(qpq);
	}
	
	//根据试卷编号查询试卷中的试题信息
	public List<QpRelationq> qpQuestion(Integer qpid) {
		String hql = "from QpRelationq  qpq where qpq.questionPaper.qpid = ? order by qpq.num asc";
		List<QpRelationq> listqpq = (List<QpRelationq>) this.getHibernateTemplate().find(hql, qpid);
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
	//根据教师编号查询试卷
	public List<QuestionPaper> ckQuestionPaper(Integer tid) {
		String hql = "from QuestionPaper qp where qp.teacher.tid = ? order by qp.qpid desc";
		List<QuestionPaper> list = (List<QuestionPaper>) this.getHibernateTemplate().find(hql, tid);
		return list;
	}
	//管理员查看试卷
	public List<QuestionPaper> ckAdminQuestionPaper() {
		String hql = "from QuestionPaper qp order by qp.qpid desc";
		List<QuestionPaper> list = (List<QuestionPaper>) this.getHibernateTemplate().find(hql,null);
		return list;
	}
	
	

	

}
