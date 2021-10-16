package com.nenu.market.strategy;

/**
 * @Author: Liangll
 * @Description: 具体策略之员工折扣
 * @Date: 22:10 2020/5/18
 */
public class EmployeeDiscount implements Discount{

    @Override
    public double calculate(double price) {
        System.out.println("您是本商场员工，凭工作证购物可享受8折优惠！");
        return price * 0.8;
    }

}