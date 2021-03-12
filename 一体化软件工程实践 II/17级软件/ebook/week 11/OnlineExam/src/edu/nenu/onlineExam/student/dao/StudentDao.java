package edu.nenu.onlineExam.student.dao;

import java.util.ArrayList;
import java.util.List;

import org.springframework.orm.hibernate5.HibernateCallback;
import org.springframework.orm.hibernate5.support.HibernateDaoSupport;

import edu.nenu.onlineExam.answerstate.entity.AnswerState;
import edu.nenu.onlineExam.bj.entity.BJ;
import edu.nenu.onlineExam.question.entity.Question;
import edu.nenu.onlineExam.questionpaper.entity.QuestionPaper;
import edu.nenu.onlineExam.student.entity.Students;
import edu.nenu.onlineExam.teacheruser.entity.Teacher;
import edu.nenu.onlineExam.testnote.entity.TestNote;
import edu.nenu.onlineExam.utils.PageHibernateCallback;


public class StudentDao extends HibernateDaoSupport{
	
	//查询学生是否存在
	public Students login(Students student) {
		String hql = "from Students where sid = ? and password = ?";
		List<Students> list = (List<Students>) this.getHibernateTemplate().find(hql, student.getSid(),student.getPassword());
		if(list != null && list.size() > 0){
			return list.get(0);
		}
		return null;
	}
	//根据教师编号查询总的记录数
	public int findCountTid(Integer tid) {
		String hql = "select count(*) from Students s where s.bj.teacher.tid= ? ";
		List<Long> list = (List<Long>) this.getHibernateTemplate().find(hql, tid);
		if(list != null && list.size()>0){
			return list.get(0).intValue();
		}
		return 0;
	}
	public int findCountAdmin() {
		String hql = "select count(*) from Students ";
		List<Long> list = (List<Long>) this.getHibernateTemplate().find(hql,null);
		if(list != null && list.size()>0){
			return list.get(0).intValue();
		}
		return 0;
	}
	//根据教师编号查询学生信息集合
	public List<Students> findByPageTid(Integer tid, int begin, int limit) {
		//SELECT s.* from teacheruser t, bj b, student s where t.tid = b.tid and b.bjid = s.bjid and t.tid = 1542110250
		String hql = "select s from Students s join s.bj b join b.teacher t where t.tid = ? order by s.sid";
		//分页实现
		List<Students> list = this.getHibernateTemplate().execute(new PageHibernateCallback<Students>(hql, new Object[]{tid}, begin, limit));
		List<Students> liststu = new ArrayList<Students>();
		String hql2 = null;
		for(int i=0; i<list.size();i++){
			Students stu = list.get(i);
			hql2 = "from BJ where bjid = ?";
			List<BJ> listbj = (List<BJ>) this.getHibernateTemplate().find(hql2, list.get(i).getBj().getBjid());
			if(listbj!=null && listbj.size()>0){
				stu.setBj(listbj.get(0));
			}
			liststu.add(stu);
		}
		return liststu;
	}
	public List<Students> findByPageAdmin(int begin, int limit) {
		String hql = "select s from Students s order by s.sid";
		//分页实现
		List<Students> list = this.getHibernateTemplate().execute(new PageHibernateCallback<Students>(hql, new Object[]{}, begin, limit));
		List<Students> liststu = new ArrayList<Students>();
		String hql2 = null;
		for(int i=0; i<list.size();i++){
			Students stu = list.get(i);
			hql2 = "from BJ where bjid = ?";
			List<BJ> listbj = (List<BJ>) this.getHibernateTemplate().find(hql2, list.get(i).getBj().getBjid());
			if(listbj!=null && listbj.size()>0){
				stu.setBj(listbj.get(0));
			}
			liststu.add(stu);
		}
		return liststu;
	}
	//查询所有班级
	public List<BJ> ckbj(Integer tid) {
		String hql = "from BJ where tid = ?";
		List<BJ> list = (List<BJ>) this.getHibernateTemplate().find(hql, tid);
		return list;
		
	}
	public List<BJ> ckbjAdmin() {
		String hql = "from BJ";
		List<BJ> list = (List<BJ>) this.getHibernateTemplate().find(hql, null);
		return list;
	}
	public Students finBySid(Integer sid) {
		String hql = "from Students where sid = ?";
		List<Students> list = (List<Students>) this.getHibernateTemplate().find(hql, sid);
		if(list!=null && list.size()>0){
			return list.get(0);
		}
		return null;
	}
	//添加学生信息
	public void addStudentSX(Students student, Integer bjid) {
		String hql = "from BJ where bjid = ?";
		List<BJ> list = (List<BJ>) this.getHibernateTemplate().find(hql, bjid);
		BJ bj = null;
		if(list!=null && list.size()>0){
			bj = list.get(0);
		}
		student.setBj(bj);
		this.getHibernateTemplate().save(student);
		
	}
	//根据学号删除学生
	public void deleteStudent(Integer sid) {
		
		String hql2 = "from Students where sid = ?";
		List<Students> liststu = (List<Students>) this.getHibernateTemplate().find(hql2, sid);
		this.getHibernateTemplate().delete(liststu.get(0));
	}
	//根据学号查询学生信息
	public List<TestNote> ckTestNote(Integer sid) {
		String hql = "from TestNote tn where tn.students.sid = ? order by tn.tnid desc";
		String hql2 = null;
		Integer score = null ;
		Integer scorexz = null;
		Integer scoretk = null;
		Integer scorepd = null;
		List<TestNote> listtn = (List<TestNote>) this.getHibernateTemplate().find(hql, sid);
		List<TestNote> list = new ArrayList<TestNote>();
		for(int i=0; i<listtn.size(); i++){
			TestNote tn = listtn.get(i);
			hql2 = "select count(*) from AnswerState a where a.testNote.tnid = ? and a.state = ? and a.question.questionType.qtid = ?";
			List<Long> listlongxz = (List<Long>) this.getHibernateTemplate().find(hql2, listtn.get(i).getTnid(),1,1);
			if(listlongxz != null && listlongxz.size()>0){
				 scorexz = listlongxz.get(0).intValue()*2;
			}
			List<Long> listlongpd = (List<Long>) this.getHibernateTemplate().find(hql2, listtn.get(i).getTnid(),1,2);
			if(listlongpd != null && listlongpd.size()>0){
				scorepd = listlongpd.get(0).intValue();
			}
			List<Long> listlongtk = (List<Long>) this.getHibernateTemplate().find(hql2, listtn.get(i).getTnid(),1,3);
			if(listlongtk != null && listlongtk.size()>0){
				scoretk = listlongtk.get(0).intValue()*2;
			}
			score = scorexz+scorepd+scoretk;
			tn.setScore(score);
			this.getHibernateTemplate().save(tn);
			list.add(tn);	
		}
		return list;
	}
	//根据考试记录编号查询选择题
	public List<AnswerState> ckAnserStatexz(Integer tnid) {
		String hql = "from AnswerState a where a.testNote.tnid = ? and a.question.questionType.qtid = ? order by a.anid asc";
		String hql2 = null;
		List<AnswerState> listas = (List<AnswerState>) this.getHibernateTemplate().find(hql, tnid, 1);
		List<AnswerState> list = new ArrayList<AnswerState>();
		for(int i=0; i<listas.size(); i++){
			AnswerState a = listas.get(i);
			hql2 = "from Question where qid = ?";
			List<Question> listq = (List<Question>) this.getHibernateTemplate().find(hql2, listas.get(i).getQuestion().getQid());
			if(listq != null && listq.size() > 0 ){
				a.setQuestion(listq.get(0));
			}
			list.add(a);
		}
		return list;
	}
	//根据考试记录编号查询判断题
	public List<AnswerState> ckAnserStatepd(Integer tnid) {
		String hql = "from AnswerState a where a.testNote.tnid = ? and a.question.questionType.qtid = ? order by a.anid asc";
		String hql2 = null;
		List<AnswerState> listas = (List<AnswerState>) this.getHibernateTemplate().find(hql, tnid, 2);
		List<AnswerState> list = new ArrayList<AnswerState>();
		for(int i=0; i<listas.size(); i++){
			AnswerState a = listas.get(i);
			hql2 = "from Question where qid = ?";
			List<Question> listq = (List<Question>) this.getHibernateTemplate().find(hql2, listas.get(i).getQuestion().getQid());
			if(listq != null && listq.size() > 0 ){
				a.setQuestion(listq.get(0));
			}
			list.add(a);
		}
		return list;
	}
	//根据考试记录编号查询填空题
	public List<AnswerState> ckAnserStatetk(Integer tnid) {
		String hql = "from AnswerState a where a.testNote.tnid = ? and a.question.questionType.qtid = ? order by a.anid asc";
		String hql2 = null;
		List<AnswerState> listas = (List<AnswerState>) this.getHibernateTemplate().find(hql, tnid, 3);
		List<AnswerState> list = new ArrayList<AnswerState>();
		for(int i=0; i<listas.size(); i++){
			AnswerState a = listas.get(i);
			hql2 = "from Question where qid = ?";
			List<Question> listq = (List<Question>) this.getHibernateTemplate().find(hql2, listas.get(i).getQuestion().getQid());
			if(listq != null && listq.size() > 0 ){
				a.setQuestion(listq.get(0));
			}
			list.add(a);
		}
		return list;
	}
	public void updatePW(Integer sid, String npw) {
		System.out.println("学号====="+sid+" ========新密码="+npw);
		String hql = "from Students where sid =? ";
		Students student = null;
		List<Students> list = (List<Students>) this.getHibernateTemplate().find(hql, sid);
		if(list != null && list.size()>0){
			student = list.get(0);
		}
		student.setPassword(npw);
		this.getHibernateTemplate().save(student);
	}
	//根据学号查看学生信息
	public Students ckStudent(Integer sid) {
		String hql = "from Students where sid = ?";
		List<Students> list = (List<Students>) this.getHibernateTemplate().find(hql, sid);
		if(list != null && list.size() > 0){
			return list.get(0);
		}
		return null;
	}
	//完善学生信息实现
	public void wsStudentSX(Students student) {
		String hql = "from Students where sid = ?";
		List<Students> list = (List<Students>) this.getHibernateTemplate().find(hql, student.getSid());
		Students stu;
		if(list != null && list.size() > 0){
			stu = list.get(0);
			stu.setPhone(student.getPhone());
			stu.setEmail(student.getEmail());
			this.getHibernateTemplate().save(stu);
		}
	}
	//根据学号查询班级信息
	public BJ myBJ(Integer sid) {
		String hql = "from Students where sid = ?";
		String hql2 = null;
		BJ bj = null;
		Teacher teacher = null;
		List<Students> liststu = (List<Students>) this.getHibernateTemplate().find(hql, sid);
		if(liststu != null && liststu.size() > 0 ){
			hql2 = "from BJ where bjid = ?";
			List<BJ> listbj = (List<BJ>) this.getHibernateTemplate().find(hql2, liststu.get(0).getBj().getBjid());
			if(listbj != null && listbj.size() > 0){
				bj = listbj.get(0);
				hql2 = "from Teacher where tid = ?";
				List<Teacher> listt = (List<Teacher>) this.getHibernateTemplate().find(hql2, listbj.get(0).getTeacher().getTid());
				if(listt != null && listt.size() > 0){
					bj.setTeacher(listt.get(0));
					return bj;
				}	
			}
		}
		return null;
	}
	public Students ckStudentXX(Integer sid) {
		String hql = "from Students where sid = ?";
		List<Students> list = (List<Students>) this.getHibernateTemplate().find(hql, sid);
		if(list != null && list.size() > 0){
			return list.get(0);
		}
		return null;
	}
	
	
	
	
}
