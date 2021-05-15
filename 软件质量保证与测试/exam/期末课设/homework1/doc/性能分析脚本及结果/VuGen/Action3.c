Action3()
{

	web_url("1.5550d03.jpg", 
		"URL=http://localhost:8090/static/img/1.5550d03.jpg", 
		"Resource=1", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t51.inf", 
		LAST);

	web_url("2.abc6223.jpg", 
		"URL=http://localhost:8090/static/img/2.abc6223.jpg", 
		"Resource=1", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t52.inf", 
		LAST);

	web_url("4.e3ee843.jpg", 
		"URL=http://localhost:8090/static/img/4.e3ee843.jpg", 
		"Resource=1", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t53.inf", 
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

	web_custom_request("listUserById_3", 
		"URL=http://120.26.186.88:8080/user/listUserById", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t55.inf", 
		"Mode=HTML", 
		"EncType=", 
		EXTRARES, 
		"Url=http://localhost:8090/1.js", "Referer=http://localhost:8090/", ENDITEM, 
		LAST);

	web_custom_request("listUserById_4", 
		"URL=http://120.26.186.88:8080/user/listUserById", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t56.inf", 
		"Mode=HTML", 
		"EncType=", 
		LAST);

	web_url("seed", 
		"URL=http://clientservices.googleapis.com/chrome-variations/seed?osname=win&channel=stable&milestone=83", 
		"Resource=0", 
		"Referer=", 
		"Snapshot=t57.inf", 
		"Mode=HTML", 
		LAST);

	web_custom_request("listPublishPaper", 
		"URL=http://120.26.186.88:8080/paper/listPublishPaper", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t58.inf", 
		"Mode=HTML", 
		"EncType=", 
		LAST);

	web_custom_request("listAllNotice_3", 
		"URL=http://120.26.186.88:8080/notice/listAllNotice", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t59.inf", 
		"Mode=HTML", 
		"EncType=", 
		LAST);

	web_custom_request("queryScoreByUser", 
		"URL=http://120.26.186.88:8080/score/queryScoreByUser", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t60.inf", 
		"Mode=HTML", 
		"EncType=", 
		LAST);

	web_submit_data("listWrongById", 
		"Action=http://120.26.186.88:8080/wrong/listWrongById", 
		"Method=POST", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t61.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		EXTRARES, 
		"Url=http://localhost:8090/static/img/Student.67879b3.jpg", "Referer=http://localhost:8090/", ENDITEM, 
		LAST);

	lr_think_time(10);

	web_submit_data("listAllConnect_9", 
		"Action=http://120.26.186.88:8080/connect/listAllConnect", 
		"Method=POST", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t62.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=paperIdStr", "Value=135", ENDITEM, 
		"Name=exerciseTypeStr", "Value=0", ENDITEM, 
		LAST);

	web_submit_data("listAllConnect_10", 
		"Action=http://120.26.186.88:8080/connect/listAllConnect", 
		"Method=POST", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t63.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=paperIdStr", "Value=135", ENDITEM, 
		"Name=exerciseTypeStr", "Value=0", ENDITEM, 
		LAST);

	web_submit_data("listAllConnect_11", 
		"Action=http://120.26.186.88:8080/connect/listAllConnect", 
		"Method=POST", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t64.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=paperIdStr", "Value=135", ENDITEM, 
		"Name=exerciseTypeStr", "Value=1", ENDITEM, 
		LAST);

	web_submit_data("listAllConnect_12", 
		"Action=http://120.26.186.88:8080/connect/listAllConnect", 
		"Method=POST", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t65.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=paperIdStr", "Value=135", ENDITEM, 
		"Name=exerciseTypeStr", "Value=2", ENDITEM, 
		LAST);

	web_submit_data("listAllConnect_13", 
		"Action=http://120.26.186.88:8080/connect/listAllConnect", 
		"Method=POST", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t66.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=paperIdStr", "Value=135", ENDITEM, 
		"Name=exerciseTypeStr", "Value=3", ENDITEM, 
		LAST);

	web_custom_request("queryScoreByUser_2", 
		"URL=http://120.26.186.88:8080/score/queryScoreByUser", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t67.inf", 
		"Mode=HTML", 
		"EncType=", 
		LAST);

	web_submit_data("judgeQuestion", 
		"Action=http://120.26.186.88:8080/paperDetail/judgeQuestion", 
		"Method=POST", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t68.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=jsonString", "Value=[{\"paperId\":135,\"paperDetailId\":181,\"solution\":\"A\"}]", ENDITEM, 
		LAST);

	web_custom_request("queryScoreByUser_3", 
		"URL=http://120.26.186.88:8080/score/queryScoreByUser", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t69.inf", 
		"Mode=HTML", 
		"EncType=", 
		LAST);

	web_submit_data("listWrongById_2", 
		"Action=http://120.26.186.88:8080/wrong/listWrongById", 
		"Method=POST", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t70.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		LAST);

/* Added by Async CodeGen.
ID = Push_0
 */
	web_stop_async("ID=Push_0", 
		LAST);

	lr_start_transaction("1_transaction");

	lr_end_transaction("1_transaction",LR_AUTO);

	lr_start_transaction("2_transaction");

	lr_end_transaction("2_transaction",LR_AUTO);

	lr_start_transaction("3_transaction");

	lr_end_transaction("3_transaction",LR_AUTO);

	return 0;
}