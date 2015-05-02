#include "Core/Animation.h"
#include "Core/Globals.h"
using namespace std;
using namespace Core;

void AnimationPool::OnNext()
{
    FOR_EACH(p,m_aniList_s.begin(),m_aniList_s.end())
    {
        if(!(*p) -> Finished()) (*p) -> OnNext();
        else{
            (*p) -> Reset();
            m_aniList_s.erase(p);
        }
    }
    FOR_EACH(p,m_aniList_h.begin(),m_aniList_h.end())
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
    FOR_EACH(p,m_aniList_s.begin(),m_aniList_s.end())
        if(!((*p) -> Forever()) && !((*p) -> Finished())) return false;
    FOR_EACH(p,m_aniList_h.begin(),m_aniList_h.end())
        if(!((*p) -> Forever()) && !((*p) -> Finished())) return false;
    return true;
}

void AnimationPool::StopOnceAnimation()
{
    FOR_EACH(p,m_aniList_s.begin(),m_aniList_s.end())
        if(!((*p) -> Forever())) {
            (*p) -> Reset();
            m_aniList_s.erase(p);
        }
    FOR_EACH(p,m_aniList_h.begin(),m_aniList_h.end())
        if(!((*p) -> Forever())) {
            delete &(*p);
            m_aniList_s.erase(p);
        }
}

void AnimationPool::StopAllAnimation()
{
    FOR_EACH(p,m_aniList_s.begin(),m_aniList_s.end())
    {
        (*p) -> Reset();
        m_aniList_s.erase(p);
    }
    FOR_EACH(p,m_aniList_h.begin(),m_aniList_h.end())
    {
        delete &(*p);
        m_aniList_h.erase(p);
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

