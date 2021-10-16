package com.nenu.student.test;

import com.nenu.student.entity.Student;
import com.nenu.student.service.*;
import org.junit.Test;

import java.util.List;

/**
 * @Author:Liangll
 * @Description: ����ҵ�񷽷�
 * @Date: 15:23 2020/4/24
 */
public class SMTest {

    /**
     * ���Բ���ȫ��ѧ������
     * @throws Exception
     */
    @Test
    public void testQueryAllUser() throws Exception{
        ListAllStudent listAllStudent = new ListAllStudent();
        try{
            List<Student> list = listAllStudent.queryAllUser();
            System.out.println(list);
            System.out.println("���Բ���ȫ��ѧ���ɹ���");
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    /**
     * ��������ѧ����Ϣ����
     * @throws Exception
     */
    @Test
    public void testAddStudentInfo() throws Exception{
        AddStudent addStudent = new AddStudent();
        int s_id = 2017011111;
        String s_name = "����";
        String s_birth = "19991001";
        String s_sex = "Ů";
        try{
            addStudent.addStudentInfo(s_id, s_name, s_birth, s_sex);
            System.out.println("���Բ���ѧ���ɹ���");
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    /**
     * ���Ը���ѧ��ѧ��ɾ����Ϣ����
     * @throws Exception
     */
    @Test
    public void testDelStudentInfo() throws Exception{
        DelStudent delStudent = new DelStudent();
        int s_id = 2017011111;
        try{
            delStudent.delStudentInfo(s_id);
            System.out.println("����ɾ��ѧ���ɹ���");
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    /**
     * �����޸�ѧ����Ϣ����
     * @throws Exception
     */
    @Test
    public void testUpdateStudentInfo() throws Exception{
        UpdateStudent updateStudent = new UpdateStudent();
        int s_id = 2017011112;
        String s_name = "��Ѿ";
        String s_birth = "19920606";
        String s_sex = "Ů";
        try{
            updateStudent.updateStudentInfo(s_id, s_name, s_birth, s_sex);
            System.out.println("�����޸�ѧ���ɹ���");
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    /**
     * ���Ը���ѧ������������Ϣ����
     * @throws Exception
     */
    @Test
    public void testQueryUser() throws Exception{
        SelectStudent selectStudent = new SelectStudent();
        String s_name = "��Ѿ";
        try{
            System.out.println(selectStudent.queryUser(s_name));
            System.out.println("���Բ���ѧ���ɹ���");
        }catch (Exception e){
            e.printStackTrace();
        }
    }
}
