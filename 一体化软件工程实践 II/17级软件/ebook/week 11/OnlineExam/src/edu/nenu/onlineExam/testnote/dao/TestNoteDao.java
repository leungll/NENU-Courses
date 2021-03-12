package edu.nenu.onlineExam.testnote.dao;

import java.util.List;

import org.springframework.orm.hibernate5.support.HibernateDaoSupport;

import edu.nenu.onlineExam.testnote.entity.TestNote;

public class TestNoteDao extends HibernateDaoSupport{
	//获得考试记录对象
	public TestNote getTestNote(Integer tnid) {
		String hql = "from TestNote where tnid = ?";
		List<TestNote> listtn = (List<TestNote>) this.getHibernateTemplate().find(hql, tnid);
		if(listtn != null && listtn.size() > 0){
			return listtn.get(0);
		}
		return null;
	}
	//保存考试结束时间
	public void saveTestNote(TestNote tn) {
		this.getHibernateTemplate().save(tn);
	}

}
