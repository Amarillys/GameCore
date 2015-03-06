#include "Misc.h"
#include "SDLbase.h"
#include "Activity.h"
#include "Globals.h"
using namespace Core;

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
    opr.x = Core::Window_W * x;
    opr.y = Core::Window_H * y;
}

void Core::Pos(SDL_Rect& opr,
                        const char base,int x,int y)
{
    const static int screen_w_p = Window_W/4;
    const static int screen_h_p = Window_H/4;
    opr.x = screen_w_p * ((base & 0xF0) / 0x10);
    opr.y = screen_h_p * (base & 0x0F);
}
