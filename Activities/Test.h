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
public:
    TestActivity()
    {
        m_t1.LoadImage("bg.png");
        m_t1.SetPos(0x20,0,0);
        m_s1.Load("battle-day.wav");
        m_s1.Play();
        m_ansList.insert(&m_ctr);
        m_xmv.SetArg(&m_t1);
    }
    void OnDraw(){m_t1.OnDraw();};

    void OnEvent(const SDL_Event* e){
        if (e -> type == SDL_MOUSEBUTTONDOWN) cout<<"MOUSE_DOWN"<<endl;
    };

    void OnEvent(Control* c,const int i){
        cout<<"Control Event:"<<c<<"-"<<i<<endl;
    };
    void OnNext(){};
    Animation* GetAnimationOnCreated(){return (Animation*)&m_xmv;}
};
