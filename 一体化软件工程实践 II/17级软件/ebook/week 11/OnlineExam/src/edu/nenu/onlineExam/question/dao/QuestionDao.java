package edu.nenu.onlineExam.question.dao;

import java.util.List;

import org.springframework.orm.hibernate5.support.HibernateDaoSupport;

import edu.nenu.onlineExam.answerstate.entity.AnswerState;
import edu.nenu.onlineExam.question.entity.Question;
import edu.nenu.onlineExam.questiontype.entity.QuestionType;
import edu.nenu.onlineExam.student.entity.Students;
import edu.nenu.onlineExam.teacheruser.entity.Teacher;
import edu.nenu.onlineExam.utils.PageHibernateCallback;

public class QuestionDao extends HibernateDaoSupport{

	public List<QuestionType> ckQuestionAndXZQT() {
		String hql = "from QuestionType";
		List<QuestionType> listqt = (List<QuestionType>) this.getHibernateTemplate().find(hql, null);
		if(listqt!=null && listqt.size()>0){
			return listqt;
		}else{
			return null;
		}
		
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
	//获取符合条件的试题总数
	public int findCountAdmin(Question question, Integer qtid) {
		String hql = "select count(*) from Question q where  q.questionType.qtid = ? and  q.qscope = ? and q.qdifficulty = ? ";
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
	//根据条件获取试题集合
	public List<Question> findQuestionAmin(Question question, Integer qtid,
			int begin, int limit) {
		String hql = "select q from Question q join q.questionType qt where qt.qtid = ? and q.qscope = ? and q.qdifficulty = ? order by q.qid";
		//分页实现
		List<Question> list = this.getHibernateTemplate().execute(new PageHibernateCallback<Question>(hql, new Object[]{qtid,question.getQscope(),question.getQdifficulty()}, begin, limit));
		if(list != null && list.size()>0){
			return list;
		}
		return null;
	}
	public Question selectQuestion(Integer qid) {
		String hql = "from Question where qid = ?";
		List<Question> list = (List<Question>) this.getHibernateTemplate().find(hql, qid);
		if(list != null && list.size()>0){
			return list.get(0);
		}
		return null;
	}
	//关键关键字查找相似试题
	public List<Question> finByOword(String oword,String qscope,String qdifficulty,Integer qtid) {
		//String hql = "select q from Question q join q.questionType qt  where q.oword = ? and q.qscope = ? and q.qdifficulty = ? and qt.qtid = ?";
		String hql = "select q from Question q join q.questionType qt  where q.oword like ? and q.qscope = ? and q.qdifficulty = ? and qt.qtid = ?";
		List<Question> list = (List<Question>) this.getHibernateTemplate().find(hql, "%"+oword+"%",qscope,qdifficulty,qtid);
		return list;
	}
	public void addQuestionXZSX(Question question,Integer qtid,Integer tid) {
		String hql = "from QuestionType where qtid = ?";
		List<QuestionType> qt = (List<QuestionType>) this.getHibernateTemplate().find(hql, qtid);
		String hql2 = "from Teacher where tid = ?";
		List<Teacher> t = (List<Teacher>) this.getHibernateTemplate().find(hql2, tid);
		if(qt != null && qt.size()>0){
			question.setQuestionType(qt.get(0));
		}
		if(t != null && t.size()>0){
			question.setTeacher(t.get(0));
		}
		
		this.getHibernateTemplate().save(question);
		
	}
	public void addAdminQuestionXZSX(Question question, Integer qtid) {
		String hql = "from QuestionType where qtid = ?";
		//根据试题中的试题类型id查询试题类型信息
		List<QuestionType> qt = (List<QuestionType>) this.getHibernateTemplate().find(hql, qtid);
		if(qt != null && qt.size()>0){
			//将试题类型信息存入到试题对象中
			question.setQuestionType(qt.get(0));
		}
		//调用hibernate中的添加方法
		this.getHibernateTemplate().save(question);
	}
	//根据试题编号查看试题信息
	public Question ckQuestionXX(Integer qid) {
		String hql = "from Question where qid = ?";
		List<Question> listq = (List<Question>) this.getHibernateTemplate().find(hql, qid);
		Question question = null;
		if(listq != null && listq.size() > 0 ){
			question = listq.get(0);
			String hql2 = "from QuestionType where qtid = ?";
			List<QuestionType> listqt = (List<QuestionType>) this.getHibernateTemplate().find(hql2, listq.get(0).getQuestionType().getQtid());
			if(listqt != null && listqt.size() > 0 ){
				question.setQuestionType(listqt.get(0));
				return question;
			}
		}
		return null;
	}
	//根据试题编号删除试题
	public void delQuestion(Integer qid) {
		//String hql2 = "from AnswerState a where a.question.qid = ?";
		String hql = "from Question where qid = ?";
		List<Question> listq = (List<Question>) this.getHibernateTemplate().find(hql, qid);
		/*List<AnswerState> listas = (List<AnswerState>) this.getHibernateTemplate().find(hql2, qid);
		for(int i=0; i<listas.size(); i++){
			
			this.getHibernateTemplate().delete(listas.get(i));
		}*/
		
		
		if(listq != null && listq.size() > 0){
			this.getHibernateTemplate().delete(listq.get(0));
		}
	}
	
	
	

}
