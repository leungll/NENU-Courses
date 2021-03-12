package com.pandawork.service.nature.impl;

import com.pandawork.common.entity.nature.Nature;
import com.pandawork.common.utils.NFException;
import com.pandawork.core.common.exception.SSException;
import com.pandawork.core.common.log.LogClerk;
import com.pandawork.core.common.util.Assert;
import com.pandawork.core.framework.dao.CommonDao;
import com.pandawork.mapper.nature.NatureMapper;
import com.pandawork.service.nature.NatureService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.Collections;
import java.util.List;


/**
 * @author : kongyy
 * @time : 2018/12/23 16:52
 */
@Service("natureService")
public class NatureServiceImpl implements NatureService {

    @Autowired
    NatureMapper natureMapper;

    @Autowired
    protected CommonDao commonDao;

    @Override
    public List<Nature> listAll() throws SSException {
        List<Nature> natureList = Collections.emptyList();
        try {
            natureList = natureMapper.listAll();
        } catch (Exception e) {
            LogClerk.errLog.error(e);
            throw SSException.get(NFException.SystemException, e);
        }
        return natureList;
    }

    @Override
    public List<Nature> listAll2() throws SSException {
        List<Nature> natureList = Collections.emptyList();
        try {
            natureList = natureMapper.listAll2();
        } catch (Exception e) {
            LogClerk.errLog.error(e);
            throw SSException.get(NFException.SystemException, e);
        }
        return natureList;
    }

    @Override
    public boolean addNature(Nature nature) throws SSException {
        try {
            return natureMapper.addNature(nature);
        } catch (Exception e) {
            LogClerk.errLog.error(e);
            throw SSException.get(NFException.SystemException, e);
        }
    }

    @Override
    public boolean update(Nature nature) throws SSException {
        try {
            return natureMapper.update(nature);
        } catch (Exception e) {
            LogClerk.errLog.error(e);
            throw SSException.get(NFException.SystemException, e);
        }
    }

    @Override
    public boolean update2(int id) throws SSException {
        try {
            return natureMapper.update2(id);
        } catch (Exception e) {
            LogClerk.errLog.error(e);
            throw SSException.get(NFException.SystemException, e);
        }
    }

    @Override
    public boolean update3(int id) throws SSException {
        try {
            return natureMapper.update3(id);
        } catch (Exception e) {
            LogClerk.errLog.error(e);
            throw SSException.get(NFException.SystemException, e);
        }
    }

    @Override
    public boolean delById(int id) throws SSException {
        if (Assert.lessOrEqualZero(id)) {
            return false;
        }
        try {
            return natureMapper.delById(id);
        } catch (Exception e) {
            LogClerk.errLog.error(e);
            throw SSException.get(NFException.DelStudentNull, e);
        }
    }



}
