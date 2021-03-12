package edu.nenu.onlineExam.questionpaper.service;

import java.util.List;

import org.springframework.transaction.annotation.Transactional;

import edu.nenu.onlineExam.qprelationq.entity.QpRelationq;
import edu.nenu.onlineExam.question.entity.Question;
import edu.nenu.onlineExam.questionpaper.dao.QuestionPaperDao;
import edu.nenu.onlineExam.questionpaper.entity.QuestionPaper;
import edu.nenu.onlineExam.questiontype.entity.QuestionType;
import edu.nenu.onlineExam.utils.PageBean;

@Transactional
public class QuestionPaperService {
	private QuestionPaperDao qpDao;

	public void setQpDao(QuestionPaperDao qpDao) {
		this.qpDao = qpDao;
	}
	//设置试卷基本信息
	public void szQuestionPaper(QuestionPaper questionPaper, Integer tid) {
		qpDao.szQuestionPaper(questionPaper,tid);
	}
	public void szAdminQuestionPaper(QuestionPaper questionPaper) {
		qpDao.szAdminQuestionPaper(questionPaper);
	}
	//查询试题类型
	public List<QuestionType> allQT() {
		return qpDao.allQT();
	}
	public Question selectQuestion(Integer qid) {
		return qpDao.selectQuestion(qid);
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
		totalCount = qpDao.findCount(question,tid,qtid);
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
		List<Question> list = qpDao.findQuestion(question,tid,qtid,begin,limit);
		pageBean.setList(list);
		return pageBean;
	}
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
		totalCount = qpDao.findCountAdmin(question,qtid);
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
		List<Question> list = qpDao.findQuestionAdmin(question,qtid,begin,limit);
		pageBean.setList(list);
		return pageBean;
	}
	//查询试卷
	public QuestionPaper getQuestionPaper() {
		return qpDao.getQuestionPaper();
	}
	//为试卷添加试题的实现
	public void tiQuestionSX(Integer qpid, Integer qid, Integer num) {
		qpDao.tjQuestionSX(qpid,qid,num);
	}
	//查询试卷中已经存在的试题
	public List<QpRelationq> qpQuestion(Integer qpid) {
		return qpDao.qpQuestion(qpid);
	}
	
	//根据教师编号查看试卷
	public List<QuestionPaper> ckQuestionPaper(Integer tid) {
		return qpDao.ckQuestionPaper(tid);
	}
	public List<QuestionPaper> ckAdminQuestionPaper() {
		return qpDao.ckAdminQuestionPaper();
	}
	
	

}
