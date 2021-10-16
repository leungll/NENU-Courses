package com.nenu.student.database;

import java.sql.*;

/**
 * @Author: Liangll
 * @Description: ���ݿ�������
 * @Date: 16:07 2020/4/20
 */
//NO.1:�ο���Google Java��̷��ָ�ϡ�5.2 ��ʶ�����͵Ĺ��� - ��������UpperCamelCase ����д
//public class DBConnection {
public class DatabaseConnection {

	private static Connection con = null;

	//NO.1:�ο���Google Java��̷��ָ�ϡ�5.2 ��ʶ�����͵Ĺ��� - ����������ģʽΪCONSTANT_CASE��ȫ����ĸ��д
//	private static String url = "jdbc:mysql://localhost:3306/db_sthomework01";
//	private static String user = "root";
//	private static String password = "mysql";

	private static final String URL = "jdbc:mysql://localhost:3306/db_sthomework01";
	private static final String USER = "root";
	private static final String PASSWORD = "mysql";

	//NO.8:�ο���Google Java��̷��ָ�ϡ�7.1.3 Javadoc���
	/**
	 * ���ݿ�����
	 * @return Connection����
	 */
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
			con = DriverManager.getConnection(URL, USER, PASSWORD);
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
