package com.nenusoftware.onlineexam.entity.answer;

/**
 * @Author:Kongyy
 * @Description: 答题的实体层
 * @Date: 19:44 2020/6/15
 */
public class Answer {

    /**
     * 答案编号
     */
    private Integer answerId;

    /**
     * 用户id
     */
    private Integer userId;

    /**
     * 题目id
     */
    private Integer paperDetailId;

    /**
     * 试卷id
     */
    private Integer paperId;

    /**
     * 这道题所得分数
     */
    private Integer score;

    /**
     * 用户的答案
     */
    private String solution;

    /**
     * 这道题正确答案
     */
    private String right;

    public Integer getAnswerId() {
        return answerId;
    }

    public void setAnswerId(Integer answerId) {
        this.answerId = answerId;
    }

    public Integer getUserId() {
        return userId;
    }

    public void setUserId(Integer userId) {
        this.userId = userId;
    }

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

    public Integer getScore() {
        return score;
    }

    public void setScore(Integer score) {
        this.score = score;
    }

    public String getSolution() {
        return solution;
    }

    public void setSolution(String solution) {
        this.solution = solution;
    }

    public String getRight() {
        return right;
    }

    public void setRight(String right) {
        this.right = right;
    }

    @Override
    public String toString() {
        return "Answer{" +
                "answerId=" + answerId +
                ", userId=" + userId +
                ", paperDetailId=" + paperDetailId +
                ", paperId=" + paperId +
                ", score=" + score +
                ", solution='" + solution + '\'' +
                ", right='" + right + '\'' +
                '}';
    }
}
