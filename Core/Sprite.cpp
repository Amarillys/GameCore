#include "Sprite.h"

using namespace Core;


void Sprite::SetRoll(float angle, int center_x, int center_y, int time, SDL_RendererFlip flip)
{
    m_rollEnabled = true;
}

void Sprite::XStopTimeUnlimited()
{

}

void Sprite::XStopTimeLimited()
{

}

void Sprite::XStopAll()
{

}

void Sprite::XSetSrc(int x, int y, int w, int h, int _time, float (* EffectConverter)(float x))
{

}

void Sprite::XZoom(int w, int h, int _time, float (* EffectConverter)(float x))
{

}

void Sprite::XSetRGB(Uint8 r, Uint8 g, Uint8 b, int _time, float (* EffectConverter)(float x))
{

}

void Sprite::XSetRoll(float angle, int center_x, int center_y, int _time, SDL_RendererFlip flip, float (* EffectConverter)(float x))
{
    m_rollEnabled = true;
}

void Sprite::XSetAlpha(int alp, int _time, float (* EffectConverter)(float x))
{

}

void Sprite::XMove(float x, float y, int _time, float (* EffectConverter)(float x))
{

}

void Sprite::XMove(char base, int x, int y, int _time, float (* EffectConverter)(float x))
{

}

void Sprite::XMove(int x, int y, int _time, float (* EffectConverter)(float x))
{

}

bool Sprite::Finished()
{
    return true;    //todo:Delete this line;
}

void Sprite::OnDraw()
{
    if(m_rollEnabled) SDL_RenderCopyEx(pRnd,m_tex,&m_src,&m_dst,
                                       m_rollAngle,&m_rollCenter,m_rollFlip);
    else SDL_RenderCopy(pRnd,m_tex,&m_src,&m_dst);
}

void Sprite::OnNext()
{

}

 Sprite::Sprite()
{
    m_rollEnabled = false;
}

