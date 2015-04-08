#pragma once
#include <forward_list>

namespace Core{
class AnimationPool;

/*** 继承于该类以编写动画并将其插入动画池 ***/
class Animation{
protected:
    AnimationPool* m_pool;
public:
    Animation(){m_pool = nullptr;}
    virtual void OnNext() = 0;  //该函数会在请求下一帧时调用
    virtual void Stop(){};  //该函数会在需要停止动画时调用
    virtual void Reset() = 0;    //该函数用于重置动画回初始状态
    virtual bool Finished() = 0;    //返回true表示动画执行完成，否则为未完成
    virtual bool Forever() = 0; //返回true表示该动画永不停止
    virtual ~Animation(){};
};

/*** 动画池 继承于该类以向子类提供同时播放多组动画的功能 ***/
//TODO:未实现
class AnimationPool{
private:
    std::forward_list<Animation*> m_aniList_s;
    std::forward_list<Animation*> m_aniList_h;
public:
    void OnNext();  //请求下一帧
    bool OnceAnimationFinished();   //不永久执行的动画是否已经全部完成
    void StopOnceAnimation();   //停止所有不永远执行的动画
    void StopAllAnimation();    //停止所有动画
    void Install(Animation&);   //安装并启动一个新动画
    void InstallAutoDel(Animation*&);   //把一个在堆中的动画完全交给池托管，完成后自动回收
    ~AnimationPool();
};
}
