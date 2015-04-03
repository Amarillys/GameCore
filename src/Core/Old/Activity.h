#ifndef _HEAD_ACTIVITY_
#define _HEAD_ACTIVITY_

#include <set>
#include <map>
#include "SDLbase.h"
#include "Layer.h"
#include "View.h"
#include "Animation.h"
#include "Control.h"


/* Activity 概念介绍 */
/*
活动（Activity）相当于一个独立的界面，该界面包含以下内容：
1.UI
2.可以操作的控件
3.控件回调函数，有控件相应你的操作时，由控件先处理消息进行控件响应，然后再传给活动
4.默认回调函数，当你的操作没有控件响应时，直接传给该函数处理。
5.动画

关于控件：
属于Control的基类，其ID就是地址值。
要使用一个控件，需要先创建它的子类以响应各种操作，
然后把它在Activity类中实例化，再把它安装到活动中。

如果收到操作，会先判断当前点击\触摸位置是否在控件上，
如果在，则调用控件的回调函数，并且由该回调函数调用Activity的控件回调函数。

关于动画：
和控件一样，也是安装机制。

创建一个Activity只需要创建其子类即可。
关于视图树，参见View.h
*/

namespace Core{
    class Activity: public Layer    //活动基类
    {
    private:
        static std::list<Activity*> m_actStack; //活动栈

        std::set<Animation *> m_heapAnimations; //堆中的动画对象，完成后释放
        std::set<Animation *> m_stackAnimations; //栈中的动画对象
        std::set<Control *> m_controls;  //已经安装的控件
        bool m_fullScreen;  //是否全屏，该属性非常重要，将会影响活动栈绘制深度
    protected:
        void InstallControl(Control *); //安装控件
        void UninstallControl(Control *);   //卸载控件
        void UninstallAllControl(Control *);    //卸载所有控件
        void InstallAnimation(Animation *); //安装栈中的动画
        void NewAnimation(Animation *);
        //在堆中创建动画，完成后丢弃，NewAnimation(new Animation())

        void StopAnimation(Animation *);    //停止指定动画，并卸载
        void StopAllAnimation();    //停止所有动画并卸载
        void AnimationNext();   //通知所有动画准备下一帧
    public:
        static void APush(Activity*);   //后置当前活动，向活动栈压入新活动
        static void APop(); //弹出当前活动，从活动栈激活上个活动
        static void AGoto(Activity*);    //弹出当前活动，跳转到目标活动
        static void AClear();   //保留当前活动，销毁栈顶下面的所有活动
        static Activity* ATop(); //取得当前活动指针
        static void ADraw();    //从全屏活动开始绘制到当前活动

        virtual void OnFocus(){}; //前置活动时
        virtual void OnLostFocus(){}; //活动失去焦点时

        virtual void Proc(const SDL_Event *){}; //无Control对象接受信息时，由该函数接受事件
        virtual void Proc(const Control *,const int){};
        //有Control对象接受信息时，Control向Activity发送的信息由此函数接受

        Control * GetFocusControl(const int,const int);    //传入鼠标\触摸位置，获取处在焦点的控件
        virtual ~Activity();
    };
}

#endif // _HEAD_ACTIVITY_
