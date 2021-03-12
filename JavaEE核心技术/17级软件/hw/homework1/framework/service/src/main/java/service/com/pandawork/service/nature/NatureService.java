package com.pandawork.service.nature;

import com.pandawork.common.entity.nature.Nature;
import com.pandawork.core.common.exception.SSException;

import java.util.List;
/**
 * @author : kongyy
 * @time : 2018/12/23 16:52
 */
public interface NatureService {

    public List<Nature> listAll( ) throws SSException;

    public List<Nature> listAll2( ) throws SSException;

    public boolean addNature(Nature nature) throws SSException;

    public boolean update(Nature nature) throws SSException;

    public boolean update2(int id) throws SSException;

    public boolean update3(int id) throws SSException;

    public boolean delById(int id) throws SSException;


}
