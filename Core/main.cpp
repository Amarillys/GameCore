#include "Core.h"
#include "../Activities/Test.h"

using namespace std;
using namespace Core;

int main( int argc, char * argv[] )
{

    CoreInit();
    ResFile::Init("000");
    TestActivity* a = NewActivity<TestActivity>();
    TestActivity2* b = NewActivity<TestActivity2>();
    a -> SetTo(b);b ->SetTo(a);
    CoreMain(a);
    ResFile::Quit();
    return 0;
}



/*
int smain( int argc, char * argv[] )
{
    PNT("Compiled at ");
    PNT(__DATE__);
    PNT(" ");
    PNT(__TIME__);
    PNT(endl);
    //初始化

    ResFile::Init("000");


    ResFile::OpenPkg("pkr.cpk");    //打开文件包
    //主循环
    {
        Font f("msyh.ttf");
        Sound s;
        s.Load("battle-day.wav");
        s.Play_Loop();
        Texture t,bg,txt;
        bg.LoadImage("bg.png");
        t.LoadImage("0.png");
        txt.LoadText(f,"文字纹理");
        t.SetSrc(0,0,290,290);
        bg.SetSrc(0,0,1024,768);
        txt.SetPos(0,0);
        t.SetPos(0,310);
        bg.SetPos(0,0);
        t.SetZoom(290,290);
        bg.SetZoom(1024,768);
        //t.SetAlpha(175);
        t.SetBlend(SDL_BLENDMODE_MOD);
        //t.SetColor(255,0,0);
        //bg.SetColor(255,0,0);
        RFList.push_back(&bg);
        RFList.push_back(&t);
        RFList.push_back(&txt);
        PNT(TTF_GetError());

        Timer FPSCounter_Timer,FPSKiller;
        Uint32 FPSCounter = 0;
        FPSKiller.Reset();
        while(1){
            while(SDL_PollEvent(&e)){
                if (e.type == SDL_QUIT) goto END;
            }
            SDL_RenderClear(pRnd);
            for(register auto p = RFList.begin();p != RFList.end();++p) (*p) -> OnDraw();
            SDL_RenderPresent(pRnd);

            FPSKiller.WaitTimer(100/60);   //FPS限制
            FPSKiller.Reset();

            FPSCounter ++;
            if (FPSCounter_Timer.GetTimer()>=1000) {
                    PNT("FPS:");
                    PNT(FPSCounter);
                    PNT(endl);
                    FPSCounter_Timer.Reset();
                    FPSCounter = 0;
            }

        }
    }


    //回收
    END:

    return 0;
}
*/
