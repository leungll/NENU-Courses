package com.pandawork.web.filter;

import com.pandawork.common.utils.WebConstants;
import com.pandawork.core.framework.web.filter.AbstractConstansFilter;

import javax.servlet.FilterChain;
import javax.servlet.ServletException;
import javax.servlet.ServletRequest;
import javax.servlet.ServletResponse;
import javax.servlet.http.HttpServletRequest;
import java.io.IOException;

/**
 * 常量拦截器
 */
public class ConstantsFilter extends AbstractConstansFilter {

    private String basePath;

    @Override
    public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain) throws IOException, ServletException {
        HttpServletRequest httpRequest = (HttpServletRequest) request;
        String path = httpRequest.getContextPath();

        int port = httpRequest.getServerPort();

        basePath = httpRequest.getScheme() + "://" + httpRequest.getServerName()
                + (port == 80 ? "" : (":" + port)) + path + "/";
        //不要删除 下载的时候要用
        request.setAttribute("tinyStaticWebsite", getTinyStaticWebsite());
        request.setAttribute("uploadStaticWebsite", getUploadStaticWebsite());

        //添加商城域名
        super.doFilter(httpRequest, response, chain);
    }

    public String getTinyStaticWebsite() {
//      return basePath + "resources/";
        return WebConstants.staticWebsite;
    }

    public  String getUploadStaticWebsite(){
        return WebConstants.staticWebsite + "uploads/";
    }

    @Override
    public String getStaticWebsite() {
//        return basePath + "resources/";
        return WebConstants.staticWebsite + "resources/";
    }

    @Override
    public String getTinyWebSite() {
        return WebConstants.staticWebsite + "uploads/";
    }

    @Override
    public String getWebfullName() {
        return WebConstants.webFullName;
    }

    @Override
    public String getWebName() {
        return WebConstants.webName;
    }

    @Override
    public String getWebTitle() {
        return WebConstants.webTitle;
    }

    @Override
    public String getWebsite() {
        return basePath;
    }

    @Override
    public void destroy() {
        //noop
    }

}
