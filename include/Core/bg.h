#include "SDLbase.h"
#include "FileSystem.h"
#include "Texture.h"

enum Display_Mode{
            AUTO = 0,
            CENTER , //居中
            TILE,   //平铺
            STRETCH,    //拉伸
            FILLED, //填充
            ADAPTABLE   //适应

        };

namespace Core
{
    class Bg
    {
    private:
        Core::Texture Bg_Tex;  //背景文件
        SDL_Surface *Bg_Sur = NULL;
        SDL_Rect BgRect;    //背景的属性，包括 x,y,w,h
        Display_Mode dp_mode;   //背景图加载模式
        int win_w,win_h;

    protected:
        char * Bg_Filename;    //背景文件名
        int Effect_Index;   //效果序号
        std::string Mask_Filename;  //遮片文件名，默认为空
        int Effect_Time;    //效果持续时间

    public:
        Bg();
        ~Bg();
        void Init();
        void Quit();
        void OnNext();
        void Load(const char * Bg_Filename,Display_Mode dp_mode);  //加载图片文件进入，并进行比例处理
        void Effect(const int Effect_Index,const std::string Mask_Filename,const std::string Effect_Time);
        void OnDraw();
        //显示处理
    };
}
