#include "GalGameUI.h"
#include "../Core/Core.h"
#include "../Misc/NumTexture.h"

using namespace Core;
using namespace std;

/* m_stat 状态
0 隐藏
1 普通显示
2 按钮淡入
3 按钮淡出
*/

bool GameMenuBtn::Proc(const SDL_Event* e, Core::Activity*)
{
    return false;   //todo
}

void GameMenuBtn::SetPos(int x, int y)
{
    m_x = x;m_y = y;
}

void GameMenuBtn::Show()
{
    m_stat = 2;

    m_timer.Reset();
}

void GameMenuBtn::Hide()
{
    m_stat = 3;

    m_timer.Reset();
}

void GameMenuBtn::Destory()
{
    m_btn.Clear();
}

void GameMenuBtn::Init(const string& menuBtn)
{
    m_btn.Load(menuBtn);

    m_stat = 0; //不显示
}

void GameMenuBtn::OnDraw()
{
    if(m_stat != 0){
        m_btn.OnDraw();
    }
}

void GameMenuBtn::OnNext()
{
    if(m_stat == 2)
    {
        float x = float(m_timer.GetTimer()) / 150;
        if(x>=1.0){m_stat = 1;m_btn.SetAlpha(192);m_btn.SetPos(m_x,m_y);}
        m_btn.SetAlpha(192 * x);
        m_btn.SetPos(int(m_x + (1 - x) * (Window_W - m_x)),m_y);
    }else if(m_stat == 3){
        float x = float(m_timer.GetTimer()) / 150;
        if(x>=1.0) m_stat = 0;
        m_btn.SetAlpha(192 * (1 - x));
        m_btn.SetPos(int(m_x + x * (Window_W - m_x)),m_y);
    }
}




