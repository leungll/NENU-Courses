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
 * @Description: 学生管理类
 * @Date: 16:36 2020/4/20
 */
public class StudentManagement extends JFrame implements ActionListener{

	//创建菜单栏对象
	JMenuBar menubar = new JMenuBar();

	/**
	 * 一级菜单
	 */
	JMenu listInformationMenu = new JMenu("输出");
	JMenu addInformationMenu = new JMenu("插入");
	JMenu delInformationMenu = new JMenu("删除");
	JMenu updateInformationMenu = new JMenu("修改");
	JMenu searchInformationMenu = new JMenu("查找");
	JMenu otherMenu = new JMenu("退出");

	/**
	 * 二级菜单
	 */
	JMenuItem listMenu = new JMenuItem("输出学生信息");
	JMenuItem addMenu = new JMenuItem("增加学生信息");
	JMenuItem deleteMenu = new JMenuItem("删除学生信息");
	JMenuItem alterMenu = new JMenuItem("修改学生信息");
	JMenuItem searchInforMenu = new JMenuItem("查询学生信息");
	JMenuItem quitMenu = new JMenuItem("退出");

	//存储主界面图片
	JLabel label = new JLabel();

	public StudentManagement() {

		super();

		//标题
		this.setTitle("东北师范大学信息科学与技术学院学生信息管理系统");
		//设置布局（卡片布局）
		this.setLayout(new BorderLayout());
		//将菜单栏组件添加到容器
		this.setJMenuBar(menubar);
		//设置窗口大小可变
		this.setResizable(true);

		//NO.15:参考《Google Java编程风格指南》4.4 列限制：80或100
//		JLabel bottom = new JLabel("学生信息管理系统V1.2  | By 梁莉莉  | 专业：软件工程  | 邮箱：liangll597@nenu.edu.cn  | Copyright 2020");
		JLabel bottom = new JLabel("学生信息管理系统V1.3  | By 梁莉莉  | " +
				"专业：软件工程  | 邮箱：liangll597@nenu.edu.cn  | Copyright 2020");

		Font font = new Font("宋体", Font.PLAIN, 16);
		bottom.setFont(font);
		this.add(bottom, BorderLayout.SOUTH);

		Font font2 = new Font("宋体", Font.PLAIN, 14);
		listInformationMenu.setFont(font2);
		addInformationMenu.setFont(font2);
		delInformationMenu.setFont(font2);
		updateInformationMenu.setFont(font2);
		searchInformationMenu.setFont(font2);
		otherMenu.setFont(font2);

		/**
		 * 一级菜单添加到菜单栏及事件监听
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
		 * 二级菜单添加到菜单栏及事件监听
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

		//添加背景
		label.setIcon(new ImageIcon("src/com/nenu/student/resources/timg.jpg"));

		//添加至窗口
		this.add(label);
		//显示到屏幕
		this.setVisible(true);
		//设置窗口的大小
		this.setSize(850, 550);
		//窗体居中显示
		this.setLocationRelativeTo(null);

		//添加一个Windows事件消息，关闭窗口的时候正常的退出
		addWindowListener(new WindowAdapter() {
			@Override
			public void windowClosing(WindowEvent e) {
				//退出
				System.exit(0);
			}
		});
	}

	/**
	 * 事件监听
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