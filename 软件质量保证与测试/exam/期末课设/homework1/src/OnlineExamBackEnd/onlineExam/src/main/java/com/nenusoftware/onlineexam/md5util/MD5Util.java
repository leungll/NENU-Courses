package com.nenusoftware.onlineexam.md5util;

import java.security.MessageDigest;

/**
 * @Author:kongyy
 * @Description: MD5加密工具类
 * @Date: 20:23 2020/6/20
 */
public class MD5Util {

    /**
     * 对明文字符串进行MD5加密
     * @param inStr 明文字符串
     * @return 加密后的密文
     */
    public static String string2MD5(String inStr) {
        MessageDigest md5 = null;
        try {
            md5 = MessageDigest.getInstance("MD5");
        } catch (Exception e) {
            System.out.println(e.toString());
            e.printStackTrace();
            return "";
        }
        char[] charArray = inStr.toCharArray();
        byte[] byteArray = new byte[charArray.length];
        for (int i = 0; i < charArray.length; i++) {
            byteArray[i] = (byte) charArray[i];
        }
        byte[] md5Bytes = md5.digest(byteArray);
        StringBuilder hexValue = new StringBuilder();
        for (byte md5Byte : md5Bytes) {
            int val = ((int) md5Byte) & 0xff;
            if (val < 16) {
                hexValue.append("0");
            }
            hexValue.append(Integer.toHexString(val));
        }
        return hexValue.toString();
    }

    /**
     * 加密解密算法 执行一次加密，两次解密
     * @param inStr 输入密码
     * @return 处理后的字符串
     */
    public static String convertMD5(String inStr) {

        char[] a = inStr.toCharArray();
        for (int i = 0; i < a.length; i++) {
            a[i] = (char) (a[i] ^ 't');
        }
        String s = new String(a);
        return s;
    }

    /**
     * 测试函数
     * @param args 输入参数
     */
    public static void main(String[] args) {
        String s = "123";
        String ss = string2MD5(s);
        System.out.println("原始：" + s);
        System.out.println("MD5后：" + string2MD5(s));
        System.out.println("加密的：" + convertMD5(ss));
        System.out.println("解密的：" + convertMD5(convertMD5(s)));
    }
}
