package com.pandawork.service.carousel;

import com.pandawork.common.entity.carousel.Carousel;
import com.pandawork.core.common.exception.SSException;

import java.util.List;

/**
 * @Author:liangll
 * @Description:
 * @Date: 21:39 2018/12/20
 */
public interface CarouselService {
    /**
     * carousel信息列表
     * @return
     * @throws SSException
     */
    public List<Carousel> listAllCarousel() throws SSException;

    /**
     * 增加carousel信息
     * @throws SSException
     */
    public boolean addCarousel(Carousel carousel)throws SSException;

    /**
     * 删除carousel信息
     * @throws SSException
     */
    public boolean delCarousel(int id) throws SSException;

    /**
     * 修改carousel信息
     * @throws SSException
     */
    public boolean updateCarousel(Carousel carousel) throws SSException;

    /**
     * 查找（根据id）
     * @throws SSException
     */
    public Carousel selectById(int id) throws SSException;
}
