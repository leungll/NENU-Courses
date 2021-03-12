> 题目：编写一个学生信息登记系统，在新生入学时，用于录入学生的各种信息，如姓名、性别、班级、电话、手机、电子邮箱、通信地址、邮政编码等。在图形用户界面上，有菜单栏，也有工具栏及各种各样的控件。当学生的信息被录入后，需要保存在文件中。

```
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import javax.swing.*;
 
public class InfoDemo extends JFrame implements ActionListener{
    //菜单条组件
    JMenuBar jmb;
    //菜单
    JMenu menu1, menu2, menu3, menu4, menu5,menu6;
    //菜单项
    JMenuItem item1, item2, item3, item4, item5, item6,item7;
    //工具条
    JToolBar jtb;
    //工具条项
    JButton jb1, jb2, jb3, jb4, jb5;
    //文本框
    TextField tf1, tf2, tf3, tf4, tf5, tf6, tf7, tf8;
 
    public void go(){
        this.setTitle("学生信息登记系统");
        this.setBounds(600, 300, 600, 280);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        this.setLocationRelativeTo(null);
        //创建菜单  
        jmb = new JMenuBar();
        //不能设定位置，会自动放在最上部
        this.setJMenuBar(jmb);
        //添加菜单
        menu1 = new JMenu("文件");
        menu2 = new JMenu("编辑");
        menu3 = new JMenu("视图");
        menu4 = new JMenu("运行");
        menu5 = new JMenu("工具");
        menu6 = new JMenu("帮助");
        item1 = new JMenuItem("新建");
        item2 = new JMenuItem("打开");
        item3 = new JMenuItem("保存");
        item4 = new JMenuItem("另存为");
        item5 = new JMenuItem("页面设置");
        item6 = new JMenuItem("打印");
        item7 = new JMenuItem("退出");
        //添加菜单项至菜单上  
        menu1.add(item1);
        menu1.add(item2);
        menu1.add(item3);
        menu1.add(item4);
        menu1.add(item5);
        menu1.add(item6);
        //将菜单加入至菜单条  
        jmb.add(menu1);
        jmb.add(menu2);
        jmb.add(menu3);
        jmb.add(menu4);
        jmb.add(menu5);
        //创建工具条        
        jtb = new JToolBar();
        this.add(jtb, BorderLayout.NORTH);
        //添加工具条
        jb1 = new JButton("新建");
        jb2 = new JButton("打开");
        jb3 = new JButton("复制");
        jb4 = new JButton("剪切");
        jb5 = new JButton("打印");
        jtb.add(jb1);
        jtb.add(jb2);
        jtb.add(jb3);
        jtb.add(jb4);
        jtb.add(jb5);
        JPanel p = getCheckBoxPanel();
        this.add(p,BorderLayout.CENTER);
        JButton button = new JButton("保存");
        this.add(button,BorderLayout.SOUTH);
        button.addActionListener(this);
        this.setVisible(true);
    }
 
    public JPanel getCheckBoxPanel(){
        JPanel p = new JPanel();
        p.setLayout(new FlowLayout());
        p.add(new JLabel("姓        名"));
        tf1 = new TextField(26);
        p.add(tf1);
        p.add(new JLabel("性        别"));
        tf2 = new TextField(26);
        p.add(tf2);
        p.add(new JLabel("班        级"));
        tf3 = new TextField(26);
        p.add(tf3);
        p.add(new JLabel("电        话"));
        tf4 = new TextField(26);
        p.add(tf4);
        p.add(new JLabel("手        机"));
        tf5 = new TextField(26);
        p.add(tf5);
        p.add(new JLabel("电子邮箱"));
        tf6 = new TextField(26);
        p.add(tf6);
        p.add(new JLabel("通信地址"));
        tf7 = new TextField(26);
        p.add(tf7);
        p.add(new JLabel("邮政编码"));
        tf8 = new TextField(26);
        p.add(tf8);
        return p;
    }
 
    public static void main(String[] args) {
        InfoDemo demo = new InfoDemo();
        demo.go();
    }
 
    @Override
    public void actionPerformed(ActionEvent e) {
        try{
            PrintStream out = new PrintStream(new File("output.txt"));
            String str1 = tf1.getText();
            out.println("姓名:" + str1);
            String str2 = tf2.getText();
            out.println("性别:" + str2);
            String str3 = tf3.getText();
            out.println("班级:" + str3);
            String str4 = tf4.getText();
            out.println("电话:" + str4);
            String str5 = tf5.getText();
            out.println("手机:" + str5);
            String str6 = tf6.getText();
            out.println("电子邮箱:" + str6);
            String str7 = tf7.getText();
            out.println("通信地址:" + str7);
            String str8 = tf8.getText();
            out.println("邮政编码:" + str8);
        }catch(FileNotFoundException ex){
            System.out.println("无法打开文件");
        }
    }
} 
```