package com.nenu.market.strategy;

/**
 * @Author: Liangll
 * @Description: 折扣价格的抽象类
 * @Date: 22:06 2020/5/18
 */
public interface Discount {

    /**
     * 折扣价格的抽象方法
     * @param price 单件物品价格
     * @return
     */
    double calculate(double price);
}
