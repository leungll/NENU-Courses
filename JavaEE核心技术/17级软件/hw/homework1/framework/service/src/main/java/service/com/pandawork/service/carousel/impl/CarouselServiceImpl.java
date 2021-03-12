package com.pandawork.service.carousel.impl;

import com.pandawork.common.entity.carousel.Carousel;
import com.pandawork.common.utils.NFException;
import com.pandawork.core.common.exception.SSException;
import com.pandawork.core.common.log.LogClerk;
import com.pandawork.core.framework.dao.CommonDao;
import com.pandawork.mapper.carousel.CarouselMapper;
import com.pandawork.service.carousel.CarouselService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.Collections;
import java.util.List;

/**
 * @Author:liangll
 * @Description:
 * @Date: 16:11 2018/8/3
 */
@Service("carouselService")
public class CarouselServiceImpl implements CarouselService {

    @Autowired
    CarouselMapper carouselMapper;

    @Autowired
    protected CommonDao commonDao;

    @Override
    public List<Carousel> listAllCarousel() throws SSException {
        List<Carousel> carouselList = Collections.emptyList();
        try {
            carouselList = carouselMapper.listAllCarousel();
        } catch (Exception e) {
            LogClerk.errLog.error(e);
            throw SSException.get(NFException.SystemException, e);
        }
        return carouselList;
    }

    @Override
    public boolean addCarousel(Carousel carousel) throws SSException {
        try {
            return carouselMapper.addCarousel(carousel);
        } catch (Exception e) {
            LogClerk.errLog.error(e);
            throw SSException.get(NFException.SystemException, e);
        }
    }

    @Override
    public boolean delCarousel(int id) throws SSException {
        try {
            return carouselMapper.delCarousel(id);
        } catch (Exception e) {
            LogClerk.errLog.error(e);
            throw SSException.get(NFException.SystemException, e);
        }
    }

    @Override
    public boolean updateCarousel(Carousel carousel) throws SSException {
        try {
            return carouselMapper.updateCarousel(carousel);
        } catch (Exception e) {
            LogClerk.errLog.error(e);
            throw SSException.get(NFException.SystemException, e);
        }
    }

    @Override
    public Carousel selectById(int id) throws SSException {
        try {
            return carouselMapper.selectById(id);
        } catch (Exception e) {
            LogClerk.errLog.error(e);
            throw SSException.get(NFException.SystemException, e);
        }
    }
}