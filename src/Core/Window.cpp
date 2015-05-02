#include "Core/Globals.h"

using namespace Core;
using namespace std;

void RndPtr::Create(const std::string& title,const bool FullScreen,const int w,const int h)
{
    if(FullScreen){
        m_wnd = SDL_CreateWindow("",
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            0,0,
                            SDL_WINDOW_FULLSCREEN_DESKTOP |
                            SDL_WINDOW_OPENGL);
    }else{
        m_wnd = SDL_CreateWindow(title.c_str(),
                            SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED,
                            w,h,
                            SDL_WINDOW_OPENGL);
    }
    m_rnd = SDL_CreateRenderer(m_wnd,-1,
                            SDL_RENDERER_ACCELERATED|
                            SDL_RENDERER_PRESENTVSYNC);
    SDL_RenderPresent(m_rnd);
    SDL_GetWindowSize(m_wnd,&m_w,&m_h);
}

void RndPtr::Destory(){
    SDL_DestroyRenderer(m_rnd);
    SDL_DestroyWindow(m_wnd);
}
