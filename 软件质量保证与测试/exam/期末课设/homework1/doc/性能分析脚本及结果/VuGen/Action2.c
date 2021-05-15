Action2()
{

	web_url("localhost:8090", 
		"URL=http://localhost:8090/", 
		"Resource=0", 
		"Referer=", 
		"Snapshot=t18.inf", 
		"Mode=HTML", 
		EXTRARES, 
		"Url=/static/css/animate.min.css", ENDITEM, 
		"Url=/static/css/reset.css", ENDITEM, 
		"Url=/app.js", ENDITEM, 
		"Url=/static/img/js.f38f3a7.png", ENDITEM, 
		"Url=/sockjs-node/info?t=1593653069191", ENDITEM, 
		"Url=/static/fonts/element-icons.535877f.woff", ENDITEM, 
		"Url=/static/img/Teacher.641aa10.jpg", ENDITEM, 
		LAST);

/* Added by Async CodeGen.
ID=Push_0
ScanType = Recording

The following URLs are considered part of this conversation:
	http://localhost:8090/sockjs-node/225/bmzrxgfs/xhr_streaming?t=1593653075818

TODO - The following callbacks have been added to AsyncCallbacks.c.
Add your code to the callback implementations as necessary.
	Push_0_RequestCB
	Push_0_ResponseHeadersCB
	Push_0_ResponseBodyBufferCB
	Push_0_ResponseCB
 */
	web_reg_async_attributes("ID=Push_0", 
		"Pattern=Push", 
		"URL=http://localhost:8090/sockjs-node/225/bmzrxgfs/xhr_streaming?t=1593653075818", 
		"RequestCB=Push_0_RequestCB", 
		"ResponseHeadersCB=Push_0_ResponseHeadersCB", 
		"ResponseBodyBufferCB=Push_0_ResponseBodyBufferCB", 
		"ResponseCB=Push_0_ResponseCB", 
		LAST);

	web_custom_request("xhr_streaming", 
		"URL=http://localhost:8090/sockjs-node/225/bmzrxgfs/xhr_streaming?t=1593653075818", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=application/javascript", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t19.inf", 
		"Mode=HTML", 
		"EncType=", 
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

	web_custom_request("listUserById", 
		"URL=http://120.26.186.88:8080/user/listUserById", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t21.inf", 
		"Mode=HTML", 
		"EncType=", 
		LAST);

	web_custom_request("listUserById_2", 
		"URL=http://120.26.186.88:8080/user/listUserById", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t22.inf", 
		"Mode=HTML", 
		"EncType=", 
		LAST);

	web_custom_request("listAllPaper", 
		"URL=http://120.26.186.88:8080/paper/listAllPaper", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t23.inf", 
		"Mode=HTML", 
		"EncType=", 
		LAST);

	web_custom_request("listAllPaperDetail", 
		"URL=http://120.26.186.88:8080/paperDetail/listAllPaperDetail", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t24.inf", 
		"Mode=HTML", 
		"EncType=", 
		LAST);

	web_custom_request("listAllPaper_2", 
		"URL=http://120.26.186.88:8080/paper/listAllPaper", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t25.inf", 
		"Mode=HTML", 
		"EncType=", 
		LAST);

	web_custom_request("listAllNotice", 
		"URL=http://120.26.186.88:8080/notice/listAllNotice", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t26.inf", 
		"Mode=HTML", 
		"EncType=", 
		LAST);

	lr_start_transaction("1_transaction");

	web_custom_request("json", 
		"URL=http://update.googleapis.com/service/update2/json?cup2key=10:1726821574&cup2hreq=b0c8b036464b792c90e3687e7e3627e788ef5453990520c7ae1c3805b6cf1659", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=", 
		"Snapshot=t27.inf", 
		"Mode=HTML", 
		"EncType=application/json", 
		"Body={\"request\":{\"@os\":\"win\",\"@updater\":\"chrome\",\"acceptformat\":\"crx2,crx3\",\"app\":[{\"appid\":\"ihnlcenocehgdaegdmhbidjhnhdchfmm\",\"enabled\":true,\"ping\":{\"ping_freshness\":\"{babfea96-1389-45a4-a925-c3f54c877ff2}\",\"rd\":4930},\"updatecheck\":{},\"version\":\"0.0.0.0\"},{\"appid\":\"llkgjffcdpffmhiakmfcdcblohccpfmo\",\"enabled\":true,\"ping\":{\"ping_freshness\":\"{51c412ce-63b3-4607-90a8-72344e6ed7d1}\",\"rd\":4930},\"updatecheck\":{},\"version\":\"0.0.0.0\"},{\"appid\":\""
		"oimompecagnajdejgnnjijobebaeigek\",\"enabled\":true,\"ping\":{\"ping_freshness\":\"{b36dd32c-83a7-4703-8ae9-c2437cbe955c}\",\"rd\":4930},\"updatecheck\":{},\"version\":\"4.10.1679.0\"},{\"appid\":\"copjbmjbojbakpaedmpkhmiplmmehfck\",\"cohort\":\"1:p1x:\",\"cohorthint\":\"Auto\",\"cohortname\":\"Auto\",\"enabled\":true,\"packages\":{\"package\":[{\"fp\":\"1.207921137eee9c0831e0bd890330986c10dfd9382034491b82de3f86ae6915f7\"}]},\"ping\":{\"ping_freshness\":\"{c66058fb-5bd3-43ff-99e2-75dd57a847b3}\","
		"\"rd\":4930},\"updatecheck\":{},\"version\":\"2018.9.6.0\"},{\"appid\":\"hfnkpimlhhgieaddgfemjhofmfblmnib\",\"cohort\":\"1:jcl:\",\"cohorthint\":\"Auto\",\"cohortname\":\"Auto\",\"enabled\":true,\"packages\":{\"package\":[{\"fp\":\"1.89a623a8740557ed0f2d5577c3513f564dcdc8573331146c236d9d09c25c27be\"}]},\"ping\":{\"ping_freshness\":\"{7413f976-6d4b-4bfb-9a36-8a1d135e631f}\",\"rd\":4930},\"updatecheck\":{},\"version\":\"5968\"},{\"appid\":\"gkmgaooipdjhmangpemjhigmamcehddo\",\"cohort\":\"1:pw3:\",\""
		"cohorthint\":\"Stable\",\"cohortname\":\"Stable\",\"enabled\":true,\"packages\":{\"package\":[{\"fp\":\"1.86d4ab947598b4c1e45ab37df6055bf0ade111d5a4cc8f3cf076674a8636078e\"}]},\"ping\":{\"ping_freshness\":\"{5fb7a9d5-e1b8-4cb8-a4ef-669bc5e18708}\",\"rd\":4930},\"tag\":\"eset_exp_b\",\"updatecheck\":{},\"version\":\"83.238.200\"},{\"appid\":\"bklopemakmnopmghhmccadeonafabnal\",\"cohort\":\"1:swl:\",\"cohorthint\":\"Auto\",\"cohortname\":\"Auto\",\"enabled\":true,\"packages\":{\"package\":[{\"fp\":"
		"\"1.6dce22b9a11fa1e62b22559c4a157ce745e7fc63c6c6941a82cf11e8ecf65b0e\"}]},\"ping\":{\"ping_freshness\":\"{38a4b949-ee6c-48dc-b15c-20818b5bf1b2}\",\"rd\":4930},\"updatecheck\":{},\"version\":\"3\"},{\"appid\":\"aemomkdncapdnfajjbbcbdebjljbpmpj\",\"enabled\":true,\"ping\":{\"ping_freshness\":\"{9aa0e9e8-73e6-4b41-b96b-3fba54f08367}\",\"rd\":4930},\"updatecheck\":{},\"version\":\"1.0.5.0\"},{\"appid\":\"hnimpnehoodheedghdeeijklkeaacbdc\",\"enabled\":true,\"packages\":{\"package\":[{\"fp\":\""
		"1.6f6bc93dcd62dc251850d2ff458fda96083ceb7fbe8eeb11248b8485ef2aea23\"}]},\"ping\":{\"ping_freshness\":\"{d6ad11b7-8cee-4ec2-814a-5e329f5b4381}\",\"rd\":4930},\"updatecheck\":{},\"version\":\"0.57.44.2492\"},{\"appid\":\"giekcmmlnklenlaomppkphknjmnnpneh\",\"cohort\":\"1:j5l:\",\"cohorthint\":\"Auto\",\"cohortname\":\"Auto\",\"enabled\":true,\"packages\":{\"package\":[{\"fp\":\"1.3eb16d6c28b502ac4cfee8f4a148df05f4d93229fa36a71db8b08d06329ff18a\"}]},\"ping\":{\"ping_freshness\":\""
		"{3872aa83-787e-448c-b8c4-5c8b0e37533a}\",\"rd\":4930},\"updatecheck\":{},\"version\":\"7\"},{\"appid\":\"khaoiebndkojlmppeemjhbpbandiljpe\",\"cohort\":\"1:cux:\",\"cohorthint\":\"Auto\",\"cohortname\":\"Auto\",\"enabled\":true,\"packages\":{\"package\":[{\"fp\":\"1.5cb8df53fe2b86bf838ea2c9ffc3d5ef8460f679a779ac8aa924b5afffd052cb\"}]},\"ping\":{\"ping_freshness\":\"{040df496-8380-46ec-8ec1-ff26d59e3303}\",\"rd\":4930},\"updatecheck\":{},\"version\":\"42\"},{\"appid\":\""
		"jflookgnkcckhobaglndicnbbgbonegd\",\"cohort\":\"1:s7x:\",\"cohorthint\":\"Auto\",\"cohortname\":\"Auto\",\"enabled\":true,\"packages\":{\"package\":[{\"fp\":\"1.5ed435e98cc36596f200cdc3fbfdab70b53d5fccfcafe6df9f82e1c54ce85fa8\"}]},\"ping\":{\"ping_freshness\":\"{76fa6d01-8313-4ab3-bdd8-dcf86c60bf9e}\",\"rd\":4930},\"updatecheck\":{},\"version\":\"1588\"},{\"appid\":\"mimojjlkmoijpicakmndhoigimigcmbb\",\"cohort\":\"1:d0j:\",\"cohorthint\":\"Chrome [M50+]\",\"cohortname\":\"Chrome [M50+]\",\""
		"enabled\":true,\"packages\":{\"package\":[{\"fp\":\"1.0adf77f9e53641b2754c1f27a07852004aca1f69b8c62f91bd21078bb6bb95d0\"}]},\"ping\":{\"ping_freshness\":\"{88505494-4694-4664-b2e8-d4acc3ed3648}\",\"rd\":4930},\"updatecheck\":{},\"version\":\"32.0.0.387\"},{\"appid\":\"gcmjkmgdlgnkkcocmoeiminaijmmjnii\",\"cohort\":\"1:bm1:vs3@0.01,vux@0.1\",\"cohorthint\":\"M54ToM99\",\"cohortname\":\"M54ToM99\",\"enabled\":true,\"packages\":{\"package\":[{\"fp\":\""
		"1.e0ea8f511064e3392d4315f9d2ecd81bfc5056347fe0b34d1e68b4a415599962\"}]},\"ping\":{\"ping_freshness\":\"{f10f1105-fcad-4232-a835-7f1b56820245}\",\"rd\":4930},\"updatecheck\":{},\"version\":\"9.12.0\"},{\"appid\":\"ggkkehgbnfjpeggfpleeakpidbkibbmn\",\"cohort\":\"1:ut9:vt9@0.01\",\"cohorthint\":\"M80ToM89\",\"cohortname\":\"M80ToM89\",\"enabled\":true,\"packages\":{\"package\":[{\"fp\":\"1.e6f203ab40ebd41a8f90958689a574828dfb977ce12183c0ff648113061fc370\"}]},\"ping\":{\"ping_freshness\":\""
		"{6dec09b5-82ed-46f3-8448-ed3527fe8505}\",\"rd\":4930},\"updatecheck\":{},\"version\":\"2020.6.14.1142\"},{\"appid\":\"ehgidpndbllacpjalkiimkbadgjfnnmc\",\"cohort\":\"1:p93:\",\"cohorthint\":\"stable32\",\"cohortname\":\"stable32\",\"enabled\":true,\"packages\":{\"package\":[{\"fp\":\"1.a4811ca3f1d231f2cbb8e5ffbacf475f3364e0a4be162e8758578c76a31ce58f\"}]},\"ping\":{\"ping_freshness\":\"{42632a03-2baf-45fc-b557-2f732c123603}\",\"rd\":4930},\"updatecheck\":{},\"version\":\"2018.7.19.1\"}],\"arch\":\""
		"x86\",\"dedup\":\"cr\",\"domainjoined\":false,\"hw\":{\"physmemory\":4},\"lang\":\"zh-CN\",\"nacl_arch\":\"x86-64\",\"os\":{\"arch\":\"x86_64\",\"platform\":\"Windows\",\"version\":\"10.0.18362.900\"},\"prodversion\":\"83.0.4103.116\",\"protocol\":\"3.1\",\"requestid\":\"{9975befb-9189-4d24-aef1-f260376d49db}\",\"sessionid\":\"{b08fe13e-b4e5-4314-af03-d86d5cb905fa}\",\"updater\":{\"autoupdatecheckenabled\":true,\"ismachine\":true,\"name\":\"Omaha\",\"updatepolicy\":-1},\"updaterversion\":\""
		"83.0.4103.116\",\"wow64\":true}}", 
		LAST);

	lr_think_time(8);

	web_submit_data("queryPaperName", 
		"Action=http://120.26.186.88:8080/paper/queryPaperName", 
		"Method=POST", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t28.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=keyStr", "Value=软件质量保证与测试小练习1", ENDITEM, 
		LAST);

	lr_end_transaction("1_transaction",LR_AUTO);

	web_submit_data("queryPaperName_2", 
		"Action=http://120.26.186.88:8080/paper/queryPaperName", 
		"Method=POST", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t29.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=keyStr", "Value=", ENDITEM, 
		LAST);

	lr_think_time(12);

	lr_start_transaction("2_transaction");

	web_submit_data("addPaper", 
		"Action=http://120.26.186.88:8080/paper/addPaper", 
		"Method=POST", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t30.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=paperName", "Value=手动录入测试1", ENDITEM, 
		LAST);

	web_submit_data("listAllConnect", 
		"Action=http://120.26.186.88:8080/connect/listAllConnect", 
		"Method=POST", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t31.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=paperIdStr", "Value=135", ENDITEM, 
		"Name=exerciseTypeStr", "Value=0", ENDITEM, 
		LAST);

	web_submit_data("listAllConnect_2", 
		"Action=http://120.26.186.88:8080/connect/listAllConnect", 
		"Method=POST", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t32.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=paperIdStr", "Value=135", ENDITEM, 
		"Name=exerciseTypeStr", "Value=1", ENDITEM, 
		LAST);

	web_submit_data("listAllConnect_3", 
		"Action=http://120.26.186.88:8080/connect/listAllConnect", 
		"Method=POST", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t33.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=paperIdStr", "Value=135", ENDITEM, 
		"Name=exerciseTypeStr", "Value=2", ENDITEM, 
		LAST);

	web_submit_data("listAllConnect_4", 
		"Action=http://120.26.186.88:8080/connect/listAllConnect", 
		"Method=POST", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t34.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=paperIdStr", "Value=135", ENDITEM, 
		"Name=exerciseTypeStr", "Value=3", ENDITEM, 
		LAST);

	web_submit_data("addPaperDetail", 
		"Action=http://120.26.186.88:8080/paperDetail/addPaperDetail", 
		"Method=POST", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t35.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=paperIdStr", "Value=135", ENDITEM, 
		"Name=exerciseTypeStr", "Value=0", ENDITEM, 
		"Name=contentStr", "Value=测试", ENDITEM, 
		"Name=typeAStr", "Value=A", ENDITEM, 
		"Name=typeBStr", "Value=B", ENDITEM, 
		"Name=typeCStr", "Value=C", ENDITEM, 
		"Name=typeDStr", "Value=D", ENDITEM, 
		"Name=answerStr", "Value=A", ENDITEM, 
		"Name=answer2", "Value=这个字段为空", ENDITEM, 
		"Name=answer3", "Value=这个字段为空", ENDITEM, 
		"Name=scoreStr", "Value=10", ENDITEM, 
		LAST);

	web_submit_data("addConnect", 
		"Action=http://120.26.186.88:8080/connect/addConnect", 
		"Method=POST", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t36.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=paperIdStr", "Value=135", ENDITEM, 
		"Name=paperDetailIdStr", "Value=181", ENDITEM, 
		LAST);

	web_submit_data("listAllConnect_5", 
		"Action=http://120.26.186.88:8080/connect/listAllConnect", 
		"Method=POST", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t37.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=paperIdStr", "Value=135", ENDITEM, 
		"Name=exerciseTypeStr", "Value=0", ENDITEM, 
		LAST);

	web_submit_data("listAllConnect_6", 
		"Action=http://120.26.186.88:8080/connect/listAllConnect", 
		"Method=POST", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t38.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=paperIdStr", "Value=135", ENDITEM, 
		"Name=exerciseTypeStr", "Value=1", ENDITEM, 
		LAST);

	web_submit_data("listAllConnect_7", 
		"Action=http://120.26.186.88:8080/connect/listAllConnect", 
		"Method=POST", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t39.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=paperIdStr", "Value=135", ENDITEM, 
		"Name=exerciseTypeStr", "Value=2", ENDITEM, 
		LAST);

	web_submit_data("listAllConnect_8", 
		"Action=http://120.26.186.88:8080/connect/listAllConnect", 
		"Method=POST", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t40.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=paperIdStr", "Value=135", ENDITEM, 
		"Name=exerciseTypeStr", "Value=3", ENDITEM, 
		LAST);

	lr_think_time(5);

	web_submit_data("publishPaper", 
		"Action=http://120.26.186.88:8080/paper/publishPaper?paperIdStr=135&beginTime=%E5%BC%80%E5%A7%8B:2020%E5%B9%B407%E6%9C%8802%E6%97%A509%E6%97%B626%E5%88%8648%E7%A7%92&endTime=%E7%BB%93%E6%9D%9F:2020%E5%B9%B407%E6%9C%8803%E6%97%A509%E6%97%B626%E5%88%8653%E7%A7%92&duration=2", 
		"Method=POST", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t41.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		LAST);

	web_custom_request("listAllPaperDetail_2", 
		"URL=http://120.26.186.88:8080/paperDetail/listAllPaperDetail", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t42.inf", 
		"Mode=HTML", 
		"EncType=", 
		LAST);

	web_custom_request("listAllPaper_3", 
		"URL=http://120.26.186.88:8080/paper/listAllPaper", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t43.inf", 
		"Mode=HTML", 
		"EncType=", 
		LAST);

	lr_end_transaction("2_transaction",LR_AUTO);

	lr_start_transaction("3_transaction");

	lr_end_transaction("3_transaction",LR_AUTO);

	lr_start_transaction("4_transaction");

	web_submit_data("addPaperDetail_2", 
		"Action=http://120.26.186.88:8080/paperDetail/addPaperDetail", 
		"Method=POST", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t44.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=exerciseTypeStr", "Value=0", ENDITEM, 
		"Name=contentStr", "Value=测试2", ENDITEM, 
		"Name=typeAStr", "Value=A", ENDITEM, 
		"Name=typeBStr", "Value=B", ENDITEM, 
		"Name=typeCStr", "Value=C", ENDITEM, 
		"Name=typeDStr", "Value=D", ENDITEM, 
		"Name=answerStr", "Value=A", ENDITEM, 
		"Name=answer2", "Value=这个字段为空", ENDITEM, 
		"Name=answer3", "Value=这个字段为空", ENDITEM, 
		"Name=scoreStr", "Value=10", ENDITEM, 
		LAST);

	web_custom_request("listAllPaperDetail_3", 
		"URL=http://120.26.186.88:8080/paperDetail/listAllPaperDetail", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t45.inf", 
		"Mode=HTML", 
		"EncType=", 
		LAST);

	lr_end_transaction("4_transaction",LR_AUTO);

	lr_start_transaction("5_transaction");

	web_submit_data("addNotice", 
		"Action=http://120.26.186.88:8080/notice/addNotice", 
		"Method=POST", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t46.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=title", "Value=公告测试test2", ENDITEM, 
		"Name=content", "Value=公告测试test2", ENDITEM, 
		LAST);

	web_custom_request("listAllNotice_2", 
		"URL=http://120.26.186.88:8080/notice/listAllNotice", 
		"Method=POST", 
		"Resource=0", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t47.inf", 
		"Mode=HTML", 
		"EncType=", 
		LAST);

	lr_end_transaction("5_transaction",LR_AUTO);

	lr_start_transaction("6_transaction");

	web_submit_data("queryScoreByPaper", 
		"Action=http://120.26.186.88:8080/score/queryScoreByPaper", 
		"Method=POST", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t48.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=paperIdStr", "Value=1", ENDITEM, 
		LAST);

	web_submit_data("listScoreByMark1", 
		"Action=http://120.26.186.88:8080/score/listScoreByMark1", 
		"Method=POST", 
		"RecContentType=application/json", 
		"Referer=http://localhost:8090/", 
		"Snapshot=t49.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=paperIdStr", "Value=1", ENDITEM, 
		LAST);

	lr_end_transaction("6_transaction",LR_AUTO);

	return 0;
}
