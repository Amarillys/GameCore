#include "Layer.h"

using namespace std;
using namespace Core;

void Layer::OnDraw()
{
    for(auto p = m_children.begin();p != m_children.end();++p)
        (*p) -> OnDraw();
}

void Layer::SetRect(char base,int x,int y,int w,int h)
{
    m_usingXD = true;
    m_x2 = x;m_y2 = y;m_w2 = w;m_h2 = h;m_base = base;

    CRect(m_rect,base,x,y);
    m_rect.w = w;
    m_rect.h = h;
    for(auto p = m_children.begin();p != m_children.end();++p)
        (*p) -> OnParentChanged();
}

void Layer::SetRect(float x,float y,float w,float h)
{
    m_usingXD = false;
    m_x1 = x;m_y1 = y;m_w1 = w;m_h1 = h;

    CRect(m_rect,x,y);
    m_rect.w = w * (m_parent -> w);
    m_rect.h = h* (m_parent -> h);
    for(auto p = m_children.begin();p != m_children.end();++p)
        (*p) -> OnParentChanged();
}

void Layer::OnParentChanged()
{
    if(m_usingXD) SetRect(m_base,m_x2,m_y2,m_w2,m_h2);
    else SetRect(m_x1,m_y1,m_w1,m_h1);
}

View* Layer::Find(const string& ID)
{
    View* ret = NULL;
    for(auto p = m_children.begin();p != m_children.end();++p)
    {
        ret = (*p) -> Find(ID);
        if(ret != NULL) return ret;
    }
    return NULL;
}

void Layer::DeleteView(const std::string& ID)
{
    View* pV = NULL;
    for(auto p = m_children.begin();p != m_children.end();++p)
    {
        if((*p) -> GetID() == ID)
        {
            pV = *p;
            m_children.erase(p);
            break;
        }
    }
    if(pV != NULL) delete pV;
}

void Layer::ClearView()
{
    for(auto p = m_children.begin();p != m_children.end();++p)
        delete *p;
    m_children.clear();
}

Layer::~Layer(){
    ClearView();
}
