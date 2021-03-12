package edu.nenu.onlineExam.answerstate.service;

import org.springframework.transaction.annotation.Transactional;

import edu.nenu.onlineExam.answerstate.dao.AnswerStateDao;
import edu.nenu.onlineExam.answerstate.entity.AnswerState;
import edu.nenu.onlineExam.question.entity.Question;
import edu.nenu.onlineExam.testnote.entity.TestNote;

@Transactional
public class AnswerStateService {
	private AnswerStateDao asDao;

	public void setAsDao(AnswerStateDao asDao) {
		this.asDao = asDao;
	}
	//±£¥Ê ‘Ã‚¥∞∏
	public void saveAnswerState(Integer tnid, Integer qid, String qas) {
		AnswerState a = asDao.hqAnswerState(tnid,qid);
		Question q = asDao.hqQuestion(qid);
		TestNote tn = asDao.hqTestNote(tnid);
		if(qas.equals(q.getQanswer())){
			a.setState(1);
		}else{
			a.setState(2);
		}
		a.setQuestion(q);
		a.setTestNote(tn);
		asDao.saveAnswerState(a);
	}
}
