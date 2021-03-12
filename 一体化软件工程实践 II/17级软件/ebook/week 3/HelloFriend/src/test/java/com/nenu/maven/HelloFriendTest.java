package com.nenu.maven;    
import static junit.framework.Assert.assertEquals;
import org.junit.Test;

import com.nenu.maven.Hello;

public class HelloFriendTest {
	@Test
	public void testHelloFriend(){
		HelloFriend helloFriend = new HelloFriend();
		String results = helloFriend.sayHelloToFriend("刚刚");

		assertEquals("Hello 刚刚! I am John",results);    
	}
}