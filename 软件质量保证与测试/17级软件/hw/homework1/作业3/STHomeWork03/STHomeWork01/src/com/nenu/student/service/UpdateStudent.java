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
 * @Description: �޸�ѧ����Ϣ
 * @Date: 17:00 2020/4/20
 */
public class UpdateStudent extends JFrame implements ActionListener {

	//NO.1:�ο���Google Java��̷��ָ�ϡ�5.2 ��ʶ�����͵Ĺ��� - �ǳ����ֶ�����lowerCamelCase ����д
//	JLabel JLNumber = new JLabel("ѧ         ��");
//	JTextField JTNumber = new JTextField();
//
//	JLabel JLName = new JLabel("��         ��");
//	JTextField JTName = new JTextField();
//
//	JLabel JLBirth = new JLabel("��������");
//	JTextField JTBirth = new JTextField();

	JLabel jlnumber = new JLabel("ѧ         ��");
	JTextField jtnumber = new JTextField();

	JLabel jlname = new JLabel("��         ��");
	JTextField jtname = new JTextField();

	JLabel jlbirth = new JLabel("��������");
	JTextField jtbirth = new JTextField();

	//NO.1:�ο���Google Java��̷��ָ�ϡ�5.2 ��ʶ�����͵Ĺ��� - �ǳ����ֶ�����lowerCamelCase ����д
//	JLabel JLSex = new JLabel("��         ��");

	JLabel jlsex = new JLabel("��         ��");
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
		jlnumber.setBounds(90, 60, 60, 25);
		jtnumber.setBounds(150, 60, 120, 25);
		this.add(jlnumber);
		this.add(jtnumber);

		//����
		jlname.setBounds(90, 100, 60, 20);
		jtname.setBounds(150, 100, 120, 25);
		this.add(jlname);
		this.add(jtname);

		//�Ա�
		jlsex.setBounds(90,140,60,20);
		//ѡ���С��İ�ť
		radioBtn01.setBounds(150, 140, 65, 20);
		//ѡ��Ů���İ�ť
		radioBtn02.setBounds(215, 140, 65, 20);
		//��ӽ���ť��
		btnGroup.add(radioBtn01);
		btnGroup.add(radioBtn02);
		this.add(jlsex);
		this.add(radioBtn01);
		this.add(radioBtn02);

		//��������
		jlbirth.setBounds(90, 180, 60, 20);
		jtbirth.setBounds(150, 180, 120, 25);
		this.add(jlbirth);
		this.add(jtbirth);

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
	 */
	//NO.15:�ο���Google Java��̷��ָ�ϡ�4.4 �����ƣ�80��100
//	public void updateStudentInfo(int studentId, String studentName, String studentBirth, String studentSex){
	public void updateStudentInfo(int studentId, String studentName,
								  String studentBirth, String studentSex){

		//NO.1:�ο���Google Java��̷��ָ�ϡ�5.2 ��ʶ�����͵Ĺ��� - �ǳ����ֶ�����lowerCamelCase ����д
//		int s_id = studentId;
//		String s_name = studentName;
//		String s_birth = studentBirth;
//		String s_sex = studentSex;

		//����ѧ��
		String sql = "select * from t_student where id='" + studentId + "'";

		//�����ݿ����Ӳ�����Statement����
		try {
			Statement stm = DatabaseConnection.getCon().createStatement();
			ResultSet rs = stm.executeQuery(sql);
			if(rs.next()) {
				//NO.15:�ο���Google Java��̷��ָ�ϡ�4.4 �����ƣ�80��100
//				sql = "update t_student set name ='" + sName  + "',birDate='" + sBirth + "',gender='" + sSex + "'where id=" + sId;
				sql = "update t_student set name ='" + studentName + "',birDate='" + studentBirth + "',gender='"
						+ studentSex + "'where id=" + studentId;

				int i = stm.executeUpdate(sql);
				if(i > 0) {
					//NO.15:�ο���Google Java��̷��ָ�ϡ�4.4 �����ƣ�80��100
//					JOptionPane.showMessageDialog(null, "�޸ĳɹ���", "��ʾ��Ϣ", JOptionPane.INFORMATION_MESSAGE);
					JOptionPane.showMessageDialog(null, "�޸ĳɹ���",
							"��ʾ��Ϣ", JOptionPane.INFORMATION_MESSAGE);
				}else {
					//NO.15:�ο���Google Java��̷��ָ�ϡ�4.4 �����ƣ�80��100
//					JOptionPane.showMessageDialog(null, "�޸�ʧ�ܣ�", "��ʾ��Ϣ", JOptionPane.INFORMATION_MESSAGE);
					JOptionPane.showMessageDialog(null, "�޸�ʧ�ܣ�",
							"��ʾ��Ϣ", JOptionPane.INFORMATION_MESSAGE);
				}
			} else {
				//NO.15:�ο���Google Java��̷��ָ�ϡ�4.4 �����ƣ�80��100
//				JOptionPane.showMessageDialog(null, "��ѧ��ѧ�������ڣ�", "��ʾ��Ϣ", JOptionPane.WARNING_MESSAGE);
				JOptionPane.showMessageDialog(null, "��ѧ��ѧ�������ڣ�",
						"��ʾ��Ϣ", JOptionPane.WARNING_MESSAGE);
			}
			stm.close();
		} catch (SQLException e1) {
			e1.printStackTrace();
		}
	}

	//NO.8:�ο���Google Java��̷��ָ�ϡ�7.1.3 Javadoc���
	/**
	 * ��Ӧ�¼�
	 * @param e
	 */
	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == ensureBtn) {

			//NO.1:�ο���Google Java��̷��ָ�ϡ�5.2 ��ʶ�����͵Ĺ��� - �ǳ����ֶ�����lowerCamelCase ����д
//			int s_id = Integer.parseInt(jtnumber.getText());
//			String s_name = jtname.getText();
//			String s_sex = "Ů";
//			String s_birth = jtbirth.getText();

			int sId = Integer.parseInt(jtnumber.getText());
			String sName = jtname.getText();
			String sSex = "Ů";
			String sBirth = jtbirth.getText();

			if(radioBtn01.isSelected()) {
				sSex = "��";
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