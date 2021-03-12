package com.pandawork.common.entity.nature;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Table;

/**
 * @author : kongyy
 * @time : 2018/12/23 16:26
 */
@Table(name = "t_nature")
@Entity
public class Nature {

    @Id
    private Integer id;

    @Column(name = "name")
    private String name;

    @Column(name = "content")
    private String content;

    @Column(name = "path")
    private String path;

    @Column(name = "status")
    private Integer status;

    public Integer getId() {
        return id;
    }

    public void setId(Integer id) {
        this.id = id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getContent() {
        return content;
    }

    public void setContent(String content) {
        this.content = content;
    }

    public String getPath() {
        return path;
    }

    public void setPath(String path) {
        this.path = path;
    }

    public Integer getStatus() {
        return status;
    }

    public void setStatus(Integer status) {
        this.status = status;
    }

    @Override
    public String toString() {
        return "Nature{" +
                "id=" + id +
                ", name='" + name + '\'' +
                ", nature='" + content + '\'' +
                ", path='" + path + '\'' +
                ", status=" + status +
                '}';
    }
}
