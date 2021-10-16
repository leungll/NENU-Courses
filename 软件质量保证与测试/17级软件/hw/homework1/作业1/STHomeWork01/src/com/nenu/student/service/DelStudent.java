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
 * @Description: 删除学生信息
 * @Date: 16:54 2020/4/20
 */
public class DelStudent extends JFrame implements ActionListener {

	JLabel JLNumber = new JLabel("学号");
	JTextField JTNumber = new JTextField();

	JButton ensureBtn = new JButton("确定");
	JButton nextBtn = new JButton("重置");
	JButton cancelBtn = new JButton("取消");

	public DelStudent() {
		this.setTitle("删除学生信息");
		this.setLayout(null);

		//姓名
		JLNumber.setBounds(120, 100, 30, 20);
		JTNumber.setBounds(150, 100, 120, 25);
		this.add(JLNumber);
		this.add(JTNumber);

		ensureBtn.setBounds(100, 250, 60, 25);
		nextBtn.setBounds(170, 250, 60, 25);
		cancelBtn.setBounds(240, 250, 60, 25);

		//添加事件监听
		ensureBtn.addActionListener(this);
		nextBtn.addActionListener(this);
		cancelBtn.addActionListener(this);
		this.add(ensureBtn);
		this.add(nextBtn);
		this.add(cancelBtn);
		this.setVisible(true);
		//设置窗口的大小
		this.setSize(380, 380);
		//窗体居中显示
		this.setLocationRelativeTo(null);
	}

	/**
	 * 根据学号删除学生信息
	 * @param studentNumber 学号
	 * @throws Exception
	 */
	public void delStudentInfo(int studentNumber) throws Exception{
		int s_id = studentNumber;

		//检索学生
		String sql = "select * from t_student where id='" + s_id + "'";

		//打开数据库连接并创建Statement对象
		try {
			Statement stm = DBConnection.getCon().createStatement();
			ResultSet rs = stm.executeQuery(sql);
			if(rs.next()) {
				sql = "delete from t_student where id ='" + s_id + "'";
				int i = stm.executeUpdate(sql);
				if(i > 0) {
					JOptionPane.showMessageDialog(null, "删除成功！", "提示信息", JOptionPane.INFORMATION_MESSAGE);
				}else {
					JOptionPane.showMessageDialog(null, "删除失败！", "提示信息", JOptionPane.INFORMATION_MESSAGE);
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
		if(e.getSource() == ensureBtn) {
			int s_id = Integer.parseInt(JTNumber.getText());

			try {
				delStudentInfo(s_id);
			} catch (Exception exception) {
				exception.printStackTrace();
			}
		}
		if(e.getSource() == nextBtn) {
			JTNumber .setText(null);
		}
		if(e.getSource() == cancelBtn) {
			setVisible(false);
		}
	}
}
