package com.nenu.student.database;

import java.sql.*;

/**
 * @Author: Liangll
 * @Description: ���ݿ�������
 * @Date: 16:07 2020/4/20
 */
public class DBConnection {

	private static Connection con = null;
	private static String url = "jdbc:mysql://localhost:3306/db_sthomework01";
	private static String user = "root";
	private static String password = "mysql";

	public static Connection getCon() {
		//�������ݿ�����
		try {
			Class.forName("com.mysql.jdbc.Driver");
		} catch (ClassNotFoundException e) {
			System.out.println("�������ݿ�����ʧ�ܣ�");
			e.printStackTrace();
		}
		//��ȡ���ݿ�����
		try {
			con = DriverManager.getConnection(url, user, password);
			if(con != null) {
				System.out.println("���ݿ����ӳɹ���");
			}
		} catch (SQLException e) {
			System.out.println("���ݿ�����ʧ�ܣ�");
			e.printStackTrace();
		}
		//����Connection����
		return con;
	}
}
