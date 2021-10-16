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
public class SMTest {

    /**
     * 测试查找全部学生方法
     * @throws Exception
     */
    @Test
    public void testQueryAllUser() throws Exception{
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
     * @throws Exception
     */
    @Test
    public void testAddStudentInfo() throws Exception{
        AddStudent addStudent = new AddStudent();
        int s_id = 2017011111;
        String s_name = "王五";
        String s_birth = "19991001";
        String s_sex = "女";
        try{
            addStudent.addStudentInfo(s_id, s_name, s_birth, s_sex);
            System.out.println("测试插入学生成功！");
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    /**
     * 测试根据学生学号删除信息方法
     * @throws Exception
     */
    @Test
    public void testDelStudentInfo() throws Exception{
        DelStudent delStudent = new DelStudent();
        int s_id = 2017011111;
        try{
            delStudent.delStudentInfo(s_id);
            System.out.println("测试删除学生成功！");
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    /**
     * 测试修改学生信息方法
     * @throws Exception
     */
    @Test
    public void testUpdateStudentInfo() throws Exception{
        UpdateStudent updateStudent = new UpdateStudent();
        int s_id = 2017011112;
        String s_name = "二丫";
        String s_birth = "19920606";
        String s_sex = "女";
        try{
            updateStudent.updateStudentInfo(s_id, s_name, s_birth, s_sex);
            System.out.println("测试修改学生成功！");
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    /**
     * 测试根据学生姓名查找信息方法
     * @throws Exception
     */
    @Test
    public void testQueryUser() throws Exception{
        SelectStudent selectStudent = new SelectStudent();
        String s_name = "二丫";
        try{
            System.out.println(selectStudent.queryUser(s_name));
            System.out.println("测试查找学生成功！");
        }catch (Exception e){
            e.printStackTrace();
        }
    }
}
