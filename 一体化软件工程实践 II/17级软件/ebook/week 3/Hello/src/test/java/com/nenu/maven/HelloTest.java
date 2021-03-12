package com.nenu.maven;    
import org.junit.Test;
import static junit.framework.Assert.*;
public class HelloTest {
	@Test
	public void testHello(){
		Hello hello = new Hello();
		String results = hello.sayHello("J2EE class");
		//╤оят
		assertEquals("Hello J2EE class!",results);    
	}
}