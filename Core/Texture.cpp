#include "Globals.h"
#include "Texture.h"
#include "Font.h"
#include <string>
#include "Misc.h"
#include "../Debug.h"
using namespace std;
using namespace Core;
void Texture::Load(const std::string& fileName)
{
    Clear();
    m_file.Load(fileName);
    m_tex = IMG_LoadTexture_RW(pRnd,(SDL_RWops*)m_file,m_file.Size());
    int w,h;
    GetInfo(w,h);
    SetSrc(0,0,w,h);
    SetZoom(w,h);
}

void Texture::Load(Font& font,const string& text)
{
    Clear();
    SDL_Color fg = {255,255,255};
    SDL_Surface* pSur = TTF_RenderUTF8_Blended((TTF_Font*)font,text.c_str(),fg);
    Load(pSur);
    SDL_FreeSurface(pSur);
}

void Texture::Load(SDL_Surface* pSur)
{
    int w,h;
    m_tex = SDL_CreateTextureFromSurface(pRnd,pSur);
    GetInfo(w,h);
    SetSrc(0,0,w,h);
    SetZoom(w,h);
}

void Texture::Load(SDL_Texture* pTex)
{
    m_tex = pTex;
}

Texture::Texture()
{
    m_tex = nullptr;
}

void Texture::OnDraw()
{
    SDL_RenderCopy(pRnd, m_tex, &m_src,&m_dst);
}

void Texture::Clear()
{
    if(m_tex != nullptr)
    {
        SDL_DestroyTexture(m_tex);
        m_tex = nullptr;
    }
    m_file.Free();
}

void Texture::SetSrc(int x, int y, int w, int h)
{
    m_src = {x, y, w, h};
}

void Texture::SetPos(int x, int y)
{
    m_dst.x = x;
    m_dst.y = y;
}

void Texture::SetPos(char base,int x,int y)
{
    Pos(m_dst,base,x,y);
}

void Texture::SetPos(float x,float y)
{
    Pos(m_dst,x,y);
}

void Texture::SetZoom(int w,int h)
{
    m_dst.w = w;
    m_dst.h = h;
}

void Texture::SetAlpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(m_tex,alpha);
}

bool Texture::InRect(int x, int y)
{
    return x >= m_dst.x && x <= m_dst.x + m_dst.w && y >= m_dst.y && y <= m_dst.y + m_dst.h;
}

void Texture::SetColor(Uint8 R,Uint8 G,Uint8 B)
{
    SDL_SetTextureColorMod(m_tex,R,G,B);
}

void Texture::SetBlend(SDL_BlendMode bln)
{
    SDL_SetTextureBlendMode(m_tex,bln);
}

void Texture::GetInfo(int& w,int& h)
{
    SDL_QueryTexture(m_tex,nullptr,nullptr,&w,&h);
}

Texture::~Texture()
{
    Clear();
    PNT("Texture Killed:"<<this<<std::endl;)
}
