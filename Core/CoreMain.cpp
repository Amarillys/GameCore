#include "Activity.h"
#include "Timer.h"
#include "Sound.h"
#include "Globals.h"
#include "Control.h"
#include "Animation.h"
#include "../Debug.h"

using namespace Core;
using namespace std;

SDL_Window* Core::pWnd= nullptr;
SDL_Renderer* Core::pRnd  = nullptr;
bool isGotoing = true;
Activity* nowFocus;
Activity* lastFocus;

int Core::Window_W;
int Core::Window_H;


namespace Core{

void Goto(Activity* a)
{
    nowFocus -> OnHide();
    lastFocus = nowFocus;
    nowFocus = a;
    isGotoing = true;
    nowFocus -> OnShow();
}

void SendEvent(SDL_Event* e,Activity* a)    //向一个活动发送SDL消息
{
    if(!(a -> m_ansList.empty())) for(auto p = a -> m_ansList.begin();p != a -> m_ansList.end();++p)  //遍历控件表
    {
        if((*p) -> Proc(e,a)) return;  //发现有控件接受该信息后返回
    }
    a -> OnEvent(e);    //无控件接受消息，发送消息给活动的OnEvent()
}

void ActivityDrawProc() //活动刷新一次处理
{
    if(isGotoing){  //如果正在跳转
        bool lastFinished = false;
        bool nowFinished = false;

        if(lastFocus != nullptr && !lastFinished) {
            if(lastFocus -> GetAnimationOnHide() != nullptr){
                lastFocus -> GetAnimationOnHide() -> OnNext();   //绘制上个活动
                if(lastFocus -> GetAnimationOnHide() -> Finished()) lastFinished = true;
            }else lastFinished = true;
            lastFocus -> OnDraw();
        }else lastFinished = true;

        if(nowFocus != nullptr && !nowFinished) {
            if(nowFocus -> GetAnimationOnShow() != nullptr){
                nowFocus -> GetAnimationOnShow() -> OnNext();   //绘制下个活动
                if(nowFocus -> GetAnimationOnShow() -> Finished()) nowFinished = true;
            }else nowFinished = true;
            nowFocus -> OnDraw();
        }else nowFinished = true;

        if(lastFinished && nowFinished) isGotoing = false;
    }

    //两个动画结束后关闭跳转状态
    else{
        nowFocus -> OnNext();
        nowFocus -> OnDraw();;
    }
}

void CoreMain(Activity* start)
{
    nowFocus = start;
    nowFocus -> OnShow();
    /* 主循环部分 */
    SDL_Event e;
    Timer FPSKiller;
    while(1){
        while(SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT) return;
            else SendEvent(&e,nowFocus);
        }
        SDL_SetRenderDrawColor(Core::pRnd,0x00,0x00,0x00,0xFF);
        SDL_RenderClear(pRnd);
        ActivityDrawProc();
        SDL_RenderPresent(pRnd);

        FPSKiller.WaitTimer(1000/60);   //FPS限制
        FPSKiller.Reset();
    }
}

void CoreInit(const string& title,const int w,const int h)
{
    SDL_Init(SDL_INIT_AUDIO |
                SDL_INIT_EVENTS|
                SDL_INIT_VIDEO |
                SDL_INIT_TIMER);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    Sound::Init();
    pWnd = SDL_CreateWindow(title.c_str(),
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            w,h,
                            SDL_WINDOW_OPENGL);
    pRnd = SDL_CreateRenderer(pWnd,-1,
                                SDL_RENDERER_ACCELERATED|
                                SDL_RENDERER_PRESENTVSYNC);
    SDL_RenderPresent(pRnd);
    SDL_GetWindowSize(pWnd,&Window_W,&Window_H);

    nowFocus = nullptr;
    lastFocus = nullptr;

}

}

void Core::CoreQuit()
{
    SDL_DestroyRenderer(pRnd);
    SDL_DestroyWindow(pWnd);
    TTF_Quit();
    IMG_Quit();
    Sound::Quit();
    SDL_Quit();
}
