#include "Misc.h"
#include "SDLbase.h"
#include "Activity.h"
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
    static int screen_w = 800;    //TODO:改为SDL获取的大小，下同
    static int screen_h = 600;
    opr.x = screen_w * x;
    opr.y = screen_h * y;
}

void Core::Pos(SDL_Rect& opr,
                        const char base,int x,int y)
{
    static int screen_w_p = 800/4;    //TODO:改为SDL获取的大小，下同
    static int screen_h_p = 600/4;
    opr.x = screen_w_p * ((base & 0xF0) / 0x10);
    opr.y = screen_h_p * (base & 0x0F);
}
