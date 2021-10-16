package com.nenusoftware.onlineexam.entity.user;

/**
 * @Author:Liangll
 * @Description: 用户的实体类
 * @Date: 21:58 2020/6/14
 */
public class User {

    /**
     * 用户Id
     */
    private Integer userId;

    /**
     * 用户名
     */
    private String username;

    /**
     * 用户密码
     */
    private String password;

    private String birthday;

    private String sex;

    private Integer power;

    private String image;

    private String powerS;

    public Integer getUserId() {
        return userId;
    }

    public void setUserId(Integer userId) {
        this.userId = userId;
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

    public String getBirthday() {
        return birthday;
    }

    public void setBirthday(String birthday) {
        this.birthday = birthday;
    }

    public String getSex() {
        return sex;
    }

    public void setSex(String sex) {
        this.sex = sex;
    }

    public Integer getPower() {
        return power;
    }

    public void setPower(Integer power) {
        this.power = power;
    }

    public String getImage() {
        return image;
    }

    public void setImage(String image) {
        this.image = image;
    }

    public String getPowerS() {
        return powerS;
    }

    public void setPowerS(String powerS) {
        this.powerS = powerS;
    }

    @Override
    public String toString() {
        return "User{" +
                "userId=" + userId +
                ", username='" + username + '\'' +
                ", password='" + password + '\'' +
                ", birthday='" + birthday + '\'' +
                ", sex='" + sex + '\'' +
                ", power=" + power +
                ", image='" + image + '\'' +
                ", powerS='" + powerS + '\'' +
                '}';
    }
}
