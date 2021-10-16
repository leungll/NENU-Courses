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
 * @Description: ����ѧ����Ϣ
 * @Date: 16:37 2020/4/20
 */
public class AddStudent extends JFrame implements ActionListener {

	//NO.1:�ο���Google Java��̷��ָ�ϡ�5.2 ��ʶ�����͵Ĺ��� - �ǳ����ֶ�����lowerCamelCase ����д
//	JLabel JLNumber = new JLabel("ѧ         ��");
//	JTextField JTNumber = new JTextField();
//
//	JLabel JLName = new JLabel("��         ��");
//	JTextField JTName = new JTextField();
//
//	JLabel JLBirth = new JLabel("��������");
//	JTextField JTBirth = new JTextField();

	JLabel numberLabel = new JLabel("ѧ         ��");
	JTextField numberTextField = new JTextField();

	JLabel nameLabel = new JLabel("��         ��");
	JTextField nameTextField = new JTextField();

	JLabel birthLabel = new JLabel("��������");
	JTextField birthTextField = new JTextField();

	//NO.1:�ο���Google Java��̷��ָ�ϡ�5.2 ��ʶ�����͵Ĺ��� - �ǳ����ֶ�����lowerCamelCase ����д
//	JLabel JLSex = new JLabel("��         ��");

	JLabel sexLabel = new JLabel("��         ��");
	//������ť�飬��������ť��ӵ���ť����
	ButtonGroup btnGroup = new ButtonGroup();
	//����������ѡ��ť
	JRadioButton radioBtn01 = new JRadioButton("��");
	JRadioButton radioBtn02 = new JRadioButton("Ů");

	JButton addBtn = new JButton("���");
	JButton readBtn = new JButton("����");
	JButton cancelBtn = new JButton("ȡ��");

	public AddStudent() {

		this.setTitle("���ѧ����Ϣ");
		//���Ĭ�ϲ��֣�ʹ���Լ����õ�������Ϊ����
		this.setLayout(null);

		//ѧ��
		numberLabel.setBounds(90, 60, 60, 25);
		numberTextField.setBounds(150, 60, 120, 25);
		this.add(numberLabel);
		this.add(numberTextField);

		//����
		nameLabel.setBounds(90, 100, 60, 20);
		nameTextField.setBounds(150, 100, 120, 25);
		this.add(nameLabel);
		this.add(nameTextField);

		//�Ա�
		sexLabel.setBounds(90,140,60,20);
		//ѡ���С��İ�ť
		radioBtn01.setBounds(150, 140, 65, 20);
		//ѡ��Ů���İ�ť
		radioBtn02.setBounds(215, 140, 65, 20);
		//��ӽ���ť��
		btnGroup.add(radioBtn01);
		btnGroup.add(radioBtn02);
		this.add(sexLabel);
		this.add(radioBtn01);
		this.add(radioBtn02);

		//��������
		birthLabel.setBounds(90, 180, 60, 20);
		birthTextField.setBounds(150, 180, 120, 25);
		this.add(birthLabel);
		this.add(birthTextField);
		
		//��ӡ����á�ȡ��
		addBtn.setBounds(90, 250, 60, 25);
		readBtn.setBounds(160, 250, 60, 25);
		cancelBtn.setBounds(230, 250, 60, 25);

		//��Ӽ���
		addBtn.addActionListener(this);
		readBtn.addActionListener(this);
		cancelBtn.addActionListener(this);
		
		this.add(addBtn);
		this.add(readBtn);
		this.add(cancelBtn);

		this.setVisible(true);
		//���ô��ڵĴ�С
		this.setSize(380, 380);
		//���������ʾ
		this.setLocationRelativeTo(null);
	}

	/**
	 * ����ѧ����Ϣ���������ݿ⣩
	 * @param studentId ѧ��
	 * @param studentName ����
	 * @param studentBirth ��������
	 * @param studentSex �Ա�
	 */
	//NO.15:�ο���Google Java��̷��ָ�ϡ�4.4 �����ƣ�80��100
//	public void addStudentInfo(int studentId, String studentName, String studentBirth, String studentSex) throws Exception{
	public void addStudentInfo(int studentId, String studentName, String studentBirth, String studentSex){
		//NO.1:�ο���Google Java��̷��ָ�ϡ�5.2 ��ʶ�����͵Ĺ��� - �ǳ����ֶ�����lowerCamelCase ����д
//		int s_Id = studentId;
//		String s_name = studentName;
//		String s_birth = studentBirth;
//		String s_sex = studentSex;

		//����ѧ�����洢�������ݿ�
		String sql = "select * from t_student where id='" + studentId + "'";

		try {
			//ִ��sql���
			Statement stm = DatabaseConnection.getCon().createStatement();
			//�������
			ResultSet rs = stm.executeQuery(sql);
			if(rs.next()) {
				JOptionPane.showMessageDialog(null, "��ѧ��ѧ���Ѵ��ڣ�", "��ʾ��Ϣ", JOptionPane.WARNING_MESSAGE);
			} else {
				//����һ����¼
				sql = "insert into t_student values('" + studentId + "','" + studentName + "','" + studentBirth + "','" + studentSex + "')";
				//ִ����sql���
				int i = stm.executeUpdate(sql);
				if(i > 0) {
					JOptionPane.showMessageDialog(null, "��ӳɹ���", "��ʾ��Ϣ", JOptionPane.INFORMATION_MESSAGE);
				}else {
					JOptionPane.showMessageDialog(null, "���ʧ�ܣ�", "��ʾ��Ϣ", JOptionPane.INFORMATION_MESSAGE);
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
		if(e.getSource() == addBtn) {
			//NO.1:�ο���Google Java��̷��ָ�ϡ�5.2 ��ʶ�����͵Ĺ��� - �ǳ����ֶ�����lowerCamelCase ����д
//			int s_id = Integer.parseInt(numberTextField.getText());
//			String s_name = nameTextField.getText();
//			String s_sex = "Ů";
//			String s_birth = birthTextField.getText();

			//��ȡ�ı����е�����
			int sId = Integer.parseInt(numberTextField.getText());
			String sName = nameTextField.getText();
			String sSex = "Ů";
			String sBirth = birthTextField.getText();

			//Ĭ��Ϊ��
			if(radioBtn01.isSelected()) {
				sSex = "��";
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