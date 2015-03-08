#include "GalGameUI.h"
#include "../Core/Core.h"
#include "../Misc/NumTexture.h"

using namespace Core;
using namespace std;

/* m_stat ״̬
0 ����
1 ��ͨ��ʾ
2 ��ť����
3 ��ť����

4 ��ť��ָ��
5 ��ť���ٱ�ָ��
6 ��ť������
7 ��ť���ɿ�
*/

/* m_showstat ״̬
0 ��ͨ��ť״̬
1 ��ť��ָ��״̬
2 ��ť������״̬
*/

bool GameMenuBtn::Proc(const SDL_Event* e, Core::Activity* a)
{
    if(e -> type == SDL_MOUSEBUTTONDOWN)
        if(InRect(m_rect,e->button.x,e->button.y))
            m_showstat = 2;

    if(e -> type == SDL_MOUSEBUTTONUP)
        if(InRect(m_rect,e->button.x,e->button.y))
        {
            m_showstat = 1;
            a -> OnEvent(this,0);
            return true;
        }
    if(e -> type == SDL_MOUSEMOTION){
        if(InRect(m_rect,e->button.x,e->button.y))
        {
            m_showstat = 1;
            a -> OnEvent((Control*)this,1);
           return true;
        }
        else m_showstat = 0;
    }
    return false;   //todo
}

void GameMenuBtn::SetPos(int x, int y)
{
    m_x = x;m_y = y;
    m_rect.x = x;m_rect.y = y;
    m_btn.GetInfo(m_rect.w,m_rect.h);
}

void GameMenuBtn::Show()
{
    m_stat = 2;
    m_visible_l = true;
    m_timer.Reset();
}

void GameMenuBtn::Hide()
{
    m_stat = 3;
    m_visible_l = false;
    m_timer.Reset();
}

void GameMenuBtn::Destory()
{
    m_btn.Clear();
}

void GameMenuBtn::Init(const string& menuBtn)
{
    m_btn.Load(menuBtn);
    m_visible_l = false;
    m_stat = 0; //����ʾ
}

void GameMenuBtn::OnDraw()
{
    if(m_stat != 0){
        m_btn.OnDraw();
    }
}

void GameMenuBtn::OnNext()
{
    if(m_stat == 1)switch(m_showstat){
    case 0:
        m_btn.SetAlpha(192);
        break;
    case 1:
        m_btn.SetAlpha(255);
        break;
    case 2:
        m_btn.SetAlpha(128);
        break;
    }

    if(m_stat == 2)
    {
        float x = float(m_timer.GetTimer()) / 128;
        if(x>=1.0){m_stat = 1;m_btn.SetAlpha(192);m_btn.SetPos(m_x,m_y);}
        m_btn.SetAlpha(192 * x);
        m_btn.SetPos(int(m_x + (1 - x) * (Window_W - m_x)),m_y);
    }else if(m_stat == 3){
        float x = float(m_timer.GetTimer()) / 128;
        if(x>=1.0) m_stat = 0;
        m_btn.SetAlpha(192 * (1 - x));
        m_btn.SetPos(int(m_x + x * (Window_W - m_x)),m_y);
    }
}




