#ifndef _HEAD_ACGCROSS_GALGAME_CORNER_
#define _HEAD_ACGCROSS_GALGAME_CORNER_

#include "Core.h"

namespace ACGCross {
namespace Galgame {


class Corner
{
    public:
        void Init();
        void Destory();
        void OnNext();
        void OnDraw();

        void Hide();
        void Show();
        bool Finished();

        bool GetVisible();

        void SetFadeSpeed(int time);
        void SetTopAlpha(int a);

    protected:
    private:
        Core::Texture m_corner;
        double m_ang;
        int m_stat;
        int m_fadeFpsTime;
        int m_fpsCounter;
        int m_topAlpha;
};

}
}

#endif // _HEAD_ACGCROSS_GALGAME_CORNER_
