#ifndef _HEAD_TIMER_
#define _HEAD_TIMER_
#include "../Debug.h"

/***** 计时器 *****
* 类似NS的那种方法。
* 每一个对象都可以是独立的计时器，但是它们使用共同的底层计时器。
* 原理是使用时间差。
* Reset重置Timer为0。
* GetTimer返回当前的时间值（毫秒数）。
* WaitTimer用来使用SDL_Delay等待计时器跑到一定时间。
* 2014.8.24
******************/

#include "SDLbase.h"
namespace Core
{
    class Timer
    {
    private:
        Uint32 m_timeStartPos;
    public:
        inline Timer();
        inline void Reset();
        inline Uint32 GetTimer();
        inline void WaitTimer(Uint32);
    };


    Timer::Timer(void)
    {
        Reset();
    }

    void Timer::Reset()
    {
        m_timeStartPos = SDL_GetTicks();
    }

    Uint32 Timer::GetTimer()
    {
        return SDL_GetTicks() - m_timeStartPos;
    }

    void Timer::WaitTimer(Uint32 _time)
    {
        Uint32 t = GetTimer();
        if (_time < t) {PNT("Timer:Not Wait\n");return;}
        else {SDL_Delay(_time - t);PNT("Timer:Wait "<<_time<<"     "<<t<<"   "<<_time - t<<std::endl);};
    }
}

#endif // _HEAD_TIMER_
