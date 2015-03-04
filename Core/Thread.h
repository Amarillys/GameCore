#ifndef _HEAD_THREAD_
#define _HEAD_THREAD_
//线程类
//线程函数原型
//void func(Thread*);

#include "SDLbase.h"
namespace Core
{
    class Thread;

    //新线程调用这个函数，处理类内的东西，void*指向调用它的对象
    int LaunchThread(void*);

    //线程函数内使用的函数
    int GetMsg(Thread* obj);    //取得输入的消息
    void ReturnMsg(Thread* obj,const int msg);  //返回一个消息给Thread对象使其可以使用成员函数获取
    void WaitMsg(Thread*,const int); //等待指定消息传入且排除其它消息
    int WaitMsg(Thread*);   //等待一个非0消息传入
    void* GetData(Thread*);  //取得一个来自Thread类对象的数据，如果有数据则返回，否则等待一个数据传入
    void ReturnData(Thread*,void* const);   //把一个数据返回给Thread类对象，如果其中有一个数据未被接受，则等待它接受

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
        void WaitFinish();  //等待线程结束
        int GetMsg();   //取得输出的消息，可能为0
        int WaitMsg();  //等待并返回一个非0的消息
        void WaitMsg(const int msg);    //等待指定消息，并且排除其它消息
        void SendMsg(const int msg);    //发送消息，如果子线有消息未接受，等待子线完成接受后再传入
        void SendData(void* const); //发送数据，如果子线有数据还没被取得则等待其取得后再发送
        void* GetData();    //取得数据，如果没有要取得数据则等待一个数据被发出
    };
}
#endif // _HEAD_THREAD_
