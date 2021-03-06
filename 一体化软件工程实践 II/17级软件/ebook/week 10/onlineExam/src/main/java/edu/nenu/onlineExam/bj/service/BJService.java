package edu.nenu.onlineExam.bj.service;

import java.util.List;

import org.springframework.transaction.annotation.Transactional;

import edu.nenu.onlineExam.bj.dao.BJDao;
import edu.nenu.onlineExam.bj.entity.BJ;

@Transactional
public class BJService {
	private BJDao bjDao;

	public void setBjDao(BJDao bjDao) {
		this.bjDao = bjDao;
	}

	public List<BJ> ckbj(Integer tid) {
		List<BJ> list = bjDao.ckbj(tid);
		return list;
	}
	public List<BJ> ckbjAdmin() {
		List<BJ> list = bjDao.ckbjAdmin();
		return list;
	}
	//按班级名查询班级的方法
	public BJ findByName(String bjname){
		return bjDao.findByName(bjname);
	}
	//添加班级信息
	public void addbjsx(BJ bj, Integer tid) {
		bjDao.addbjsx(bj,tid);
	}
	
	//根据班级id删除班级
	public void deleteBJ(Integer bjid) {
		bjDao.deleteBJ(bjid);
	}
	
	
}
