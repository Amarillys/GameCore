#include "ACGCross\GalgameActivity\GalgameActivity.h"

using namespace std;
using namespace Core;
using namespace ACGCross::Galgame;

GalgameActivity::GalgameActivity()
{
    RegControl(m_menuBtn);
}

void GalgameActivity::OnShow()
{
    m_clk.Init();
    m_clk.SetPos(20,22);
    m_menuBtn.Init("GalGameSystem\\menuBtn.png");
    m_menuBtn.SetPos(pRnd.GetW() - 125,22);

    m_fnt.Open("C:\\WINDOWS\\FONTS\\simhei.ttf");
    m_textBox.Init();
    m_textBox.SetEffectSpeed(1000);
    m_textBox.SetFont(m_fnt);
    m_textBox.SetSpeed(100);
    m_textBox.SetColor(255,255,255);
    m_textBox.SetRect(50,200,500,200);
    m_textBox.SetHeight(32);
    wstring str = L"测试中的文本框。";
    m_textBox.AddText(str);
    m_textBox.AddPic("pic.png",2,200);
    m_textBox.SetColor(255,255,0);
    m_textBox.Br();
    m_textBox.SetHeight(16);
    m_textBox.AddText(str);
}

void GalgameActivity::OnHide()
{
    m_clk.Destory();
    m_menuBtn.Destory();
    //m_textBox.Destory();
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
    }else if(e.type == SDL_MOUSEBUTTONUP){
        //wstring str = L"点击测试中呵呵呵呵呵呵呵";
        //m_textBox.AddText(str);
        //m_textBox.AddPic("pic.png",1,1000);
        m_textBox.Clear();
        //m_textBox.Hide();
    }//else if(e.type == SDL_MOUSEWHEEL) m_textBox.Show();
}

void GalgameActivity::OnEvent(Control* c,const Uint32 m){
    if(c == &m_menuBtn){
        if(m == 0) {PNT("MenuButtonClicked"<<endl);}
        if(m == 1) PNT("MenuButtonMotion"<<endl);
    }
}

