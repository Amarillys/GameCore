#pragma once
#include <list>
#include "Texture.h"
/**** 关于,float (*EffectConverter)(float x) ****/
/* 指向一个函数，给该函数传入的x值在[0,正无穷)之间
* 要求该函数在x大于等于1.0时返回 -1.0
* 传入的x为动画进展的百分比
* 函数应该对x进行转换，使其变为符合你想要的动画的函数
* 比如，圆弧平滑移动时，需要用到圆弧函数
* 那么你可以参考以下代码：
float ArcFunc(float x)
{
    if (x>=1.0) return -1.0;
    else return sqrt(1-(x-1)*(x-1));
}
* else后边的是经过推算得出的圆弧函数的代码
*/

//int _FPStime如果传入-1则无时间限制，单位为帧，而此时输入的数据都是以每秒为单位
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
    bool Finished();    //仅确定有时间限制的动画是否结束

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
