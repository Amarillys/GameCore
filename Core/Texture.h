#ifndef _HEAD_TEXTURE_
#define _HEAD_TEXTURE_

#include "Globals.h"
//#include "RenderDrawer.h"
#include "FileSystem.h"


/* 纹理类 属于SDL封装部分，不要在活动层使用。*/
namespace Core
{
    class Font;
    class Texture//: public RenderDrawer
    {
    protected:
        SDL_Texture * m_tex;
        SDL_Rect m_src;
        SDL_Rect m_dst;
        ResFile m_file;
    public:
        Texture();
        void OnDraw();
        void Clear();
        void Load(const std::string& file);  //从文件加载图像
        void Load(Font&,const std::string&); //加载文字
        void Load(SDL_Surface*);
        void Load(SDL_Texture*);
        void SetSrc(int x, int y, int w, int h); //图像剪裁
        void SetPos(int x, int y);   //设置位置
        void SetPos(char base,int x,int y);
        void SetPos(float x,float y);
        void SetZoom(int w, int h);  //设置缩放
        void SetAlpha(Uint8);   //透明度
        void SetColor(Uint8 R,Uint8 G,Uint8 B); //色调调整
        void SetBlend(SDL_BlendMode);   //设置SDL透明方式
        /*
        std::SDL_BLENDMODE_NONE  不透明（默认）
        std::SDL_BLENDMODE_BLEND 普通透明
        std::SDL_BLENDMODE_ADD   亮白色半透明
        std::SDL_BLENDMODE_MOD   黑暗半透明
        */
        void GetInfo(int& w,int& h);    //取得信息
        bool InRect(int x, int y);   //判断某坐标是否在该纹理范围内
        virtual ~Texture();
    };
}
#endif // _HEAD_TEXTURE_
