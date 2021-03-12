package cn.edu.nenu.ssh.service;

import cn.edu.nenu.ssh.entity.Customer;

public interface CustomerService {

	
	/**
	 * 通过id查询用户
	 * @param CustomerId
	 * @return
	 */
	public Customer findCustomerById(Long CustomerId);
}
