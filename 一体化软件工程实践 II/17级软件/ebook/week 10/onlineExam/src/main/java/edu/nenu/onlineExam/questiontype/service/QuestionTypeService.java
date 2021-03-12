package edu.nenu.onlineExam.questiontype.service;

import org.springframework.transaction.annotation.Transactional;

import edu.nenu.onlineExam.questiontype.dao.QuestionTypeDao;

@Transactional
public class QuestionTypeService {

	private QuestionTypeDao qtDao;

	public void setQtDao(QuestionTypeDao qtDao) {
		this.qtDao = qtDao;
	}
}
