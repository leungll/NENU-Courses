package com.nenu.student.test;

import com.nenu.student.entity.Student;
import com.nenu.student.service.*;
import org.junit.Test;

import java.util.List;

/**
 * @Author:Liangll
 * @Description: 测试业务方法
 * @Date: 15:23 2020/4/24
 */
//NO.1:参考《Google Java编程风格指南》5.2 标识符类型的规则 - 类名都以UpperCamelCase 风格编写
//public class SMTest {
public class StudentManagementTest {

    /**
     * 测试查找全部学生方法
     */
    @Test
    public void testQueryAllUser(){
        ListAllStudent listAllStudent = new ListAllStudent();
        try{
            List<Student> list = listAllStudent.queryAllUser();
            System.out.println(list);
            System.out.println("测试查找全部学生成功！");
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    /**
     * 测试增加学生信息方法
     */
    @Test
    public void testAddStudentInfo(){
        AddStudent addStudent = new AddStudent();
        //NO.1:参考《Google Java编程风格指南》5.2 标识符类型的规则 - 非常量字段名以lowerCamelCase 风格编写
//        int s_id = 2017011111;
//        String s_name = "王五";
//        String s_birth = "19991001";
//        String s_sex = "女";

        int sId = 2017011111;
        String sName = "王五";
        String sBirth = "19991001";
        String sSex = "女";
        try{
            addStudent.addStudentInfo(sId, sName, sBirth, sSex);
            System.out.println("测试插入学生成功！");
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    /**
     * 测试根据学生学号删除信息方法
     */
    @Test
    public void testDelStudentInfo(){
        DelStudent delStudent = new DelStudent();
        //NO.1:参考《Google Java编程风格指南》5.2 标识符类型的规则 - 非常量字段名以lowerCamelCase 风格编写
//        int s_id = 2017011111;
        int sId = 2017011111;
        try{
            delStudent.delStudentInfo(sId);
            System.out.println("测试删除学生成功！");
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    /**
     * 测试修改学生信息方法
     */
    @Test
    public void testUpdateStudentInfo(){
        UpdateStudent updateStudent = new UpdateStudent();
        //NO.1:参考《Google Java编程风格指南》5.2 标识符类型的规则 - 非常量字段名以lowerCamelCase 风格编写
//        int s_id = 2017011112;
//        String s_name = "二丫";
//        String s_birth = "19920606";
//        String s_sex = "女";

        int sId = 2017011112;
        String sName = "二丫";
        String sBirth = "19920606";
        String sSex = "女";
        try{
            updateStudent.updateStudentInfo(sId, sName, sBirth, sSex);
            System.out.println("测试修改学生成功！");
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    /**
     * 测试根据学生姓名查找信息方法
     */
    @Test
    public void testQueryUser(){
        SelectStudent selectStudent = new SelectStudent();
        //NO.1:参考《Google Java编程风格指南》5.2 标识符类型的规则 - 非常量字段名以lowerCamelCase 风格编写
//        String s_name = "二丫";
        String sName = "二丫";
        try{
            System.out.println(selectStudent.queryUser(sName));
            System.out.println("测试查找学生成功！");
        }catch (Exception e){
            e.printStackTrace();
        }
    }
}
