#include "Animation.h"
using namespace std;
using namespace Core;

void AnimationPool::OnNext()
{
    for(auto p = m_aniList_s.begin();p != m_aniList_s.end();++p)
    {
        if(!(*p) -> Finished()) (*p) -> OnNext();
        else{
            (*p) -> Reset();
            m_aniList_s.erase(p);
        }
    }
    for(auto p = m_aniList_h.begin();p != m_aniList_h.end();++p)
    {
        if(!(*p) -> Finished()) (*p) -> OnNext();
        else {
            delete *p;
            m_aniList_s.erase(p);
        }
    }
}

bool AnimationPool::OnceAnimationFinished()
{
    for(auto p = m_aniList_s.begin();p != m_aniList_s.end();++p)
        if(!((*p) -> Forever()) && !((*p) -> Finished())) return false;
    for(auto p = m_aniList_h.begin();p != m_aniList_h.end();++p)
        if(!((*p) -> Forever()) && !((*p) -> Finished())) return false;
    return true;
}

void AnimationPool::StopOnceAnimation()
{
    for(auto p = m_aniList_s.begin();p != m_aniList_s.end();++p)
        if(!((*p) -> Forever())) {
            (*p) -> Reset();
            m_aniList_s.erase(p);
        }
    for(auto p = m_aniList_h.begin();p != m_aniList_h.end();++p)
        if(!((*p) -> Forever())) {
            delete &(*p);
            m_aniList_s.erase(p);
        }
}

void AnimationPool::StopAllAnimation()
{
    for(auto p = m_aniList_s.begin();p != m_aniList_s.end();++p)
    {
        (*p) -> Reset();
        m_aniList_s.erase(p);
    }
    for(auto p = m_aniList_h.begin();p != m_aniList_h.end();++p)
    {
        delete &(*p);
        m_aniList_s.erase(p);
    }
}

void AnimationPool::Install(Animation& a)
{
    m_aniList_s.push_front(&a);
}

void AnimationPool::InstallAutoDel(Animation*& p)
{
    m_aniList_h.push_front(p);
    p = nullptr;
}

 AnimationPool::~AnimationPool()
{
    StopAllAnimation();
}

