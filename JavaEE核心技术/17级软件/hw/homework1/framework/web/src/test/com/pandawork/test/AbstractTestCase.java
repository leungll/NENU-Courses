package com.pandawork.test;
import com.pandawork.core.framework.bean.StaticAutoWire;
import junit.framework.TestCase;
import org.junit.runner.RunWith;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;

/**
 * AbstractTestCase
 *
 * @author: dujuan
 * @time: 2015/8/14 13:48
 */
@RunWith(SpringJUnit4ClassRunner.class)
@ContextConfiguration(locations = {"classpath:applicationContext.xml"})
public abstract class AbstractTestCase extends TestCase {

}



