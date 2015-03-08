#include "GalGameUI.h"

using namespace std;
using namespace Core;

GalgameUI::GalgameUI()
{
    m_ansList.push_back(&m_menuBtn);
}

void GalgameUI::OnShow()
{
    m_clk.Init("GalGameSystem\\fg.png","GalGameSystem\\num.png");
    m_clk.SetPos(40,22);
    m_menuBtn.Init("GalGameSystem\\menuBtn.png");
    m_menuBtn.SetPos(Core::Window_H + 50,22);
}

void GalgameUI::OnHide()
{
    m_clk.Destory();
    m_menuBtn.Destory();
}

void GalgameUI::OnNext()
{
    m_clk.OnNext();
    m_menuBtn.OnNext();
}

void GalgameUI::OnDraw()
{
    m_clk.OnDraw();
    m_menuBtn.OnDraw();
}

void GalgameUI::OnEvent(const SDL_Event* e)
{
    if(e -> type == SDL_MOUSEMOTION){
        if(e -> motion.y <Core::Window_H/3 && !m_clk.GetVisible()) {m_clk.Show();m_menuBtn.Show();}
        else if(e -> motion.y >= Core::Window_H/3 && m_clk.GetVisible()) {m_clk.Hide();m_menuBtn.Hide();}
    }
}

void GalgameUI::OnEvent(const Control*,const int){};    //todo

