package com.pandawork.common.utils;


import com.pandawork.core.common.log.LogClerk;
import com.pandawork.core.common.sytem.SystemInstance;

import java.io.UnsupportedEncodingException;

/**
 * 常量
 */
public class WebConstants {

    static  {
        // 读取属性文件中的值，设置初值
        SystemInstance systemInstance = SystemInstance.getIntance();
        String temp = "";
        staticWebsite = (String) systemInstance.getProperty("staticWebsite");
        uploadWebsite = (String) systemInstance.getProperty("uploadWebsite");
        wechatWebsite = (String) systemInstance.getProperty("wechatWebsite");


        temp = (String) systemInstance.getProperty("webTitle");
        try {
            webTitle = new String(temp.getBytes("ISO-8859-1"), "UTF-8");
        } catch (UnsupportedEncodingException e) {
            LogClerk.errLog.error(e.getMessage());
            webTitle = "";
        }
        temp = (String) systemInstance.getProperty("webName");
        try {
            webName = new String(temp.getBytes("ISO-8859-1"), "UTF-8");
        } catch (UnsupportedEncodingException e) {
            LogClerk.errLog.error(e.getMessage());
            webName = "";
        }
        temp = (String) systemInstance.getProperty("webFullName");
        try {
            webFullName = new String(temp.getBytes("ISO-8859-1"), "UTF-8");
        } catch (UnsupportedEncodingException e) {
            LogClerk.errLog.error(e.getMessage());
            webFullName = "";
        }
    }

    //第一平台


    // 网站标题
    public static String webTitle;

    // 网站名称
    public static String webName;

    public static String webFullName;

    public final static String staticWebsite;

    // 文件上传服务器地址
    public static final String uploadWebsite;

    public static final String wechatWebsite;

    // 用户ID
    public static final String WebUserId = "web_user_id";

    // web端的常量姓名
    public static final String WebUserName = "web_user_name";

    // web端的常量登录名
    public static final String WebLoginName = "web_login_name";

    public static final String WEB_ADMIN_USER_CENTER_KEY = "web_admin_vip_key";

    public static final String FILE_SEPARATOR = "/";

    public static final String ID_CARD_PIC_FOLDER = "/idCardPic/";
}
