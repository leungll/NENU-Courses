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
 * @Description: 输出所有学生数据
 * @Date: 12:08 2020/4/22
 */
public class ListAllStudent extends JFrame {

    private Object [][]rowData;
    private final Object []column = {"学号", "姓名", "出生日期", "性别"};

    //NO.1:参考《Google Java编程风格指南》5.2 标识符类型的规则 - 非常量字段名以lowerCamelCase 风格编写
//    JTextField JTName = new JTextField(16);

    JTextField jtname = new JTextField(16);

    public ListAllStudent() {
        jtname.setText(null);
        setTable(" ");
    }

    /**
     * 设置表格的样式
     * @param name
     */
    public void setTable(String name) {
        this.setVisible(false);

        JFrame jf = new JFrame("学生全部信息");
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
        table.setPreferredScrollableViewportSize(new Dimension(550,400));

        //把表格放到滚动面板中（自动添加到顶部）
        JScrollPane scrollPane = new JScrollPane(table);
        panel.add(scrollPane);
        jf.add(panel);
        jf.pack();
        jf.setContentPane(panel);
        jf.setVisible(true);
    }

    /**
     * 查询所有用户学生
     * @return 所有学生数据生成的list集合
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
     * 生成学生数据
     * @return 学生数据二维数组
     */
    public Object[][] queryData(String name){
        if (" ".equals(name)) {
            List<Student> list = queryAllUser();
            if(list.size() >= 20){
                //NO.15:参考《Google Java编程风格指南》4.4 列限制：80或100
//                JOptionPane.showMessageDialog(null, "学生信息已超过20条！", "提示信息", JOptionPane.WARNING_MESSAGE);
                JOptionPane.showMessageDialog(null, "学生信息已超过20条！",
                        "提示信息", JOptionPane.WARNING_MESSAGE);
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