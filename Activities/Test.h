#include "..\Core\Core.h"
#include <iostream>
using namespace Core;
using namespace std;

class TestControl:public Control    //该控件接管键盘按键处理
{
public:
    bool Proc (const SDL_Event* e,Activity* a)
    {
        if (e -> type == SDL_KEYDOWN){
            a -> OnEvent(this,233);
            return true;
        }else return false;
    }
};

class XMove:public Animation
{
private:
    Texture* m_tex;
    int k;
public:
    XMove(){k = 401;}
    void SetArg(Texture* t)
    {
        m_tex = t;
        k = 0;
    }
    void OnNext()
    {
        m_tex -> SetPos(k,k);
        k++;
    }
    bool Finished(){return k>=400;}
};

class TestActivity:public Core::Activity
{
private:
    Core::Texture m_t1;
    Core::Sound m_s1;
    TestControl m_ctr;
    XMove m_xmv;
    Activity* m_tr;
public:
    TestActivity()
    {
        m_t1.LoadImage("bg.png");
        m_t1.SetPos(0x20,0,0);
        m_s1.Load("battle-day.wav");
        m_ansList.insert(&m_ctr);
    }
    ~TestActivity(){cout<<"Test1Killed"<<endl;}
    void OnShow(){
        m_s1.Play();
    }
    void OnHide(){m_s1.Stop();}
    void OnDraw(){m_t1.OnDraw();};
    void SetTo(Activity* t){m_tr = t;}

    void OnEvent(const SDL_Event* e){
        if (e -> type == SDL_MOUSEBUTTONDOWN) cout<<"MOUSE_DOWN"<<endl;
        if (e -> type == SDL_MOUSEBUTTONUP) m_xmv.SetArg(&m_t1);
    };

    void OnEvent(Control* c,const int i){
        Goto(m_tr);
    };
    void OnNext(){
        if (!m_xmv.Finished()) m_xmv.OnNext();
    };
    Animation* GetAnimationOnHide(){return nullptr;}
};

class TestActivity2:public Core::Activity DBGCLASS
{
private:
    Core::Texture m_t1;
    TestControl m_ctr;
    XMove m_xmv;
    Activity* m_tr;
public:
    TestActivity2()
    {
        DBGCLASS_SETDBGINFO(m_t1,"testTexture");
        m_t1.LoadImage("bg.png");
        m_t1.SetPos(0x20,0,0);
        m_ansList.insert(&m_ctr);
    }
    ~TestActivity2(){cout<<"Test2Killed"<<endl;}
    void OnShow(){}
    void OnHide(){}
    void OnDraw(){m_t1.OnDraw();};
    void SetTo(Activity* t){m_tr = t;}

    void OnEvent(const SDL_Event* e){
        if (e -> type == SDL_MOUSEBUTTONDOWN) cout<<"MOUSE_DOWN"<<endl;
        if (e -> type == SDL_MOUSEBUTTONUP) m_xmv.SetArg(&m_t1);
    };

    void OnEvent(Control* c,const int i){
        Goto(m_tr);
    };
    void OnNext(){
        if (!m_xmv.Finished()) m_xmv.OnNext();
    };
};
