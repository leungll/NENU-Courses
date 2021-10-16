package com.nenu.market.context;

import com.nenu.market.strategy.Discount;

/**
 * @Author: Liangll
 * @Description: 环境类
 * @Date: 22:03 2020/5/18
 */
public class MarketAccounts {

    /**
     * 商品价格
     */
    private double price;

    /**
     * 维持一个对抽象折扣类的引用
     */
    private Discount discount;

    /**
     * 设置价格
     * @param price 商品价格
     */
    public void setPrice(double price) {
        this.price = price;
    }

    /**
     * 注入一个折扣类对象
     * @param discount 折扣类对象
     */
    public void setDiscount(Discount discount) {
        this.discount = discount;
    }

    /**
     * 调用折扣类
     * @return 折扣价计算方法
     */
    public double getPrice() {
        return discount.calculate(this.price);
    }
}
