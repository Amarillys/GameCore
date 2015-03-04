#include "Activity.h"
#include "Timer.h"
#include "Sound.h"
#include "Globals.h"
#include "Control.h"
#include "Animation.h"

using namespace Core;

SDL_Window* Core::pWnd= nullptr;
SDL_Renderer* Core::pRnd  = nullptr;
bool isGotoing = true;
Activity* nowFocus;
Activity* lastFocus;


namespace Core{

std::set<Activity*> actList;

void Goto(Activity* a)
{
    nowFocus -> OnHide();
    lastFocus = nowFocus;
    nowFocus = a;
    isGotoing = true;
    nowFocus -> OnShow();
}

void SendEvent(SDL_Event* e,Activity* a)    //��һ�������SDL��Ϣ
{
    if(!(a -> m_ansList.empty())) for(auto p = a -> m_ansList.begin();p != a -> m_ansList.end();++p)  //�����ؼ���
    {
        if((*p) -> Proc(e,a)) return;  //�����пؼ����ܸ���Ϣ�󷵻�
    }
    a -> OnEvent(e);    //�޿ؼ�������Ϣ��������Ϣ�����OnEvent()
}

void ActivityDrawProc() //�ˢ��һ�δ���
{
    if(isGotoing){  //���������ת
        bool lastFinished = false;
        bool nowFinished = false;

        if(lastFocus != nullptr && !lastFinished) {
            if(lastFocus -> GetAnimationOnDestroy() != nullptr){
                lastFocus -> GetAnimationOnDestroy() -> OnNext();   //�����ϸ��
                if(lastFocus -> GetAnimationOnDestroy() -> Finished()) lastFinished = true;
            }else lastFinished = true;
            lastFocus -> OnDraw();
        }else lastFinished = true;

        if(nowFocus != nullptr && !nowFinished) {
            if(nowFocus -> GetAnimationOnCreated() != nullptr){
                nowFocus -> GetAnimationOnCreated() -> OnNext();   //�����¸��
                if(nowFocus -> GetAnimationOnCreated() -> Finished()) nowFinished = true;
            }else nowFinished = true;
            nowFocus -> OnDraw();
        }else nowFinished = true;

        if(lastFinished && nowFinished) isGotoing = false;
    }

    //��������������ر���ת״̬
    else{
        nowFocus -> OnNext();
        nowFocus -> OnDraw();
    }
}

void CoreMain(Activity* start)
{
    nowFocus = start;
    /* ��ѭ������ */
    SDL_Event e;
    Timer FPSKiller;
    while(1){
        while(SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT) goto CORE_END;
            else SendEvent(&e,nowFocus);
        }
        SDL_RenderClear(pRnd);
        ActivityDrawProc();
        SDL_RenderPresent(pRnd);

        FPSKiller.WaitTimer(1000/60);   //FPS����
        FPSKiller.Reset();
        }
    /* ��ѭ������ */

CORE_END:
    if(!actList.empty())
        for(auto p = actList.begin();p != actList.end();++p)
            delete *p;

    SDL_DestroyRenderer(pRnd);
    SDL_DestroyWindow(pWnd);
    TTF_Quit();
    IMG_Quit();
    Sound::Quit();
    SDL_Quit();
}

void CoreInit()
{
    SDL_Init(SDL_INIT_AUDIO |
                SDL_INIT_EVENTS|
                SDL_INIT_VIDEO |
                SDL_INIT_TIMER);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    Sound::Init();
    pWnd = SDL_CreateWindow("Gaming",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            800,600,
                            SDL_WINDOW_OPENGL);
    pRnd = SDL_CreateRenderer(pWnd,-1,
                                SDL_RENDERER_ACCELERATED|
                                SDL_RENDERER_PRESENTVSYNC);
    SDL_RenderPresent(pRnd);

    nowFocus = nullptr;
    lastFocus = nullptr;

}

}
