package edu.nenu.onlineExam.testnote.service;

import java.util.Date;

import org.springframework.transaction.annotation.Transactional;

import edu.nenu.onlineExam.testnote.dao.TestNoteDao;
import edu.nenu.onlineExam.testnote.entity.TestNote;
@Transactional
public class TestNoteService {
	private TestNoteDao tnDao;

	public void setTnDao(TestNoteDao tnDao) {
		this.tnDao = tnDao;
	}
	//插入考试结束时间
	public void upEndTime(Integer tnid) {
		TestNote tn = tnDao.getTestNote(tnid);
		tn.setEtime(new Date());
		tnDao.saveTestNote(tn);
	}
}
