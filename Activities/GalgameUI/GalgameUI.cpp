#include "../GalGameUI.h"

using namespace std;
using namespace Core;

const int Window_H = pRnd.GetH(),Window_W = pRnd.GetW();

GalgameUI::GalgameUI()
{
    m_ansList.push_back(&m_menuBtn);
}

void GalgameUI::OnShow()
{
    m_clk.Init("GalGameSystem\\fg.png","GalGameSystem\\num.png");
    m_clk.SetPos(20,22);
    m_menuBtn.Init("GalGameSystem\\menuBtn.png");
    m_menuBtn.SetPos(Window_W - 125,22);
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
   // m_textBox.OnNext();
}

void GalgameUI::OnDraw()
{
    m_clk.OnDraw();
    m_menuBtn.OnDraw();
    //m_textBox.OnDraw();
}

void GalgameUI::OnEvent(const SDL_Event* e)
{
    if(e -> type == SDL_MOUSEMOTION){
        if(e -> motion.y <Window_H/3){
            if(!m_clk.GetVisible())
                m_clk.Show();
            if(!m_menuBtn.GetVisible())
                m_menuBtn.Show();
        }
        else if(e -> motion.y >= Window_H/3 && m_clk.GetVisible() && m_menuBtn.GetVisible())
        {m_clk.Hide();m_menuBtn.Hide();}
    }
}

void GalgameUI::OnEvent(Control* c,const int m){
    if(c == &m_menuBtn){
        if(m == 0) PNT("MenuButtonClicked"<<endl);
        if(m == 1) PNT("MenuButtonMotion"<<endl);
    }
}

