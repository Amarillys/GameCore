<<<<<<< HEAD
#pragma once
#include "../Core/Core.h"

=======
#include "../Core/Core.h"
#include "../Misc/MathFunc.h"
>>>>>>> origin/master
#include "../Misc/NumTexture.h"


class Clock:public Core::RenderDrawer{
private:
    Core::Texture m_fg;
    NumTexture m_clk;

    int m_bx;

    int m_x;
    int m_y;
    int m_numWei;
    int m_fgWei;

    int m_stat;

    bool m_visible;
    bool m_visible_l;

    char m_sz [4];
    bool m_fg_showing;
    float m_fg_last = 0.0;
    Core::Timer m_timer_fg;
public:
<<<<<<< HEAD
    ~Clock(){};
    void OnNext();
    void OnDraw();
    void Init(const std::string& num,const std::string& fg);  //必须先Init，否则可能出错
    void Destory();
    void Hide();
    void Show();
    void SetPos(int x,int y);
    bool GetVisible(){return m_visible_l;}
};

class GameMenuBtn:public Core::RenderDrawer,public Core::Control
{
private:
    Core::Texture m_list,
                        m_btn;

    bool m_visible_l;

    int m_x,
         m_y,
         m_stat;

    Core::Timer m_timer;

    SDL_Rect m_cont;

public:
    GameMenuBtn(){};
    ~GameMenuBtn(){};
    void OnNext();
    void OnDraw();
    void Init(const std::string& menuBtn);  //必须先Init，否则可能出错
=======
    void OnNext();
    void OnDraw();
    void OnInit(const std::string& num,const std::string& fg);  //������Init��������ܳ���
>>>>>>> origin/master
    void Destory();
    void Hide();
    void Show();
    void SetPos(int x,int y);
    bool GetVisible(){return m_visible_l;}
<<<<<<< HEAD
    bool Proc (const SDL_Event* e,Core::Activity*);
=======
>>>>>>> origin/master
};

class GalgameUI:public Core::Activity
{

private:
    Clock m_clk;
<<<<<<< HEAD
    GameMenuBtn m_menuBtn;
public:
    GalgameUI();
    ~GalgameUI(){};
    void OnShow();
    void OnHide();
    void OnNext();
    void OnDraw();
    void OnEvent(const SDL_Event* e);
    void OnEvent(const Core::Control*,const int);
=======
public:
    GalgameUI(){};
    void OnShow();
    void OnHide(){};
    void OnNext();
    void OnDraw();
    void OnEvent(const SDL_Event* e);
>>>>>>> origin/master
};
