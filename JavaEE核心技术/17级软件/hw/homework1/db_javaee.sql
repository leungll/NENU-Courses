/*
Navicat MySQL Data Transfer

Source Server         : localhost_3306
Source Server Version : 50619
Source Host           : localhost:3306
Source Database       : db_javaee

Target Server Type    : MYSQL
Target Server Version : 50619
File Encoding         : 65001

Date: 2018-12-29 12:51:58
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `t_build`
-- ----------------------------
DROP TABLE IF EXISTS `t_build`;
CREATE TABLE `t_build` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) DEFAULT NULL,
  `content` varchar(255) DEFAULT NULL,
  `path` varchar(255) DEFAULT NULL,
  `status` int(11) DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of t_build
-- ----------------------------

-- ----------------------------
-- Table structure for `t_carousel`
-- ----------------------------
DROP TABLE IF EXISTS `t_carousel`;
CREATE TABLE `t_carousel` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) DEFAULT NULL,
  `path` varchar(255) DEFAULT NULL,
  `status` varchar(255) NOT NULL DEFAULT 'No',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=67 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of t_carousel
-- ----------------------------
INSERT INTO `t_carousel` VALUES ('62', '1', '/images/20181229124706一.png', 'No');
INSERT INTO `t_carousel` VALUES ('63', '2', '/images/20181229124714二.png', 'No');
INSERT INTO `t_carousel` VALUES ('64', '3', '/images/20181229124720三.png', 'No');
INSERT INTO `t_carousel` VALUES ('65', '4', '/images/20181229124727四.PNG', 'No');
INSERT INTO `t_carousel` VALUES ('66', '5', '/images/20181229124740五.PNG', 'No');

-- ----------------------------
-- Table structure for `t_nature`
-- ----------------------------
DROP TABLE IF EXISTS `t_nature`;
CREATE TABLE `t_nature` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) DEFAULT NULL,
  `content` varchar(255) DEFAULT NULL,
  `path` varchar(255) DEFAULT NULL,
  `status` int(11) DEFAULT '0' COMMENT '状态',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=36 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of t_nature
-- ----------------------------
INSERT INTO `t_nature` VALUES ('33', '1', null, '/images/201812291249051.jpg', '1');
INSERT INTO `t_nature` VALUES ('34', '2', null, '/images/201812291249112.jpg', '1');
INSERT INTO `t_nature` VALUES ('35', '3', null, '/images/201812291249163.jpg', '0');

-- ----------------------------
-- Table structure for `t_perpon`
-- ----------------------------
DROP TABLE IF EXISTS `t_perpon`;
CREATE TABLE `t_perpon` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) DEFAULT NULL,
  `cotent` varchar(255) DEFAULT NULL,
  `path` varchar(255) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of t_perpon
-- ----------------------------

-- ----------------------------
-- Table structure for `t_picture`
-- ----------------------------
DROP TABLE IF EXISTS `t_picture`;
CREATE TABLE `t_picture` (
  `id` int(10) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) DEFAULT NULL,
  `path` varchar(255) DEFAULT NULL,
  `status` varchar(255) DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of t_picture
-- ----------------------------
INSERT INTO `t_picture` VALUES ('1', 'hello2', '/666', null);
INSERT INTO `t_picture` VALUES ('2', 'hello2', '/666', null);
INSERT INTO `t_picture` VALUES ('3', 'hello2', '/666', null);
INSERT INTO `t_picture` VALUES ('4', 'hello2', '/666', null);
INSERT INTO `t_picture` VALUES ('5', 'hello2', '/666', '0');

-- ----------------------------
-- Table structure for `t_user`
-- ----------------------------
DROP TABLE IF EXISTS `t_user`;
CREATE TABLE `t_user` (
  `id` int(20) NOT NULL AUTO_INCREMENT,
  `username` varchar(255) NOT NULL COMMENT '用户名',
  `password` varchar(255) NOT NULL COMMENT '密码',
  `power` int(10) NOT NULL DEFAULT '0' COMMENT '是否为超级管理员',
  `sig` varchar(11) NOT NULL DEFAULT 'null' COMMENT '签名',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=93 DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of t_user
-- ----------------------------
INSERT INTO `t_user` VALUES ('79', 'ha', '123', '1', '123123');
INSERT INTO `t_user` VALUES ('82', '1', 'wqeqw', '1', 'ssdfsd');
INSERT INTO `t_user` VALUES ('91', 'admin', '12341234', '1', 'AHAHAH');
INSERT INTO `t_user` VALUES ('92', '11', '12341234', '0', '真是棒呆了');
