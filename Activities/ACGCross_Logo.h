#include "../Core/Core.h"
#include "../Misc/MathFunc.h"



class ACGCross_Logo:public Core::Activity
{
private:
    Core::Texture m_logo;
    Core::Texture m_logo2;
    Core::Texture m_yzsz;
    Core::Thread* m_init;
    Core::Timer m_timer;
    Uint8 m_stat;
    Core::Activity* m_goto;

    SDL_Rect m_sta0_logoRect;
    SDL_Rect m_sta1_logoRect;
    SDL_Rect m_sta1_backRect;
public:
    ACGCross_Logo();
    void SetInitThread(Core::Thread* t){m_init = t;}
    void SetGoto(Activity* a){m_goto = a;}
    void OnShow();
    void OnHide();
    void OnNext();
    void OnDraw();
};
