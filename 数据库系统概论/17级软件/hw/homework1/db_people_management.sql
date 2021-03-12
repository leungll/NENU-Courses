/*
 Navicat Premium Data Transfer

 Source Server         : localhost_3306
 Source Server Type    : MySQL
 Source Server Version : 50619
 Source Host           : localhost:3306
 Source Schema         : db_people_management

 Target Server Type    : MySQL
 Target Server Version : 50619
 File Encoding         : 65001

 Date: 27/06/2019 10:41:29
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for t_department
-- ----------------------------
DROP TABLE IF EXISTS `t_department`;
CREATE TABLE `t_department`  (
  `department_id` int(50) NOT NULL AUTO_INCREMENT COMMENT '部门编号id',
  `department_name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL COMMENT '部门名称',
  `department_manager` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL COMMENT '部门负责人姓名',
  `department_num` int(50) DEFAULT NULL COMMENT '部门人数',
  PRIMARY KEY (`department_id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 5 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Records of t_department
-- ----------------------------
INSERT INTO `t_department` VALUES (1, '技术部后端', '徐敏洪', 4);
INSERT INTO `t_department` VALUES (2, '技术部前端', '金溪', 4);
INSERT INTO `t_department` VALUES (3, '产品部', '杨孟贤', 4);
INSERT INTO `t_department` VALUES (4, '新媒体运营部', '肖晓潇', 4);

-- ----------------------------
-- Table structure for t_position_salary
-- ----------------------------
DROP TABLE IF EXISTS `t_position_salary`;
CREATE TABLE `t_position_salary`  (
  `position_id` int(50) NOT NULL AUTO_INCREMENT COMMENT '职位编号id',
  `position_name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL COMMENT '职位名称',
  `department_id` int(50) DEFAULT NULL COMMENT '所属部门编号id',
  `salary` int(50) DEFAULT NULL COMMENT '职位对应的资本工资',
  PRIMARY KEY (`position_id`) USING BTREE,
  INDEX `department_id2`(`department_id`) USING BTREE,
  CONSTRAINT `department_id2` FOREIGN KEY (`department_id`) REFERENCES `t_department` (`department_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE = InnoDB AUTO_INCREMENT = 9 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Records of t_position_salary
-- ----------------------------
INSERT INTO `t_position_salary` VALUES (11, '负责人', 1, 21000);
INSERT INTO `t_position_salary` VALUES (12, '负责人', 2, 18000);
INSERT INTO `t_position_salary` VALUES (13, '负责人', 3, 15000);
INSERT INTO `t_position_salary` VALUES (14, '负责人', 4, 14000);
INSERT INTO `t_position_salary` VALUES (15, '普通职工', 1, 15000);
INSERT INTO `t_position_salary` VALUES (16, '普通职工', 2, 13000);
INSERT INTO `t_position_salary` VALUES (17, '普通职工', 3, 10000);
INSERT INTO `t_position_salary` VALUES (18, '普通职工', 4, 8000);

-- ----------------------------
-- Table structure for t_sign_in
-- ----------------------------
DROP TABLE IF EXISTS `t_sign_in`;
CREATE TABLE `t_sign_in`  (
  `sign_id` int(50) NOT NULL AUTO_INCREMENT COMMENT '打卡编号id',
  `staff_id` int(50) DEFAULT NULL COMMENT '打卡职工编号id',
  `sign_time` date DEFAULT NULL COMMENT '打卡时间',
  PRIMARY KEY (`sign_id`) USING BTREE,
  INDEX `staff_id`(`staff_id`) USING BTREE,
  CONSTRAINT `staff_id` FOREIGN KEY (`staff_id`) REFERENCES `t_staff` (`staff_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE = InnoDB AUTO_INCREMENT = 17 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Records of t_sign_in
-- ----------------------------
INSERT INTO `t_sign_in` VALUES (21, 104, '2018-05-30');
INSERT INTO `t_sign_in` VALUES (22, 101, '2018-05-30');
INSERT INTO `t_sign_in` VALUES (23, 103, '2018-05-30');
INSERT INTO `t_sign_in` VALUES (24, 110, '2018-05-30');
INSERT INTO `t_sign_in` VALUES (25, 116, '2018-05-30');
INSERT INTO `t_sign_in` VALUES (26, 104, '2019-06-01');
INSERT INTO `t_sign_in` VALUES (27, 111, '2018-05-30');
INSERT INTO `t_sign_in` VALUES (28, 102, '2018-05-30');
INSERT INTO `t_sign_in` VALUES (29, 106, '2018-05-30');

-- ----------------------------
-- Table structure for t_staff
-- ----------------------------
DROP TABLE IF EXISTS `t_staff`;
CREATE TABLE `t_staff`  (
  `staff_id` int(50) NOT NULL AUTO_INCREMENT COMMENT '职工编号id',
  `department_id` int(50) DEFAULT NULL COMMENT '所属部门编号id',
  `staff_name` varchar(255) CHARACTER SET utf8 COLLATE utf8_general_ci DEFAULT NULL COMMENT '姓名',
  `staff_age` int(50) DEFAULT NULL COMMENT '年龄',
  `position_id` int(50) DEFAULT NULL COMMENT '职位编号id',
  `total_salary` int(50) DEFAULT NULL COMMENT '职工总工资',
  PRIMARY KEY (`staff_id`) USING BTREE,
  INDEX `department_id`(`department_id`) USING BTREE,
  INDEX `position_id`(`position_id`) USING BTREE,
  CONSTRAINT `position_id` FOREIGN KEY (`position_id`) REFERENCES `t_position_salary` (`position_id`) ON DELETE CASCADE ON UPDATE CASCADE,
  CONSTRAINT `department_id` FOREIGN KEY (`department_id`) REFERENCES `t_department` (`department_id`) ON DELETE CASCADE ON UPDATE CASCADE
) ENGINE = InnoDB AUTO_INCREMENT = 17 CHARACTER SET = utf8 COLLATE = utf8_general_ci ROW_FORMAT = Compact;

-- ----------------------------
-- Records of t_staff
-- ----------------------------
INSERT INTO `t_staff` VALUES (101, 1, '杨兴邦', 38, 15, 16900);
INSERT INTO `t_staff` VALUES (102, 1, '王兆国', 29, 15, 15600);
INSERT INTO `t_staff` VALUES (103, 1, '刘少华', 30, 15, 17000);
INSERT INTO `t_staff` VALUES (104, 1, '徐敏洪', 45, 11, 23000);
INSERT INTO `t_staff` VALUES (105, 2, '孙霞', 25, 16, 13890);
INSERT INTO `t_staff` VALUES (106, 2, '金溪', 28, 12, 20800);
INSERT INTO `t_staff` VALUES (107, 2, '李万', 36, 16, 15000);
INSERT INTO `t_staff` VALUES (108, 2, '余能', 30, 16, 14800);
INSERT INTO `t_staff` VALUES (109, 3, '王爱莲', 23, 17, 8560);
INSERT INTO `t_staff` VALUES (110, 3, '杨孟贤', 26, 13, 18900);
INSERT INTO `t_staff` VALUES (111, 3, '沈洁', 24, 17, 14000);
INSERT INTO `t_staff` VALUES (112, 3, '梁红', 30, 17, 12100);
INSERT INTO `t_staff` VALUES (113, 4, '孔凡河', 22, 18, 11810);
INSERT INTO `t_staff` VALUES (114, 4, '甘燕', 23, 18, 10470);
INSERT INTO `t_staff` VALUES (115, 4, '屈海婉', 22, 18, 9600);
INSERT INTO `t_staff` VALUES (116, 4, '肖晓潇', 25, 14, 16040);

SET FOREIGN_KEY_CHECKS = 1;
