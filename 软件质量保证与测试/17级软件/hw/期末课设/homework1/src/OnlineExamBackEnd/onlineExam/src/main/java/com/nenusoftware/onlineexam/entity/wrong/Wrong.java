package com.nenusoftware.onlineexam.entity.wrong;


/**
 * @Author:kongyy
 * @Description: 错题集的实体
 * @Date: 20:23 2020/6/16
 */
public class Wrong {

    /**
     *错题id
     */
    private Integer wrongId;

    /**
     *题目id
     */
    private Integer paperDetailId;

    /**
     *用户id
     */
    private Integer userId;

    /**
     *用户的答案
     */
    private String answer;

    /**
     *这道题正确答案
     */
    private String right;

    /**
     *试卷id
     */
    private Integer paperId;

    /**
     *这道题的分值
     */
    private Integer score;

    /**
     *用户在这道题上得了多少分
     */
    private Integer nowScore;

    public Integer getWrongId() {
        return wrongId;
    }

    public void setWrongId(Integer wrongId) {
        this.wrongId = wrongId;
    }

    public Integer getPaperDetailId() {
        return paperDetailId;
    }

    public void setPaperDetailId(Integer paperDetailId) {
        this.paperDetailId = paperDetailId;
    }

    public Integer getUserId() {
        return userId;
    }

    public void setUserId(Integer userId) {
        this.userId = userId;
    }

    public String getAnswer() {
        return answer;
    }

    public void setAnswer(String answer) {
        this.answer = answer;
    }

    public String getRight() {
        return right;
    }

    public void setRight(String right) {
        this.right = right;
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

    public Integer getNowScore() {
        return nowScore;
    }

    public void setNowScore(Integer nowScore) {
        this.nowScore = nowScore;
    }

    @Override
    public String toString() {
        return "Wrong{" +
                "wrongId=" + wrongId +
                ", paperDetailId=" + paperDetailId +
                ", userId=" + userId +
                ", answer='" + answer + '\'' +
                ", right='" + right + '\'' +
                ", paperId=" + paperId +
                ", score=" + score +
                ", nowScore=" + nowScore +
                '}';
    }
}
