#include "ACGCross\NumTexture.h"
using namespace ACGCross;


void NumTexture::SetNum(char n)
{
    int w,h;
    GetInfo(w,h);
    w /= 10;
    SetSrc(w * (n - '0'),0,w,h);
}


void NumTexture::Load(const std::string& fileName)
{
    Texture::Load(fileName);
    int w,h;
    GetInfo(w,h);
    SetZoom(w/10,h);
}

int NumTexture::GetWei()
{
    int w,h;
    GetInfo(w,h);
    return w / 10;
}


