#include <list>
#include "Texture.h"

class Sprite:public Texture{

struct SpriteTask{
        short int TaskType;
        int int_arg[8];
        float float_arg[4];
}

private:
        std::list<SpriteTask> m_tasks;
public:
        void OnNext();
        void OnDraw();
        bool Finished();
        void StopAnimation();

        void XMove(int x,int y);
        void XMove(char base,int x,int y);
        void XMove(float x,float y);
        void XMove_Arc(int x,int y);
        void XMove_Arc(char base,int x,int y);
        void XMove_Arc(float x,float y);
        void XSetAlapha(int alp);
        void XSetRoll(...);
        void XSetRGB(Uint8 r,Uint8 g,Uint8 b);
        void XZoom(...);
        void XSetSrc(int x,int y,int w,int h);
        void XStart();
};
