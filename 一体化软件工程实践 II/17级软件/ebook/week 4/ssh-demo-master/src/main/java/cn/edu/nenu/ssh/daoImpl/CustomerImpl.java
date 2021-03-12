package cn.edu.nenu.ssh.daoImpl;

import org.springframework.orm.hibernate5.support.HibernateDaoSupport;

import cn.edu.nenu.ssh.dao.CustomerDao;
import cn.edu.nenu.ssh.entity.Customer;

public class CustomerImpl extends HibernateDaoSupport implements CustomerDao {

	@Override
	public Customer findCustomerById(Long CustomerId) {
		return this.getHibernateTemplate().get(Customer.class, CustomerId);
	}

}
