#ifndef _HEAD_RENDERDRAWER_
#define _HEAD_RENDERDRAWER_

/* 绘制类 */
/* 继承于该类的子类可以绘制东西到屏幕上 */
namespace Core
{
    class RenderDrawer{
    public:
        virtual void OnDraw() = 0;
        virtual ~RenderDrawer(){};
    };
}
#endif
