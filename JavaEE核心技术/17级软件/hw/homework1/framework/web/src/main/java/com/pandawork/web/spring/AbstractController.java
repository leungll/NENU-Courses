package com.pandawork.web.spring;

import com.pandawork.common.enums.CookieNameEnums;
import com.pandawork.common.utils.CookieUtil;
import com.pandawork.common.utils.WebConstants;
import com.pandawork.core.common.exception.SSException;
import com.pandawork.core.common.util.Assert;
import com.pandawork.core.framework.bean.StaticAutoWire;
import com.pandawork.core.framework.web.spring.controller.Base;
import com.pandawork.service.User.UserService;
import com.pandawork.service.nature.NatureService;
import net.sf.json.JSON;
import net.sf.json.JSONArray;
import net.sf.json.JSONObject;
import org.springframework.beans.factory.annotation.Qualifier;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;


/**
 * 添加抽象父类，进行封装核心的信息。
 *
 * @author Lionel
 * @E-mail lionel@pandawork.net
 * @time 2012-8-14
 */
public class AbstractController extends Base {
    // 默认分页size
    protected final static int DEFAULT_PAGE_SIZE = 10;
    // ajax默认成功代码
    protected final static int AJAX_SUCCESS_CODE = 0;
    // ajax默认失败代码
    protected final static int AJAX_FAILURE_CODE = 1;

    protected final static String DISABLED_STRING = "（已停用）";

    // 系统异常返回页面
    protected final static String ADMIN_SYS_ERR_PAGE = "forward:/500.jsp";
    // 禁止访问返回页面
    protected final static String ADMIN_FORBIDDEN_PAGE = "forward:/403.jsp";
    // 无法找到404页面
    protected final static String ADMIN_NOT_FOUND_PAGE = "forward:/404.jsp";

    // 系统异常返回页面
    protected final static String VIP_SYS_ERR_PAGE = ADMIN_SYS_ERR_PAGE;
    // 禁止访问返回页面
    protected final static String VIP_FORBIDDEN_PAGE = ADMIN_FORBIDDEN_PAGE;
    // 无法找到404页面
    protected final static String VIP_NOT_FOUND_PAGE = ADMIN_NOT_FOUND_PAGE;

    /**
     * 当前用户ID
     */
    private ThreadLocal<Integer> hostId = new ThreadLocal<Integer>();
    private ThreadLocal<String> hostName = new ThreadLocal<String>();

    // ${website}
    private ThreadLocal<String> website = new ThreadLocal<String>();


    //TODO:在用户确认之后修改此方法
    @Override
    public void init(HttpServletRequest request, HttpServletResponse response) {
        super.init(request, response); // 执行父类的初始化

       /* Integer partyId = (Integer) request.getAttribute(WebConstants.WebPartyId);
        hostId.set(partyId);
        String name = (String) request.getAttribute(WebConstants.WebUserName);
        hostName.set(name);
        Integer userId = (Integer) request.getAttribute(WebConstants.WebUId);
        uId.set(userId);*/

        Integer id = (Integer) request.getAttribute(WebConstants.WebUserId);
        if (!Assert.isNull(id)) {
            hostId.set(id);
        } else {
            hostId.set(CookieUtil.getIdCookie(request, CookieNameEnums.WebUserId));
        }

        String loginName = (String) request.getAttribute(WebConstants.WebLoginName);
        if (!Assert.isNull(loginName)) {
            hostName.set(loginName);
        } else {
            hostName.set(CookieUtil.getValueByName(request, CookieNameEnums.WebLoginName));
        }
        website.set((String) request.getAttribute("website"));
    }

    /**
     * 获取用户ID,如果当前用户不登录，默认返回0；
     *
     * @return
     * @author Lionel
     * @E-mail lionel@pandawork.net
     * @time 2012-8-14
     */
    protected Integer getHostId() {
        if (hostId.get() == null) {
            return 0;
        }
        return hostId.get();
    }

    //验证partyId是否存在

    protected String getHostName() {
        return this.hostName.get();
    }


    /**
     * 获取当前网址
     *
     * @return
     */
    protected String getWebsite() {
        return this.website.get();
    }

    /**
     * 发送无数据与的json对象
     *
     * @param code
     * @return
     */
    protected JSONObject sendJsonObject(int code) {
        JSONObject jsonObject = new JSONObject();
        jsonObject.put("code", code);
        return jsonObject;
    }

    /**
     * 发送json对象
     *
     * @param json
     * @return
     */
    protected JSONObject sendJsonObject(JSON json, int code) {
        JSONObject jsonObject = new JSONObject();
        jsonObject.put("code", code);
        if (json != null) {
            jsonObject.put("data", json);
        }
        return jsonObject;
    }

    // 发送ajax错误信息
    protected JSONObject sendErrMsgAndErrCode(SSException e) {
        JSONObject json = new JSONObject();
        json.put("code", AJAX_FAILURE_CODE);
        json.put("errMsg", e.getMessage());
        return json;
    }

    // 发送ajax分页信息
    protected JSONObject sendJsonArray(JSONArray jsonArray, int dataCount, int pageSize) {
        JSONObject jsonObject = new JSONObject();
        jsonObject.put("code", AJAX_SUCCESS_CODE);
        jsonObject.put("list", jsonArray);
        jsonObject.put("dataCount", dataCount);
        jsonObject.put("pageSize", pageSize);
        return jsonObject;
    }

    // 默认按照默认的pagesize返回数据
    protected JSONObject sendJsonArray(JSONArray jsonArray, int dataCount) {
        JSONObject jsonObject = new JSONObject();
        jsonObject.put("code", AJAX_SUCCESS_CODE);
        jsonObject.put("list", jsonArray);
        jsonObject.put("dataCount", dataCount);
        jsonObject.put("pageSize", DEFAULT_PAGE_SIZE);
        return jsonObject;
    }

//    @StaticAutoWire
//    @Qualifier("studentService")
//    protected static StudentService studentService ;

    @StaticAutoWire
    @Qualifier("userService")
    protected static UserService userService;

    @StaticAutoWire
    @Qualifier("natureService")
    protected static NatureService natureService;
}
