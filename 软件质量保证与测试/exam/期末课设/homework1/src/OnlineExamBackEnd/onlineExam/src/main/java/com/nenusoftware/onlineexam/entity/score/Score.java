package com.nenusoftware.onlineexam.entity.score;

/**
 * @Author:kongyy
 * @Description: 成绩的实体
 * @Date: 20:23 2020/6/18
 */
public class Score {

    /**
     * 成绩编号
     */
    private Integer scoreId;

    /**
     * 用户编号
     */
    private Integer userId;

    /**
     * 试卷编号
     */
    private Integer paperId;

    /**
     * 分数
     */
    private Integer mark;

    /**
     * 用户名
     */
    private String username;

    /**
     * 试卷名称
     */
    private String paperName;

    public Integer getScoreId() {
        return scoreId;
    }

    public void setScoreId(Integer scoreId) {
        this.scoreId = scoreId;
    }

    public Integer getUserId() {
        return userId;
    }

    public void setUserId(Integer userId) {
        this.userId = userId;
    }

    public Integer getPaperId() {
        return paperId;
    }

    public void setPaperId(Integer paperId) {
        this.paperId = paperId;
    }

    public Integer getMark() {
        return mark;
    }

    public void setMark(Integer mark) {
        this.mark = mark;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getPaperName() {
        return paperName;
    }

    public void setPaperName(String paperName) {
        this.paperName = paperName;
    }

    @Override
    public String toString() {
        return "Score{" +
                "scoreId=" + scoreId +
                ", userId=" + userId +
                ", paperId=" + paperId +
                ", mark=" + mark +
                ", username='" + username + '\'' +
                ", paperName='" + paperName + '\'' +
                '}';
    }
}
