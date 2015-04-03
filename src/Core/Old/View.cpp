#include "View.h"
using namespace Core;
using namespace std;
void View::CRect(SDL_Rect& opr,
                float x,float y)
{
    opr.x = m_parent -> x * x;
    opr.y = m_parent -> y * y;
}

void View::CRect(SDL_Rect& opr,
                        const char base,int x,int y)
{
    opr.x = m_parent -> x / 4 * ((base & 0xF0) / 0x10);
    opr.y = m_parent -> y / 4 * (base & 0x0F);
}

View* View::Find(const std::string& ID)
{
    if (ID == m_ID) return this;
    else return NULL;
}

void View::SetID(const string& ID)
{
    m_ID = ID;
}

void View::SetParent(SDL_Rect* p)
{
    m_parent = p;
}

string View::GetID()
{
    return m_ID;
}
/*
void View::SetRect(const float x,const float y,const float w,const float h)
{
    SDL_Rect r;
    CRect(r,x,y);
    r.w = m_parent -> w * w;
    r.h = m_parent -> h * h;
    SetRect(r.x,r.y,r.w,r.h);
}

void View::SetRect(const char base,const int x,const int y ,const int w,const int h)
{
    SDL_Rect r;
    CRect(r,x,y);
    r.w = w;
    r.h = h;
    SetRect(r.x,r.y,r.w,r.h);
}
*/
