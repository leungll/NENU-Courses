# STHomeWork04
Strategy Mode of The Department Store Discount Dystem for Software Quality Assurance and Testing course, Spring 2020, NENU 

## 开发环境
- JAVA版本：1.8
- 开发工具：IntelliJ IDEA 2020.1
- 版本控制工具：Git 2.18.0

## 需求描述
某学校内商场要开发一套收银系统，在该系统中需要为不同类型的用户提供不同的购物打折方式，具体打折方案如下：

- 本商场员工凭工作证购物可享受 **`8折`** 优惠；
- 学生凭学生证购物可享受每满100 **`减免10元`** 的优惠；
- VIP用户除享受 **`6折`** 优惠（还可进行积分，积分累计到一定额度可换取奖品）。

该系统将来可能还要根据需要引入新的打折方式。

## 实现功能
- 应用设计模式中的 **策略 (Strategy) 模式** 实现核心结构
- 用 **OCP** 和 **DIP** 分析这个实例的设计和实现
- 绘制静态**类图**（模式基本结构图）
- 绘制**时序图**
- 实现**图形界面**
- 实现通过读取配置文件并利用**反射机制**生成对象

## 项目结构
```
│  README.md
│  STHomeWork04.iml
│                         
└─src
    └─com
        └─nenu
            └─market
                ├─client
                │      Client.java
                │      
                ├─context
                │      MarketAccounts.java
                │      
                ├─res
                │      config.xml
                │      
                ├─strategy
                │      Discount.java
                │      EmployeeDiscount.java
                │      StudentDiscount.java
                │      UserDiscount.java
                │      
                └─util
                        XmlUtil.java
```

## Strategy 模式分析
### 策略（Strategy）模式
- 定义：
    - 定义一系列算法类，将每一个算法封装起来，并让它们可以相互替换。策略模式让算法独立于使用它的客户而变化。它也被称为政策模式，是一种行为型模式。
- 角色：
    - Context（环境类）：环境类是使用算法的角色，它在解决某个问题（即实现某个方法）时可以采用多种策略。在环境类中维持一个对抽象策略类的引用实例，用于定义所采用的策略。
    - Strategy（抽象策略类）：它为所支持的算法声明了抽象方法，是所有策略类的父类，它可以是抽象类或具体类，也可以是接口。环境类通过抽象策略类中声明的方法在运行时调用具体策略类中实现的算法。
    - ConcreteStrategy（具体策略类）：它实现了在抽象策略类中声明的算法，在运行时，具体策略类将覆盖在环境类中定义的抽象策略类对象，使用一种具体的算法实现某个业务处理。

### 模式基本结构图

![class diagram](https://cdn.jsdelivr.net/gh/leungll/ImgHosting/img/类图.png)

### 具体分析
- 在本例中，`MarketAccounts` 充当**环境类**角色，`Discount` 充当**抽象**策略角色， `EmployeeDiscount`、 `StudentDiscount` 和 `UserDiscount` 充当**具体**策略角色。
- 将算法的定义放在专门的 `Discount` 策略类中，每一个具体策略类封装了一种实现算法，使用算法的 `MarketAccounts` 环境类针对抽象策略类进行编程，符合“**依赖倒转 (DIP) 原则**”。
- 用户可以在不修改原有系统的基础上选择具体算法或行为，也可灵活地增加新的算法或行为，符合“**开放-封闭原则 (OCP) 原则**”。
- 此外，为了提高系统的灵活性和可扩展性，将具体策略类的类名存储在配置文件 (路径： `src\com\nenu\market\res\config.xml`) 中，通过工具类 `XmlUtil` 来读取配置文件并反射生成对象。

## 时序图
![sequence diagram](https://cdn.jsdelivr.net/gh/leungll/ImgHosting/img/时序图.png)
