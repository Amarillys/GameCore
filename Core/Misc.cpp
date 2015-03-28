#include "Misc.h"
#include "SDLbase.h"
#include "Activity.h"
#include "Globals.h"

using namespace Core;

const int Window_H = pRnd.GetH(),Window_W = pRnd.GetW();

void Core::GetString(std::ifstream& in,std::string& str)
{
    str = "";
    while(1)
    {
        char ch = in.get();
        if(ch == '\0') break;
        else str += ch;
    }
}

void Core::Pos(SDL_Rect& opr,
                        float x,float y)
{
    opr.x = Window_W * x;
    opr.y = Window_H * y;
}

void Core::Pos(SDL_Rect& opr,
                        const char base,int x,int y)
{
    const static int screen_w_p = Window_W/4;
    const static int screen_h_p = Window_H/4;
    opr.x = screen_w_p * ((base & 0xF0) / 0x10) + x;
    opr.y = screen_h_p * (base & 0x0F) + y;
}

bool Core::InRect(const SDL_Rect& r,int x,int y)
{
    return
        x >= r.x && x <= r.x + r.w &&
        y >= r.y && y <=r.y + r.h;
}
