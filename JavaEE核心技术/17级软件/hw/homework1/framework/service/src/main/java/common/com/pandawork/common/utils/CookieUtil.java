package com.pandawork.common.utils;


import com.pandawork.common.enums.CookieNameEnums;

import javax.servlet.http.Cookie;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Cookie工具类
 *
 * @author: zhangteng
 * @time: 2014/9/4 11:05
 */
public final class CookieUtil {

    // 默认生存时间，生存时间为-1，浏览器关闭，cookie将被清除
    public static final int DEFAULT_MAX_AGE = -1;

    // cookie存放根路径，默认存放位置
    public static String ROOT_PATH = "/";

    /**
     * 添加一个cookie
     *
     * @param response
     * @param cookieName    cookie名称
     * @param value         cookie值
     * @param path          cookie存放路径
     * @param maxAge        cookie生存时间
     */
    public static void setCookie(HttpServletResponse response,
                          CookieNameEnums cookieName,
                          String value,
                          String path,
                          int maxAge) {
        Cookie cookie = new Cookie(cookieName.getName(), value);
        cookie.setPath(path);
        cookie.setMaxAge(maxAge);

        response.addCookie(cookie);
    }

    /**
     * 添加一个cookie
     *
     * @param response
     * @param cookieName cookie名称
     * @param value      cookie值
     */
    public static void setCookie(HttpServletResponse response,
                          CookieNameEnums cookieName,
                          String value) {
        setCookie(response, cookieName, value, ROOT_PATH, DEFAULT_MAX_AGE);
    }

    /**
     * 添加一个cookie
     *
     * @param response
     * @param cookieName cookie名称
     * @param value      cookie值
     * @param path       cookie存放路径
     */
    public static void setCookie(HttpServletResponse response,
                          CookieNameEnums cookieName,
                          String value,
                          String path) {
        setCookie(response, cookieName, value, path, DEFAULT_MAX_AGE);
    }

    /**
     * 添加一个cookie
     *
     * @param response
     * @param cookieName cookie名称
     * @param value      cookie值
     * @param maxAge     cookie生存时间
     */
    public static void setCookie(HttpServletResponse response,
                          CookieNameEnums cookieName,
                          String value,
                          int maxAge) {
        setCookie(response, cookieName, value, ROOT_PATH, maxAge);
    }

    /**
     * 根据cookie名称获取cookie
     *
     * @param request
     * @param cookieName    cookie名称
     * @return
     */
    public static Cookie getCookie(HttpServletRequest request,
                            CookieNameEnums cookieName) {
        if(cookieName == null) {
            return null;
        }
        Cookie[] cookies = request.getCookies();
        if(cookies!=null && cookies.length!=0) {
            for(Cookie cookie : cookies) {
                if(cookie.getName().equals(cookieName.getName())) {
                    return cookie;
                }
            }
        }
        return null;
    }

    /**
     * 根据cookie名称获取cookie值
     *
     * @param request
     * @param cookieName    cookie名称
     * @return
     */
    public static String getValueByName(HttpServletRequest request,
                                 CookieNameEnums cookieName) {
        if (cookieName == null) {
            return null;
        }
        Cookie[] cookies = request.getCookies();
        if (cookies != null && cookies.length != 0) {
            for (Cookie cookie : cookies) {
                if (cookie.getName().equals(cookieName.getName())) {
                    return cookie.getValue();
                }
            }
        }
        return null;
    }

    public static Integer getIdCookie(HttpServletRequest request,
                                     CookieNameEnums cookieName) {
        if (cookieName == null) {
            return null;
        }
        Cookie[] cookies = request.getCookies();
        if (cookies != null && cookies.length != 0) {
            for (Cookie cookie : cookies) {
                if (cookie.getName().equals(cookieName.getName())) {
                    return Integer.parseInt(cookie.getValue());
                }
            }
        }
        return null;
    }
}
