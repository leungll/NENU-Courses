<!--
 * @Author: Lili Liang
 * @Date: 2021-03-12 12:12:18
 * @LastEditors: Lili Liang
 * @LastEditTime: 2024-03-31 22:19:54
 * @Description: Please set description
-->

# 东北师范大学信息科学与技术学院课程攻略 共享计划
Guidance for courses in School of Information Science and Technology, NENU

**Read this in other languages: [English](README.md), [简体中文](README_zh.md).**

![GitHub last commit](https://img.shields.io/github/last-commit/leungll/NENU-Courses?color=red&style=flat-square) 
![GitHub repo size](https://img.shields.io/github/repo-size/leungll/NENU-Courses?style=flat-square) 
![GitHub language count](https://img.shields.io/github/languages/count/leungll/NENU-Courses?color=9cf&style=flat-square) 
![GitHub contributors](https://img.shields.io/github/contributors/leungll/NENU-Courses?color=green&style=flat-square) 
![GitHub](https://img.shields.io/github/license/leungll/NENU-Courses?color=orange&style=flat-square)

![GitHub Repo stars](https://img.shields.io/github/stars/leungll/NENU-Courses?style=social) 
![GitHub forks](https://img.shields.io/github/forks/leungll/NENU-Courses?style=social) 
![GitHub watchers](https://img.shields.io/github/watchers/leungll/NENU-Courses?style=social)

## 介绍
> 受 [浙江大学课程攻略共享计划](https://github.com/QSCTech/zju-icicles)、[清华大学计算机系课程攻略](https://github.com/Salensoft/thu-cst-cracker) 的启发，创立了本项目。

## 前言
>正如浙大课程攻略中所说，来到一所大学，从第一次接触许多课，直到一门一门完成，这个过程中我们时常收集起许多资料和情报。
   
有些是需要在网上搜索的电子书，每次见到一门新课程，Google 一下教材名称，有的可以立即找到，有的却是要花费许多眼力；有些是历年试卷或者 A4 纸，前人精心收集制作，抱着能对他人有用的想法公开，却需要在各个群或者私下中摸索以至于从学长手中代代相传；有些是上完一门课才恍然领悟的技巧，原来这门课重点如此，当初本可以更轻松地完成得更好……

我也曾很努力地收集各种课程资料，但到最后，某些重要信息的得到却往往依然是纯属偶然。这种状态时常令我感到后怕与不安。我也曾在课程结束后终于有了些许方法与总结，但这些想法无处诉说，最终只能把花费时间与精力才换来的经验耗散在了漫漫的遗忘之中。

每每偶得学长学姐的资料，便如获珍宝，每每考试结束之后，自己的总结与心血便如同敝履一般被丢弃。

我们希望能够将这些隐晦的、不确定的、口口相传的资料和经验，变为公开的、易于获取的和大家能够共同完善、积累的共享资料。

我们希望只要是**前人走过的弯路，后人就不必再走**。大家的精力与时间应该浪费在那些值得你浪费的地方。

## 特性
- 本项目至今为止收录了以下内容：

    - 课程攻略：`README.md`
    - 教学课件和参考教材：`ebook/`
    - 平时作业与参考答案：`hw/`
    - 历年试卷和复习资料：`exam/`

- 文件的排布规则：
    ```
    ├─学科/      (e.g. Java语言与面向对象设计)
        ├─年级/  (e.g. 17级软件)
        │   ├─ebook/
        │   │      README.md
        │   ├─exam/
        │   │      README.md
        │   ├─hw/
        │   │      README.md
        │      
        └─README.md
    ```

## 平台
### 为什么采用 GitHub 项目作为平台？
- QQ / 微信群大多为年级和专业所分隔，无法长期共同保有，并且群文件也缺乏组织
- GitHub 项目可以使用目录进行文件组织，并且每个目录均可以在显示文件列表的同时显示一个 `README`，十分适合本项目的需求
- GitHub 带有便捷的 `Issue` 和 `Pull Request` 协作功能，并且可以方便地对贡献的质量进行监督和调整

### 上传什么资料？
- 选课攻略
- 电子版教材
- 平时作业答案
- 历年试卷
- 复习资料
- 优秀代码案例

### 警告
下列内容为不适合上传的内容。如果您认为缺少这些资料将会影响资源的完整性，请优先考虑放在校内资源平台，或联系您的教师并由教师发布。建议您撰写一个 `README` 文档并放置一些链接或指引文字来帮助找到这些资源。
- 盗版电子书/付费电子书
- 盗版/破解版/绿色版付费软件及其安装包
- 课程/教师主页上列出的内容（请在获得教师许可后上传）

如果您认为本仓库的一些文件侵犯了您的权益，请向我们发送邮件：l.liang0316@gmail.com，确认属实后将即刻予以删除。

## 相关说明
### 命名说明
- 请避免在文件中出现老师的具体名字，请用您 **所在年级** 指代，比如您是 17级软件 上 编译原理 的 `leungll`，请在 `编译原理/17级软件/` 中上传对应资料
- 如果可以，请在 `README.md` 文件中添加自己的想法（可选）
- 对于老师的评价可写在对应课程的 `README.md` 中，老师的名字请用 **拼音** 指代
- 如果想上传课件（请确保无版权问题），推荐使用 `pdf` 格式，避免系统差

### Watch、Star、Fork的说明
- `star` 的作用是收藏，方便您日后查找
- `watch` 的作用是关注，此仓库更新时，您会收到通知
- `fork` 的作用是参与，当您增加新的内容，然后 `Pull Request`，我们会考虑把您的修改与仓库原内容合并

## 使用指南
### 查找搜索文件
- 使用浏览器进入仓库首页之后，按下快捷键 `t`，进入 `文件搜索模式`，输入你想要寻找的文件名或者文件夹名，即可实时展示搜索结果 
- `火狐浏览器` 可使用扩展插件：[Octotree](https://addons.mozilla.org/zh-CN/firefox/addon/octotree/) 或者 [GiteeTree](https://addons.mozilla.org/zh-CN/firefox/addon/giteetree/) ，方便在网页上浏览项目的文件夹和文件

### 下载方式
- 下载某个文件夹：`复制该文件夹的网址`

    - 进入 [DownGit](https://minhaskamal.github.io/DownGit/#/home) 、[DownGit国内版](http://zhoudaxiaa.gitee.io/downgit/#/home) 、[GitZip](https://kinolien.github.io/gitzip/) 、[GitHub文件加速](https://shrill-pond-3e81.hunsh.workers.dev/) 任一工具中，`粘贴网址`，选择 `Download` 即可

    - Chromium 系浏览器与火狐浏览器可以选择安装 `GitZip` 插件：[Chrome](https://chrome.google.com/webstore/detail/gitzip-for-github/ffabmkklhbepgcgfonabamgnfafbdlkn) 下载、[火狐](https://addons.mozilla.org/en-US/firefox/addon/gitzip/) 下载

- 下载完整项目：

    - `zip` 下载：点击仓库上方绿色按钮 `↓Code` ，选择 `Download ZIP`

    - 命令行下载：`git clone https://github.com/leungll/NENU-Courses.git`

- 与此同时，我们也添加了 [Gitee](https://gitee.com/LL_Leung/NENU-Courses) 同步仓库，您可以在 [Gitee](https://gitee.com/LL_Leung/NENU-Courses) 中获取此项目的所有资源（此方法可以避免被墙）

### 贡献方法
> 本仓库未采用 `git-lfs`，请注意不要上传超过 `100M` 的单个文件，否则 `Commit` 无效

由于本项目体积很大，故可以采用在 Github Web 端直接上传的方式，具体操作如下：
- Fork 本项目：电脑浏览器中打开 [本项目](https://github.com/leungll/NENU-Courses) ，然后点击右上角的 `Fork按键` 即可

- 上传文件
    - 上传到 `已有文件夹` ：进入对应文件夹，点击仓库上方绿色按钮 `↓Code` 旁的 `Add file` 按钮，选择 `Upload files`，上传您的文件

    - 上传文件到 `新文件夹` ：进入文件夹，点击仓库上方绿色按钮 `↓Code` 旁的 `Add file` 按钮，选择 `Upload files` ，**把浏览器地址栏中文件夹名称改为你想要 `新建的文件夹名称`**，然后回车，上传您的文件

- 提交 PR ：`Fork` 本项目，然后在 `GitHub` 网页端点击 `Upload File` 上传文件，发起 `PR` 即可。请注意留意项目的文件组织。

- 也可直接附加在 `Issue` 中，由维护者进行添加

如果希望匿名贡献，可以 Email 至邮箱：l.liang0316@gmail.com，注明 "NENU-Courses" 即可。

## 开源力量
- Issue、PR、纠错、资料、选课/考试攻略，完全欢迎！
- 来自大家的关注、维护和贡献，才是让这个项目继续存在的动力
- 如果您有更好的建议，请在 Issues 中发表您的看法并加以讨论；如果您想直接联系我们，请向我们发送邮件：l.liang0316@gmail.com，您的建议是对我们的最好帮助！
- 感谢对本项目贡献的同学（排名按照 commit 先后顺序）：[leungll](https://github.com/leungll)（17级软件）、[Kongyy](https://github.com/2420795001)（17级软件）、[lyfer233](https://github.com/lyfer233)（19级计科）…… 以及在电脑前的您！

## 许可
由贡献者编写部分的许可：

[CC-BY-NC-SA：署名-非商业性使用-相同方式共享](https://creativecommons.org/licenses/by-nc-sa/4.0/deed.zh)

>资料仅供参考，请自行判断其适用性

其他部分的版权归属于其各自的作者

## 附录
### 东北师范大学学风建设实施细则
#### 第六章 规范与惩处（学生）
 >第二十六条 学生在科学研究、学术活动中，有下列情形的属于违反学术道德规范
 
（一）侵占、抄袭、剽窃、盗用他人的学术成果，包括未经发表的研究材料与方法、论文成果、技术报告、软件程序和研究数据等；

（二）引用他人的数据、资料、观点构成本人成果的主要部分或实质部分；引用他人研究成果不注明出处；

（三）由他人代写或代他人撰写学术、学位论文，或在撰写各类论文中有不正当交易；

（四）为得出某种符合自己主观愿望的结论而篡改他人研究成果、伪造实验数据或资料，隐瞒不利数据，伪造创新成果和新发现；

（五）重复发表研究成果；

（六）其他违反公认学术道德规范的行为。 

>第二十七条 有违反学术道德规范的学生，应对由此产生的影响和损失承担责任。学校视情节严重程度，对当事人分别给予组织处理或纪律处分，触犯法律者，移送司法机关依法追究法律责任。

## Reference
- [浙江大学课程攻略共享计划](https://github.com/QSCTech/zju-icicles)
- [清华大学计算机系课程攻略](https://github.com/Salensoft/thu-cst-cracker)
