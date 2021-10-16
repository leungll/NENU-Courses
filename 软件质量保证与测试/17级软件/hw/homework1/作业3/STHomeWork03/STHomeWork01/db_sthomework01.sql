/*
 Navicat Premium Data Transfer

 Source Server         : localhost_3306
 Source Server Type    : MySQL
 Source Server Version : 80015
 Source Host           : localhost:3306
 Source Schema         : db_sthomework01

 Target Server Type    : MySQL
 Target Server Version : 80015
 File Encoding         : 65001

 Date: 25/04/2020 11:10:31
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for t_student
-- ----------------------------
DROP TABLE IF EXISTS `t_student`;
CREATE TABLE `t_student`  (
  `id` int(11) NOT NULL AUTO_INCREMENT COMMENT '学生学号（唯一）',
  `name` varchar(255) CHARACTER SET utf8 COLLATE utf8_unicode_ci DEFAULT NULL COMMENT '学生姓名',
  `birDate` varchar(255) CHARACTER SET utf8 COLLATE utf8_unicode_ci DEFAULT NULL COMMENT '学生出生日期',
  `gender` varchar(255) CHARACTER SET utf8 COLLATE utf8_unicode_ci DEFAULT NULL COMMENT '学生性别',
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 2017012843 CHARACTER SET = utf8 COLLATE = utf8_unicode_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of t_student
-- ----------------------------
INSERT INTO `t_student` VALUES (2016035987, '白云', '19600728', '女');
INSERT INTO `t_student` VALUES (2017011111, '王五', '19991001', '女');
INSERT INTO `t_student` VALUES (2017011112, '二丫', '19920606', '女');
INSERT INTO `t_student` VALUES (2017011254, '李彦宏', '19800304', '男');
INSERT INTO `t_student` VALUES (2017012842, '张三', '19991021', '女');
INSERT INTO `t_student` VALUES (2017035481, '吴恩达', '19841204', '男');
INSERT INTO `t_student` VALUES (2017061588, '马云', '19750806', '男');
INSERT INTO `t_student` VALUES (2017068896, '乔布斯', '19850505', '男');

SET FOREIGN_KEY_CHECKS = 1;
