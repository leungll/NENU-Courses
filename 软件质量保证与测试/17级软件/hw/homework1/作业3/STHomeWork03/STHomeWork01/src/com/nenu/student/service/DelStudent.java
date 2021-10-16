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
 * @Description: ɾ��ѧ����Ϣ
 * @Date: 16:54 2020/4/20
 */
public class DelStudent extends JFrame implements ActionListener {

	//NO.1:�ο���Google Java��̷��ָ�ϡ�5.2 ��ʶ�����͵Ĺ��� - �ǳ����ֶ�����lowerCamelCase ����д
//	JLabel JLNumber = new JLabel("ѧ��");
//	JTextField JTNumber = new JTextField();

	JLabel jlnumber = new JLabel("ѧ��");
	JTextField jtnumber = new JTextField();

	JButton ensureBtn = new JButton("ȷ��");
	JButton nextBtn = new JButton("����");
	JButton cancelBtn = new JButton("ȡ��");

	public DelStudent() {
		this.setTitle("ɾ��ѧ����Ϣ");
		this.setLayout(null);

		//����
		jlnumber.setBounds(120, 100, 30, 20);
		jtnumber.setBounds(150, 100, 120, 25);
		this.add(jlnumber);
		this.add(jtnumber);

		ensureBtn.setBounds(100, 250, 60, 25);
		nextBtn.setBounds(170, 250, 60, 25);
		cancelBtn.setBounds(240, 250, 60, 25);

		//����¼�����
		ensureBtn.addActionListener(this);
		nextBtn.addActionListener(this);
		cancelBtn.addActionListener(this);
		this.add(ensureBtn);
		this.add(nextBtn);
		this.add(cancelBtn);
		this.setVisible(true);
		//���ô��ڵĴ�С
		this.setSize(380, 380);
		//���������ʾ
		this.setLocationRelativeTo(null);
	}

	/**
	 * ����ѧ��ɾ��ѧ����Ϣ
	 * @param studentNumber ѧ��
	 */
	public void delStudentInfo(int studentNumber){
		//NO.1:�ο���Google Java��̷��ָ�ϡ�5.2 ��ʶ�����͵Ĺ��� - �ǳ����ֶ�����lowerCamelCase ����д
//		int s_id = studentNumber;

		int sId = studentNumber;

		//����ѧ��
		String sql = "select * from t_student where id='" + sId + "'";

		//�����ݿ����Ӳ�����Statement����
		try {
			Statement stm = DatabaseConnection.getCon().createStatement();
			ResultSet rs = stm.executeQuery(sql);
			if(rs.next()) {
				sql = "delete from t_student where id ='" + sId + "'";
				int i = stm.executeUpdate(sql);
				if(i > 0) {
					JOptionPane.showMessageDialog(null, "ɾ���ɹ���", "��ʾ��Ϣ", JOptionPane.INFORMATION_MESSAGE);
				}else {
					JOptionPane.showMessageDialog(null, "ɾ��ʧ�ܣ�", "��ʾ��Ϣ", JOptionPane.INFORMATION_MESSAGE);
				}
			}
			stm.close();
		} catch (SQLException e1) {
			e1.printStackTrace();
		}
	}

	/**
	 * ����¼�
	 * @param e
	 */
	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == ensureBtn) {
			//NO.1:�ο���Google Java��̷��ָ�ϡ�5.2 ��ʶ�����͵Ĺ��� - �ǳ����ֶ�����lowerCamelCase ����д
//			int s_id = Integer.parseInt(jtnumber.getText());

			int sId = Integer.parseInt(jtnumber.getText());

			try {
				delStudentInfo(sId);
			} catch (Exception exception) {
				exception.printStackTrace();
			}
		}
		if(e.getSource() == nextBtn) {
			jtnumber.setText(null);
		}
		if(e.getSource() == cancelBtn) {
			setVisible(false);
		}
	}
}