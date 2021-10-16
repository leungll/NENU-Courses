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
 * @Description: 修改学生信息
 * @Date: 17:00 2020/4/20
 */
public class UpdateStudent extends JFrame implements ActionListener {

	//NO.1:参考《Google Java编程风格指南》5.2 标识符类型的规则 - 非常量字段名以lowerCamelCase 风格编写
//	JLabel JLNumber = new JLabel("学         号");
//	JTextField JTNumber = new JTextField();
//
//	JLabel JLName = new JLabel("姓         名");
//	JTextField JTName = new JTextField();
//
//	JLabel JLBirth = new JLabel("出生日期");
//	JTextField JTBirth = new JTextField();

	JLabel jlnumber = new JLabel("学         号");
	JTextField jtnumber = new JTextField();

	JLabel jlname = new JLabel("姓         名");
	JTextField jtname = new JTextField();

	JLabel jlbirth = new JLabel("出生日期");
	JTextField jtbirth = new JTextField();

	//NO.1:参考《Google Java编程风格指南》5.2 标识符类型的规则 - 非常量字段名以lowerCamelCase 风格编写
//	JLabel JLSex = new JLabel("性         别");

	JLabel jlsex = new JLabel("性         别");
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
		jlnumber.setBounds(90, 60, 60, 25);
		jtnumber.setBounds(150, 60, 120, 25);
		this.add(jlnumber);
		this.add(jtnumber);

		//姓名
		jlname.setBounds(90, 100, 60, 20);
		jtname.setBounds(150, 100, 120, 25);
		this.add(jlname);
		this.add(jtname);

		//性别
		jlsex.setBounds(90,140,60,20);
		//选择“男”的按钮
		radioBtn01.setBounds(150, 140, 65, 20);
		//选择“女”的按钮
		radioBtn02.setBounds(215, 140, 65, 20);
		//添加进按钮组
		btnGroup.add(radioBtn01);
		btnGroup.add(radioBtn02);
		this.add(jlsex);
		this.add(radioBtn01);
		this.add(radioBtn02);

		//出生日期
		jlbirth.setBounds(90, 180, 60, 20);
		jtbirth.setBounds(150, 180, 120, 25);
		this.add(jlbirth);
		this.add(jtbirth);

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
	 */
	//NO.15:参考《Google Java编程风格指南》4.4 列限制：80或100
//	public void updateStudentInfo(int studentId, String studentName, String studentBirth, String studentSex){
	public void updateStudentInfo(int studentId, String studentName,
								  String studentBirth, String studentSex){

		//NO.1:参考《Google Java编程风格指南》5.2 标识符类型的规则 - 非常量字段名以lowerCamelCase 风格编写
//		int s_id = studentId;
//		String s_name = studentName;
//		String s_birth = studentBirth;
//		String s_sex = studentSex;

		//检索学生
		String sql = "select * from t_student where id='" + studentId + "'";

		//打开数据库连接并创建Statement对象
		try {
			Statement stm = DatabaseConnection.getCon().createStatement();
			ResultSet rs = stm.executeQuery(sql);
			if(rs.next()) {
				//NO.15:参考《Google Java编程风格指南》4.4 列限制：80或100
//				sql = "update t_student set name ='" + sName  + "',birDate='" + sBirth + "',gender='" + sSex + "'where id=" + sId;
				sql = "update t_student set name ='" + studentName + "',birDate='" + studentBirth + "',gender='"
						+ studentSex + "'where id=" + studentId;

				int i = stm.executeUpdate(sql);
				if(i > 0) {
					//NO.15:参考《Google Java编程风格指南》4.4 列限制：80或100
//					JOptionPane.showMessageDialog(null, "修改成功！", "提示信息", JOptionPane.INFORMATION_MESSAGE);
					JOptionPane.showMessageDialog(null, "修改成功！",
							"提示信息", JOptionPane.INFORMATION_MESSAGE);
				}else {
					//NO.15:参考《Google Java编程风格指南》4.4 列限制：80或100
//					JOptionPane.showMessageDialog(null, "修改失败！", "提示信息", JOptionPane.INFORMATION_MESSAGE);
					JOptionPane.showMessageDialog(null, "修改失败！",
							"提示信息", JOptionPane.INFORMATION_MESSAGE);
				}
			} else {
				//NO.15:参考《Google Java编程风格指南》4.4 列限制：80或100
//				JOptionPane.showMessageDialog(null, "该学号学生不存在！", "提示信息", JOptionPane.WARNING_MESSAGE);
				JOptionPane.showMessageDialog(null, "该学号学生不存在！",
						"提示信息", JOptionPane.WARNING_MESSAGE);
			}
			stm.close();
		} catch (SQLException e1) {
			e1.printStackTrace();
		}
	}

	//NO.8:参考《Google Java编程风格指南》7.1.3 Javadoc标记
	/**
	 * 响应事件
	 * @param e
	 */
	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == ensureBtn) {

			//NO.1:参考《Google Java编程风格指南》5.2 标识符类型的规则 - 非常量字段名以lowerCamelCase 风格编写
//			int s_id = Integer.parseInt(jtnumber.getText());
//			String s_name = jtname.getText();
//			String s_sex = "女";
//			String s_birth = jtbirth.getText();

			int sId = Integer.parseInt(jtnumber.getText());
			String sName = jtname.getText();
			String sSex = "女";
			String sBirth = jtbirth.getText();

			if(radioBtn01.isSelected()) {
				sSex = "男";
			}

			try {
				updateStudentInfo(sId, sName, sBirth, sSex);
			} catch (Exception exception) {
				exception.printStackTrace();
			}
		}

		if(e.getSource() == readBtn) {
			jtnumber.setText(null);
			jtname.setText(null);
			jtbirth.setText(null);
		}

		if(e.getSource() == cancelBtn) {
			setVisible(false);
		}
	}
}