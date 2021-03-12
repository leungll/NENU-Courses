SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `adminuser`
-- ----------------------------
DROP TABLE IF EXISTS `adminuser`;
CREATE TABLE `adminuser` (
  `uid` int(11) NOT NULL COMMENT '管理员id',
  `username` varchar(20) NOT NULL COMMENT '管理员用户名',
  `password` varchar(20) NOT NULL COMMENT '管理员登录密码',
  PRIMARY KEY (`uid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of adminuser
-- ----------------------------
INSERT INTO `adminuser` VALUES ('170001', 'admin', '123321');

-- ----------------------------
-- Table structure for `answerstate`
-- ----------------------------
DROP TABLE IF EXISTS `answerstate`;
CREATE TABLE `answerstate` (
  `anid` int(11) NOT NULL AUTO_INCREMENT COMMENT '答题情况表id',
  `qid` int(11) DEFAULT NULL COMMENT '试题id',
  `state` int(2) DEFAULT NULL COMMENT '答题情况1(对)2（错）3（没有做）',
  `tnid` int(11) DEFAULT NULL COMMENT '考试记录id',
  PRIMARY KEY (`anid`),
  KEY `FKd7jutiww9p5b57lou5pd8mwf8` (`qid`),
  KEY `FKs0if9cb8bpy9fl75bvckn4yhx` (`tnid`),
  CONSTRAINT `FKd7jutiww9p5b57lou5pd8mwf8` FOREIGN KEY (`qid`) REFERENCES `question` (`qid`),
  CONSTRAINT `FKs0if9cb8bpy9fl75bvckn4yhx` FOREIGN KEY (`tnid`) REFERENCES `testnote` (`tnid`)
) ENGINE=InnoDB AUTO_INCREMENT=259 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of answerstate
-- ----------------------------
INSERT INTO `answerstate` VALUES ('241', '17', '1', '111');
INSERT INTO `answerstate` VALUES ('242', '19', '1', '111');
INSERT INTO `answerstate` VALUES ('243', '23', '1', '111');
INSERT INTO `answerstate` VALUES ('244', '30', '1', '111');
INSERT INTO `answerstate` VALUES ('245', '33', '1', '111');
INSERT INTO `answerstate` VALUES ('246', '28', '1', '111');
INSERT INTO `answerstate` VALUES ('247', '17', '1', '112');
INSERT INTO `answerstate` VALUES ('248', '19', '1', '112');
INSERT INTO `answerstate` VALUES ('249', '23', '1', '112');
INSERT INTO `answerstate` VALUES ('250', '30', '1', '112');
INSERT INTO `answerstate` VALUES ('251', '33', '1', '112');
INSERT INTO `answerstate` VALUES ('252', '28', '1', '112');
INSERT INTO `answerstate` VALUES ('253', '17', '1', '113');
INSERT INTO `answerstate` VALUES ('254', '19', '1', '113');
INSERT INTO `answerstate` VALUES ('255', '23', '1', '113');
INSERT INTO `answerstate` VALUES ('256', '30', '1', '113');
INSERT INTO `answerstate` VALUES ('257', '33', '1', '113');
INSERT INTO `answerstate` VALUES ('258', '28', '1', '113');

-- ----------------------------
-- Table structure for `bj`
-- ----------------------------
DROP TABLE IF EXISTS `bj`;
CREATE TABLE `bj` (
  `bjid` int(11) NOT NULL AUTO_INCREMENT COMMENT '班级id',
  `bjname` varchar(50) NOT NULL COMMENT '班级名称',
  `tid` int(11) DEFAULT NULL COMMENT '教师id',
  PRIMARY KEY (`bjid`),
  KEY `FK6yinq5ty7u2qeadvxciby0lyb` (`tid`),
  CONSTRAINT `bj_ibfk_1` FOREIGN KEY (`tid`) REFERENCES `teacheruser` (`tid`) ON DELETE SET NULL ON UPDATE CASCADE,
  CONSTRAINT `FK6yinq5ty7u2qeadvxciby0lyb` FOREIGN KEY (`tid`) REFERENCES `teacheruser` (`tid`)
) ENGINE=InnoDB AUTO_INCREMENT=7 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of bj
-- ----------------------------
INSERT INTO `bj` VALUES ('1', '17软件工程1班', '1752501');
INSERT INTO `bj` VALUES ('2', '17软件工程2班', '1752501');
INSERT INTO `bj` VALUES ('5', '17计算机', '1752503');
INSERT INTO `bj` VALUES ('6', '17教育技术', '1752503');

-- ----------------------------
-- Table structure for `qprelationq`
-- ----------------------------
DROP TABLE IF EXISTS `qprelationq`;
CREATE TABLE `qprelationq` (
  `rid` int(11) NOT NULL AUTO_INCREMENT COMMENT '试卷与试题对应关系id',
  `num` int(11) DEFAULT NULL COMMENT '试题序号',
  `qpid` int(11) DEFAULT NULL COMMENT '试卷id',
  `qid` int(11) DEFAULT NULL COMMENT '试题id',
  PRIMARY KEY (`rid`),
  KEY `FKd51r19r2uqe1gn6v4jap2o7ci` (`qpid`),
  KEY `FKoypfe6ge2wu7fih09xuyeyrr9` (`qid`),
  CONSTRAINT `FKd51r19r2uqe1gn6v4jap2o7ci` FOREIGN KEY (`qpid`) REFERENCES `questionpaper` (`qpid`),
  CONSTRAINT `FKoypfe6ge2wu7fih09xuyeyrr9` FOREIGN KEY (`qid`) REFERENCES `question` (`qid`)
) ENGINE=InnoDB AUTO_INCREMENT=41 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of qprelationq
-- ----------------------------
INSERT INTO `qprelationq` VALUES ('18', '1', '53', '17');
INSERT INTO `qprelationq` VALUES ('19', '2', '53', '18');
INSERT INTO `qprelationq` VALUES ('20', '3', '53', '21');
INSERT INTO `qprelationq` VALUES ('21', '4', '53', '24');
INSERT INTO `qprelationq` VALUES ('22', '5', '53', '23');
INSERT INTO `qprelationq` VALUES ('23', '6', '53', '30');
INSERT INTO `qprelationq` VALUES ('24', '7', '53', '31');
INSERT INTO `qprelationq` VALUES ('25', '8', '53', '32');
INSERT INTO `qprelationq` VALUES ('26', '9', '53', '28');
INSERT INTO `qprelationq` VALUES ('27', '10', '53', '29');
INSERT INTO `qprelationq` VALUES ('28', '1', '54', '17');
INSERT INTO `qprelationq` VALUES ('29', '2', '54', '19');
INSERT INTO `qprelationq` VALUES ('30', '3', '54', '23');
INSERT INTO `qprelationq` VALUES ('31', '4', '54', '30');
INSERT INTO `qprelationq` VALUES ('32', '5', '54', '33');
INSERT INTO `qprelationq` VALUES ('33', '6', '54', '28');
INSERT INTO `qprelationq` VALUES ('34', '1', '56', '18');
INSERT INTO `qprelationq` VALUES ('35', '2', '56', '17');
INSERT INTO `qprelationq` VALUES ('36', '3', '56', '19');
INSERT INTO `qprelationq` VALUES ('37', '4', '56', '24');
INSERT INTO `qprelationq` VALUES ('38', '5', '56', '30');
INSERT INTO `qprelationq` VALUES ('39', '6', '56', '31');
INSERT INTO `qprelationq` VALUES ('40', '7', '56', '28');

-- ----------------------------
-- Table structure for `question`
-- ----------------------------
DROP TABLE IF EXISTS `question`;
CREATE TABLE `question` (
  `qid` int(11) NOT NULL AUTO_INCREMENT COMMENT '试题id',
  `qcontent` varchar(800) NOT NULL COMMENT '试题内容',
  `aoption` varchar(255) DEFAULT NULL COMMENT '选项a',
  `boption` varchar(255) DEFAULT NULL COMMENT '选项b',
  `coption` varchar(255) DEFAULT NULL COMMENT '选项c',
  `doption` varchar(255) DEFAULT NULL COMMENT '选项d',
  `qanswer` varchar(255) DEFAULT NULL COMMENT '试题答案',
  `qanalysis` varchar(800) DEFAULT NULL COMMENT '试题解析',
  `oword` varchar(50) DEFAULT NULL COMMENT '关键字1',
  `qscope` varchar(20) DEFAULT NULL COMMENT '试题范围',
  `qdifficulty` varchar(8) DEFAULT NULL COMMENT '试题难度',
  `qdate` datetime DEFAULT NULL COMMENT '添加日期',
  `qtid` int(11) DEFAULT NULL COMMENT '试题类型id',
  `tid` int(11) DEFAULT NULL COMMENT '教师编号id',
  PRIMARY KEY (`qid`),
  KEY `FKbaasjyxv0bvhkje9wfs7aikau` (`qtid`),
  KEY `FK8k438jxhyrfu1p2w8hajfeitg` (`tid`),
  CONSTRAINT `FK8k438jxhyrfu1p2w8hajfeitg` FOREIGN KEY (`tid`) REFERENCES `teacheruser` (`tid`),
  CONSTRAINT `FKbaasjyxv0bvhkje9wfs7aikau` FOREIGN KEY (`qtid`) REFERENCES `questiontype` (`qtid`),
  CONSTRAINT `question_ibfk_1` FOREIGN KEY (`qtid`) REFERENCES `questiontype` (`qtid`) ON DELETE SET NULL ON UPDATE CASCADE,
  CONSTRAINT `question_ibfk_2` FOREIGN KEY (`tid`) REFERENCES `teacheruser` (`tid`) ON DELETE SET NULL ON UPDATE CASCADE
) ENGINE=InnoDB AUTO_INCREMENT=34 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of question
-- ----------------------------
INSERT INTO `question` VALUES ('17', '()是构成C语言程序的基本单位。', '函数', '过程', '子程序', '子例程', '函数', '   							函数是构成C语言程序的基本单位\r\n   						', '单位', '第一单元', '简单', '2018-05-25 11:11:01', '1', '1752501');
INSERT INTO `question` VALUES ('18', 'C语言程序从（）开始执行。', '程序中第一条可执行语句', '程序中第一个函数', '程序中的main函数', '包含文件中的第一个函数', '程序中的main函数', '   							C语言程序从程序中的第一个main函数开始执行\r\n   						', '执行顺序', '第一单元', '简单', '2018-05-25 11:15:42', '1', '1752501');
INSERT INTO `question` VALUES ('19', '以下说法中正确的是（）', 'C语言程序总是从第一个定义的函数开始执行', '在C语言程序中，要调用的函数必须在main()函数中定义', 'C语言程序总是从main()函数开始执行', 'C语言程序中的main()函数必须放在程序的开始部分', 'C语言程序总是从main()函数开始执行', '   							C语言总是从main()函数开始执行。\r\n   						', '执行顺序', '第一单元', '简单', '2018-05-25 11:19:53', '1', '1752501');
INSERT INTO `question` VALUES ('20', '下列关于C语言的说法错误的是（）', 'C程序的工作过程是编辑、编译、连接、运行', 'C语言不区分大小写', 'C程序的三种基本结构是顺序、选择、循环', 'C程序从main函数开始执行', 'C语言不区分大小写', '   							C语言区分大小写\r\n   						', '大小写', '第一单元', '简单', '2018-05-25 11:23:00', '1', '1752501');
INSERT INTO `question` VALUES ('21', '下列正确的标识符是（）', '-a1', 'a[i]', 'a2_i', 'int t', 'a2_i', '   							（1）只能由字母、数字、下划线构成。（2）数字不能作为标识符的开头。（3）关键字不能作为标识符。\r\n   						', '标识符', '第一单元', '简单', '2018-05-25 11:26:02', '1', '1752501');
INSERT INTO `question` VALUES ('22', '下列C语言用户标识符中合法的是（）', '3ax', 'x', 'case', '-e2', 'x', '   							选项A中的标识符以数字开头不满足；选项C为关键字；选项D中的“-”开头\r\n   						', '标识符', '第一单元', '简单', '2018-05-25 11:28:38', '1', '1752501');
INSERT INTO `question` VALUES ('23', 'C语言中的简单数据类型包括（）', '整型、实型、逻辑型', '整型、实型、逻辑型、字符型', '整型、字符型、逻辑型', '整型、实型、字符型', '整型、实型、字符型', '   							C语言中的简单数据类型包括：整型、实型、字符型。\r\n   						', '数据类型', '第一单元', '简单', '2018-05-25 11:31:29', '1', '1752501');
INSERT INTO `question` VALUES ('24', '在C语言程序中，表达式5%2的结果是（）', '2.5', '2', '1', '3', '1', '   							%为求余运算符，该运算符只能对整型数据进行运算。且符号与被模数相同。5%2=1；\r\n   						', '余数', '第一单元', '简单', '2018-05-25 11:34:05', '1', '1752501');
INSERT INTO `question` VALUES ('25', '若有说明：int a[][3]={{1,2,3},{4,5},{6,7}}; 则数组a的第一维的大小为: ( )', '2', '3', '4', '无确定值', '3', '   							二维数组的一维大小，即指二维数组的行数，在本题中，按行对二维数组赋值，因此内层有几个大括号，数组就有几行\r\n   						', '数组', '第一单元', '中等', '2018-05-25 11:36:49', '1', '1752501');
INSERT INTO `question` VALUES ('26', 'C语言中函数返回值的类型是由（）决定的', '函数定义时指定的类型', 'return语句中的表达式类型', '调用该函数时的实参的数据类型', '形参的数据类型', '函数定义时指定的类型', '   							C语言中函数返回值的类型是由函数定义时指定的类型决定的\r\n   						', '返回类型', '第一单元', '中等', '2018-05-25 12:49:12', '1', '1752501');
INSERT INTO `question` VALUES ('27', '在C语言中，表示静态存储类别的关键字是', 'auto', 'register', 'static', 'extern', 'static', '   							static\r\n   						', '静态存储', '第一单元', '中等', '2018-05-25 12:50:40', '1', '1752501');
INSERT INTO `question` VALUES ('28', '#include <stdio.h>\r\nmain()\r\n{ int a=1,b=3,c=5;\r\nif (c==a+b)\r\n printf(\"yes\\n\");\r\nelse\r\n printf(\"no\\n\");\r\n}', '', '', '', '', 'no', '   							==表示判断符号两边的值是否相等；=表示将符号右边的值赋给左边的变量\r\n   						', '判断', '第一单元', '简单', '2018-05-25 12:54:53', '3', '1752501');
INSERT INTO `question` VALUES ('29', '#include <stdio.h>\r\nmain()\r\n{ int a=12, b= -34, c=56, min=0;\r\nmin=a;\r\n  if(min>b)  \r\nmin=b;\r\n  if(min>c)  \r\nmin=c;\r\nprintf(\"min=%d\", min);\r\n}', '', '', '', '', 'min=34', '   							选择结构\r\n   						', '选择结构', '第一单元', '中等', '2018-05-25 12:56:07', '3', '1752501');
INSERT INTO `question` VALUES ('30', '在函数调用时，实际参数和形式参数可以同名', '', '', '', '', '对', '   							在函数调用时，实际参数和形式参数可以同名\r\n   						', '形式参数和实际参数', '第一单元', '简单', '2018-05-25 13:06:28', '2', '1752501');
INSERT INTO `question` VALUES ('31', '函数间的数据传递不可以使用全局变量', '', '', '', '', '错', '   							函数间的数据传递可以使用全局变量\r\n   						', '数据传递', '第一单元', '简单', '2018-05-25 13:07:35', '2', '1752501');
INSERT INTO `question` VALUES ('32', '主调函数和被调函数总是在同一个文件里', '', '', '', '', '错', '   							主调函数和被调函数可以在同一个文件里\r\n   						', '函数位置', '第一单元', '简单', '2018-05-25 13:08:25', '2', '1752501');
INSERT INTO `question` VALUES ('33', 'struct是声明结构体类型时用的关键字', '', '', '', '', '对', '   							struct是声明结构体类型时用的关键字\r\n   						', '关键字', '第一单元', '中等', '2018-05-25 13:09:27', '2', '1752501');

-- ----------------------------
-- Table structure for `questionpaper`
-- ----------------------------
DROP TABLE IF EXISTS `questionpaper`;
CREATE TABLE `questionpaper` (
  `qpid` int(11) NOT NULL AUTO_INCREMENT COMMENT '试卷id',
  `qpdate` datetime NOT NULL COMMENT '出卷时间',
  `time` int(11) NOT NULL COMMENT '考试时长',
  `tid` int(11) DEFAULT NULL COMMENT '教师编号',
  PRIMARY KEY (`qpid`),
  KEY `FKtk78cxay18odowy9u2cgwyg1g` (`tid`),
  CONSTRAINT `FKtk78cxay18odowy9u2cgwyg1g` FOREIGN KEY (`tid`) REFERENCES `teacheruser` (`tid`)
) ENGINE=InnoDB AUTO_INCREMENT=57 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of questionpaper
-- ----------------------------
INSERT INTO `questionpaper` VALUES ('53', '2018-05-25 13:10:43', '2', '1752501');
INSERT INTO `questionpaper` VALUES ('54', '2018-05-25 13:14:20', '1', '1752501');
INSERT INTO `questionpaper` VALUES ('56', '2018-05-27 01:51:39', '120', null);

-- ----------------------------
-- Table structure for `questiontype`
-- ----------------------------
DROP TABLE IF EXISTS `questiontype`;
CREATE TABLE `questiontype` (
  `qtid` int(11) NOT NULL AUTO_INCREMENT COMMENT '试题类型id',
  `qtname` varchar(50) NOT NULL COMMENT '试题类型名称',
  `score` int(11) NOT NULL COMMENT '该题型分数',
  PRIMARY KEY (`qtid`)
) ENGINE=InnoDB AUTO_INCREMENT=4 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of questiontype
-- ----------------------------
INSERT INTO `questiontype` VALUES ('1', '选择题', '2');
INSERT INTO `questiontype` VALUES ('2', '判断题', '1');
INSERT INTO `questiontype` VALUES ('3', '读程序题', '2');

-- ----------------------------
-- Table structure for `student`
-- ----------------------------
DROP TABLE IF EXISTS `student`;
CREATE TABLE `student` (
  `sid` int(11) NOT NULL COMMENT '学号',
  `password` varchar(20) NOT NULL COMMENT '密码',
  `name` varchar(20) DEFAULT NULL COMMENT '学生姓名',
  `phone` varchar(20) DEFAULT NULL COMMENT '电话',
  `email` varchar(255) DEFAULT NULL COMMENT '邮箱',
  `bjid` int(11) DEFAULT NULL COMMENT '班级id',
  PRIMARY KEY (`sid`),
  KEY `FKg38hb6ioau31cosrf7uoesly1` (`bjid`),
  CONSTRAINT `FKg38hb6ioau31cosrf7uoesly1` FOREIGN KEY (`bjid`) REFERENCES `bj` (`bjid`),
  CONSTRAINT `student_ibfk_1` FOREIGN KEY (`bjid`) REFERENCES `bj` (`bjid`) ON DELETE SET NULL ON UPDATE CASCADE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of student
-- ----------------------------
INSERT INTO `student` VALUES ('1752601', '1752601', '赵伟', '18317526001', 'zh@163.com', '1');
INSERT INTO `student` VALUES ('1752602', '1752602', '乔羽', '18317526002', 'qy@163.com', '1');
INSERT INTO `student` VALUES ('1752603', '1752603', '孙涛', '18317526003', 'st@163.com', '1');
INSERT INTO `student` VALUES ('1752604', '1752604', '孙婷', '18317526004', 'stt@163.com', '1');
INSERT INTO `student` VALUES ('1752605', '1752605', '李阳', '18317526005', 'ly@163.com', '1');

-- ----------------------------
-- Table structure for `teacheruser`
-- ----------------------------
DROP TABLE IF EXISTS `teacheruser`;
CREATE TABLE `teacheruser` (
  `tid` int(11) NOT NULL COMMENT '教师编号id',
  `password` varchar(20) NOT NULL COMMENT '教师登录密码',
  `tname` varchar(20) DEFAULT NULL COMMENT '教师姓名',
  `phone` varchar(20) DEFAULT NULL COMMENT '电话',
  `email` varchar(255) DEFAULT NULL COMMENT '邮箱',
  PRIMARY KEY (`tid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of teacheruser
-- ----------------------------
INSERT INTO `teacheruser` VALUES ('1752501', '1752501', '李华', '18317525001', 'lh@163.com');
INSERT INTO `teacheruser` VALUES ('1752503', '1752503', '张磊', '18317525003', 'zl@163.com');

-- ----------------------------
-- Table structure for `testcontrol`
-- ----------------------------
DROP TABLE IF EXISTS `testcontrol`;
CREATE TABLE `testcontrol` (
  `tcid` int(11) NOT NULL AUTO_INCREMENT COMMENT '考场控制id',
  `state` int(2) DEFAULT NULL COMMENT '考场状态0(关闭考场)/1(开启考场)',
  `mode` int(2) DEFAULT NULL COMMENT '考试方式2(随机抽取试卷)/3(指定试卷)',
  `qpid` int(11) DEFAULT NULL COMMENT '试卷编号',
  `tname` varchar(50) DEFAULT NULL COMMENT '考试名称',
  `tdate` datetime DEFAULT NULL COMMENT '考试日期',
  PRIMARY KEY (`tcid`),
  KEY `FKl0o4w7svuyuv70ryda3jybth8` (`qpid`),
  CONSTRAINT `FKl0o4w7svuyuv70ryda3jybth8` FOREIGN KEY (`qpid`) REFERENCES `questionpaper` (`qpid`),
  CONSTRAINT `testcontrol_ibfk_1` FOREIGN KEY (`qpid`) REFERENCES `questionpaper` (`qpid`)
) ENGINE=InnoDB AUTO_INCREMENT=10 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of testcontrol
-- ----------------------------
INSERT INTO `testcontrol` VALUES ('6', '1', '2', null, '2018期末考试', '2018-05-25 13:16:16');

-- ----------------------------
-- Table structure for `testnote`
-- ----------------------------
DROP TABLE IF EXISTS `testnote`;
CREATE TABLE `testnote` (
  `tnid` int(11) NOT NULL AUTO_INCREMENT COMMENT '考试记录id',
  `sid` int(11) DEFAULT NULL COMMENT '学号',
  `qpid` int(11) DEFAULT NULL COMMENT '试卷编号',
  `tdate` datetime DEFAULT NULL COMMENT '考试日期',
  `tname` varchar(50) DEFAULT NULL COMMENT '考试名称',
  `stime` datetime DEFAULT NULL COMMENT '开始答题时间',
  `etime` datetime DEFAULT NULL COMMENT '交卷时间',
  `score` int(11) DEFAULT NULL COMMENT '分数',
  PRIMARY KEY (`tnid`),
  KEY `FK60hojljg7tpfi9oneceys96ok` (`sid`),
  KEY `FK2jvkm5uf544yj5u3wf2q8ga72` (`qpid`),
  CONSTRAINT `FK2jvkm5uf544yj5u3wf2q8ga72` FOREIGN KEY (`qpid`) REFERENCES `questionpaper` (`qpid`),
  CONSTRAINT `FK60hojljg7tpfi9oneceys96ok` FOREIGN KEY (`sid`) REFERENCES `student` (`sid`),
  CONSTRAINT `testnote_ibfk_1` FOREIGN KEY (`sid`) REFERENCES `student` (`sid`),
  CONSTRAINT `testnote_ibfk_2` FOREIGN KEY (`qpid`) REFERENCES `questionpaper` (`qpid`)
) ENGINE=InnoDB AUTO_INCREMENT=114 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of testnote
-- ----------------------------
INSERT INTO `testnote` VALUES ('111', '1752601', '54', '2018-05-25 13:16:16', '2018期末考试', '2018-05-26 20:22:10', '2018-05-26 20:22:33', '10');
INSERT INTO `testnote` VALUES ('112', '1752602', '54', '2018-05-25 13:16:16', '2018期末考试', '2018-05-26 21:57:10', '2018-05-26 21:57:31', '10');
INSERT INTO `testnote` VALUES ('113', '1752603', '54', '2018-05-25 13:16:16', '2018期末考试', '2018-05-27 21:33:57', '2018-05-27 21:34:20', '10');
