(function(){

    var site ={
        website: 'http://vmsystem/', //站点地址
        staticWebsite: 'http://vmsystem/',// 前端服务器地址
        //staticWebsite: 'http://static.jy.nenu.edu.net/', // 前端服务器地址
        puiWebsite: 'http://pui.pandawork.net/1.1/' //pui地址
        // //website: 'http://jyp:88/', //站点地址
        // website:'http://jyoa.nenu.edu.net/',
        // //staticWebsite: 'http://jyp:88/',
        // staticWebsite: 'http://jyoa.nenu.edu.net/resources/', // 前端服务器地址
        // puiWebsite: 'http://jyoa.nenu.edu.net/resources/pui/' //pui地址
    }

    _pw_env = {
        status: 0, //0-前端调试，1-后端调试, 2-后端部署
        website: site.website,
        staticWebsite: site.staticWebsite,
        puiWebsite: site.puiWebsite,
        tag: '',
        pkgs:[
            {
                name: 'io',
                path: site.staticWebsite + 'resources/js/'
            },
            {
                name: 'module',
                path: site.staticWebsite + 'resources/js/'
            },
            {
                name: 'page',
                path: site.staticWebsite + 'resources/js/'
            },
            {
                name: 'common',
                path: site.staticWebsite+'resources/js/page'
            }
        ],
        preload: ['sizzle'],//预加载模块
        //对pui各个组件的一个
        modSettings:{
            notifier: {
                top: 100
            },
            dialog:{
                //opacity: 0.5,//ie8下dialog显示不正常
                position: 'fixed',
                themeUrl: site.staticWebsite + 'resources/css/widget/core.css'
            },
            ztree:{
                themeUrl: site.staticWebsite + 'resources/css/widget/core.css'
            },
            defender:{
                themeUrl: site.staticWebsite + 'resources/css/widget/core.css'  
            },
            scroll:{
                cursorborderradius: 0,
                cursorcolor: '#3d3d3d'
            },
            tooltip:{
                position: { 
                    my: 'tc',
                    at: 'bc' //options: tl,tc,tr, rt,rc,rb, bl,bc,br,lt,lc,lb 
                },
                styles:{
                    uri: site.staticWebsite + 'resources/css/widget/core.css'  
                }
            }
        },
        //统一错误信息
        msg:{
        },
        //统一路径位置
        url:{
            module:{
                company:{
                    getCompany:site.website+'reception/ajax/company'
                },
                linkage:{
                    getCity:site.website+'company/ajax/companyPlace/query'
                },
                select:{
                    getOption:site.website+'recruit/ajax/getSelectList'					
                    //getOption:site.website+'test/api-data/005.json'
                }
            }
            // recruit:{
            //     need:{
            //         add:site.website+'recruit/jobRequest/ajax/add',
            //         del:site.website+'recruit/jobRequest/ajax'
            //     },
            //     visitor:{
            //         add:site.website+'recruit/view/ajax/add',
            //         del:site.website+'recruit/view/ajax',
            //         getContact:site.website+'contact/ajax/telphone',
            //         getLeader:site.website+'contact/ajax/grade'
            //     },
            //     recruit:{
            //         valid:site.website+'recruit/ajax/timePlaceConflict',
            //         delBatch:site.website+'recruit/ajax/del',
            //         enter:site.website+'recruit/enter'
            //     },
            //     interview:{
            //         valid:site.website+'recruit/interview/ajax/timePlaceConflict',
            //         del:site.website+'recruit/ajax/'
            //     },
            //     written:{
            //         valid:site.website+'recruit/written/ajax/timePlaceConflict',
            //         del:site.website+'recruit/ajax/'
            //     },
            //     lecture:{
            //         load:site.website+'recruit/lecture/ajax/graph',
            //         add:site.website+'recruit/lecture/ajax/saveAmbassador',
            //         // addVisitor:site.website+'/test/api-data/030.json',
            //         // editVisitor:site.website+'/test/api-data/030.json',
            //         // delVisitor:site.website+'/test/api-data/030.json'
            //         addVisitor:site.website+'recruit/ajax/visitor/add',
            //         editVisitor:site.website+'recruit/ajax/visitor/update',
            //         delVisitor:site.website+'recruit/ajax/visitor'
            //     },
            //     space:{
            //         load:site.website+'recruit/space/ajax/graph'
            //     }
            // },
            // banquet:{
            //     select:{
            //         attendee:site.website+'feast/ajax/getPersonList',
            //         contact:site.website+'feast/ajax/getPersonList',
            //         getUser:site.website+'feast/getQuickFeastLeader'
            //     },
            //     feast:{
            //         //con:site.website+'/feast/generalOfficeNew/check',
            //         //communication:site.website+'/test/api-data/031.json'
            //         communication:site.website+'/feast/generalOfficeNew/check'
            //     }
            // },
            // company:{
            //     companyInfo:{
            //         addConnecter:site.website+'contact/ajax/add',
            //         delConnecter:site.website+'contact/ajax',
            //         delBatch:site.website+'company/ajax/del'
            //     },
            //     contact:{
            //         add:site.website+'contact/ajax/add',
            //         del:site.website+'contact/ajax/del',
            //         mod:site.website+'contact/ajax/update',
            //         getContact:site.website+'contact/ajax/update'
            //     }
            // },
            // reception:{
            //     vehicle:{
            //         delBatch:site.website+'reception/ajax/car/batchdel'
            //     },
            //     hotel:{
            //         delBatch:site.website+'reception/ajax/hotel/batchdel'
            //     }
            // },
            // system:{
            //     user:{
            //         lock:site.website+'user/lock',
            //         unlock:site.website+'user/unlock',
            //         delBatch:site.website+'user/del',
            //         addValid:site.website+'user/add/isExist',
            //         modValid:site.website+'user/update/isExist'
            //     },
            //     place:{
            //         del:site.website+'place/ajax/del',
            //         nameValid:site.website+'place/add/isExist'
            //     }
            // },
            // Index:{
            //     getInfo:site.website+'index/ajax/time',
            //     getLectureDate:site.website+'recruit/index/getRecruitDateInMonth',
            //     //getLectureDate:site.website+'test/api-data/028.json'
            //     message:{
            //         del:site.website+'message/ajax/delete',
            //         handle:site.website+'message/ajax/handle',
            //         // get:site.website+'test/api-data/005.json',
            //         get:site.website+'user/role/list',
            //         send:site.website+'message/insert/batch'
            //     }
            // }
        }
    }
})()