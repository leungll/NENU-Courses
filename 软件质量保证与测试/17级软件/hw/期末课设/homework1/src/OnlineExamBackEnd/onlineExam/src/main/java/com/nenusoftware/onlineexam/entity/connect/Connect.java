package com.nenusoftware.onlineexam.entity.connect;

/**
 * @Author:Liangll
 * @Description: 列出题目实体类
 * @Date: 22:59 2020/6/17
 */
public class Connect {

    /**
     *编号
     */
    private Integer id;

    /**
     * 试卷Id
     */
    private Integer paperId;

    /**
     * 题目Id
     */
    private Integer paperDetailId;

    /**
     * 剩余时间
     */
    private long leftover;

    /**
     * 备注
     */
    private String log;

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public Integer getPaperId() {
        return paperId;
    }

    public void setPaperId(Integer paperId) {
        this.paperId = paperId;
    }

    public Integer getPaperDetailId() {
        return paperDetailId;
    }

    public void setPaperDetailId(Integer paperDetailId) {
        this.paperDetailId = paperDetailId;
    }

    public String getLog() {
        return log;
    }

    public void setLog(String log) {
        this.log = log;
    }

    public long getLeftover() {
        return leftover;
    }

    public void setLeftover(long leftover) {
        this.leftover = leftover;
    }

    @Override
    public String toString() {
        return "Connect{" +
                "id=" + id +
                ", paperId=" + paperId +
                ", paperDetailId=" + paperDetailId +
                ", leftover=" + leftover +
                ", log='" + log + '\'' +
                '}';
    }
}
