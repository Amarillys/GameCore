#ifndef _HEAD_GLOBALS_
#define _HEAD_GLOBALS_

#include "SDLbase.h"
#include <string>
#include <set>
namespace Core{
    class Activity;
    extern SDL_Window* pWnd;
    extern SDL_Renderer* pRnd;
    extern std::set<Activity*> actList;
    void CoreInit();    //��ܳ�ʼ��
    void CoreMain(Activity*);   //���ִ��
    void SendEvent(const SDL_Event*,Activity*);  //��һ���������Ϣ
    void Goto(Activity*);   //���ת

    template<class T>
    T* NewActivity() //��Ӧ��ʹ�ø÷��������
    {T* p = new T();actList.insert((Activity*)p);return p;}
}

#define BYTE unsigned char


#include "OS.h"
#endif
