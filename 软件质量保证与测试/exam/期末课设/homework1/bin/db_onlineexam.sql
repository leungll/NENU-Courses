/*
 Navicat Premium Data Transfer

 Source Server         : 120.26.186.88_3306
 Source Server Type    : MySQL
 Source Server Version : 80020
 Source Host           : 120.26.186.88:3306
 Source Schema         : db_onlineexam

 Target Server Type    : MySQL
 Target Server Version : 80020
 File Encoding         : 65001

 Date: 05/07/2020 08:51:10
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for t_answer
-- ----------------------------
DROP TABLE IF EXISTS `t_answer`;
CREATE TABLE `t_answer`  (
  `answerId` int(0) NOT NULL AUTO_INCREMENT COMMENT '答题情况Id（唯一）',
  `userId` int(0) DEFAULT NULL COMMENT '用户编号',
  `exerciseId` int(0) DEFAULT NULL COMMENT '试卷题目编号',
  `score` int(0) DEFAULT NULL COMMENT '分值',
  `checked` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL COMMENT '所选答案',
  PRIMARY KEY (`answerId`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 8 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Records of t_answer
-- ----------------------------
INSERT INTO `t_answer` VALUES (1, 1, 1, 1, '1');
INSERT INTO `t_answer` VALUES (2, 2, 2, 6, '0');
INSERT INTO `t_answer` VALUES (4, 2, 2, 6, '0');
INSERT INTO `t_answer` VALUES (5, 2, 2, 6, '0');
INSERT INTO `t_answer` VALUES (6, 2, 2, 6, '0');
INSERT INTO `t_answer` VALUES (7, 2, 2, 6, '0');

-- ----------------------------
-- Table structure for t_connect
-- ----------------------------
DROP TABLE IF EXISTS `t_connect`;
CREATE TABLE `t_connect`  (
  `id` int(0) NOT NULL AUTO_INCREMENT COMMENT '主键',
  `paperId` int(0) DEFAULT NULL COMMENT '试卷编号',
  `paperDetailId` int(11) UNSIGNED ZEROFILL DEFAULT 00000000000 COMMENT '试题编号',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 264 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of t_connect
-- ----------------------------
INSERT INTO `t_connect` VALUES (1, 4, 00000000001);
INSERT INTO `t_connect` VALUES (2, 4, 00000000002);
INSERT INTO `t_connect` VALUES (3, 4, 00000000003);
INSERT INTO `t_connect` VALUES (4, 4, 00000000004);
INSERT INTO `t_connect` VALUES (5, 4, 00000000005);
INSERT INTO `t_connect` VALUES (6, 4, 00000000006);
INSERT INTO `t_connect` VALUES (7, 4, 00000000007);
INSERT INTO `t_connect` VALUES (8, 4, 00000000008);
INSERT INTO `t_connect` VALUES (9, 1, 00000000009);
INSERT INTO `t_connect` VALUES (10, 1, 00000000010);
INSERT INTO `t_connect` VALUES (11, 1, 00000000011);
INSERT INTO `t_connect` VALUES (12, 1, 00000000012);
INSERT INTO `t_connect` VALUES (13, 1, 00000000013);
INSERT INTO `t_connect` VALUES (14, 2, 00000000014);
INSERT INTO `t_connect` VALUES (15, 2, 00000000015);
INSERT INTO `t_connect` VALUES (16, 2, 00000000016);
INSERT INTO `t_connect` VALUES (17, 2, 00000000017);
INSERT INTO `t_connect` VALUES (18, 2, 00000000018);
INSERT INTO `t_connect` VALUES (19, 3, 00000000019);
INSERT INTO `t_connect` VALUES (20, 3, 00000000020);
INSERT INTO `t_connect` VALUES (21, 3, 00000000021);
INSERT INTO `t_connect` VALUES (22, 3, 00000000022);
INSERT INTO `t_connect` VALUES (23, 3, 00000000023);
INSERT INTO `t_connect` VALUES (24, 6, 00000000024);
INSERT INTO `t_connect` VALUES (25, 6, 00000000025);
INSERT INTO `t_connect` VALUES (26, 6, 00000000026);
INSERT INTO `t_connect` VALUES (27, 6, 00000000027);
INSERT INTO `t_connect` VALUES (28, 6, 00000000028);
INSERT INTO `t_connect` VALUES (29, 6, 00000000029);
INSERT INTO `t_connect` VALUES (30, 6, 00000000030);
INSERT INTO `t_connect` VALUES (31, 6, 00000000031);
INSERT INTO `t_connect` VALUES (32, 5, 00000000032);
INSERT INTO `t_connect` VALUES (33, 5, 00000000033);
INSERT INTO `t_connect` VALUES (34, 5, 00000000034);
INSERT INTO `t_connect` VALUES (35, 5, 00000000035);
INSERT INTO `t_connect` VALUES (36, 5, 00000000036);
INSERT INTO `t_connect` VALUES (37, 5, 00000000037);
INSERT INTO `t_connect` VALUES (38, 5, 00000000038);
INSERT INTO `t_connect` VALUES (39, 5, 00000000039);
INSERT INTO `t_connect` VALUES (40, 5, 00000000040);
INSERT INTO `t_connect` VALUES (41, 5, 00000000041);
INSERT INTO `t_connect` VALUES (42, 5, 00000000042);
INSERT INTO `t_connect` VALUES (43, 5, 00000000043);
INSERT INTO `t_connect` VALUES (44, 5, 00000000044);
INSERT INTO `t_connect` VALUES (45, 5, 00000000045);
INSERT INTO `t_connect` VALUES (49, 5, 00000000046);
INSERT INTO `t_connect` VALUES (50, 62, 00000000000);
INSERT INTO `t_connect` VALUES (51, 63, 00000000000);
INSERT INTO `t_connect` VALUES (52, 64, 00000000000);
INSERT INTO `t_connect` VALUES (53, 65, 00000000000);
INSERT INTO `t_connect` VALUES (54, 65, 00000000067);
INSERT INTO `t_connect` VALUES (55, 66, 00000000000);
INSERT INTO `t_connect` VALUES (56, 67, 00000000000);
INSERT INTO `t_connect` VALUES (57, 67, 00000000068);
INSERT INTO `t_connect` VALUES (58, 68, 00000000000);
INSERT INTO `t_connect` VALUES (59, 69, 00000000000);
INSERT INTO `t_connect` VALUES (60, 70, 00000000000);
INSERT INTO `t_connect` VALUES (61, 71, 00000000000);
INSERT INTO `t_connect` VALUES (62, 72, 00000000000);
INSERT INTO `t_connect` VALUES (63, 73, 00000000000);
INSERT INTO `t_connect` VALUES (64, 73, 00000000069);
INSERT INTO `t_connect` VALUES (65, 74, 00000000000);
INSERT INTO `t_connect` VALUES (66, 74, 00000000070);
INSERT INTO `t_connect` VALUES (67, 75, 00000000000);
INSERT INTO `t_connect` VALUES (68, 75, 00000000071);
INSERT INTO `t_connect` VALUES (69, 75, 00000000072);
INSERT INTO `t_connect` VALUES (70, 75, 00000000073);
INSERT INTO `t_connect` VALUES (71, 76, 00000000000);
INSERT INTO `t_connect` VALUES (72, 76, 00000000074);
INSERT INTO `t_connect` VALUES (73, 77, 00000000000);
INSERT INTO `t_connect` VALUES (74, 77, 00000000075);
INSERT INTO `t_connect` VALUES (75, 77, 00000000076);
INSERT INTO `t_connect` VALUES (76, 78, 00000000000);
INSERT INTO `t_connect` VALUES (77, 78, 00000000077);
INSERT INTO `t_connect` VALUES (78, 78, 00000000078);
INSERT INTO `t_connect` VALUES (79, 78, 00000000079);
INSERT INTO `t_connect` VALUES (80, 78, 00000000080);
INSERT INTO `t_connect` VALUES (81, 79, 00000000000);
INSERT INTO `t_connect` VALUES (82, 79, 00000000081);
INSERT INTO `t_connect` VALUES (83, 79, 00000000082);
INSERT INTO `t_connect` VALUES (84, 79, 00000000083);
INSERT INTO `t_connect` VALUES (85, 80, 00000000000);
INSERT INTO `t_connect` VALUES (86, 80, 00000000084);
INSERT INTO `t_connect` VALUES (87, 80, 00000000085);
INSERT INTO `t_connect` VALUES (88, 81, 00000000000);
INSERT INTO `t_connect` VALUES (89, 81, 00000000086);
INSERT INTO `t_connect` VALUES (90, 81, 00000000087);
INSERT INTO `t_connect` VALUES (91, 82, 00000000000);
INSERT INTO `t_connect` VALUES (92, 83, 00000000000);
INSERT INTO `t_connect` VALUES (93, 83, 00000000091);
INSERT INTO `t_connect` VALUES (94, 83, 00000000092);
INSERT INTO `t_connect` VALUES (95, 83, 00000000093);
INSERT INTO `t_connect` VALUES (96, 84, 00000000000);
INSERT INTO `t_connect` VALUES (97, 84, 00000000094);
INSERT INTO `t_connect` VALUES (98, 100000, 00000000095);
INSERT INTO `t_connect` VALUES (99, 85, 00000000000);
INSERT INTO `t_connect` VALUES (100, 85, 00000000097);
INSERT INTO `t_connect` VALUES (101, 86, 00000000000);
INSERT INTO `t_connect` VALUES (102, 87, 00000000000);
INSERT INTO `t_connect` VALUES (103, 88, 00000000000);
INSERT INTO `t_connect` VALUES (104, 89, 00000000000);
INSERT INTO `t_connect` VALUES (105, 89, 00000000004);
INSERT INTO `t_connect` VALUES (106, 89, 00000000005);
INSERT INTO `t_connect` VALUES (107, 89, 00000000007);
INSERT INTO `t_connect` VALUES (108, 89, 00000000010);
INSERT INTO `t_connect` VALUES (109, 90, 00000000000);
INSERT INTO `t_connect` VALUES (110, 90, 00000000004);
INSERT INTO `t_connect` VALUES (111, 90, 00000000005);
INSERT INTO `t_connect` VALUES (112, 90, 00000000090);
INSERT INTO `t_connect` VALUES (113, 90, 00000000096);
INSERT INTO `t_connect` VALUES (114, 90, 00000000092);
INSERT INTO `t_connect` VALUES (115, 90, 00000000093);
INSERT INTO `t_connect` VALUES (116, 91, 00000000000);
INSERT INTO `t_connect` VALUES (117, 91, 00000000013);
INSERT INTO `t_connect` VALUES (118, 91, 00000000006);
INSERT INTO `t_connect` VALUES (119, 91, 00000000004);
INSERT INTO `t_connect` VALUES (120, 91, 00000000097);
INSERT INTO `t_connect` VALUES (121, 91, 00000000092);
INSERT INTO `t_connect` VALUES (122, 92, 00000000000);
INSERT INTO `t_connect` VALUES (123, 92, 00000000093);
INSERT INTO `t_connect` VALUES (124, 92, 00000000094);
INSERT INTO `t_connect` VALUES (125, 92, 00000000095);
INSERT INTO `t_connect` VALUES (126, 92, 00000000096);
INSERT INTO `t_connect` VALUES (127, 92, 00000000097);
INSERT INTO `t_connect` VALUES (128, 93, 00000000000);
INSERT INTO `t_connect` VALUES (129, 94, 00000000000);
INSERT INTO `t_connect` VALUES (130, -1, 00000000098);
INSERT INTO `t_connect` VALUES (131, 95, 00000000000);
INSERT INTO `t_connect` VALUES (132, 95, 00000000099);
INSERT INTO `t_connect` VALUES (133, 96, 00000000000);
INSERT INTO `t_connect` VALUES (134, 96, 00000000100);
INSERT INTO `t_connect` VALUES (135, 96, 00000000101);
INSERT INTO `t_connect` VALUES (136, 97, 00000000000);
INSERT INTO `t_connect` VALUES (137, 97, 00000000004);
INSERT INTO `t_connect` VALUES (138, 97, 00000000007);
INSERT INTO `t_connect` VALUES (139, 97, 00000000010);
INSERT INTO `t_connect` VALUES (140, 98, 00000000000);
INSERT INTO `t_connect` VALUES (141, 98, 00000000004);
INSERT INTO `t_connect` VALUES (142, 98, 00000000091);
INSERT INTO `t_connect` VALUES (143, 98, 00000000098);
INSERT INTO `t_connect` VALUES (144, 99, 00000000000);
INSERT INTO `t_connect` VALUES (145, 99, 00000000004);
INSERT INTO `t_connect` VALUES (146, 99, 00000000091);
INSERT INTO `t_connect` VALUES (147, 99, 00000000098);
INSERT INTO `t_connect` VALUES (148, 100, 00000000000);
INSERT INTO `t_connect` VALUES (149, 100, 00000000103);
INSERT INTO `t_connect` VALUES (150, 100, 00000000104);
INSERT INTO `t_connect` VALUES (151, 101, 00000000000);
INSERT INTO `t_connect` VALUES (152, 101, 00000000105);
INSERT INTO `t_connect` VALUES (153, 101, 00000000106);
INSERT INTO `t_connect` VALUES (154, 102, 00000000000);
INSERT INTO `t_connect` VALUES (155, 102, 00000000107);
INSERT INTO `t_connect` VALUES (156, 103, 00000000000);
INSERT INTO `t_connect` VALUES (157, 103, 00000000108);
INSERT INTO `t_connect` VALUES (158, 104, 00000000000);
INSERT INTO `t_connect` VALUES (159, 104, 00000000109);
INSERT INTO `t_connect` VALUES (160, 105, 00000000000);
INSERT INTO `t_connect` VALUES (161, 105, 00000000110);
INSERT INTO `t_connect` VALUES (162, 105, 00000000111);
INSERT INTO `t_connect` VALUES (163, 106, 00000000000);
INSERT INTO `t_connect` VALUES (164, 106, 00000000112);
INSERT INTO `t_connect` VALUES (165, 106, 00000000113);
INSERT INTO `t_connect` VALUES (166, 107, 00000000000);
INSERT INTO `t_connect` VALUES (167, 107, 00000000114);
INSERT INTO `t_connect` VALUES (168, 108, 00000000000);
INSERT INTO `t_connect` VALUES (169, 108, 00000000004);
INSERT INTO `t_connect` VALUES (170, 108, 00000000007);
INSERT INTO `t_connect` VALUES (171, 108, 00000000114);
INSERT INTO `t_connect` VALUES (172, 108, 00000000097);
INSERT INTO `t_connect` VALUES (173, 108, 00000000094);
INSERT INTO `t_connect` VALUES (174, 109, 00000000000);
INSERT INTO `t_connect` VALUES (175, 109, 00000000115);
INSERT INTO `t_connect` VALUES (176, 110, 00000000000);
INSERT INTO `t_connect` VALUES (177, 110, 00000000116);
INSERT INTO `t_connect` VALUES (178, 111, 00000000000);
INSERT INTO `t_connect` VALUES (179, 111, 00000000117);
INSERT INTO `t_connect` VALUES (180, 112, 00000000000);
INSERT INTO `t_connect` VALUES (181, 112, 00000000118);
INSERT INTO `t_connect` VALUES (182, -1, 00000000119);
INSERT INTO `t_connect` VALUES (183, 113, 00000000000);
INSERT INTO `t_connect` VALUES (184, 113, 00000000120);
INSERT INTO `t_connect` VALUES (185, 114, 00000000000);
INSERT INTO `t_connect` VALUES (186, 114, 00000000121);
INSERT INTO `t_connect` VALUES (187, 115, 00000000000);
INSERT INTO `t_connect` VALUES (188, 115, 00000000122);
INSERT INTO `t_connect` VALUES (189, 116, 00000000000);
INSERT INTO `t_connect` VALUES (190, 116, 00000000123);
INSERT INTO `t_connect` VALUES (191, 117, 00000000000);
INSERT INTO `t_connect` VALUES (192, 117, 00000000126);
INSERT INTO `t_connect` VALUES (193, 117, 00000000127);
INSERT INTO `t_connect` VALUES (194, 118, 00000000000);
INSERT INTO `t_connect` VALUES (195, 118, 00000000128);
INSERT INTO `t_connect` VALUES (196, 118, 00000000129);
INSERT INTO `t_connect` VALUES (197, 118, 00000000130);
INSERT INTO `t_connect` VALUES (198, 118, 00000000131);
INSERT INTO `t_connect` VALUES (199, 119, 00000000000);
INSERT INTO `t_connect` VALUES (200, 119, 00000000004);
INSERT INTO `t_connect` VALUES (201, 119, 00000000006);
INSERT INTO `t_connect` VALUES (202, 119, 00000000094);
INSERT INTO `t_connect` VALUES (203, 119, 00000000131);
INSERT INTO `t_connect` VALUES (204, 119, 00000000129);
INSERT INTO `t_connect` VALUES (205, 120, 00000000000);
INSERT INTO `t_connect` VALUES (206, 121, 00000000000);
INSERT INTO `t_connect` VALUES (207, 122, 00000000000);
INSERT INTO `t_connect` VALUES (208, 122, 00000000006);
INSERT INTO `t_connect` VALUES (209, 122, 00000000094);
INSERT INTO `t_connect` VALUES (210, 122, 00000000145);
INSERT INTO `t_connect` VALUES (211, 123, 00000000000);
INSERT INTO `t_connect` VALUES (212, 123, 00000000149);
INSERT INTO `t_connect` VALUES (213, 123, 00000000150);
INSERT INTO `t_connect` VALUES (214, 123, 00000000151);
INSERT INTO `t_connect` VALUES (215, 123, 00000000152);
INSERT INTO `t_connect` VALUES (216, 124, 00000000000);
INSERT INTO `t_connect` VALUES (217, 124, 00000000155);
INSERT INTO `t_connect` VALUES (218, 124, 00000000156);
INSERT INTO `t_connect` VALUES (219, 124, 00000000157);
INSERT INTO `t_connect` VALUES (220, 124, 00000000158);
INSERT INTO `t_connect` VALUES (221, 125, 00000000000);
INSERT INTO `t_connect` VALUES (222, 125, 00000000160);
INSERT INTO `t_connect` VALUES (223, 127, 00000000000);
INSERT INTO `t_connect` VALUES (224, 129, 00000000000);
INSERT INTO `t_connect` VALUES (225, 130, 00000000000);
INSERT INTO `t_connect` VALUES (226, 131, 00000000000);
INSERT INTO `t_connect` VALUES (227, 131, 00000000004);
INSERT INTO `t_connect` VALUES (228, 131, 00000000006);
INSERT INTO `t_connect` VALUES (229, 131, 00000000091);
INSERT INTO `t_connect` VALUES (232, NULL, 00000000000);
INSERT INTO `t_connect` VALUES (233, NULL, 00000000000);
INSERT INTO `t_connect` VALUES (234, 135, 00000000000);
INSERT INTO `t_connect` VALUES (235, 135, 00000000181);
INSERT INTO `t_connect` VALUES (236, 136, 00000000000);
INSERT INTO `t_connect` VALUES (237, 136, 00000000183);
INSERT INTO `t_connect` VALUES (238, 137, 00000000000);
INSERT INTO `t_connect` VALUES (239, 138, 00000000000);
INSERT INTO `t_connect` VALUES (240, 138, 00000000001);
INSERT INTO `t_connect` VALUES (241, 138, 00000000003);
INSERT INTO `t_connect` VALUES (242, 138, 00000000006);
INSERT INTO `t_connect` VALUES (243, 138, 00000000008);
INSERT INTO `t_connect` VALUES (244, 139, 00000000000);
INSERT INTO `t_connect` VALUES (245, 139, 00000000006);
INSERT INTO `t_connect` VALUES (246, 139, 00000000001);
INSERT INTO `t_connect` VALUES (247, 139, 00000000002);
INSERT INTO `t_connect` VALUES (248, 139, 00000000008);
INSERT INTO `t_connect` VALUES (249, 140, 00000000000);
INSERT INTO `t_connect` VALUES (250, 140, 00000000198);
INSERT INTO `t_connect` VALUES (251, 140, 00000000199);
INSERT INTO `t_connect` VALUES (252, 140, 00000000200);
INSERT INTO `t_connect` VALUES (253, 140, 00000000201);
INSERT INTO `t_connect` VALUES (254, 141, 00000000000);
INSERT INTO `t_connect` VALUES (255, 141, 00000000010);
INSERT INTO `t_connect` VALUES (256, 141, 00000000008);
INSERT INTO `t_connect` VALUES (257, 141, 00000000003);
INSERT INTO `t_connect` VALUES (258, 141, 00000000005);
INSERT INTO `t_connect` VALUES (259, 142, 00000000000);
INSERT INTO `t_connect` VALUES (260, 142, 00000000204);
INSERT INTO `t_connect` VALUES (261, 142, 00000000205);
INSERT INTO `t_connect` VALUES (262, 142, 00000000206);
INSERT INTO `t_connect` VALUES (263, 142, 00000000207);
INSERT INTO `t_connect` VALUES (264, 143, 00000000000);
INSERT INTO `t_connect` VALUES (265, 144, 00000000000);
INSERT INTO `t_connect` VALUES (266, 145, 00000000000);
INSERT INTO `t_connect` VALUES (267, 146, 00000000000);
INSERT INTO `t_connect` VALUES (268, 147, 00000000000);
INSERT INTO `t_connect` VALUES (269, 148, 00000000000);

-- ----------------------------
-- Table structure for t_notice
-- ----------------------------
DROP TABLE IF EXISTS `t_notice`;
CREATE TABLE `t_notice`  (
  `noticeId` int(0) NOT NULL AUTO_INCREMENT COMMENT '公告Id（唯一）',
  `userId` int(0) DEFAULT NULL COMMENT '用户编号',
  `title` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL COMMENT '标题',
  `content` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL COMMENT '内容',
  `createTime` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL COMMENT '发布时间',
  PRIMARY KEY (`noticeId`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 58 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Records of t_notice
-- ----------------------------
INSERT INTO `t_notice` VALUES (32, 1, '期末考试通知', '期末考试在即，请同学们认真复习！', 'Thu Jul 02 06:43:37 CST 2020');
INSERT INTO `t_notice` VALUES (54, 2, '小测试', '软件测试与实践小测试已发放，请同学们在规定的时间之内做完！', 'Thu Jul 02 15:43:46 CST 2020');
INSERT INTO `t_notice` VALUES (55, 1, '考试诚信', '请同学们认真考试！诚信考试！', 'Thu Jul 02 15:46:11 CST 2020');
INSERT INTO `t_notice` VALUES (56, 2, '功能测试教师发公告', '你好', 'Thu Jul 02 21:45:17 CST 2020');
INSERT INTO `t_notice` VALUES (57, 1, '新增管理员端公告测试', '你不好', 'Thu Jul 02 21:57:03 CST 2020');

-- ----------------------------
-- Table structure for t_paper
-- ----------------------------
DROP TABLE IF EXISTS `t_paper`;
CREATE TABLE `t_paper`  (
  `paperId` int(0) NOT NULL AUTO_INCREMENT COMMENT '试卷编号Id（唯一）',
  `paperName` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL COMMENT '试卷名称',
  `status` int(0) DEFAULT 0 COMMENT '是否发布(0：未发布，1：已发布)',
  `beginTime` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL COMMENT '发布时间',
  `endTime` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL COMMENT '结束时间',
  `duration` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL COMMENT '做题时长',
  PRIMARY KEY (`paperId`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 143 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Records of t_paper
-- ----------------------------
INSERT INTO `t_paper` VALUES (1, '软件质量保证与测试小练习1', 1, '开始:2020年06月08日15时00分00秒', '结束:2020年07月05日14时42分1秒', '10');
INSERT INTO `t_paper` VALUES (2, '软件质量保证与测试小练习2', 1, '开始:2020年06月08日15时00分00秒', '结束:2020年07月05日23时59分59秒', '10');
INSERT INTO `t_paper` VALUES (3, '软件质量保证与测试小练习3', 1, '开始:2020年06月08日15时00分00秒', '结束:2020年07月05日23时59分59秒', '10');
INSERT INTO `t_paper` VALUES (4, '2020年春季学期软件质量保证与测试期末考试卷A', 1, '开始:2020年07月03日00时00分00秒', '结束:2020年07月05日23时59分59秒', '120');
INSERT INTO `t_paper` VALUES (5, '2020年春季学期软件质量保证与测试期末考试卷B', 1, '开始:2020年07月02日00时00分00秒', '结束:2020年07月08日23时59分59秒', '120');
INSERT INTO `t_paper` VALUES (6, '2020年春季学期编译原理期末考试', 1, '开始:2020年07月05日00时00分00秒', '结束:2020年07月08日23时59分59秒', '120');

-- ----------------------------
-- Table structure for t_paperdetail
-- ----------------------------
DROP TABLE IF EXISTS `t_paperdetail`;
CREATE TABLE `t_paperdetail`  (
  `paperDetailId` int(0) NOT NULL AUTO_INCREMENT COMMENT '试卷详细表Id（唯一）',
  `paperId` int(0) DEFAULT 0 COMMENT '试卷编号Id',
  `exerciseId` int(0) DEFAULT 0 COMMENT '题目编号',
  `content` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL COMMENT '题目内容',
  `typeA` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT '' COMMENT '选项A',
  `typeB` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT '' COMMENT '选项B',
  `typeC` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT '' COMMENT '选项C',
  `typeD` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT '' COMMENT '选项D',
  `answer` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT '' COMMENT '正确答案或关键字1',
  `answer2` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT '' COMMENT '关键字2',
  `answer3` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT '' COMMENT '关键字3',
  `exerciseType` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL COMMENT '题目类型',
  `score` int(0) DEFAULT NULL COMMENT '分值',
  PRIMARY KEY (`paperDetailId`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 208 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Records of t_paperdetail
-- ----------------------------
INSERT INTO `t_paperdetail` VALUES (1, 4, 1, '软件测试的目的是( )。', '试验性运行软件', '发现软件错误', '证明软件正确', '找出软件中全部错误', 'B', '', '', '选择题', 5);
INSERT INTO `t_paperdetail` VALUES (2, 4, 2, '黑盒法是根据程序的( )来设计测试用例的。', '应用范围', '内部逻辑', '功能', '输入数据', 'C', '', '', '选择题', 5);
INSERT INTO `t_paperdetail` VALUES (3, 4, 3, '与设计测试用例无关的文档是( )。', '项目开发计划', '需求规格说明书', '设计说明书', '源程序', 'A', '', '', '选择题', 5);
INSERT INTO `t_paperdetail` VALUES (4, 4, 4, '用黑盒技术设计测试用例的方法之一为( )。', '因果图', '逻辑覆盖', '循环覆盖', '基本路径测试', 'A', '', '', '选择题', 5);
INSERT INTO `t_paperdetail` VALUES (5, 4, 5, '按照软件测试用例的设计方法而论，软件测试可以分为白盒测试法和______。', '', '', '', '', '黑盒测试法', '', '', '填空题', 20);
INSERT INTO `t_paperdetail` VALUES (6, 4, 6, '集成测试指在_______测试基础上，将所有模块按照设计要求组装成一个完整的系统进行的测试。', '', '', '', '', '单元', '', '', '填空题', 20);
INSERT INTO `t_paperdetail` VALUES (7, 4, 7, '要覆盖含循环结构的所有路径是不可能的，一般通过限制_______来测试。', '', '', '', '', '循环次数', '', '', '填空题', 20);
INSERT INTO `t_paperdetail` VALUES (8, 4, 8, '请解释什么是性能测试。', '', '', '', '', '需求规格说明书', '性能相关', '性能需求', '简答题', 20);
INSERT INTO `t_paperdetail` VALUES (9, 1, 9, '单元测试时，调用被测模块的是( )。', '桩模块', '通信模块', '驱动模块', '代理模块', 'C', '', '', '选择题', 20);
INSERT INTO `t_paperdetail` VALUES (10, 1, 10, '根据软件需求规格说明，在开发环境下对已集成的软件系统进行的测试是( )。', '系统测试', '单元测试', '集成测试', '验收测试', 'A', '', '', '选择题', 20);
INSERT INTO `t_paperdetail` VALUES (11, 1, 11, '下列接口测试中，要延续到系统测试阶段来完成的是( )。', '系统外部接口', '系统内部接口', '函数或方法接口', '类接口', 'A', '', '', '选择题', 20);
INSERT INTO `t_paperdetail` VALUES (12, 1, 12, '大多数实际情况下，性能测试的实现方法是( )。', '黑盒测试', '白盒测试', '静态分析', '可靠性测试', 'A', '', '', '选择题', 20);
INSERT INTO `t_paperdetail` VALUES (13, 1, 13, '对程序的测试最好由( )来做，对程序的调试最好由谁来做( )。', '程序员，第三方测试机构', '第三方测试机构，程序员', '程序开发组，程序员', '程序开发组，程序开发组', 'B', '', '', '选择题', 20);
INSERT INTO `t_paperdetail` VALUES (14, 2, 14, '软件设计阶段的测试主要采取的方式是( )。', '评审', '白盒测试', '黑盒测试', '动态测试', 'A', '', '', '选择题', 20);
INSERT INTO `t_paperdetail` VALUES (15, 2, 15, '集成测试对系统内部的交互以及集成后系统功能检验了何种质量特性( )。', '正确性', '可靠性', '可使用性', '可维护性', 'A', '', '', '选择题', 20);
INSERT INTO `t_paperdetail` VALUES (16, 2, 16, '软件生存周期过程中，修改错误代价最大的阶段是( )。', '需求阶段', '设计阶段', '编程阶段', '发布运行阶段', 'D', '', '', '选择题', 20);
INSERT INTO `t_paperdetail` VALUES (17, 2, 17, '在边界值分析中，下列数据通常不用来做数据测试的是( )。', '正好等于边界的值', '等价类中的等价值', '刚刚大于边界的值', '刚刚小于边界的值', 'B', '', '', '选择题', 20);
INSERT INTO `t_paperdetail` VALUES (18, 2, 18, '单元测试中设计测试用例的依据是( )。', '概要设计规格说明书', '用户需求规格说明书', '项目计划说明书', '详细设计规格说明书', 'D', '', '', '选择题', 20);
INSERT INTO `t_paperdetail` VALUES (19, 3, 19, '通常可分为白盒测试和黑盒测试。白盒测试是根据程序的( )来设计测试用例。', '功能', '性能', '内部逻辑', '内部数据', 'C', '', '', '选择题', 20);
INSERT INTO `t_paperdetail` VALUES (20, 3, 20, '如果一个判定中的复合条件表达式为（A > 1）or（B <= 3），则为了达到100%的条件覆盖率，至少需要设计多少个测试用例( )。', '1', '2', '3', '4', 'B', '', '', '选择题', 20);
INSERT INTO `t_paperdetail` VALUES (21, 3, 21, '经验表明，在程序测试中，某模块与其他模块相比，若该模块已发现并改正的错误较多，则该模块中残存的错误数目与其他模块相比，通常应该( )。', '较少', '较多', '相似', '不确定', 'B', '', '', '选择题', 20);
INSERT INTO `t_paperdetail` VALUES (22, 3, 22, '不属于白盒测试的技术是( )。', '路径覆盖', '判定覆盖', '循环覆盖', '边界值分析', 'D', '', '', '选择题', 20);
INSERT INTO `t_paperdetail` VALUES (23, 3, 23, '测试的关键问题是( )。', '如何组织软件评审', '如何选择测试用例', '如何验证程序的正确性', '如何采用综合策略', 'B', '', '', '选择题', 20);
INSERT INTO `t_paperdetail` VALUES (24, 6, 24, '构造编译程序应掌握( )。', '源程序', '编译方法', '目标语言', '以上三项', 'D', '', '', '选择题', 5);
INSERT INTO `t_paperdetail` VALUES (25, 6, 25, '编译程序绝大多数时间花在( )上。', '出错处理', '目标代码生成', '词法分析', '表格管理', 'D', '', '', '选择题', 5);
INSERT INTO `t_paperdetail` VALUES (26, 6, 26, '编译程序是对( )。', '汇编程序的翻译', '高级语言程序的解释执行', '机器语言的执行', '高级语言程序的翻译', 'D', '', '', '选择题', 5);
INSERT INTO `t_paperdetail` VALUES (27, 6, 27, '词法分析所依据的是( )。', '语义规则', '构词规则', '语法规则', '等价变换规则', 'B', '', '', '选择题', 5);
INSERT INTO `t_paperdetail` VALUES (28, 6, 28, '字符集为 {0，1 }，写出一个正则表达式，该正则表达式正好定义下面的字符串集合：第二个字符是1的所有字符串。', '', '', '', '', '(0|1)1(0|1)*', '', '', '填空题', 20);
INSERT INTO `t_paperdetail` VALUES (29, 6, 29, '词法分析器的输入是_______。', '', '', '', '', '源程序', '', '', '填空题', 20);
INSERT INTO `t_paperdetail` VALUES (30, 6, 30, '词法分析器的输出是_______。', '', '', '', '', 'token或token链', '', '', '填空题', 20);
INSERT INTO `t_paperdetail` VALUES (31, 6, 31, '计算机执行用高级语言编写的程序有哪些途径？他们之间主要区别是什么？', '', '', '', '', '编译程序', '解释程序', '这个字段为空', '简答题', 20);
INSERT INTO `t_paperdetail` VALUES (32, 5, 32, '软件测试的目的是( )。', '试验性运行软件', '发现软件错误', '证明软件正确', '找出软件中全部错误', 'B', '', '', '选择题', 5);
INSERT INTO `t_paperdetail` VALUES (33, 5, 33, '黑盒法是根据程序的( )来设计测试用例的。', '应用范围', '内部逻辑', '功能', '输入数据', 'C', '', '', '选择题', 5);
INSERT INTO `t_paperdetail` VALUES (34, 5, 34, '与设计测试用例无关的文档是( )。', '项目开发计划', '需求规格说明书', '设计说明书', '源程序', 'A', '', '', '选择题', 5);
INSERT INTO `t_paperdetail` VALUES (35, 5, 35, '用黑盒技术设计测试用例的方法之一为( )。', '因果图', '逻辑覆盖', '循环覆盖', '基本路径测试', 'A', '', '', '选择题', 5);
INSERT INTO `t_paperdetail` VALUES (36, 5, 36, '单元测试时，调用被测模块的是( )。', '桩模块', '通信模块', '驱动模块', '代理模块', 'C', '', '', '选择题', 5);
INSERT INTO `t_paperdetail` VALUES (37, 5, 37, '测试的关键问题是如何选择测试用例。', '对', '错', '', '', 'A', '', '', '判断题', 5);
INSERT INTO `t_paperdetail` VALUES (38, 5, 38, '软件测试用例主要由输入数据和测试计划两部分组成。', '对', '错', '', '', 'B', '', '', '判断题', 5);
INSERT INTO `t_paperdetail` VALUES (39, 5, 39, '路径覆盖查错能力最强。', '对', '错', '', '', 'A', '', '', '判断题', 5);
INSERT INTO `t_paperdetail` VALUES (40, 5, 40, '边界值分析属于白盒测试的技术。', '对', '错', '', '', 'B', '', '', '判断题', 5);
INSERT INTO `t_paperdetail` VALUES (41, 5, 41, '黑盒测试是根据软件的规格说明来设计测试用例。', '对', '错', '', '', 'A', '', '', '判断题', 5);
INSERT INTO `t_paperdetail` VALUES (42, 5, 42, '按照软件测试用例的设计方法而论，软件测试可以分为白盒测试法和______。', '', '', '', '', '黑盒测试法', '', '', '填空题', 8);
INSERT INTO `t_paperdetail` VALUES (43, 5, 43, '集成测试指在_______测试基础上，将所有模块按照设计要求组装成一个完整的系统进行的测试。', '', '', '', '', '单元', '', '', '填空题', 8);
INSERT INTO `t_paperdetail` VALUES (44, 5, 44, '要覆盖含循环结构的所有路径是不可能的，一般通过限制_______来测试。', '', '', '', '', '循环次数', '', '', '填空题', 8);
INSERT INTO `t_paperdetail` VALUES (45, 5, 45, '什么是压力测试？请简要回答。', '', '', '', '', '模拟巨大的工作负荷，以查看系统在峰值使用情况下是否可以正常运行', '通过逐步增加系统负载来测试系统性能的变化', '最终确定在什么负载条件下系统性能处于失效状态', '简答题', 13);
INSERT INTO `t_paperdetail` VALUES (46, 5, 46, '什么是性能测试？请简要回答。', '', '', '', '', '主要检验软件是否达到需求规格说明书中规定的各类性能指标', '满足一些性能相关的约束和限制条件', '性能测试', '简答题', 13);

-- ----------------------------
-- Table structure for t_score
-- ----------------------------
DROP TABLE IF EXISTS `t_score`;
CREATE TABLE `t_score`  (
  `scoreId` int(0) NOT NULL AUTO_INCREMENT COMMENT '成绩Id（唯一）',
  `userId` int(0) DEFAULT NULL COMMENT '用户编号',
  `paperId` int(0) DEFAULT NULL COMMENT '试卷编号',
  `mark` int(0) DEFAULT NULL COMMENT '成绩',
  `paperName` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL COMMENT '试卷名称',
  PRIMARY KEY (`scoreId`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 53 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Records of t_score
-- ----------------------------
INSERT INTO `t_score` VALUES (37, 2, 1, 80, '软件质量保证与测试小练习1');
INSERT INTO `t_score` VALUES (38, 2, 2, 80, '软件质量保证与测试小练习2');
INSERT INTO `t_score` VALUES (39, 2, 3, 80, '软件质量保证与测试小练习3');
INSERT INTO `t_score` VALUES (41, 2, 3, 100, '软件质量保证与测试小练习3');
INSERT INTO `t_score` VALUES (43, 2, 1, 100, '软件质量保证与测试小练习1');
INSERT INTO `t_score` VALUES (45, 2, 135, 10, '手动录入测试1');
INSERT INTO `t_score` VALUES (46, 2, 1, 20, '软件质量保证与测试小练习1');
INSERT INTO `t_score` VALUES (47, 2, 5, 75, '2020年春季学期软件质量保证与测试期末考试卷B');
INSERT INTO `t_score` VALUES (48, 2, 1, 20, '软件质量保证与测试小练习1');
INSERT INTO `t_score` VALUES (49, 2, 1, 100, '软件质量保证与测试小练习1');
INSERT INTO `t_score` VALUES (50, 2, 142, 75, '功能测试卷1');
INSERT INTO `t_score` VALUES (51, 4, 1, 100, '软件质量保证与测试小练习1');
INSERT INTO `t_score` VALUES (52, 4, 5, 92, '2020年春季学期软件质量保证与测试期末考试卷B');

-- ----------------------------
-- Table structure for t_user
-- ----------------------------
DROP TABLE IF EXISTS `t_user`;
CREATE TABLE `t_user`  (
  `userId` int(0) NOT NULL AUTO_INCREMENT COMMENT '用户Id（唯一）',
  `username` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL COMMENT '用户名不允许重复',
  `password` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL COMMENT '用户密码',
  `birthday` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL COMMENT '出生日期',
  `sex` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL COMMENT '性别',
  `power` int(0) DEFAULT NULL COMMENT '权限（0为学生，1为教师，2为管理员）',
  `image` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL COMMENT '头像',
  PRIMARY KEY (`userId`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 26 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Records of t_user
-- ----------------------------
INSERT INTO `t_user` VALUES (1, 'admin', '202cb962ac59075b964b07152d234b70', '19990316', '男', 2, 'http://120.26.186.88:8080/img/1.jpg');
INSERT INTO `t_user` VALUES (2, 'student', '202cb962ac59075b964b07152d234b70', '19990316', '女', 0, 'http://120.26.186.88:8080/img/4.jpg');
INSERT INTO `t_user` VALUES (3, 'teacher', '202cb962ac59075b964b07152d234b70', '19990316', '女', 1, 'http://120.26.186.88:8080/img/3.jpg');
INSERT INTO `t_user` VALUES (4, 'student2', '202cb962ac59075b964b07152d234b70', '19990608', '男', 0, 'http://120.26.186.88:8080/img/2.jpg');
INSERT INTO `t_user` VALUES (5, 'student3', '202cb962ac59075b964b07152d234b70', '19970608', '女', 0, 'http://120.26.186.88:8080/img/5.jpg');

-- ----------------------------
-- Table structure for t_wrong
-- ----------------------------
DROP TABLE IF EXISTS `t_wrong`;
CREATE TABLE `t_wrong`  (
  `wrongId` int(0) NOT NULL AUTO_INCREMENT COMMENT 'primary key',
  `userId` int(0) DEFAULT NULL COMMENT '用户id',
  `paperId` int(0) DEFAULT NULL COMMENT '试卷id',
  `paperDetailId` int(0) DEFAULT NULL COMMENT '试题在数据库中的id',
  `answer` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL COMMENT '用户的答案',
  `right` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL COMMENT '这道题正确的答案',
  `score` int(0) DEFAULT NULL COMMENT '这道题的分值',
  `nowScore` int(0) DEFAULT NULL COMMENT '用户得分',
  PRIMARY KEY (`wrongId`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 123 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Records of t_wrong
-- ----------------------------
INSERT INTO `t_wrong` VALUES (104, 2, 1, 9, 'A', 'C', 20, 0);
INSERT INTO `t_wrong` VALUES (105, 2, 2, 18, 'B', 'D', 20, 0);
INSERT INTO `t_wrong` VALUES (106, 2, 3, 20, 'C', 'B', 20, 0);
INSERT INTO `t_wrong` VALUES (107, 2, 3, 20, 'C', 'B', 20, 0);
INSERT INTO `t_wrong` VALUES (108, 2, 1, 10, 'C', 'A', 20, 0);
INSERT INTO `t_wrong` VALUES (109, 2, 1, 11, 'B', 'A', 20, 0);
INSERT INTO `t_wrong` VALUES (110, 2, 1, 12, 'D', 'A', 20, 0);
INSERT INTO `t_wrong` VALUES (111, 2, 1, 13, 'C', 'B', 20, 0);
INSERT INTO `t_wrong` VALUES (122, 4, 5, 42, '黑盒测试', '黑盒测试法', 8, 0);

SET FOREIGN_KEY_CHECKS = 1;
