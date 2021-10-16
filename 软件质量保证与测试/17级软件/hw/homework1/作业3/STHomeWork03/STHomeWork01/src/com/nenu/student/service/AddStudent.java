package com.nenu.student.service;

import com.nenu.student.database.DatabaseConnection;

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

	//NO.1:参考《Google Java编程风格指南》5.2 标识符类型的规则 - 非常量字段名以lowerCamelCase 风格编写
//	JLabel JLNumber = new JLabel("学         号");
//	JTextField JTNumber = new JTextField();
//
//	JLabel JLName = new JLabel("姓         名");
//	JTextField JTName = new JTextField();
//
//	JLabel JLBirth = new JLabel("出生日期");
//	JTextField JTBirth = new JTextField();

	JLabel numberLabel = new JLabel("学         号");
	JTextField numberTextField = new JTextField();

	JLabel nameLabel = new JLabel("姓         名");
	JTextField nameTextField = new JTextField();

	JLabel birthLabel = new JLabel("出生日期");
	JTextField birthTextField = new JTextField();

	//NO.1:参考《Google Java编程风格指南》5.2 标识符类型的规则 - 非常量字段名以lowerCamelCase 风格编写
//	JLabel JLSex = new JLabel("性         别");

	JLabel sexLabel = new JLabel("性         别");
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
		numberLabel.setBounds(90, 60, 60, 25);
		numberTextField.setBounds(150, 60, 120, 25);
		this.add(numberLabel);
		this.add(numberTextField);

		//姓名
		nameLabel.setBounds(90, 100, 60, 20);
		nameTextField.setBounds(150, 100, 120, 25);
		this.add(nameLabel);
		this.add(nameTextField);

		//性别
		sexLabel.setBounds(90,140,60,20);
		//选择“男”的按钮
		radioBtn01.setBounds(150, 140, 65, 20);
		//选择“女”的按钮
		radioBtn02.setBounds(215, 140, 65, 20);
		//添加进按钮组
		btnGroup.add(radioBtn01);
		btnGroup.add(radioBtn02);
		this.add(sexLabel);
		this.add(radioBtn01);
		this.add(radioBtn02);

		//出生日期
		birthLabel.setBounds(90, 180, 60, 20);
		birthTextField.setBounds(150, 180, 120, 25);
		this.add(birthLabel);
		this.add(birthTextField);
		
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
	 */
	//NO.15:参考《Google Java编程风格指南》4.4 列限制：80或100
//	public void addStudentInfo(int studentId, String studentName, String studentBirth, String studentSex) throws Exception{
	public void addStudentInfo(int studentId, String studentName, String studentBirth, String studentSex){
		//NO.1:参考《Google Java编程风格指南》5.2 标识符类型的规则 - 非常量字段名以lowerCamelCase 风格编写
//		int s_Id = studentId;
//		String s_name = studentName;
//		String s_birth = studentBirth;
//		String s_sex = studentSex;

		//检索学生，存储进入数据库
		String sql = "select * from t_student where id='" + studentId + "'";

		try {
			//执行sql语句
			Statement stm = DatabaseConnection.getCon().createStatement();
			//查重语句
			ResultSet rs = stm.executeQuery(sql);
			if(rs.next()) {
				JOptionPane.showMessageDialog(null, "该学号学生已存在！", "提示信息", JOptionPane.WARNING_MESSAGE);
			} else {
				//插入一条记录
				sql = "insert into t_student values('" + studentId + "','" + studentName + "','" + studentBirth + "','" + studentSex + "')";
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
			//NO.1:参考《Google Java编程风格指南》5.2 标识符类型的规则 - 非常量字段名以lowerCamelCase 风格编写
//			int s_id = Integer.parseInt(numberTextField.getText());
//			String s_name = nameTextField.getText();
//			String s_sex = "女";
//			String s_birth = birthTextField.getText();

			//获取文本框中的内容
			int sId = Integer.parseInt(numberTextField.getText());
			String sName = nameTextField.getText();
			String sSex = "女";
			String sBirth = birthTextField.getText();

			//默认为男
			if(radioBtn01.isSelected()) {
				sSex = "男";
			}

			try {
				addStudentInfo(sId, sName, sBirth, sSex);
			} catch (Exception exception) {
				exception.printStackTrace();
			}
		}

		if(e.getSource() == readBtn) {
			numberTextField.setText(null);
			nameTextField .setText(null);
			birthTextField.setText(null);
		}

		if(e.getSource() == cancelBtn) {
			setVisible(false);
		}
	}
}