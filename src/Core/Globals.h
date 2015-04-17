#ifndef _HEAD_GLOBALS_
#define _HEAD_GLOBALS_

#define FPS 60

#include "SDLbase.h"
#include <string>
#include "../Core/Debug.h"
namespace Core{
    class Activity;
    class RndPtr;

    void CoreInit(const std::string& title,const bool FullScreen,const int w,const int h);
    //框架初始化并创建窗口
    //运行该代码后再单开代码块，声明和初始化各个活动

    extern RndPtr pRnd;
    void CoreMain(Activity&);   //框架执行
    //初始化活动的代码块的最后一行调用此函数，传入第一个执行的活动即可

    void CoreQuit();    //框架销毁
    //在代码块外执行该函数

    void Goto(Activity*);   //跳转活动

    class RndPtr{   //渲染器和窗口智能指针
    friend void CoreInit(const std::string& title,const bool FullScreen,const int w,const int h);
    friend void CoreQuit();
    private:
        SDL_Window* m_wnd;
        SDL_Renderer* m_rnd;
        int m_w,m_h;

        void Create(const std::string& title,const bool FullScreen,const int w,const int h);
        void Destory();
    public:
        int GetW(); //逻辑宽
        int GetH(); //逻辑高
        inline int GetPhW(){return m_w;}    //物理宽
        inline int GetPhH(){return m_h;}    //物理高
        inline operator SDL_Window* (){return m_wnd;};
        inline operator SDL_Renderer* (){return m_rnd;};
    };
}

#define BYTE unsigned char


#include "OS.h"
#endif
