package edu.nenu.onlineExam.answerstate.entity;
/**
 * 学生试题的答题情况
 */
import edu.nenu.onlineExam.question.entity.Question;
import edu.nenu.onlineExam.testnote.entity.TestNote;

public class AnswerState {
	private Integer anid;	//答题情况id
	private Integer state;	//答题情况
	private Question question;	
	private TestNote testNote;
	
	public Integer getAnid() {
		return anid;
	}
	public void setAnid(Integer anid) {
		this.anid = anid;
	}
	public Integer getState() {
		return state;
	}
	public void setState(Integer state) {
		this.state = state;
	}
	public Question getQuestion() {
		return question;
	}
	public void setQuestion(Question question) {
		this.question = question;
	}
	public TestNote getTestNote() {
		return testNote;
	}
	public void setTestNote(TestNote testNote) {
		this.testNote = testNote;
	}
}
