#ifndef _HEAD_CONTROL_
#define _HEAD_CONTROL_

#include "SDLbase.h"


/* �ؼ�������� */
/*
�ؼ�����Ӧ����View����
������ʱ�������ꡢ�����ڵ�ǰ�ؼ���������
�����Proc������Ӧ����������Ȼ���ٵ��û�е�Proc������һ��������
*/
namespace Core{
    class Activity;
    class Control   //�ؼ�����
    {
    public:
        virtual bool Proc (const SDL_Event* e,Activity*) =0;
        //�ص�����,������Ϣ������ÿؼ����ܴ���Ϣ���򷵻�true�����򷵻�false
    };
}

#endif // _HEAD_CONTROL_
