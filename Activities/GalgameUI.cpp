#include "GalGameUI.h"
#include <ctime>

using namespace std;
using namespace Core;

void Clock::SetPos(int x, int y)
{
    m_bx = x;m_y = y;
    m_fg.SetPos(m_x + 2*m_numWei,m_y);
}

void Clock::OnNext()
{


    //时间的获取与处理
    time_t rawtime;
    time (&rawtime);
    struct tm * timeinfo = localtime(&rawtime);

    m_sz[0] = timeinfo ->tm_hour / 10 + '0';
    m_sz[1] = timeinfo ->tm_hour % 10 + '0';
    m_sz[2] = timeinfo ->tm_min / 10 + '0';
    m_sz[3] = timeinfo ->tm_min % 10 + '0';

    if(m_stat == 0) //正常显示
    {
        //冒号的动画
        float fg_now = float(m_timer_fg.GetTimer()%1000)/1000;
        if(m_fg_last > fg_now) m_fg_showing = !m_fg_showing;
        if(m_fg_showing)
            m_fg.SetAlpha(192 * fg_now);
        else
            m_fg.SetAlpha(192 - 192 * fg_now);
        m_fg_last = fg_now;
    }else if(m_stat == 1){  //出现
        float x = float(m_timer_fg.GetTimer())/128;
        if(x >= 1.0){m_stat = 0;m_timer_fg.Reset();return;}
        m_x = m_bx * x;
        m_clk.SetAlpha(192 * x);
        m_fg.SetAlpha(192*x);
    }else if(m_stat == 2){  //消失
        float x = float(m_timer_fg.GetTimer())/128;
        if(x >= 1.0){m_stat = 0;m_timer_fg.Reset();m_visible = false;return;}
        m_x = m_bx * (1 - x);
        m_clk.SetAlpha(192 * (1-x));
        m_fg.SetAlpha(192*(1-x));
    }
}

void Clock::Hide()
{
    m_visible_l = false;
    m_stat = 2;
    m_timer_fg.Reset();
}

void Clock::Show()
{
    m_visible_l = m_visible = true;
    m_stat = 1;
    m_timer_fg.Reset();
}

void Clock::Destory()
{
    m_fg.Clear();
    m_clk.Clear();
}

void Clock::OnInit(const std::string& num,const std::string& fg)
{
    m_fg.Load(num);
    m_clk.Load(fg);
    m_fg.SetAlpha(0);
    m_fg_showing = false;
    m_timer_fg.Reset();
    m_fg_last = 0.0;
    m_visible = false;
    m_numWei = m_clk.GetWei();
    int h;
    m_fg.GetInfo(m_fgWei,h);
    m_stat = 0;

    m_fg.SetAlpha(0);
    m_clk.SetAlpha(0);
}

void Clock::OnDraw()
{
    if(m_visible){
        m_fg.OnDraw();

        m_clk.SetNum(m_sz[0]);
        m_clk.SetPos(m_x,m_y);
        m_clk.OnDraw();

        m_clk.SetNum(m_sz[1]);
        m_clk.SetPos(m_x + m_numWei,m_y);
        m_clk.OnDraw();

        m_clk.SetNum(m_sz[2]);
        m_clk.SetPos(m_x + 2*m_numWei +m_fgWei,m_y);
        m_clk.OnDraw();

        m_clk.SetNum(m_sz[3]);
        m_clk.SetPos(m_x + 3*m_numWei+m_fgWei,m_y);
        m_clk.OnDraw();
    }
}

void GalgameUI::OnShow()
{
    m_clk.OnInit("GalGameSystem\\fg.png","GalGameSystem\\num.png");
}

void GalgameUI::OnNext()
{
    m_clk.SetPos(40,22);
    m_clk.OnNext();
}

void GalgameUI::OnDraw()
{
    m_clk.OnDraw();
}

void GalgameUI::OnEvent(const SDL_Event* e)
{
    if(e -> type == SDL_MOUSEMOTION){
        if(e -> motion.y <Core::Window_H/3 && !m_clk.GetVisible()) m_clk.Show();
        else if(e -> motion.y >= Core::Window_H/3 && m_clk.GetVisible()) m_clk.Hide();
    }


}

