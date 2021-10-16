package com.nenu.student.service;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.*;
import javax.swing.*;

import com.nenu.student.database.DatabaseConnection;
import com.nenu.student.entity.Student;

/**
 * @Author: Liangll
 * @Description: ����ѧ������������Ϣ
 * @Date: 17:08 2020/4/20
 */
public class SelectStudent extends JFrame implements ActionListener {

	private Object [][]rowData;
	private final Object []column = {"ѧ��", "����", "��������", "�Ա�"};

	JPanel ePanel = new JPanel();
	JPanel wPanel = new JPanel();

	//NO.1:�ο���Google Java��̷��ָ�ϡ�5.2 ��ʶ�����͵Ĺ��� - �ǳ����ֶ�����lowerCamelCase ����д
//	JLabel JLName = new JLabel("����");
//	JTextField JTName = new JTextField(16);

	JLabel jlname = new JLabel("����");
	JTextField jtname = new JTextField(16);

	JButton searchBtn = new JButton("��ѯ");
	JButton nextBtn = new JButton("����");
	JButton cancelBtn = new JButton("ȡ��");

	public SelectStudent() {
		this.setTitle("��ѯѧ����Ϣ");
		this.setLayout(new BorderLayout());

		//�����
		wPanel.add(jlname);
		wPanel.add(jtname);

		//��ť
		ePanel.add(searchBtn);
		ePanel.add(nextBtn);
		ePanel.add(cancelBtn);

		//��Ӽ����¼�
		searchBtn.addActionListener(this);
		nextBtn.addActionListener(this);
		cancelBtn.addActionListener(this);

		//����
		this.add(ePanel, BorderLayout.SOUTH);
		this.add(wPanel, BorderLayout.NORTH);

		this.pack();
		//���������ʾ
		this.setLocationRelativeTo(null);
		//���ڴ�С
		this.setSize(400, 150);
		this.setVisible(true);
	}

	/**
	 * ���ñ�����ʽ
	 * @param name
	 */
	public void setTable(String name) {
		this.setVisible(false);
		JFrame jf = new JFrame("��ѯ���");
		jf.setLocationRelativeTo(null);
		JPanel panel = new JPanel();

		//���������
		Object [][]rowData = queryData(name);
		JTable table = new JTable(rowData, column);

		/**
		 * ���ñ��������ɫ
		 */
		//������ɫ
		table.setForeground(Color.BLACK);
		//������ʽ
		table.setFont(new Font(null, Font.PLAIN, 14));
		//ѡ�к����屳��
		table.setSelectionBackground(Color.DARK_GRAY);
		//ѡ�к�������ɫ
		table.setSelectionForeground(Color.LIGHT_GRAY);
		//������ɫ
		table.setGridColor(Color.GRAY);

		/**
		 * ���ò�ѯ�����ͷ
		 */
		//���ñ�ͷ������ʽ
		table.getTableHeader().setFont(new Font(null, Font.BOLD, 14));

		//��ͷ����������ɫ
		table.getTableHeader().setForeground(Color.BLACK);

		//�������ֶ��ı��п�
		table.getTableHeader().setResizingAllowed(false);

		//�������϶��������и���
		table.getTableHeader().setReorderingAllowed(false);

		//�����и�30
		table.setRowHeight(30);

		//�п�����Ϊ100
		table.getColumnModel().getColumn(0).setPreferredWidth(80);
		table.getColumnModel().getColumn(3).setPreferredWidth(80);

		//���ù�������ӿڴ�С
		table.setPreferredScrollableViewportSize(new Dimension(550,200));

		//�ѱ��ŵ���������У��Զ���ӵ�������
		JScrollPane scrollPane = new JScrollPane(table);
		panel.add(scrollPane);
		jf.add(panel);
		jf.pack();
		jf.setContentPane(panel);
		jf.setVisible(true);
	}

	/**
	 * ����ѧ����������
	 * @return ���ҵ���ѧ�����ݷ���
	 */
	public Student queryUser(String name){
		Connection conn = null;
		//Ԥ�������
		PreparedStatement ps = null;
		//�����
		ResultSet rs = null;
		Student student = new Student();
		String sql = "select * from t_student where name='" + name + "'";
		try {
			conn = DatabaseConnection.getCon();
			//��ȡ�����
			ps = conn.prepareStatement(sql);
			rs = ps.executeQuery();
			if(rs.next()){
				student.setId(rs.getInt(1));
				student.setName(rs.getString(2));
				student.setBirDate(rs.getString(3));
				student.setGender(rs.getString(4));
			}else {
				//NO.15:�ο���Google Java��̷��ָ�ϡ�4.4 �����ƣ�80��100
//				JOptionPane.showMessageDialog(null, "���˺Ų����ڣ�", "��ʾ��Ϣ", JOptionPane.WARNING_MESSAGE);
				JOptionPane.showMessageDialog(null, "���˺Ų����ڣ�",
						"��ʾ��Ϣ", JOptionPane.WARNING_MESSAGE);

			}
			conn.close();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return student;
	}

    /**
     * ����ѧ������
     * @return ѧ�����ݶ�ά����
     */
    public Object[][] queryData(String name){
		if(" ".equals(name)) {
			//NO.15:�ο���Google Java��̷��ָ�ϡ�4.4 �����ƣ�80��100
//			JOptionPane.showMessageDialog(null, "����Ϊ�գ����������룡", "��ʾ��Ϣ", JOptionPane.WARNING_MESSAGE);
			JOptionPane.showMessageDialog(null, "����Ϊ�գ����������룡", "��ʾ��Ϣ", JOptionPane.WARNING_MESSAGE);

		}else {
        	Student student = queryUser(name);
			//������Ϊ1,��ֹ����Խ��
			rowData = new Object[1][column.length];
			rowData[0][0] = student.getId();
			rowData[0][1] = student.getName();
			rowData[0][2] = student.getBirDate();
			rowData[0][3] = student.getGender();
		}
		return rowData;
    }

	//NO.8:�ο���Google Java��̷��ָ�ϡ�7.1.3 Javadoc���
	/**
	 * ��Ӧ�¼�
	 * @param e
	 */
	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == searchBtn) {
			String name = jtname.getText();
			setTable(name);
		}
		if(e.getSource() == nextBtn) {
			jtname.setText(null);
		}
		if(e.getSource() == cancelBtn) {
			this.setVisible(false);
		}
	}
}