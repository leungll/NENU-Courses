package com.nenu.student.service;

import java.awt.Font;
import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

/**
 * @Author: Liangll
 * @Description: ѧ��������
 * @Date: 16:36 2020/4/20
 */
public class StudentManagement extends JFrame implements ActionListener{

	//�����˵�������
	JMenuBar menubar = new JMenuBar();

	/**
	 * һ���˵�
	 */
	JMenu listInformationMenu = new JMenu("���");
	JMenu addInformationMenu = new JMenu("����");
	JMenu delInformationMenu = new JMenu("ɾ��");
	JMenu updateInformationMenu = new JMenu("�޸�");
	JMenu searchInformationMenu = new JMenu("����");
	JMenu otherMenu = new JMenu("�˳�");

	/**
	 * �����˵�
	 */
	JMenuItem listMenu = new JMenuItem("���ѧ����Ϣ");
	JMenuItem addMenu = new JMenuItem("����ѧ����Ϣ");
	JMenuItem deleteMenu = new JMenuItem("ɾ��ѧ����Ϣ");
	JMenuItem alterMenu = new JMenuItem("�޸�ѧ����Ϣ");
	JMenuItem searchInforMenu = new JMenuItem("��ѯѧ����Ϣ");
	JMenuItem quitMenu = new JMenuItem("�˳�");

	//�洢������ͼƬ
	JLabel label = new JLabel();

	public StudentManagement() {

		super();

		//����
		this.setTitle("����ʦ����ѧ��Ϣ��ѧ�뼼��ѧԺѧ����Ϣ����ϵͳ");
		//���ò��֣���Ƭ���֣�
		this.setLayout(new BorderLayout());
		//���˵��������ӵ�����
		this.setJMenuBar(menubar);
		//���ô��ڴ�С�ɱ�
		this.setResizable(true);

		//NO.15:�ο���Google Java��̷��ָ�ϡ�4.4 �����ƣ�80��100
//		JLabel bottom = new JLabel("ѧ����Ϣ����ϵͳV1.2  | By ������  | רҵ���������  | ���䣺liangll597@nenu.edu.cn  | Copyright 2020");
		JLabel bottom = new JLabel("ѧ����Ϣ����ϵͳV1.3  | By ������  | " +
				"רҵ���������  | ���䣺liangll597@nenu.edu.cn  | Copyright 2020");

		Font font = new Font("����", Font.PLAIN, 16);
		bottom.setFont(font);
		this.add(bottom, BorderLayout.SOUTH);

		Font font2 = new Font("����", Font.PLAIN, 14);
		listInformationMenu.setFont(font2);
		addInformationMenu.setFont(font2);
		delInformationMenu.setFont(font2);
		updateInformationMenu.setFont(font2);
		searchInformationMenu.setFont(font2);
		otherMenu.setFont(font2);

		/**
		 * һ���˵���ӵ��˵������¼�����
		 */
		menubar.add(listInformationMenu);
		menubar.add(addInformationMenu);
		menubar.add(delInformationMenu);
		menubar.add(updateInformationMenu);
		menubar.add(searchInformationMenu);
		menubar.add(otherMenu);
		listInformationMenu.addActionListener(this);
		addInformationMenu.addActionListener(this);
		delInformationMenu.addActionListener(this);
		updateInformationMenu.addActionListener(this);
		searchInformationMenu.addActionListener(this);
		otherMenu.addActionListener(this);

		/**
		 * �����˵���ӵ��˵������¼�����
		 */
		listInformationMenu.add(listMenu);
		addInformationMenu.add(addMenu);
		delInformationMenu.add(deleteMenu);
		updateInformationMenu.add(alterMenu);
		searchInformationMenu.add(searchInforMenu);
		otherMenu.add(quitMenu);
		listMenu.addActionListener(this);
		addMenu.addActionListener(this);
		deleteMenu.addActionListener(this);
		alterMenu.addActionListener(this);
		searchInforMenu.addActionListener(this);
		quitMenu.addActionListener(this);

		//��ӱ���
		label.setIcon(new ImageIcon("src/com/nenu/student/resources/timg.jpg"));

		//���������
		this.add(label);
		//��ʾ����Ļ
		this.setVisible(true);
		//���ô��ڵĴ�С
		this.setSize(850, 550);
		//���������ʾ
		this.setLocationRelativeTo(null);

		//���һ��Windows�¼���Ϣ���رմ��ڵ�ʱ���������˳�
		addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent e) {
				//�˳�
				System.exit(0);
			}
		});
	}

	/**
	 * �¼�����
	 * @param e
	 */
	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == listMenu) {
			new ListAllStudent();
		}

		if(e.getSource() == addMenu) {
			new AddStudent();
		}

		if(e.getSource() == deleteMenu) {
			new DelStudent();
		}

		if(e.getSource() == alterMenu) {
			new UpdateStudent();
		}

		if(e.getSource() == searchInforMenu) {
			new SelectStudent();
		}

		if(e.getSource() == quitMenu) {
			System.exit(0);
		}
	}
}