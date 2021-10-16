package com.nenu.student.service;

import com.nenu.student.database.DBConnection;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

/**
 * @Author: Liangll
 * @Description: 增加学生信息
 * @Date: 16:37 2020/4/20
 */
public class AddStudent extends JFrame implements ActionListener {

	JLabel JLNumber = new JLabel("学         号");
	JTextField JTNumber = new JTextField();

	JLabel JLName = new JLabel("姓         名");
	JTextField JTName = new JTextField();

	JLabel JLBirth = new JLabel("出生日期");
	JTextField JTBirth = new JTextField();

	JLabel JLSex = new JLabel("性         别");
	//创建按钮组，把两个按钮添加到按钮组中
	ButtonGroup btnGroup = new ButtonGroup();
	//创建两个单选按钮
	JRadioButton radioBtn01 = new JRadioButton("男");
	JRadioButton radioBtn02 = new JRadioButton("女");

	JButton addBtn = new JButton("添加");
	JButton readBtn = new JButton("重置");
	JButton cancelBtn = new JButton("取消");

	public AddStudent() {

		this.setTitle("添加学生信息");
		//清空默认布局，使用自己设置的坐标作为布局
		this.setLayout(null);

		//学号
		JLNumber.setBounds(90, 60, 60, 25);
		JTNumber.setBounds(150, 60, 120, 25);
		this.add(JLNumber);
		this.add(JTNumber);

		//姓名
		JLName.setBounds(90, 100, 60, 20);
		JTName.setBounds(150, 100, 120, 25);
		this.add(JLName);
		this.add(JTName);	

		//性别
		JLSex.setBounds(90,140,60,20);
		//选择“男”的按钮
		radioBtn01.setBounds(150, 140, 65, 20);
		//选择“女”的按钮
		radioBtn02.setBounds(215, 140, 65, 20);
		//添加进按钮组
		btnGroup.add(radioBtn01);
		btnGroup.add(radioBtn02);
		this.add(JLSex);
		this.add(radioBtn01);
		this.add(radioBtn02);

		//出生日期
		JLBirth.setBounds(90, 180, 60, 20);
		JTBirth.setBounds(150, 180, 120, 25);
		this.add(JLBirth);
		this.add(JTBirth);
		
		//添加、重置、取消
		addBtn.setBounds(90, 250, 60, 25);
		readBtn.setBounds(160, 250, 60, 25);
		cancelBtn.setBounds(230, 250, 60, 25);

		//添加监听
		addBtn.addActionListener(this);
		readBtn.addActionListener(this);
		cancelBtn.addActionListener(this);
		
		this.add(addBtn);
		this.add(readBtn);
		this.add(cancelBtn);

		this.setVisible(true);
		//设置窗口的大小
		this.setSize(380, 380);
		//窗体居中显示
		this.setLocationRelativeTo(null);
	}

	/**
	 * 增加学生信息（连接数据库）
	 * @param studentId 学号
	 * @param studentName 姓名
	 * @param studentBirth 出生日期
	 * @param studentSex 性别
	 * @throws Exception
	 */
	public void addStudentInfo(int studentId, String studentName, String studentBirth, String studentSex) throws Exception{
		int s_id = studentId;
		String s_name = studentName;
		String s_birth = studentBirth;
		String s_sex = studentSex;

		//检索学生，存储进入数据库
		String sql = "select * from t_student where id='" + s_id + "'";

		try {
			//执行sql语句
			Statement stm = DBConnection.getCon().createStatement();
			//查重语句
			ResultSet rs = stm.executeQuery(sql);
			if(rs.next()) {
				JOptionPane.showMessageDialog(null, "该学号学生已存在！", "提示信息", JOptionPane.WARNING_MESSAGE);
			} else {
				//插入一条记录
				sql = "insert into t_student values('" + s_id + "','" + s_name + "','" + s_birth + "','" + s_sex + "')";
				//执行了sql语句
				int i = stm.executeUpdate(sql);
				if(i > 0) {
					JOptionPane.showMessageDialog(null, "添加成功！", "提示信息", JOptionPane.INFORMATION_MESSAGE);
				}else {
					JOptionPane.showMessageDialog(null, "添加失败！", "提示信息", JOptionPane.INFORMATION_MESSAGE);
				}
			}
			stm.close();
		} catch (SQLException e1) {
			e1.printStackTrace();
		}
	}

	/**
	 * 点击事件
	 * @param e
	 */
	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == addBtn) {
			//获取文本框中的内容
			int s_id = Integer.parseInt(JTNumber.getText());
			String s_name = JTName.getText();
			String s_sex = "女";
			String s_birth = JTBirth.getText();

			//默认为男
			if(radioBtn01.isSelected()) {
				s_sex = "男";
			}

			try {
				addStudentInfo(s_id, s_name, s_birth, s_sex);
			} catch (Exception exception) {
				exception.printStackTrace();
			}
		}

		if(e.getSource() == readBtn) {
			JTNumber.setText(null);
			JTName .setText(null);
			JTBirth.setText(null);
		}

		if(e.getSource() == cancelBtn) {
			setVisible(false);
		}
	}
}
