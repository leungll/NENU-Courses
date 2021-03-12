package com.pandawork.mapper.nature;

import com.pandawork.common.entity.nature.Nature;
import org.apache.ibatis.annotations.Param;

import java.util.List;

/**
 * @author : kongyy
 * @time : 2018/12/23 16:49
 */
public interface NatureMapper {

    public boolean addNature(@Param("nature") Nature nature) throws Exception;

    public boolean update(@Param("nature") Nature nature) throws Exception;

    public boolean update2(@Param("id") int id) throws Exception;

    public boolean update3(@Param("id") int id) throws Exception;

    public boolean delById(@Param("id") int id) throws Exception;

    public List<Nature> listAll( ) throws Exception;

    public List<Nature> listAll2( ) throws Exception;

}
