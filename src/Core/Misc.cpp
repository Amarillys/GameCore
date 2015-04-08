#include "Misc.h"
#include "SDLbase.h"
#include "Activity.h"
#include "Globals.h"

using namespace std;
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

void Core::Pos(int& opr_x,int& opr_y,
                        float x,float y)
{
    opr_x = pRnd.GetW() * x;
    opr_y = pRnd.GetH() * y;
}

void Core::Pos(int& opr_x,int& opr_y,
                        const char base,int x,int y)
{
    if((base & 0xF0) == 0xA0) opr_x = pRnd.GetW()/3;
    else if((base & 0xF0) == 0xB0) opr_x = pRnd.GetW()/3 * 2;
    else opr_x = (pRnd.GetW()/4) * ((base & 0xF0) / 0x10) + x;

    if((base & 0x0F) == 0x0A) opr_y = pRnd.GetH()/3;
    else if((base & 0x0F) == 0x0B) opr_y = pRnd.GetH()/3 * 2;
    else opr_y = (pRnd.GetH()/4) * (base & 0x0F) + y;
}

bool Core::InRect(const SDL_Rect& r,int x,int y)
{
    return
        x >= r.x && x <= r.x + r.w &&
        y >= r.y && y <=r.y + r.h;
}

void Core::Activity::RegControl(Control& c)
{m_ansList.push_front(&c);}
