#ifndef _HEAD_SPRITE_
#define _HEAD_SPRITE_

#include "View.h"
#include "Texture.h"

/* 精灵类 派生于纹理类，可以作为视图子节点使用。 */
namespace Core{
    class Sprite:public View,public Texture
    {
    public:
        using Texture::SetZoom;

        void LoadImage(const std::string& file);  //从文件加载图像并自动设置大小、缩放
        void LoadText(Font&,std::string&); //加载文字并自动设置大小、缩放

        void SetPos(float x, float y);   //设置位置
        void SetPos(char base,int x,int y);

        void SetZoom(float w,float h);  //设置缩放
        virtual ~Sprite(){};
    };
}

#endif // _HEAD_SPRITE_
