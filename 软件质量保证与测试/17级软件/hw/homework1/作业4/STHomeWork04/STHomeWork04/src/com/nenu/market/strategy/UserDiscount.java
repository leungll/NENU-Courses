package com.nenu.market.strategy;

/**
 * @Author: Liangll
 * @Description: 具体策略之VIP用户折扣
 * @Date: 22:15 2020/5/18
 */
public class UserDiscount implements Discount{

    @Override
    public double calculate(double price) {
        System.out.println("您是本商场VIP用户，除享受6折优惠外，还可进行积分，积分累计到一定额度可换取奖品！");
        return price * 0.6;
    }

}
