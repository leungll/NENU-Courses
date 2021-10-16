/*
  路由模块
*/
import Vue from 'vue'
import VueRouter from 'vue-router'
VueRouter.prototype.goBack = function () {
  this.isBack = true;
  window.history.go(-1)
};
// 引入路由组件文件夹下的组件
import Login from '@/pages/Login/Login.vue'
import admin from '@/pages/Admin/admin.vue'
import Teacher from '@/pages/Teacher/Teacher.vue'

// 路由组件懒加载
const Home = () => import('@/pages/Home/Home.vue')
const Profile = () => import('@/pages/Profile/Profile.vue')

Vue.use(VueRouter)

// 配置路由表并导出
export default new VueRouter({
  //  去掉地址中的哈希#
  // mode: 'history',
  routes: [
    {
      path: '/',
      redirect: '/home'
    },
    {
      path: '/home',
      name:'Home',
      component: Home,
      // 此时的Home等都是返回路由组件的函数，只有请求对应的路由路径时(第一次)才会执行此函数并加载路由组件
      // 标识此路由是否显示FooterGuide
      meta: {
        showFooter: true
      }
    },
    {
      path:'/admin',
      component:admin
    },
    {
      path:'/Teacher',
      component:Teacher
    },

    {
      path:'/Profile',
      name:'Profile',
      component:Profile,
      meta: {
        showFooter: true
      }
    },

    {
      path: '/login',
      name:'Login',
      component: Login
    }
  ]
})
