package com.pandawork.common.enums;

/**
 * CookieName枚举类
 * 将cookie的名称放在枚举类中，方便后端统一管理cookie
 *
 * @author: zhangteng
 * @time: 2014/9/4 11:09
 */
public enum CookieNameEnums {

    WebLoginName("当前用户登录名称", "web.login.name"),
    WebUserId("当前登录用户ID", "web.user.id");

    private String name;
    private String description;

    CookieNameEnums(String description, String name) {
        this.description = description;
        this.name = name;
    }

    public String getName() {
        return name;
    }

    public String getDescription() {
        return description;
    }
}
