#ifndef _HEAD_TIMER_
#define _HEAD_TIMER_
#include "../Debug.h"

/***** ��ʱ�� *****
* ����NS�����ַ�����
* ÿһ�����󶼿����Ƕ����ļ�ʱ������������ʹ�ù�ͬ�ĵײ��ʱ����
* ԭ����ʹ��ʱ��
* Reset����TimerΪ0��
* GetTimer���ص�ǰ��ʱ��ֵ������������
* WaitTimer����ʹ��SDL_Delay�ȴ���ʱ���ܵ�һ��ʱ�䡣
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
