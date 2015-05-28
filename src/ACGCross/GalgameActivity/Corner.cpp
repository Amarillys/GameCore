#include "ACGCross\GalgameActivity\Corner.h"

using namespace ACGCross::Galgame;

//m_stat
//0 ����
//1 ��ʾ
//-1 ��������
//-2 ������ʾ

void Corner::OnDraw()
{
        if(m_stat != 0) m_corner.OnDraw();
}

void Corner::OnNext()
{
    if(m_stat != 0){
        m_ang += 0.15;
        m_corner.SetRollAngle(m_ang);
    }

    if(m_stat == -1){
        m_fpsCounter ++;
        if(m_fpsCounter >= m_fadeFpsTime)
            m_stat = 0;
        else m_corner.SetAlpha(m_topAlpha - float(m_fpsCounter)/m_fadeFpsTime * m_topAlpha);
    }else if(m_stat == -2){
        m_fpsCounter ++;
        if(m_fpsCounter >= m_fadeFpsTime){
            m_corner.SetAlpha(m_topAlpha);
            m_stat = 1;
        }
        m_corner.SetAlpha(float(m_fpsCounter)/m_fadeFpsTime * m_topAlpha);
    }
}

void Corner::Init()
{
    m_corner.Load("GalGameSystem\\corner.png");
    m_corner.SetAlpha(0);
    m_corner.SetPos(0x44,-128,-147);
    m_corner.SetRollEnable(true);
    m_corner.SetRollCenter(128,147);
    m_stat = 0;
    m_ang = 0;
}

void Corner::Destory()
{
    m_corner.Clear();
}

void Corner::SetTopAlpha(int a)
{
    m_topAlpha = a;
}



void Corner::SetFadeSpeed(int time)
{m_fadeFpsTime = float(time) / 1000 * FPS;}

void Corner::Hide(){
    if(m_stat == 0) return;
    m_stat = -1;
    m_fpsCounter = 0;
}

void Corner::Show(){
    if(m_stat == 1) return;
    m_stat = -2;
    m_fpsCounter = 0;
}

bool Corner::Finished(){
    return m_stat >= 0;
}

bool Corner::GetVisible(){
    return m_stat == 1 || m_stat == -2;
}
