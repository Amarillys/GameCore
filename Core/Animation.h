#ifndef _HEAD_ANIMATION_
#define _HEAD_ANIMATION_

namespace Core{
    class Animation
    {
    public:
        virtual void OnNext() =0;  //需要下一帧动画时
        virtual bool Finished() =0;    //是否已经完成该动画
    };
}

#endif // _HEAD_ANIMATION_
