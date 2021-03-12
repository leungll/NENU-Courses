package com.pandawork.test;

import com.pandawork.common.entity.nature.Nature;
import com.pandawork.core.common.exception.SSException;
import com.pandawork.service.nature.NatureService;
import org.junit.Test;
import org.springframework.beans.factory.annotation.Autowired;

/**
 * 学生管理系统
 * 测试service页面
 * studentService
 * Created by fujia on 2016/3/26.
 */
public class NatureServiceTest extends AbstractTestCase {

    @Autowired
    NatureService natureService;

    //测试新增学生信息
    @Test
    public void testAddNature() throws SSException {
        Nature nature = new Nature();
        nature.setName("me888");
        nature.setContent("hahahahhhh");
        nature.setPath("djfsjdlfjslkd");
        natureService.addNature(nature);
        System.out.println("添加成功");
    }

    //测试查询学生信息列表
    @Test
    public void testListAll() throws SSException{
        System.out.print(natureService.listAll());
    }

    //测试删除学生信息
    @Test
    public void testDelById() throws SSException{
        Nature nature = new Nature();
        nature.setId(2);
        natureService.delById(nature.getId());
        System.out.println("16");
    }

    //测试更新学生信息
    @Test
    public void testUpdate() throws SSException{
        Nature nature = new Nature();
        nature.setId(3);
        nature.setName("a");
        nature.setContent("dsfsdfsd");
        nature.setPath("dfsdfsdf");
        nature.setStatus(2);
        natureService.update(nature);
        System.out.println("12");
    }

    @Test
    public void testUpdate2() throws SSException{
        int id;
        id = 12;
        natureService.update2(id);
        System.out.println("12");
    }

    @Test
    public void testUpdate3() throws SSException{
        int id;
        id = 25;
        natureService.update3(id);
        System.out.println("12");
    }

    @Test
    public void testListAll2() throws SSException{
        System.out.print(natureService.listAll2());
    }
}
