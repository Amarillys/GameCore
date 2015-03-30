#include "ACGCross_Logo.h"
using namespace std;
using namespace Core;
using namespace ACGCross;

Logo::Logo()
{
    m_init = nullptr;
}

void Logo::OnShow()
{
    m_logo.Load("ACGCross\\ACGCross_Logo.png");
    m_logo.SetZoom(192*2,192*2);
    m_logo2.Load("ACGCross\\ACGCross_Logo2.png");
    m_logo2.SetZoom(192*2,192*2);
    m_yzsz.Load("ACGCross\\ACGCross_Chn.png");
    m_logo.SetPos(0x22,-192,-192);
    m_logo2.SetPos(0x22,-192,-192);
    m_yzsz.SetAlpha(0);

    if(m_init != nullptr) m_init -> Run();
    m_stat = 0;
    m_logo.SetBlend(SDL_BLENDMODE_MOD);
    m_logo.SetAlpha(0);

    Pos(m_sta0_logoRect.x,m_sta0_logoRect.y,0x22,-192,-192);
    m_sta0_logoRect.w = 0;m_sta0_logoRect.h = 0;

    m_sta1_logoRect = m_sta0_logoRect;
    m_sta1_logoRect.x += 1;m_sta1_logoRect.y += 1;
    m_sta1_logoRect.w = 382;
    m_sta1_backRect = {0,pRnd.GetH(),pRnd.GetW(),0};
    m_timer.Reset();
}

void Logo::OnHide()
{
    m_logo.Clear();
    m_logo2.Clear();
    m_yzsz.Clear();
}

void Logo::OnNext()
{
    if(m_stat == 0){
        m_sta0_logoRect.h = m_sta0_logoRect.w = float(m_timer.GetTimer()) / 256 * 384;
        if(m_sta0_logoRect.h >= 384) m_sta0_logoRect.h = m_sta0_logoRect.w = 384;
    }else if(m_stat == 1){
        float x = ArcFunc(float(m_timer.GetTimer()) / 512);
        m_sta1_logoRect.y = pRnd.GetH()/2 - 192 +382 * x;
        m_sta1_logoRect.h = pRnd.GetH()/2 + 192 - m_sta1_logoRect.y;
        m_sta1_backRect.h = -(pRnd.GetH() * x);
        if(x == -1.0) {m_stat = 2;m_timer.Reset();}
    }else if(m_stat == 2){
        float x = float(m_timer.GetTimer()) / 512;
        m_logo.SetPos(0x22,-192,-192-96*ArcFunc(x));
        m_logo2.SetPos(0x22,-192,-192-96*ArcFunc(x));
        m_yzsz.SetPos(0x22,-193,200 - 256*ArcFunc(x));
        m_yzsz.SetAlpha(255*ArcFunc(x));
        m_logo2.SetAlpha(255*ArcFunc(x));
        if(x >= 1.0){
            m_stat = 3;
            m_logo2.SetPos(0x22,-192,-192-96);
            m_yzsz.SetPos(0x22,-193,200 - 256);
            m_yzsz.SetAlpha(255);
            m_logo2.SetAlpha(255);
            m_timer.Reset();
        }
    }else if(m_stat == 4){
        float x = ArcFunc(float(m_timer.GetTimer()) / 512);
        Uint8 v = 255*x;
        m_logo2.SetAlpha(255-v);
        m_yzsz.SetAlpha(255-v);
        if(x == -1.0) {
            m_stat = 5;
        }
    }else if(m_stat == 5){
        Goto(m_goto);
    }
}

void Logo::OnDraw()
{
    if(m_stat == 0){
        SDL_SetRenderDrawColor(pRnd,0xFF,0xFF,0xFF,0xFF);
        SDL_RenderDrawRect(pRnd,&m_sta0_logoRect);
        if(m_sta0_logoRect.h >= 384) {m_stat = 1;m_timer.Reset();}
    }else if(m_stat == 1){
        SDL_SetRenderDrawColor(pRnd,0xFF,0xFF,0xFF,0xFF);
        SDL_RenderFillRect(pRnd,&m_sta0_logoRect);

        SDL_RenderFillRect(pRnd,&m_sta1_backRect);
        SDL_SetRenderDrawColor(pRnd,0x00,0x00,0x00,0xFF);
        SDL_RenderFillRect(pRnd,&m_sta1_logoRect);
        m_logo.OnDraw();

    }else if(m_stat == 2 || m_stat == 3){
        SDL_SetRenderDrawColor(pRnd,0xFF,0xFF,0xFF,0xFF);
        SDL_RenderClear(pRnd);
        if(m_stat == 2) m_logo.OnDraw();
        m_logo2.OnDraw();
        m_yzsz.OnDraw();
        if(m_stat == 3 && m_timer.GetTimer() >= 1500){
            if(m_init != nullptr) {if(!m_init -> Running()) {m_stat = 4;m_timer.Reset();}}
            else {m_stat = 4;m_timer.Reset();}
        }
    }else if(m_stat == 4){
        SDL_SetRenderDrawColor(pRnd,0xFF,0xFF,0xFF,0xFF);
        SDL_RenderClear(pRnd);
        m_logo2.OnDraw();
        m_yzsz.OnDraw();
    }else{
        SDL_SetRenderDrawColor(pRnd,0,0,0,0xFF);
        SDL_RenderClear(pRnd);
    }
}
