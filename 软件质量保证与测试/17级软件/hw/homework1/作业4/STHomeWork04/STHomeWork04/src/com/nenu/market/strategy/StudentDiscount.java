package com.nenu.market.strategy;

/**
 * @Author: Liangll
 * @Description: 具体策略之学生折扣
 * @Date: 22:13 2020/5/18
 */
public class StudentDiscount implements Discount {

    @Override
    public double calculate(double price) {
        System.out.println("您是学生，凭学生证购物可享受每满100减免10元的优惠！");

        //返钱条件
        int priceCondition = 100;
        //返钱数
        int moneyReturn = 10;

        if(price >= moneyReturn){
            price = price - moneyReturn * Math.floor(price / priceCondition);
        }
        return price;
    }

}
