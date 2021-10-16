package com.nenu.student.service;

import com.nenu.student.database.DatabaseConnection;
import com.nenu.student.entity.Student;

import javax.swing.*;
import java.awt.*;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

/**
 * @Author: Liangll
 * @Description: �������ѧ������
 * @Date: 12:08 2020/4/22
 */
public class ListAllStudent extends JFrame {

    private Object [][]rowData;
    private final Object []column = {"ѧ��", "����", "��������", "�Ա�"};

    //NO.1:�ο���Google Java��̷��ָ�ϡ�5.2 ��ʶ�����͵Ĺ��� - �ǳ����ֶ�����lowerCamelCase ����д
//    JTextField JTName = new JTextField(16);

    JTextField jtname = new JTextField(16);

    public ListAllStudent() {
        jtname.setText(null);
        setTable(" ");
    }

    /**
     * ���ñ�����ʽ
     * @param name
     */
    public void setTable(String name) {
        this.setVisible(false);

        JFrame jf = new JFrame("ѧ��ȫ����Ϣ");
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
        table.setPreferredScrollableViewportSize(new Dimension(550,400));

        //�ѱ��ŵ���������У��Զ���ӵ�������
        JScrollPane scrollPane = new JScrollPane(table);
        panel.add(scrollPane);
        jf.add(panel);
        jf.pack();
        jf.setContentPane(panel);
        jf.setVisible(true);
    }

    /**
     * ��ѯ�����û�ѧ��
     * @return ����ѧ���������ɵ�list����
     */
    public java.util.List<Student> queryAllUser(){
        Connection conn = null;
        PreparedStatement ps = null;
        ResultSet rs = null;
        String sql = "select * from t_student";
        java.util.List<Student> list = new ArrayList<Student>();

        try {
            conn = DatabaseConnection.getCon();
            ps = conn.prepareStatement(sql);
            rs = ps.executeQuery();

            while(rs.next()){
                Student student = new Student();
                student.setId(rs.getInt(1));
                student.setName(rs.getString(2));
                student.setBirDate(rs.getString(3));
                student.setGender(rs.getString(4));
                list.add(student);
            }

            conn.close();
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return list;
    }

    /**
     * ����ѧ������
     * @return ѧ�����ݶ�ά����
     */
    public Object[][] queryData(String name){
        if (" ".equals(name)) {
            List<Student> list = queryAllUser();
            if(list.size() >= 20){
                //NO.15:�ο���Google Java��̷��ָ�ϡ�4.4 �����ƣ�80��100
//                JOptionPane.showMessageDialog(null, "ѧ����Ϣ�ѳ���20����", "��ʾ��Ϣ", JOptionPane.WARNING_MESSAGE);
                JOptionPane.showMessageDialog(null, "ѧ����Ϣ�ѳ���20����",
                        "��ʾ��Ϣ", JOptionPane.WARNING_MESSAGE);
            }
            rowData = new Object[list.size()][column.length];
            for(int i = 0;i < list.size();i++){
                for(int j = 0;j < column.length;j++) {
                    rowData[i][0] = list.get(i).getId();
                    rowData[i][1] = list.get(i).getName();
                    rowData[i][2] = list.get(i).getBirDate();
                    rowData[i][3] = list.get(i).getGender();
                    System.out.print(rowData[i][j] + "    ");
                }
                System.out.println();
            }
        }
        return rowData;
    }
}