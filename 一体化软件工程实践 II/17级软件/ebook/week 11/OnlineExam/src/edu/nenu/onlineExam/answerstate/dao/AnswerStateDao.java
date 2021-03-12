package edu.nenu.onlineExam.answerstate.dao;

import java.util.List;

import org.springframework.orm.hibernate5.support.HibernateDaoSupport;

import edu.nenu.onlineExam.answerstate.entity.AnswerState;
import edu.nenu.onlineExam.question.entity.Question;
import edu.nenu.onlineExam.testnote.entity.TestNote;

public class AnswerStateDao extends HibernateDaoSupport{
	
	//根据试题id和tnid查询answerState
	public AnswerState hqAnswerState(Integer tnid, Integer qid) {
		String hql = "from AnswerState a where a.question.qid = ? and a.testNote.tnid = ?";
		List<AnswerState> listas = (List<AnswerState>) this.getHibernateTemplate().find(hql, qid,tnid);
		if(listas != null && listas.size() > 0){
			return listas.get(0);
		}
		return null;
	}
	//根据试题编号查询试题
	public Question hqQuestion(Integer qid) {
		String hql = "from Question where qid = ?";
		List<Question> listq = (List<Question>) this.getHibernateTemplate().find(hql, qid);
		if(listq != null && listq.size() > 0){
			return listq.get(0);
		}
		return null;
	}
	//根据考试记录编号查询考试记录
	public TestNote hqTestNote(Integer tnid) {
		String hql = "from TestNote where tnid = ?";
		List<TestNote> list = (List<TestNote>) this.getHibernateTemplate().find(hql, tnid);
		if(list != null && list.size() > 0){
			return list.get(0);
		}
		return null;
	}
	//保存学生答题情况
	public void saveAnswerState(AnswerState a) {
		this.getHibernateTemplate().save(a);
	}

}
