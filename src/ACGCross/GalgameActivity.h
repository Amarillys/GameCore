#pragma once
#include "../Core/Core.h"
#include "../ACGCross/NumTexture.h"

#include "GalgameActivity/TextBox.h"
#include "GalgameActivity/Clock.h"
#include "GalgameActivity/GameMenu.h"

namespace ACGCross{
namespace Galgame{

class GalgameActivity:public Core::Activity
{

private:
    Clock m_clk;        //崩溃是因为表坏了
    GameMenuBtn m_menuBtn;
    TextBox m_textBox;
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
