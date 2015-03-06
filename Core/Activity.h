#include <list>
#include "SDLbase.h"

namespace Core{
    class Activity;
    class Control;
    class Animation;

    class Activity
    {
    friend void Core::SendEvent(SDL_Event* e,Activity* a);
    protected:
        std::list<Control*> m_ansList;
        //�����Control��Ҫ��Ӧ�����������ӵ��������
    public:
        virtual ~Activity(){};


        virtual void OnShow(){};    //��Goto������ʱִ��
        virtual void OnHide(){};    //��Goto������ʱִ��

        virtual void OnDraw()=0;    //���ƻ
        virtual void OnEvent(const SDL_Event*){};
        //��û�пؼ�������Ϣʱ���ص��˺���
        virtual void OnEvent(Control*,const int){};
        //���пؼ�������Ϣʱ����Control���ô˺�����������ؼ�������Ϣ

        virtual void OnNext() {};   //��������붯���͵��������������ж�������һ֡

        virtual Animation* GetAnimationOnShow(){return nullptr;}
        //���붯�����л�ʱ���ϸ������ĵ�������ͬʱ����

        virtual Animation* GetAnimationOnHide(){return nullptr;}
        //�����������л�ʱ���¸������ĵ��붯��ͬʱ����
    };
}
