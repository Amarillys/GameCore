#include <sdl.h>
#include "Core/Bg.h"
#include "Core/Globals.h"

using namespace Core;

void Bg::Init()
{

}

void Bg::Load(const char * Bg_Filename,Display_Mode dp_mode)
{
    Bg_Sur=IMG_Load(Bg_Filename);
    Bg_Tex.Load(Bg_Sur);
    Bg_Tex.GetSize( BgRect.w , BgRect.h );
    win_w = pRnd.GetW();    //获取窗口宽度
    win_h = pRnd.GetH();    //获取窗口长度

    switch(dp_mode)
    {
    case CENTER:    //居中
        BgRect.x = ( win_w - BgRect.w ) / 2;
        BgRect.y = ( win_h - BgRect.h ) / 2;
        break;

    case TILE:  //平铺，暂不支持
        break;

    case STRETCH:   //拉伸
        BgRect.x = BgRect.y =0;
        BgRect.w = win_w;
        BgRect.h = win_h;
        break;

    case FILLED:    //填充
        if( BgRect.w / BgRect.h < win_w / win_h)
        {
            BgRect.x = 0;
            BgRect.y = ( win_h - BgRect.h * win_w / BgRect.w ) /2;
            BgRect.h = BgRect.h * win_w / BgRect.w ;
            BgRect.w = win_w ;
        }
        else
        {
            BgRect.x = (win_w- BgRect.w * win_h / BgRect.h ) / 2 ;
            BgRect.y = 0;
            BgRect.w = BgRect.w * win_h / BgRect.h;
            BgRect.h = win_h;
        }
        break;

    default:
    case AUTO:
        //if( w < win_w && h < win_h )

    case ADAPTABLE:
        if( BgRect.w / BgRect.h > win_w / win_h)
        {
            BgRect.x = 0;
            BgRect.y = ( win_h - BgRect.h * win_w / BgRect.w) / 2 ;
            BgRect.h = BgRect.h * win_w / BgRect.w;
            BgRect.w = win_w ;
        }
        else
        {
            BgRect.y = 0;
            BgRect.x = ( win_w - BgRect.w * win_h / BgRect.h) / 2 ;
            BgRect.w = BgRect.w * win_h / BgRect.h;
            BgRect.h = win_h ;
        }
        break;
    }
    Bg_Tex.SetPos( BgRect.x , BgRect.y );
    Bg_Tex.SetZoom( BgRect.w , BgRect.h );
}

void Bg::Effect(const int Effect_Index,const std::string Mask_Filename,const std::string Effect_Time)
{

}

void Bg::OnDraw()
{
    Bg_Tex.OnDraw();
}

void Bg::OnNext()
{
    Bg_Tex.SetAlpha(125);

}

void Bg::Quit()
{

}

Bg::Bg()
{

}

Bg::~Bg()
{

}
