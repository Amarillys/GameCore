#ifndef _HEAD_GLOBALS_
#define _HEAD_GLOBALS_

#include "SDLbase.h"
#include <string>
#include <set>
namespace Core{
    class Activity;
    extern SDL_Window* pWnd;
    extern SDL_Renderer* pRnd;
    extern std::set<Activity*> actList;
    void CoreInit();    //框架初始化
    void CoreMain(Activity*);   //框架执行
    void SendEvent(const SDL_Event*,Activity*);  //向一个活动发送消息
    void Goto(Activity*);   //活动跳转

    template<class T>
    T* NewActivity() //你应该使用该方法创建活动
    {T* p = new T();actList.insert((Activity*)p);return p;}
}

#define BYTE unsigned char


#include "OS.h"
#endif
