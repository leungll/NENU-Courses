package com.pandawork.common.entity.user;

import com.pandawork.core.common.entity.AbstractEntity;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Table;

/**
 * @author : kongyy
 * @time : 2018/12/19 10:22
 */

@Table(name = "t_user")
@Entity
public class User extends AbstractEntity {

    @Id
    public Integer id;

    @Column(name = "username")
    public  String username;

    @Column(name = "password")
    private String password;

    @Column(name = "sig")
    private String sig;

    @Column(name = "power")
    private Integer power;

    public Integer getId() {
        return id;
    }

    @Override
    public void setId(Integer id) {
        this.id = id;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getPassword() {
        return password;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public String getSig() {
        return sig;
    }

    public void setSig(String sig) {
        this.sig = sig;
    }

    public Integer getPower() {
        return power;
    }

    public void setPower(Integer power) {
        this.power = power;
    }

    @Override
    public String toString() {
        return "User{" +
                "id=" + id +
                ", username='" + username + '\'' +
                ", password='" + password + '\'' +
                ", sig='" + sig + '\'' +
                ", power=" + power +
                '}';
    }
}
