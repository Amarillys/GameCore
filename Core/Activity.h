#include <set>
#include "SDLbase.h"

namespace Core{
    class Activity;
    class Control;
    class Animation;

    class Activity
    {
    friend void Core::SendEvent(SDL_Event* e,Activity* a);
    protected:
        std::set<Control*> m_ansList;
        //�����Control��Ҫ��Ӧ�����������ӵ��������
    public:
        virtual ~Activity(){};


        virtual void OnShow(){};    //��Goto������ʱִ��
        virtual void OnHide(){};    //��Goto������ʱִ��

        virtual void OnDraw()=0;    //���ƻ
        virtual void OnEvent(const SDL_Event*)=0;
        //��û�пؼ�������Ϣʱ���ص��˺���
        virtual void OnEvent(Control*,const int)=0;
        //���пؼ�������Ϣʱ����Control���ô˺�����������ؼ�������Ϣ

        virtual void OnNext() =0;   //��������붯���͵��������������ж�������һ֡

        virtual Animation* GetAnimationOnShow(){return nullptr;}
        //���붯�����л�ʱ���ϸ������ĵ�������ͬʱ����

        virtual Animation* GetAnimationOnHide(){return nullptr;}
        //�����������л�ʱ���¸������ĵ��붯��ͬʱ����
    };
}
