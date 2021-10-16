/* -------------------------------------------------------------------------------
	Script Title       : 
	Script Description : 
                        
                        
	Recorder Version   : 2739
   ------------------------------------------------------------------------------- */

vuser_init()
{

	web_url("localhost:8090", 
		"URL=http://localhost:8090/", 
		"Resource=0", 
		"Referer=", 
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		EXTRARES, 
		"Url=http://at.alicdn.com/t/font_1070199_erifwizjidd.css", ENDITEM, 
		"Url=/static/css/reset.css", ENDITEM, 
		"Url=/static/css/animate.min.css", ENDITEM, 
		"Url=/app.js", ENDITEM, 
		"Url=/static/img/js.f38f3a7.png", ENDITEM, 
		"Url=/sockjs-node/info?t=1593652554450", ENDITEM, 
		"Url=/sockjs-node/info?t=1593652574359", ENDITEM, 
		"Url=/static/img/admin.49233f6.jpg", ENDITEM, 
		"Url=/static/fonts/element-icons.535877f.woff", ENDITEM, 
		LAST);

	web_websocket_connect("ID=0", 
		"URI=ws://localhost:8090/sockjs-node/068/ezm212vc/websocket", 
		"Origin=http://localhost:8090", 
		"OnOpenCB=OnOpenCB0", 
		"OnMessageCB=OnMessageCB0", 
		"OnErrorCB=OnErrorCB0", 
		"OnCloseCB=OnCloseCB0", 
		LAST);

	/*Connection ID 0 received buffer WebSocketReceive0*/

	/*Connection ID 0 received buffer WebSocketReceive1*/

	/*Connection ID 0 received buffer WebSocketReceive2*/

	/*Connection ID 0 received buffer WebSocketReceive3*/

	web_submit_data("login", 
		"Action=http://120.26.186.88:8080/user/login", 
		"Method=POST", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=username", "Value=admin", ENDITEM, 
		"Name=password", "Value=123", ENDITEM, 
		LAST);

	web_submit_data("login", 
		"Action=http://120.26.186.88:8080/user/login", 
		"Method=POST", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t20.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=username", "Value=teacher", ENDITEM, 
		"Name=password", "Value=123", ENDITEM, 
		LAST);
	
	web_submit_data("login_2", 
		"Action=http://120.26.186.88:8080/user/login", 
		"Method=POST", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t54.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=username", "Value=student", ENDITEM, 
		"Name=password", "Value=123", ENDITEM, 
		EXTRARES, 
		"Url=http://localhost:8090/static/img/3.b06e831.jpg", "Referer=http://localhost:8090/", ENDITEM, 
		LAST);

	return 0;
}
