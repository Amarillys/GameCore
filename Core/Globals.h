#ifndef _HEAD_GLOBALS_
#define _HEAD_GLOBALS_

#include "SDLbase.h"
#include <string>
#include "../Debug.h"
namespace Core{
    class Activity;
    extern SDL_Window* pWnd;
    extern SDL_Renderer* pRnd;
    extern int Window_W,Window_H;
    void CoreInit(const std::string& title,const int w,const int h);    //框架初始化
    void CoreMain(Activity*);   //框架执行
<<<<<<< HEAD
    void CoreQuit();    //框架销毁
    void SendEvent(const SDL_Event*,Activity*);  //向一个活动发送消息
    void Goto(Activity*);   //活动跳转
=======
    void SendEvent(const SDL_Event*,Activity*);  //向一个活动发送消息
    void Goto(Activity*);   //活动跳转

    template<class T>
    T* NewActivity() //你应该使用该方法创建活动
    {T* p = new T();actList.push_front((Activity*)p);return p;}
>>>>>>> origin/master
}

#define BYTE unsigned char


#include "OS.h"
#endif
