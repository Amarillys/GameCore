#pragma once
#include <list>
#include "Texture.h"
/**** ����,float (*EffectConverter)(float x) ****/
/* ָ��һ�����������ú��������xֵ��[0,������)֮��
* Ҫ��ú�����x���ڵ���1.0ʱ���� -1.0
* �����xΪ������չ�İٷֱ�
* ����Ӧ�ö�x����ת����ʹ���Ϊ��������Ҫ�Ķ����ĺ���
* ���磬Բ��ƽ���ƶ�ʱ����Ҫ�õ�Բ������
* ��ô����Բο����´��룺
float ArcFunc(float x)
{
    if (x>=1.0) return -1.0;
    else return sqrt(1-(x-1)*(x-1));
}
* else��ߵ��Ǿ�������ó���Բ�������Ĵ���
*/

//int _FPStime�������-1����ʱ�����ƣ���λΪ֡������ʱ��������ݶ�����ÿ��Ϊ��λ
namespace Core{

class Sprite:public Texture{

struct SpriteTask{
        short int TaskType;
        int FPStime;
        float per;
        int int_arg[8];
        float float_arg[4];
};

private:
    std::list<SpriteTask> m_tasks;

    bool m_rollEnabled;
    float m_rollAngle;
    SDL_Point m_rollCenter;
    SDL_RendererFlip m_rollFlip;
public:
    Sprite();
    void OnNext();
    void OnDraw();
    bool Finished();    //��ȷ����ʱ�����ƵĶ����Ƿ����

    void XMove(int x,int y,int _FPStime,float (*EffectConverter)(float x) = nullptr);
    void XMove(char base,int x,int y,int _FPStime,float (*EffectConverter)(float x) = nullptr);
    void XMove(float x,float y,int _FPStime,float (*EffectConverter)(float x) = nullptr);
    void XSetAlpha(int alp,int _FPStime,float (*EffectConverter)(float x) = nullptr);
    void XSetRoll(float angle,int center_x,int center_y,int _FPStime,SDL_RendererFlip flip,float (*EffectConverter)(float x) = nullptr);
    void XSetRGB(Uint8 r,Uint8 g,Uint8 b,int _FPStime,float (*EffectConverter)(float x) = nullptr);
    void XZoom(int w,int h,int _FPStime,float (*EffectConverter)(float x) = nullptr);
    void XSetSrc(int x,int y,int w,int h,int _FPStime,float (*EffectConverter)(float x) = nullptr);
    void XStopAll();
    void XStopTimeLimited();
    void XStopTimeUnlimited();

    void SetRoll(float angle,int center_x,int center_y,int time,SDL_RendererFlip flip);
};

}
