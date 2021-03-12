package edu.nenu.onlineExam.qprelationq.service;

import org.springframework.transaction.annotation.Transactional;

import edu.nenu.onlineExam.qprelationq.dao.QpRelationqDao;

@Transactional
public class QpRelationqService {
	private QpRelationqDao qprqDao;

	public void setQprqDao(QpRelationqDao qprqDao) {
		this.qprqDao = qprqDao;
	}
}
