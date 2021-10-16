Action()
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

	web_custom_request("listUserById", 
		"URL=http://120.26.186.88:8080/user/listUserById", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		"EncType=", 
		LAST);

	web_custom_request("listUserById_2", 
		"URL=http://120.26.186.88:8080/user/listUserById", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t6.inf", 
		"Mode=HTML", 
		"EncType=", 
		LAST);

	web_custom_request("listAllPaper", 
		"URL=http://120.26.186.88:8080/paper/listAllPaper", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t7.inf", 
		"Mode=HTML", 
		"EncType=", 
		LAST);

	web_custom_request("listAllPaper_2", 
		"URL=http://120.26.186.88:8080/paper/listAllPaper", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t8.inf", 
		"Mode=HTML", 
		"EncType=", 
		LAST);

	web_custom_request("listAllPaperDetail", 
		"URL=http://120.26.186.88:8080/paperDetail/listAllPaperDetail", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t9.inf", 
		"Mode=HTML", 
		"EncType=", 
		LAST);

	web_custom_request("listAllNotice", 
		"URL=http://120.26.186.88:8080/notice/listAllNotice", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t10.inf", 
		"Mode=HTML", 
		"EncType=", 
		LAST);

	web_custom_request("listAllUser", 
		"URL=http://120.26.186.88:8080/user/listAllUser", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t11.inf", 
		"Mode=HTML", 
		"EncType=", 
		LAST);

	/*Connection ID 0 received buffer WebSocketReceive4*/

	web_custom_request("json", 
		"URL=http://update.googleapis.com/service/update2/json?cup2key=10:4000206003&cup2hreq=cf07e7e2b13eb6c534c8dd2fd15168981e72a33b890d8417c9ba9783507a0b49", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=", 
		"Snapshot=t12.inf", 
		"Mode=HTML", 
		"EncType=application/json", 
		"Body={\"request\":{\"@os\":\"win\",\"@updater\":\"chrome\",\"acceptformat\":\"crx2,crx3\",\"app\":[{\"appid\":\"aemomkdncapdnfajjbbcbdebjljbpmpj\",\"enabled\":true,\"ping\":{\"ping_freshness\":\"{0c8a819c-c51e-4d39-88d5-83c585aabaa9}\",\"rd\":4930},\"updatecheck\":{},\"version\":\"1.0.5.0\"},{\"appid\":\"ehgidpndbllacpjalkiimkbadgjfnnmc\",\"cohort\":\"1:p93:\",\"cohorthint\":\"stable32\",\"cohortname\":\"stable32\",\"enabled\":true,\"packages\":{\"package\":[{\"fp\":\""
		"1.a4811ca3f1d231f2cbb8e5ffbacf475f3364e0a4be162e8758578c76a31ce58f\"}]},\"ping\":{\"ping_freshness\":\"{12caa23b-157b-485e-9ed4-c26453121780}\",\"rd\":4930},\"updatecheck\":{},\"version\":\"2018.7.19.1\"},{\"appid\":\"giekcmmlnklenlaomppkphknjmnnpneh\",\"cohort\":\"1:j5l:\",\"cohorthint\":\"Auto\",\"cohortname\":\"Auto\",\"enabled\":true,\"packages\":{\"package\":[{\"fp\":\"1.3eb16d6c28b502ac4cfee8f4a148df05f4d93229fa36a71db8b08d06329ff18a\"}]},\"ping\":{\"ping_freshness\":\""
		"{d3a4a134-718b-4fbc-8d9c-25c167fb0021}\",\"rd\":4930},\"updatecheck\":{},\"version\":\"7\"},{\"appid\":\"khaoiebndkojlmppeemjhbpbandiljpe\",\"cohort\":\"1:cux:\",\"cohorthint\":\"Auto\",\"cohortname\":\"Auto\",\"enabled\":true,\"packages\":{\"package\":[{\"fp\":\"1.5cb8df53fe2b86bf838ea2c9ffc3d5ef8460f679a779ac8aa924b5afffd052cb\"}]},\"ping\":{\"ping_freshness\":\"{1ee33f62-1b71-4fe9-b0b0-3916de7ba744}\",\"rd\":4930},\"updatecheck\":{},\"version\":\"42\"},{\"appid\":\""
		"llkgjffcdpffmhiakmfcdcblohccpfmo\",\"enabled\":true,\"ping\":{\"ping_freshness\":\"{7d1cf7cf-2192-44da-98cb-5f1e8ccd5542}\",\"rd\":4930},\"updatecheck\":{},\"version\":\"0.0.0.0\"},{\"appid\":\"oimompecagnajdejgnnjijobebaeigek\",\"enabled\":true,\"ping\":{\"ping_freshness\":\"{c516ae1f-5b0a-49b8-9462-0882e405facf}\",\"rd\":4930},\"updatecheck\":{},\"version\":\"4.10.1679.0\"},{\"appid\":\"hnimpnehoodheedghdeeijklkeaacbdc\",\"enabled\":true,\"packages\":{\"package\":[{\"fp\":\""
		"1.6f6bc93dcd62dc251850d2ff458fda96083ceb7fbe8eeb11248b8485ef2aea23\"}]},\"ping\":{\"ping_freshness\":\"{7b6c10d3-dbe5-4b6c-ad05-712de84c4a81}\",\"rd\":4930},\"updatecheck\":{},\"version\":\"0.57.44.2492\"},{\"appid\":\"gkmgaooipdjhmangpemjhigmamcehddo\",\"cohort\":\"1:pw3:\",\"cohorthint\":\"Stable\",\"cohortname\":\"Stable\",\"enabled\":true,\"packages\":{\"package\":[{\"fp\":\"1.86d4ab947598b4c1e45ab37df6055bf0ade111d5a4cc8f3cf076674a8636078e\"}]},\"ping\":{\"ping_freshness\":\""
		"{c54ee0c0-d57c-4a23-8806-6bacb4f8d7a2}\",\"rd\":4930},\"tag\":\"eset_exp_b\",\"updatecheck\":{},\"version\":\"83.238.200\"},{\"appid\":\"gcmjkmgdlgnkkcocmoeiminaijmmjnii\",\"cohort\":\"1:bm1:vs3@0.01,vux@0.1\",\"cohorthint\":\"M54ToM99\",\"cohortname\":\"M54ToM99\",\"enabled\":true,\"packages\":{\"package\":[{\"fp\":\"1.e0ea8f511064e3392d4315f9d2ecd81bfc5056347fe0b34d1e68b4a415599962\"}]},\"ping\":{\"ping_freshness\":\"{5af13618-d597-4194-8e5d-e4d3c2b5d84f}\",\"rd\":4930},\"updatecheck\":{},\""
		"version\":\"9.12.0\"},{\"appid\":\"jflookgnkcckhobaglndicnbbgbonegd\",\"cohort\":\"1:s7x:\",\"cohorthint\":\"Auto\",\"cohortname\":\"Auto\",\"enabled\":true,\"packages\":{\"package\":[{\"fp\":\"1.5ed435e98cc36596f200cdc3fbfdab70b53d5fccfcafe6df9f82e1c54ce85fa8\"}]},\"ping\":{\"ping_freshness\":\"{72e391e2-9600-457e-a429-7258054a9fa8}\",\"rd\":4930},\"updatecheck\":{},\"version\":\"1588\"},{\"appid\":\"mimojjlkmoijpicakmndhoigimigcmbb\",\"cohort\":\"1:d0j:\",\"cohorthint\":\"Chrome [M50+]\",\""
		"cohortname\":\"Chrome [M50+]\",\"enabled\":true,\"packages\":{\"package\":[{\"fp\":\"1.0adf77f9e53641b2754c1f27a07852004aca1f69b8c62f91bd21078bb6bb95d0\"}]},\"ping\":{\"ping_freshness\":\"{0f3074be-c60c-4f20-a944-a3b54d9c8799}\",\"rd\":4930},\"updatecheck\":{},\"version\":\"32.0.0.387\"},{\"appid\":\"bklopemakmnopmghhmccadeonafabnal\",\"cohort\":\"1:swl:\",\"cohorthint\":\"Auto\",\"cohortname\":\"Auto\",\"enabled\":true,\"packages\":{\"package\":[{\"fp\":\""
		"1.6dce22b9a11fa1e62b22559c4a157ce745e7fc63c6c6941a82cf11e8ecf65b0e\"}]},\"ping\":{\"ping_freshness\":\"{ba12a979-7d7f-4905-910a-703907cc6044}\",\"rd\":4930},\"updatecheck\":{},\"version\":\"3\"},{\"appid\":\"copjbmjbojbakpaedmpkhmiplmmehfck\",\"cohort\":\"1:p1x:\",\"cohorthint\":\"Auto\",\"cohortname\":\"Auto\",\"enabled\":true,\"packages\":{\"package\":[{\"fp\":\"1.207921137eee9c0831e0bd890330986c10dfd9382034491b82de3f86ae6915f7\"}]},\"ping\":{\"ping_freshness\":\""
		"{267e83d0-0007-4401-a975-995a7ae1a6f5}\",\"rd\":4930},\"updatecheck\":{},\"version\":\"2018.9.6.0\"},{\"appid\":\"hfnkpimlhhgieaddgfemjhofmfblmnib\",\"cohort\":\"1:jcl:\",\"cohorthint\":\"Auto\",\"cohortname\":\"Auto\",\"enabled\":true,\"packages\":{\"package\":[{\"fp\":\"1.89a623a8740557ed0f2d5577c3513f564dcdc8573331146c236d9d09c25c27be\"}]},\"ping\":{\"ping_freshness\":\"{e4bd31b8-c220-476c-b2ed-8f0acd2eca5c}\",\"rd\":4930},\"updatecheck\":{},\"version\":\"5968\"},{\"appid\":\""
		"ggkkehgbnfjpeggfpleeakpidbkibbmn\",\"cohort\":\"1:ut9:vt9@0.01\",\"cohorthint\":\"M80ToM89\",\"cohortname\":\"M80ToM89\",\"enabled\":true,\"packages\":{\"package\":[{\"fp\":\"1.e6f203ab40ebd41a8f90958689a574828dfb977ce12183c0ff648113061fc370\"}]},\"ping\":{\"ping_freshness\":\"{1dcbc794-4988-46e8-8905-7de6d42e0adc}\",\"rd\":4930},\"updatecheck\":{},\"version\":\"2020.6.14.1142\"},{\"appid\":\"ihnlcenocehgdaegdmhbidjhnhdchfmm\",\"enabled\":true,\"ping\":{\"ping_freshness\":\""
		"{44c5ab78-72f3-4703-9b73-5a1537bac027}\",\"rd\":4930},\"updatecheck\":{},\"version\":\"0.0.0.0\"}],\"arch\":\"x86\",\"dedup\":\"cr\",\"domainjoined\":false,\"hw\":{\"physmemory\":4},\"lang\":\"zh-CN\",\"nacl_arch\":\"x86-64\",\"os\":{\"arch\":\"x86_64\",\"platform\":\"Windows\",\"version\":\"10.0.18362.900\"},\"prodversion\":\"83.0.4103.116\",\"protocol\":\"3.1\",\"requestid\":\"{68d5a5a1-ccf0-4258-b985-842b8ebf296d}\",\"sessionid\":\"{c36eb8f6-db71-43b3-8239-d4c86ec53f37}\",\"updater\":{\""
		"autoupdatecheckenabled\":true,\"ismachine\":true,\"name\":\"Omaha\",\"updatepolicy\":-1},\"updaterversion\":\"83.0.4103.116\",\"wow64\":true}}", 
		LAST);
	
	/*Connection ID 0 received buffer WebSocketReceive5*/

	lr_start_transaction("1_transaction");

	/*Connection ID 0 received buffer WebSocketReceive6*/

	web_submit_data("queryPaperName", 
		"Action=http://120.26.186.88:8080/paper/queryPaperName", 
		"Method=POST", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t13.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=keyStr", "Value=软件质量保证与测试小练习1", ENDITEM, 
		LAST);

	lr_end_transaction("1_transaction",LR_AUTO);

	lr_start_transaction("2_transaction");

	lr_end_transaction("2_transaction",LR_AUTO);

	lr_start_transaction("3_transaction");

	web_submit_data("addNotice", 
		"Action=http://120.26.186.88:8080/notice/addNotice", 
		"Method=POST", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t14.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=title", "Value=公告测试test1", ENDITEM, 
		"Name=content", "Value=公告测试test1", ENDITEM, 
		LAST);

	web_custom_request("listAllNotice_2", 
		"URL=http://120.26.186.88:8080/notice/listAllNotice", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t15.inf", 
		"Mode=HTML", 
		"EncType=", 
		LAST);

	lr_end_transaction("3_transaction",LR_AUTO);

	lr_think_time(9);

	lr_start_transaction("4_transaction");

	web_submit_data("queryScoreByPaper", 
		"Action=http://120.26.186.88:8080/score/queryScoreByPaper", 
		"Method=POST", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t16.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=paperIdStr", "Value=1", ENDITEM, 
		LAST);

	web_submit_data("listScoreByMark1", 
		"Action=http://120.26.186.88:8080/score/listScoreByMark1", 
		"Method=POST", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t17.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=paperIdStr", "Value=1", ENDITEM, 
		LAST);

	lr_end_transaction("4_transaction",LR_AUTO);

	lr_start_transaction("5_transaction");

	lr_end_transaction("5_transaction",LR_AUTO);

	return 0;
}