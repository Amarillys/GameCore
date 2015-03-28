#ifndef _HEAD_GLOBALS_
#define _HEAD_GLOBALS_

#define FPS 60

#include "SDLbase.h"
#include <string>
#include "../Debug.h"
namespace Core{
    class Activity;
    class RndPtr;

    void CoreInit(const std::string& title,const bool FullScreen,const int w,const int h);
    //框架初始化

    extern RndPtr pRnd;
    void CoreMain(Activity&);   //框架执行
    void CoreQuit();    //框架销毁
    void SendEvent(const SDL_Event*,Activity*);  //向一个活动发送消息
    void Goto(Activity&);   //活动跳转

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
        inline int GetW(){return m_w;};
        inline int GetH(){return m_h;};
        inline operator SDL_Window* (){return m_wnd;};
        inline operator SDL_Renderer* (){return m_rnd;};
    };
}

#define BYTE unsigned char


#include "OS.h"
#endif
