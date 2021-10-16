package com.nenu.student.database;

import java.sql.*;

/**
 * @Author: Liangll
 * @Description: 数据库连接类
 * @Date: 16:07 2020/4/20
 */
public class DBConnection {

	private static Connection con = null;
	private static String url = "jdbc:mysql://localhost:3306/db_sthomework01";
	private static String user = "root";
	private static String password = "mysql";

	public static Connection getCon() {
		//加载数据库驱动
		try {
			Class.forName("com.mysql.jdbc.Driver");
		} catch (ClassNotFoundException e) {
			System.out.println("加载数据库驱动失败！");
			e.printStackTrace();
		}
		//获取数据库连接
		try {
			con = DriverManager.getConnection(url, user, password);
			if(con != null) {
				System.out.println("数据库连接成功！");
			}
		} catch (SQLException e) {
			System.out.println("数据库连接失败！");
			e.printStackTrace();
		}
		//返回Connection对象
		return con;
	}
}
