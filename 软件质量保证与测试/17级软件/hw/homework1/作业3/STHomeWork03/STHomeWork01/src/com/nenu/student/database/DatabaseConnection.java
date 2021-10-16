package com.nenu.student.database;

import java.sql.*;

/**
 * @Author: Liangll
 * @Description: 数据库连接类
 * @Date: 16:07 2020/4/20
 */
//NO.1:参考《Google Java编程风格指南》5.2 标识符类型的规则 - 类名都以UpperCamelCase 风格编写
//public class DBConnection {
public class DatabaseConnection {

	private static Connection con = null;

	//NO.1:参考《Google Java编程风格指南》5.2 标识符类型的规则 - 常量名命名模式为CONSTANT_CASE，全部字母大写
//	private static String url = "jdbc:mysql://localhost:3306/db_sthomework01";
//	private static String user = "root";
//	private static String password = "mysql";

	private static final String URL = "jdbc:mysql://localhost:3306/db_sthomework01";
	private static final String USER = "root";
	private static final String PASSWORD = "mysql";

	//NO.8:参考《Google Java编程风格指南》7.1.3 Javadoc标记
	/**
	 * 数据库驱动
	 * @return Connection对象
	 */
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
			con = DriverManager.getConnection(URL, USER, PASSWORD);
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
