#ifndef _HEAD_ANIMATION_
#define _HEAD_ANIMATION_

namespace Core{
    class Animation
    {
    public:
        virtual void OnNext() =0;  //��Ҫ��һ֡����ʱ
        virtual bool Finished() =0;    //�Ƿ��Ѿ���ɸö���
    };
}

#endif // _HEAD_ANIMATION_
