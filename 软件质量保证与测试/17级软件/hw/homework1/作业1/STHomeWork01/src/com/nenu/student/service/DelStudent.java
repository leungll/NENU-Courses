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
 * @Description: ɾ��ѧ����Ϣ
 * @Date: 16:54 2020/4/20
 */
public class DelStudent extends JFrame implements ActionListener {

	JLabel JLNumber = new JLabel("ѧ��");
	JTextField JTNumber = new JTextField();

	JButton ensureBtn = new JButton("ȷ��");
	JButton nextBtn = new JButton("����");
	JButton cancelBtn = new JButton("ȡ��");

	public DelStudent() {
		this.setTitle("ɾ��ѧ����Ϣ");
		this.setLayout(null);

		//����
		JLNumber.setBounds(120, 100, 30, 20);
		JTNumber.setBounds(150, 100, 120, 25);
		this.add(JLNumber);
		this.add(JTNumber);

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
	 * @throws Exception
	 */
	public void delStudentInfo(int studentNumber) throws Exception{
		int s_id = studentNumber;

		//����ѧ��
		String sql = "select * from t_student where id='" + s_id + "'";

		//�����ݿ����Ӳ�����Statement����
		try {
			Statement stm = DBConnection.getCon().createStatement();
			ResultSet rs = stm.executeQuery(sql);
			if(rs.next()) {
				sql = "delete from t_student where id ='" + s_id + "'";
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
