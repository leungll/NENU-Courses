package com.nenusoftware.onlineexam.entity.paperdetail;

/**
 * @Author:kongyy
 * @Description: 试卷详细信息的实体
 * @Date: 21:43 2020/6/15
 */
public class PaperDetail {

    /**
     * 试卷详细信息的编号
     */
    private Integer paperDetailId;

    /**
     * 试卷编号
     */
    private Integer paperId;

    /**
     * 练习题号
     */
    private Integer exerciseId;

    /**
     * 题目内容
     */
    private String content;

    /**
     * 选项A
     */
    private String typeA;

    /**
     * 选项B
     */
    private String typeB;

    /**
     * 选项C
     */
    private String typeC;

    /**
     * 选项D
     */
    private String typeD;

    /**
     * 题目答案或关键字段1
     */
    private String answer;

    /**
     * 关键字段2
     */
    private String answer2;

    /**
     * 关键字段3
     */
    private String answer3;

    /**
     * 题目类型
     */
    private String exerciseType;

    /**
     * 题目分值
     */
    private Integer score;

    private String solution;

    public Integer getPaperDetailId() {
        return paperDetailId;
    }

    public void setPaperDetailId(Integer paperDetailId) {
        this.paperDetailId = paperDetailId;
    }

    public Integer getPaperId() {
        return paperId;
    }

    public void setPaperId(Integer paperId) {
        this.paperId = paperId;
    }

    public Integer getExerciseId() {
        return exerciseId;
    }

    public void setExerciseId(Integer exerciseId) {
        this.exerciseId = exerciseId;
    }

    public String getContent() {
        return content;
    }

    public void setContent(String content) {
        this.content = content;
    }

    public String getTypeA() {
        return typeA;
    }

    public void setTypeA(String typeA) {
        this.typeA = typeA;
    }

    public String getTypeB() {
        return typeB;
    }

    public void setTypeB(String typeB) {
        this.typeB = typeB;
    }

    public String getTypeC() {
        return typeC;
    }

    public void setTypeC(String typeC) {
        this.typeC = typeC;
    }

    public String getTypeD() {
        return typeD;
    }

    public void setTypeD(String typeD) {
        this.typeD = typeD;
    }

    public String getAnswer() {
        return answer;
    }

    public void setAnswer(String answer) {
        this.answer = answer;
    }

    public String getExerciseType() {
        return exerciseType;
    }

    public void setExerciseType(String exerciseType) {
        this.exerciseType = exerciseType;
    }

    public Integer getScore() {
        return score;
    }

    public void setScore(Integer score) {
        this.score = score;
    }

    public String getAnswer2() {
        return answer2;
    }

    public void setAnswer2(String answer2) {
        this.answer2 = answer2;
    }

    public String getAnswer3() {
        return answer3;
    }

    public void setAnswer3(String answer3) {
        this.answer3 = answer3;
    }

    public String getSolution() {
        return solution;
    }

    public void setSolution(String solution) {
        this.solution = solution;
    }

    @Override
    public String toString() {
        return "PaperDetail{" +
                "paperDetailId=" + paperDetailId +
                ", paperId=" + paperId +
                ", exerciseId=" + exerciseId +
                ", content='" + content + '\'' +
                ", typeA='" + typeA + '\'' +
                ", typeB='" + typeB + '\'' +
                ", typeC='" + typeC + '\'' +
                ", typeD='" + typeD + '\'' +
                ", answer='" + answer + '\'' +
                ", answer2='" + answer2 + '\'' +
                ", answer3='" + answer3 + '\'' +
                ", exerciseType='" + exerciseType + '\'' +
                ", score=" + score +
                ", solution='" + solution + '\'' +
                '}';
    }
}