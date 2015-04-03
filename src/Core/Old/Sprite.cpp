#include "Sprite.h"

using namespace Core;

void Sprite::LoadImage(const std::string& file)
{
    Texture::LoadImage(file);
    int w,h;
    Texture::GetInfo(w,h);
    Texture::SetSrc(0,0,w,h);
    Sprite::SetPos(0x22,0,0);
}

void Sprite::LoadText(Font& font,std::string& text)
{
    Texture::LoadText(font,text);
    int w,h;
    Texture::GetInfo(w,h);
    Texture::SetSrc(0,0,w,h);
    Sprite::SetPos(0x22,0,0);
}

void Sprite::SetPos(float x, float y)
{
    CRect(m_dst,x,y);
}

void Sprite::SetPos(char base,int x,int y)
{
    CRect(m_dst,base,x,y);
}

void Sprite::SetZoom(float w,float h)
{
    int w2,h2;
    Texture::GetInfo(w2,h2);
    Texture::SetZoom(w2*w,h2*h);
}
