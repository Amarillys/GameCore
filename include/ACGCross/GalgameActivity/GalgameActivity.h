#pragma once
#include "Core.h"

//#include "TextBox.h"
#include "Clock.h"
#include "GameMenu.h"
#include "TextBox.h"

namespace ACGCross{
namespace Galgame{

class GalgameActivity:public Core::Activity
{

private:
    Clock m_clk;
    GameMenuBtn m_menuBtn;
    TextBox m_textBox;
    Core::Font m_fnt;
public:
    GalgameActivity();
    void OnShow();
    void OnHide();
    void OnNext();
    void OnDraw();
    void OnEvent(const SDL_Event&);
    void OnEvent(Core::Control*,const Uint32);
};

}
}
