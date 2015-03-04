#ifndef _HEAD_THREAD_
#define _HEAD_THREAD_
//�߳���
//�̺߳���ԭ��
//void func(Thread*);

#include "SDLbase.h"
namespace Core
{
    class Thread;

    //���̵߳�������������������ڵĶ�����void*ָ��������Ķ���
    int LaunchThread(void*);

    //�̺߳�����ʹ�õĺ���
    int GetMsg(Thread* obj);    //ȡ���������Ϣ
    void ReturnMsg(Thread* obj,const int msg);  //����һ����Ϣ��Thread����ʹ�����ʹ�ó�Ա������ȡ
    void WaitMsg(Thread*,const int); //�ȴ�ָ����Ϣ�������ų�������Ϣ
    int WaitMsg(Thread*);   //�ȴ�һ����0��Ϣ����
    void* GetData(Thread*);  //ȡ��һ������Thread���������ݣ�����������򷵻أ�����ȴ�һ�����ݴ���
    void ReturnData(Thread*,void* const);   //��һ�����ݷ��ظ�Thread��������������һ������δ�����ܣ���ȴ�������

    /*
    class Locker
    {

    public:
        virtual void Lock() =0;
        virtual void Unlock() =0;
    };
    */

    class Mutex
    {
    private:
        SDL_mutex* m_mtx;

    public:
        inline Mutex(){m_mtx = SDL_CreateMutex();};
        inline ~Mutex(){SDL_DestroyMutex(m_mtx);};
        virtual void Lock(){SDL_LockMutex(m_mtx);};
        virtual void Unlock(){SDL_UnlockMutex(m_mtx);};
    };

    class Thread:public Mutex
    {
        friend int LaunchThread(void*);
        friend int GetMsg(Thread*);
        friend void ReturnMsg(Thread*,const int);
        friend void* GetData(Thread*);
        friend void ReturnData(Thread*,void* const);

    private:
        void (*m_func)(Thread*);
        volatile int m_imsg;
        volatile int m_omsg;
        volatile void* m_idata;
        volatile void* m_odata;
        volatile bool m_running;
        SDL_Thread* m_thread;

    public:
        Thread(void (*func)(Thread*));
        ~Thread();
        void Run();
        bool Running();
        void WaitFinish();  //�ȴ��߳̽���
        int GetMsg();   //ȡ���������Ϣ������Ϊ0
        int WaitMsg();  //�ȴ�������һ����0����Ϣ
        void WaitMsg(const int msg);    //�ȴ�ָ����Ϣ�������ų�������Ϣ
        void SendMsg(const int msg);    //������Ϣ�������������Ϣδ���ܣ��ȴ�������ɽ��ܺ��ٴ���
        void SendData(void* const); //�������ݣ�������������ݻ�û��ȡ����ȴ���ȡ�ú��ٷ���
        void* GetData();    //ȡ�����ݣ����û��Ҫȡ��������ȴ�һ�����ݱ�����
    };
}
#endif // _HEAD_THREAD_
