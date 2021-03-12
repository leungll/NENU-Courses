package edu.nenu.onlineExam.question.service;

import java.util.List;

import org.springframework.transaction.annotation.Transactional;

import edu.nenu.onlineExam.question.dao.QuestionDao;
import edu.nenu.onlineExam.question.entity.Question;
import edu.nenu.onlineExam.questiontype.entity.QuestionType;
import edu.nenu.onlineExam.student.entity.Students;
import edu.nenu.onlineExam.utils.PageBean;

@Transactional
public class QuestionService {
	private QuestionDao questionDao;

	public void setQuestionDao(QuestionDao questionDao) {
		this.questionDao = questionDao;
	}

	public List<QuestionType> ckQuestionAndXZQT() {
		return questionDao.ckQuestionAndXZQT();
	}
	//根据教师编号、试题类型编号、等查询试题
	public PageBean<Question> ckQuestion(Question question, Integer tid,
			Integer qtid,int page) {
		PageBean<Question> pageBean = new PageBean<Question>();
		//设置当前页数
		pageBean.setPage(page);
		//设置每页显示的记录数
		int limit = 3;
		pageBean.setLimit(limit);
		//设置总的记录数
		int totalCount = 0;
		totalCount = questionDao.findCount(question,tid,qtid);
		pageBean.setTotalCount(totalCount);
		//设置总的页数
		int totalPage = 0;
		if(totalCount % limit == 0){
			totalPage = totalCount /limit ;
		}else{
			totalPage = totalCount / limit +1;
		}
		pageBean.setTotalPage(totalPage);
		//每页显示的数据集合
		//从哪条记录开始
		int begin = (page - 1) * limit;
		List<Question> list = questionDao.findQuestion(question,tid,qtid,begin,limit);
		pageBean.setList(list);
		return pageBean;
	}
	//管理员根据试题类型编号、等查询试题
	public PageBean<Question> ckAdminQuestion(Question question, Integer qtid,
			int page) {
		PageBean<Question> pageBean = new PageBean<Question>();
		//设置当前页数
		pageBean.setPage(page);
		//设置每页显示的记录数
		int limit = 3;
		pageBean.setLimit(limit);
		//设置总的记录数
		int totalCount = 0;
		totalCount = questionDao.findCountAdmin(question,qtid);
		pageBean.setTotalCount(totalCount);
		//设置总的页数
		int totalPage = 0;
		if(totalCount % limit == 0){
			totalPage = totalCount /limit ;
		}else{
			totalPage = totalCount / limit +1;
		}
		pageBean.setTotalPage(totalPage);
		//每页显示的数据集合
		//从哪条记录开始
		int begin = (page - 1) * limit;
		List<Question> list = questionDao.findQuestionAmin(question,qtid,begin,limit);
		pageBean.setList(list);
		return pageBean;
	}	
	public Question selectQuestion(Integer qid) {
		
		return questionDao.selectQuestion(qid);
	}
	
	//根据关键字查找是否有相似的试题
	public List<Question> findByOword(String oword,String qscope,String qdifficulty,Integer qtid) {
		
		return questionDao.finByOword(oword,qscope,qdifficulty,qtid);
	}
	//添加试题实现
	public void addQuestionXZSX(Question question,Integer qtid, Integer tid) {
		questionDao.addQuestionXZSX(question,qtid,tid);
	}
	public void addAdminQuestionXZSX(Question question, Integer qtid) {
		questionDao.addAdminQuestionXZSX(question,qtid);
	}
	//根据试题编号查看试题信息
	public Question ckQuestionXX(Integer qid) {
		return questionDao.ckQuestionXX(qid);
	}
	//根据试题编号删除试题
	public void delQuestion(Integer qid) {
		questionDao.delQuestion(qid);
	}

	

	
}
