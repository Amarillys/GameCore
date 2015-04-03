#include "../GalgameActivity.h"

using namespace std;
using namespace Core;
using namespace ACGCross::Galgame;

GalgameActivity::GalgameActivity()
{
    RegControl(m_menuBtn);
}

void GalgameActivity::OnShow()
{
    m_clk.Init("GalGameSystem\\fg.png","GalGameSystem\\num.png");
    m_clk.SetPos(20,22);
    m_menuBtn.Init("GalGameSystem\\menuBtn.png");
    m_menuBtn.SetPos(pRnd.GetW() - 125,22);
    m_textBox.Init();
}

void GalgameActivity::OnHide()
{
    m_clk.Destory();
    m_menuBtn.Destory();
    m_textBox.Destory();
}

void GalgameActivity::OnNext()
{
    m_clk.OnNext();
    m_menuBtn.OnNext();
    m_textBox.OnNext();
}

void GalgameActivity::OnDraw()
{
    m_clk.OnDraw();
    m_menuBtn.OnDraw();
    m_textBox.OnDraw();
}

void GalgameActivity::OnEvent(const SDL_Event& e)
{
    if(e.type == SDL_MOUSEMOTION){
        if(e.motion.y <pRnd.GetH()/5){
            if(!m_clk.GetVisible())
                m_clk.Show();
            if(!m_menuBtn.GetVisible())
                m_menuBtn.Show();
        }
        else if(e.motion.y >= pRnd.GetH()/5 && /*m_clk.GetVisible() &&*/ m_menuBtn.GetVisible())
        {m_clk.Hide();m_menuBtn.Hide();}
    }
}

void GalgameActivity::OnEvent(Control* c,const Uint32 m){
    if(c == &m_menuBtn){
        if(m == 0) {PNT("MenuButtonClicked"<<endl);}
        if(m == 1) PNT("MenuButtonMotion"<<endl);
    }
}

