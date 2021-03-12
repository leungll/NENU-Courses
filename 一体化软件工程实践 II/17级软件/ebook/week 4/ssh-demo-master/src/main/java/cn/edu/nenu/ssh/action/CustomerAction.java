package cn.edu.nenu.ssh.action;

import com.opensymphony.xwork2.ActionSupport;

import cn.edu.nenu.ssh.entity.Customer;
import cn.edu.nenu.ssh.service.CustomerService;

public class CustomerAction extends ActionSupport {

	//注入service
	private CustomerService customerService;
	
	//属性封装到custId
	private Long custId;//客户id
	
	//存放到值栈（get方式）
	private Customer customer;//客户信息
	
	
	public CustomerService getCustomerService() {
		return customerService;
	}
	public void setCustomerService(CustomerService customerService) {
		this.customerService = customerService;
	}
	public Long getCustId() {
		return custId;
	}
	public void setCustId(Long custId) {
		this.custId = custId;
	}
	public Customer getCustomer() {
		return customer;
	}
	public void setCustomer(Customer customer) {
		this.customer = customer;
	}
	
	
	//action方法
	public String queryCustomer(){
		customer=customerService.findCustomerById(custId);
		return "success";
	}
	
	
}
