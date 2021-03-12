package cn.edu.nenu.ssh.dao;

import cn.edu.nenu.ssh.entity.Customer;

public interface CustomerDao {

	/**
	 * 通过id查询用户
	 * @param CustomerId
	 * @return
	 */
	public Customer findCustomerById(Long CustomerId);
}
