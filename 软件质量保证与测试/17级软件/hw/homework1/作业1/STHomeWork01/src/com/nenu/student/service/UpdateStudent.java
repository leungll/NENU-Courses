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
 * @Description: �޸�ѧ����Ϣ
 * @Date: 17:00 2020/4/20
 */
public class UpdateStudent extends JFrame implements ActionListener {

	JLabel JLNumber = new JLabel("ѧ         ��");
	JTextField JTNumber = new JTextField();

	JLabel JLName = new JLabel("��         ��");
	JTextField JTName = new JTextField();

	JLabel JLBirth = new JLabel("��������");
	JTextField JTBirth = new JTextField();

	JLabel JLSex = new JLabel("��         ��");
	//������ť�飬��������ť��ӵ���ť����
	ButtonGroup btnGroup = new ButtonGroup();
	//����������ѡ��ť
	JRadioButton radioBtn01 = new JRadioButton("��");
	JRadioButton radioBtn02 = new JRadioButton("Ů");

	JButton ensureBtn = new JButton("ȷ��");
	JButton readBtn = new JButton("����");
	JButton cancelBtn = new JButton("ȡ��");

	public UpdateStudent() {
		this.setTitle("�޸�ѧ����Ϣ");
		this.setLayout(null);

		//ѧ��
		JLNumber.setBounds(90, 60, 60, 25);
		JTNumber.setBounds(150, 60, 120, 25);
		this.add(JLNumber);
		this.add(JTNumber);

		//����
		JLName.setBounds(90, 100, 60, 20);
		JTName.setBounds(150, 100, 120, 25);
		this.add(JLName);
		this.add(JTName);

		//�Ա�
		JLSex.setBounds(90,140,60,20);
		//ѡ���С��İ�ť
		radioBtn01.setBounds(150, 140, 65, 20);
		//ѡ��Ů���İ�ť
		radioBtn02.setBounds(215, 140, 65, 20);
		//��ӽ���ť��
		btnGroup.add(radioBtn01);
		btnGroup.add(radioBtn02);
		this.add(JLSex);
		this.add(radioBtn01);
		this.add(radioBtn02);

		//��������
		JLBirth.setBounds(90, 180, 60, 20);
		JTBirth.setBounds(150, 180, 120, 25);
		this.add(JLBirth);
		this.add(JTBirth);

		//��ӡ����á�ȡ��
		ensureBtn.setBounds(90, 250, 60, 25);
		readBtn.setBounds(160, 250, 60, 25);
		cancelBtn.setBounds(230, 250, 60, 25);

		//��Ӽ���
		ensureBtn.addActionListener(this);
		readBtn.addActionListener(this);
		cancelBtn.addActionListener(this);
		this.add(ensureBtn);
		this.add(readBtn);
		this.add(cancelBtn);

		this.setVisible(true);
		//���ô��ڵĴ�С
		this.setSize(380, 380);
		//���������ʾ
		this.setLocationRelativeTo(null);
	}

	/**
	 *����ѧ��ѧ���޸���Ϣ
	 * @param studentId ѧ��
	 * @param studentName ����
	 * @param studentBirth ��������
	 * @param studentSex �Ա�
	 * @throws Exception
	 */
	public void updateStudentInfo(int studentId, String studentName, String studentBirth, String studentSex) throws Exception{
		int s_id = studentId;
		String s_name = studentName;
		String s_birth = studentBirth;
		String s_sex = studentSex;

		//����ѧ��
		String sql = "select * from t_student where id='" + s_id + "'";

		//�����ݿ����Ӳ�����Statement����
		try {
			Statement stm = DBConnection.getCon().createStatement();
			ResultSet rs = stm.executeQuery(sql);
			if(rs.next()) {
				sql = "update t_student set name ='" + s_name  + "',birDate='" + s_birth + "',gender='" + s_sex + "'where id=" + s_id;
				int i = stm.executeUpdate(sql);
				if(i > 0) {
					JOptionPane.showMessageDialog(null, "�޸ĳɹ���", "��ʾ��Ϣ", JOptionPane.INFORMATION_MESSAGE);
				}else {
					JOptionPane.showMessageDialog(null, "�޸�ʧ�ܣ�", "��ʾ��Ϣ", JOptionPane.INFORMATION_MESSAGE);
				}
			} else {
				JOptionPane.showMessageDialog(null, "��ѧ��ѧ�������ڣ�", "��ʾ��Ϣ", JOptionPane.WARNING_MESSAGE);
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
			String s_sex = "Ů";
			String s_birth = JTBirth.getText();

			if(radioBtn01.isSelected()) {
				s_sex = "��";
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
