package com.nenu.student.service;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.sql.*;
import javax.swing.*;

import com.nenu.student.database.DBConnection;
import com.nenu.student.entity.Student;

/**
 * @Author: Liangll
 * @Description: 根据学生姓名查找信息
 * @Date: 17:08 2020/4/20
 */
public class SelectStudent extends JFrame implements ActionListener {

	private Object [][]rowData;
	private Object []column = {"学号", "姓名", "出生日期", "性别"};

	JPanel ePanel = new JPanel();
	JPanel wPanel = new JPanel();

	JLabel JLName = new JLabel("姓名");
	JTextField JTName = new JTextField(16);

	JButton searchBtn = new JButton("查询");
	JButton nextBtn = new JButton("重置");
	JButton cancelBtn = new JButton("取消");

	public SelectStudent() {
		this.setTitle("查询学生信息");
		this.setLayout(new BorderLayout());

		//输入框
		wPanel.add(JLName);
		wPanel.add(JTName);

		//按钮
		ePanel.add(searchBtn);
		ePanel.add(nextBtn);
		ePanel.add(cancelBtn);

		//添加监听事件
		searchBtn.addActionListener(this);
		nextBtn.addActionListener(this);
		cancelBtn.addActionListener(this);

		//布局
		this.add(ePanel, BorderLayout.SOUTH);
		this.add(wPanel, BorderLayout.NORTH);

		this.pack();
		//窗体居中显示
		this.setLocationRelativeTo(null);
		//窗口大小
		this.setSize(400, 150);
		this.setVisible(true);
	}

	/**
	 * 设置表格的样式
	 * @param name
	 */
	public void setTable(String name) {
		this.setVisible(false);
		JFrame jf = new JFrame("查询结果");
		jf.setLocationRelativeTo(null);
		JPanel panel = new JPanel();

		//表格所有行
		Object [][]rowData = queryData(name);
		JTable table = new JTable(rowData, column);

		/**
		 * 设置表格内容颜色
		 */
		//字体颜色
		table.setForeground(Color.BLACK);
		//字体样式
		table.setFont(new Font(null, Font.PLAIN, 14));
		//选中后字体背景
		table.setSelectionBackground(Color.DARK_GRAY);
		//选中后字体颜色
		table.setSelectionForeground(Color.LIGHT_GRAY);
		//网格颜色
		table.setGridColor(Color.GRAY);

		/**
		 * 设置查询结果表头
		 */
		//设置表头字体样式
		table.getTableHeader().setFont(new Font(null, Font.BOLD, 14));

		//表头名称字体颜色
		table.getTableHeader().setForeground(Color.BLACK);

		//不允许手动改变列宽
		table.getTableHeader().setResizingAllowed(false);

		//不允许拖动重新排列各列
		table.getTableHeader().setReorderingAllowed(false);

		//设置行高30
		table.setRowHeight(30);

		//列宽设置为100
		table.getColumnModel().getColumn(0).setPreferredWidth(80);
		table.getColumnModel().getColumn(3).setPreferredWidth(80);

		//设置滚动面板视口大小
		table.setPreferredScrollableViewportSize(new Dimension(550,200));

		//把表格放到滚动面板中（自动添加到顶部）
		JScrollPane scrollPane = new JScrollPane(table);
		panel.add(scrollPane);
		jf.add(panel);
		jf.pack();
		jf.setContentPane(panel);
		jf.setVisible(true);
	}

	/**
	 * 根据学生姓名查找
	 * @return 查找到的学生数据返回
	 */
	public Student queryUser(String name){
		Connection conn = null;
		//预编译语句
		PreparedStatement ps = null;
		//结果集
		ResultSet rs = null;
		Student student = new Student();
		String sql = "select * from t_student where name='" + name + "'";
		try {
			conn = DBConnection.getCon();
			//获取结果集
			ps = conn.prepareStatement(sql);
			rs = ps.executeQuery();
			if(rs.next()){
				student.setId(rs.getInt(1));
				student.setName(rs.getString(2));
				student.setBirDate(rs.getString(3));
				student.setGender(rs.getString(4));
			}else {
				JOptionPane.showMessageDialog(null, "该账号不存在！", "提示信息", JOptionPane.WARNING_MESSAGE);
			}
			conn.close();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return student;
	}

    /**
     * 生成学生数据
     * @return 学生数据二维数组
     */
    public Object[][] queryData(String name){
		if(name.equals(" ")) {
			JOptionPane.showMessageDialog(null, "输入为空，请重新输入！", "提示信息", JOptionPane.WARNING_MESSAGE);
        }else {
        	Student student = queryUser(name);
			//行设置为1,防止数组越界
			rowData = new Object[1][column.length];
			rowData[0][0] = student.getId();
			rowData[0][1] = student.getName();
			rowData[0][2] = student.getBirDate();
			rowData[0][3] = student.getGender();
		}
		return rowData;
    }

	@Override
	public void actionPerformed(ActionEvent e) {
		if(e.getSource() == searchBtn) {
			String name = JTName.getText();
			setTable(name);
		}
		if(e.getSource() == nextBtn) {
			JTName.setText(null);
		}
		if(e.getSource() == cancelBtn) {
			this.setVisible(false);
		}
	}
}
