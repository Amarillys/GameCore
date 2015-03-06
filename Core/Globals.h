#ifndef _HEAD_GLOBALS_
#define _HEAD_GLOBALS_

#include "SDLbase.h"
#include <string>
#include <list>
namespace Core{
    class Activity;
    extern SDL_Window* pWnd;
    extern SDL_Renderer* pRnd;
    extern std::list<Activity*> actList;
    extern int Window_W,Window_H;
    void CoreInit(const std::string& title,const int w,const int h);    //��ܳ�ʼ��
    void CoreMain(Activity*);   //���ִ��
    void SendEvent(const SDL_Event*,Activity*);  //��һ���������Ϣ
    void Goto(Activity*);   //���ת

    template<class T>
    T* NewActivity() //��Ӧ��ʹ�ø÷��������
    {T* p = new T();actList.push_front((Activity*)p);return p;}
}

#define BYTE unsigned char


#include "OS.h"
#endif
