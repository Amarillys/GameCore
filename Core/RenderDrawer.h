#ifndef _HEAD_RENDERDRAWER_
#define _HEAD_RENDERDRAWER_

/* ������ */
/* �̳��ڸ����������Ի��ƶ�������Ļ�� */
namespace Core
{
    class RenderDrawer{
    public:
        virtual void OnDraw() = 0;
        virtual ~RenderDrawer(){};
    };
}
#endif
