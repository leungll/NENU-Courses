package com.nenu.market.client;

import com.nenu.market.context.MarketAccounts;
import com.nenu.market.strategy.Discount;
import com.nenu.market.util.XmlUtil;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 * @Author: Liangll
 * @Description: 客户类
 * @Date: 22:21 2020/5/18
 */
public class Client extends JFrame implements ActionListener {

    JLabel priceLabel = new JLabel("商品价格");
    JTextField priceField = new JTextField();

    JLabel numLabel = new JLabel("商品数量");
    JTextField numField = new JTextField();

    JLabel discountLabel = new JLabel("折扣方式");
    JTextField discountField = new JTextField();

    JLabel totalLabel = new JLabel("总计");
    JTextField totalField = new JTextField();

    JButton addBtn = new JButton("确定");
    JButton readBtn = new JButton("重置");
    JButton cancelBtn = new JButton("退出");

    public static void main(String[] args) {
        new Client();
    }

    public Client() {
        this.setTitle("欢迎来到商场收银系统！");
        this.setVisible(true);
        this.setSize(400, 380);
        //窗体居中显示
        this.setLocationRelativeTo(null);
        this.setLayout(null);

        Font font = new Font("宋体", Font.PLAIN, 16);

        //商品价格
        priceLabel.setBounds(70, 60, 70, 25);
        priceField.setBounds(150, 60, 120, 25);
        priceLabel.setFont(font);
        priceField.setFont(font);
        this.add(priceLabel);
        this.add(priceField);

        //商品数量
        numLabel.setBounds(70, 100, 70, 20);
        numField.setBounds(150, 100, 120, 25);
        numLabel.setFont(font);
        numField.setFont(font);
        this.add(numLabel);
        this.add(numField);

        //折扣方式
        discountLabel.setBounds(70, 140, 670, 20);
        discountField.setBounds(150, 140, 120, 25);
        discountLabel.setFont(font);
        discountField.setFont(font);
        this.add(discountLabel);
        this.add(discountField);

        //总计
        totalLabel.setBounds(70, 180, 670, 20);
        totalField.setBounds(150, 180, 120, 25);
        totalLabel.setFont(font);
        totalField.setFont(font);
        this.add(totalLabel);
        this.add(totalField);

        //确定、重置、取消
        addBtn.setBounds(90, 270, 60, 25);
        readBtn.setBounds(160, 270, 60, 25);
        cancelBtn.setBounds(230, 270, 60, 25);

        //添加监听
        addBtn.addActionListener(this);
        readBtn.addActionListener(this);
        cancelBtn.addActionListener(this);

        this.add(addBtn);
        this.add(readBtn);
        this.add(cancelBtn);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        //确定按钮
        if(e.getSource() == addBtn){
            double price = Double.parseDouble(priceField.getText());
            int num = Integer.parseInt(numField.getText());

            System.out.println("商品单价：" + price);
            System.out.println("商品数量：" + num);

            MarketAccounts mt = new MarketAccounts();

            double originalPrice = price * num;
            double currentPrice;

            mt.setPrice(originalPrice);
            System.out.println("商品原始总价为：" + originalPrice);
            System.out.println("----------------------------------------------");

            //读取配置文件并反射生成具体折扣对象
            Discount discount = (Discount) XmlUtil.getBean();
            //注入折扣对象
            mt.setDiscount(discount);

            String tempDiscountWay = discount.toString();
            String[] tempWay = tempDiscountWay.split("@");
            String[] tempWay2 = tempWay[0].split("\\.");

            if("EmployeeDiscount".equals(tempWay2[4])){
                discountField.setText("员工优惠");
            }else if(("StudentDiscount".equals(tempWay2[4]))){
                discountField.setText("学生优惠");
            }else if(("UserDiscount".equals(tempWay2[4]))){
                discountField.setText("VIP用户优惠");
            }

            currentPrice = mt.getPrice();
            totalField.setText(currentPrice + "元");
            System.out.println("商品折后价为：" + currentPrice);
        }

        //重置按钮
        if(e.getSource() == readBtn) {
            priceField.setText(null);
            numField.setText(null);
            discountField.setText(null);
            totalField.setText(null);
        }

        //退出按钮
        if(e.getSource() == cancelBtn) {
            setVisible(false);
        }
    }
}