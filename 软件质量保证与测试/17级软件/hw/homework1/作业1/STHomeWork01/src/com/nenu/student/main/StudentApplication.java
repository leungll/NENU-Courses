package com.nenu.student.main;

import com.nenu.student.service.StudentManagement;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * @Author: Liangll
 * @Description: 启动界面
 * @Date: 16:29 2020/4/20
 */
public class StudentApplication extends Frame implements ActionListener {
    public static void main(String[] args) {
        new StudentManagement();
    }
    @Override
    public void actionPerformed(ActionEvent e) {
        // TODO Auto-generated method stub
    }
}


