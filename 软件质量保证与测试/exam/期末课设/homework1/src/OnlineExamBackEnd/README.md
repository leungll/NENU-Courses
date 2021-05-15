# OnlineExamBackEnd
Back End of OnlineExamSystem for Software Quality Assurance and Testing course, Spring 2020, NENU

## 1 开发环境介绍
>远程服务器版本：Aliyun云服务器ECS、CentOS 7.3 64位

### 1.1 前端工具和环境
- 开发工具：Microsoft VS Code x64 1.44.2
- Node.js：V10.15.0
- Vue.js：V2.5.21
- 版本控制工具：Git

### 1.2 后端工具和环境
- 开发工具：IntelliJ IDEA 2020.1.1 x64
- Java版本：jdk1.8
- 本地服务器：Tomcat 9.0.6
- 数据库：MySQL 8.0
- 版本管理工具：Maven 3.5.4
- 版本控制工具：Git 2.18.0 x64

## 2 后端项目入口：
- 本地：`localhost:8080`（本地跑需导入数据库文件）
- 远程服务器：`120.26.186.88:8080`（前端Vue代码接口对接的是远程服务器端口）

## 3 关键技术
>框架组合：SpringBoot + Vue.js 前后端分离模式

### 3.1 前端
- Vue.js 框架
- Element-UI组件
- Axios 前后端分离

### 3.2 后端
- SpringBoot 框架
- SpringMVC 开发模式
- MyBatis 数据库操作工具
- MySQL 数据库
- Maven 版本控制
- FastJson 解析Json数据
- HTTP 请求头记录Session，判断用户属性
- Junit 单元测试
- 后台接口API: Swagger

