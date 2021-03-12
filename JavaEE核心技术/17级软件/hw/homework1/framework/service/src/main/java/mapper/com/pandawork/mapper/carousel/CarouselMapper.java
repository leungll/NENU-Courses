package com.pandawork.mapper.carousel;

import com.pandawork.common.entity.carousel.Carousel;
import org.apache.ibatis.annotations.Param;

import java.util.List;

/**
 * @Author:liangll
 * @Description:
 * @Date: 15:51 2018/8/3
 */
public interface CarouselMapper {

    /**
     * 查询所有carousel列表
     * @throws Exception
     */
    public List<Carousel> listAllCarousel() throws Exception;

    /**
     * 增加carousel
     * @param carousel
     * @throws Exception
     */
    public boolean addCarousel(@Param("carousel") Carousel carousel) throws Exception;

    /**
     *删除carousel
     * @param id
     * @throws Exception
     */
    public boolean delCarousel(@Param("id") int id) throws Exception;

    /**
     * 修改carousel
     * @param carousel
     * @throws Exception
     */
    public boolean updateCarousel(@Param("carousel") Carousel carousel) throws Exception;

    /**
     * 根据id查询信息
     * @param id
     * @returns
     * @throws Exception
     */
    public Carousel selectById(@Param("id") int id) throws Exception;

}
