package com.nenu.market.util;

import org.w3c.dom.Document;
import org.w3c.dom.Node;
import org.w3c.dom.NodeList;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import java.io.File;

/**
 * @Author: Liangll
 * @Description: 配置类
 * @Date: 22:17 2020/5/18
 */
public class XmlUtil {

    /**
     * 从XML配置文件中提取具体类类名
     * @return 返回一个实例对象
     */
    public static Object getBean() {
        try {
            //创建文档对象
            DocumentBuilderFactory dFactory = DocumentBuilderFactory.newInstance();
            DocumentBuilder builder = dFactory.newDocumentBuilder();
            Document doc;
            doc = builder.parse(new File("src/com/nenu/market/res/config.xml"));

            //获取包含类名的文本节点
            NodeList nl = doc.getElementsByTagName("className");
            Node classNode = nl.item(0).getFirstChild();
            String cName = classNode.getNodeValue();

            //通过类名生成实例对象并将其返回
            Class c = Class.forName(cName);
            Object obj = c.newInstance();
            return obj;
        } catch(Exception e) {
            e.printStackTrace();
            return null;
        }
    }
}
