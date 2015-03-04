#include <set>
#include "SDLbase.h"

namespace Core{
    class Activity;
    class Control;
    class Animation;

    class Activity
    {
    friend void Core::SendEvent(SDL_Event* e,Activity* a);
    protected:
        std::set<Control*> m_ansList;
        //如果有Control需要相应操作，把它加到这个表里
    public:
        virtual ~Activity(){};


        virtual void OnShow(){};    //当Goto到这个活动时执行
        virtual void OnHide(){};    //当Goto出这个活动时执行

        virtual void OnDraw()=0;    //绘制活动
        virtual void OnEvent(const SDL_Event*)=0;
        //当没有控件接受消息时，回调此函数
        virtual void OnEvent(Control*,const int)=0;
        //当有控件接收消息时，由Control调用此函数，并传入控件给的消息

        virtual void OnNext() =0;   //请求除淡入动画和淡出动画以外所有动画的下一帧

        virtual Animation* GetAnimationOnCreated(){return nullptr;}
        //淡入动画，切换时与上个动画的淡出动画同时播放

        virtual Animation* GetAnimationOnDestroy(){return nullptr;}
        //淡出动画，切换时与下个动画的淡入动画同时播放
    };
}
