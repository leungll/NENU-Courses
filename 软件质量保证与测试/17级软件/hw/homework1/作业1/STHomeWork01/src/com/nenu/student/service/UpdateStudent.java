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
 * @Description: 修改学生信息
 * @Date: 17:00 2020/4/20
 */
public class UpdateStudent extends JFrame implements ActionListener {

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

	JButton ensureBtn = new JButton("确定");
	JButton readBtn = new JButton("重置");
	JButton cancelBtn = new JButton("取消");

	public UpdateStudent() {
		this.setTitle("修改学生信息");
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
		ensureBtn.setBounds(90, 250, 60, 25);
		readBtn.setBounds(160, 250, 60, 25);
		cancelBtn.setBounds(230, 250, 60, 25);

		//添加监听
		ensureBtn.addActionListener(this);
		readBtn.addActionListener(this);
		cancelBtn.addActionListener(this);
		this.add(ensureBtn);
		this.add(readBtn);
		this.add(cancelBtn);

		this.setVisible(true);
		//设置窗口的大小
		this.setSize(380, 380);
		//窗体居中显示
		this.setLocationRelativeTo(null);
	}

	/**
	 *根据学生学号修改信息
	 * @param studentId 学号
	 * @param studentName 姓名
	 * @param studentBirth 出生日期
	 * @param studentSex 性别
	 * @throws Exception
	 */
	public void updateStudentInfo(int studentId, String studentName, String studentBirth, String studentSex) throws Exception{
		int s_id = studentId;
		String s_name = studentName;
		String s_birth = studentBirth;
		String s_sex = studentSex;

		//检索学生
		String sql = "select * from t_student where id='" + s_id + "'";

		//打开数据库连接并创建Statement对象
		try {
			Statement stm = DBConnection.getCon().createStatement();
			ResultSet rs = stm.executeQuery(sql);
			if(rs.next()) {
				sql = "update t_student set name ='" + s_name  + "',birDate='" + s_birth + "',gender='" + s_sex + "'where id=" + s_id;
				int i = stm.executeUpdate(sql);
				if(i > 0) {
					JOptionPane.showMessageDialog(null, "修改成功！", "提示信息", JOptionPane.INFORMATION_MESSAGE);
				}else {
					JOptionPane.showMessageDialog(null, "修改失败！", "提示信息", JOptionPane.INFORMATION_MESSAGE);
				}
			} else {
				JOptionPane.showMessageDialog(null, "该学号学生不存在！", "提示信息", JOptionPane.WARNING_MESSAGE);
			}
			stm.close();
		} catch (SQLException e1) {
			e1.printStackTrace();
		}
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == ensureBtn) {
			int s_id = Integer.parseInt(JTNumber.getText());
			String s_name = JTName.getText();
			String s_sex = "女";
			String s_birth = JTBirth.getText();

			if(radioBtn01.isSelected()) {
				s_sex = "男";
			}

			try {
				updateStudentInfo(s_id, s_name, s_birth, s_sex);
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
