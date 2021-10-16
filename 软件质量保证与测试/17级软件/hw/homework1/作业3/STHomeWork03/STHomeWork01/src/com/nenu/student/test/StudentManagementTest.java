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
//NO.1:�ο���Google Java��̷��ָ�ϡ�5.2 ��ʶ�����͵Ĺ��� - ��������UpperCamelCase ����д
//public class SMTest {
public class StudentManagementTest {

    /**
     * ���Բ���ȫ��ѧ������
     */
    @Test
    public void testQueryAllUser(){
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
     */
    @Test
    public void testAddStudentInfo(){
        AddStudent addStudent = new AddStudent();
        //NO.1:�ο���Google Java��̷��ָ�ϡ�5.2 ��ʶ�����͵Ĺ��� - �ǳ����ֶ�����lowerCamelCase ����д
//        int s_id = 2017011111;
//        String s_name = "����";
//        String s_birth = "19991001";
//        String s_sex = "Ů";

        int sId = 2017011111;
        String sName = "����";
        String sBirth = "19991001";
        String sSex = "Ů";
        try{
            addStudent.addStudentInfo(sId, sName, sBirth, sSex);
            System.out.println("���Բ���ѧ���ɹ���");
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    /**
     * ���Ը���ѧ��ѧ��ɾ����Ϣ����
     */
    @Test
    public void testDelStudentInfo(){
        DelStudent delStudent = new DelStudent();
        //NO.1:�ο���Google Java��̷��ָ�ϡ�5.2 ��ʶ�����͵Ĺ��� - �ǳ����ֶ�����lowerCamelCase ����д
//        int s_id = 2017011111;
        int sId = 2017011111;
        try{
            delStudent.delStudentInfo(sId);
            System.out.println("����ɾ��ѧ���ɹ���");
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    /**
     * �����޸�ѧ����Ϣ����
     */
    @Test
    public void testUpdateStudentInfo(){
        UpdateStudent updateStudent = new UpdateStudent();
        //NO.1:�ο���Google Java��̷��ָ�ϡ�5.2 ��ʶ�����͵Ĺ��� - �ǳ����ֶ�����lowerCamelCase ����д
//        int s_id = 2017011112;
//        String s_name = "��Ѿ";
//        String s_birth = "19920606";
//        String s_sex = "Ů";

        int sId = 2017011112;
        String sName = "��Ѿ";
        String sBirth = "19920606";
        String sSex = "Ů";
        try{
            updateStudent.updateStudentInfo(sId, sName, sBirth, sSex);
            System.out.println("�����޸�ѧ���ɹ���");
        }catch (Exception e){
            e.printStackTrace();
        }
    }

    /**
     * ���Ը���ѧ������������Ϣ����
     */
    @Test
    public void testQueryUser(){
        SelectStudent selectStudent = new SelectStudent();
        //NO.1:�ο���Google Java��̷��ָ�ϡ�5.2 ��ʶ�����͵Ĺ��� - �ǳ����ֶ�����lowerCamelCase ����д
//        String s_name = "��Ѿ";
        String sName = "��Ѿ";
        try{
            System.out.println(selectStudent.queryUser(sName));
            System.out.println("���Բ���ѧ���ɹ���");
        }catch (Exception e){
            e.printStackTrace();
        }
    }
}
