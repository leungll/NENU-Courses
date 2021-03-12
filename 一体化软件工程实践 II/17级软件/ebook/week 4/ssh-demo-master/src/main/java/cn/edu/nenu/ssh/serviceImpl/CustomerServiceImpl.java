package cn.edu.nenu.ssh.serviceImpl;

import cn.edu.nenu.ssh.dao.CustomerDao;
import cn.edu.nenu.ssh.entity.Customer;
import cn.edu.nenu.ssh.service.CustomerService;

public class CustomerServiceImpl implements CustomerService {

	private CustomerDao customerDao;
	public void setCustomerDao(CustomerDao customerDao) {
		this.customerDao = customerDao;
	}
	public CustomerDao getCustomerDao() {
		return customerDao;
	}


	@Override
	public Customer findCustomerById(Long CustomerId) {
		return customerDao.findCustomerById(CustomerId);
	}

}
