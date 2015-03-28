#pragma once
#include "../Core/Core.h"
#include "../Misc/NumTexture.h"

class GalgameUI_TextBox
{
private:
    //文字窗样式
    SDL_Rect m_window;
    //Core::Font m_font;

    //基本属性
    int m_stat; //状态码

    //渲染
    Core::Texture m_showedText;
    Core::Texture m_showingChar;

    //文字显示配置
    int m_speedFps;
    SDL_Color m_color;
    int m_effectType;
    int m_effectFps;
    int m_wordSize;
    Core::Font m_font;

    //文字内容
    std::wstring m_input;
    Uint16 m_inputCut;
public:
    void Init();
    void SetWindow(char base,int x,int y,int w,int h);
    void SetFont(const std::string& font);

    void SetEffect(int effectNumber,int fps);

    void ShowString(const std::wstring);
    void Clear();
    void SetSpeed(int _time);
    void SetColor(Uint8 r,Uint8 g,Uint8 b);
    void SetCharSize(int s);    //中文字长宽相等，英文字以高度为主

    void Hide();
    void Show();
    bool GetVisible();

    void OnDraw();
    void OnNext();
    bool Finished();
    void StopAnimation();
};


class GalgameUI_Clock{
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
    void OnNext();
    void OnDraw();
    void Init(const std::string& num,const std::string& fg);  //必须先Init，否则可能出错
    void Destory();
    void Hide();
    void Show();
    void SetPos(int x,int y);
    bool GetVisible(){return m_visible_l;}
};

class GalgameUI_GameMenuBtn:public Core::Control
{
private:
    Core::Texture m_btn;

    bool m_visible_l;

    int m_x,
         m_y,
         m_stat,
         m_showstat;

    Core::Timer m_timer;

    SDL_Rect m_rect;

public:
    GalgameUI_GameMenuBtn(){};
    void OnNext();
    void OnDraw();
    void Init(const std::string& menuBtn);  //必须先Init，否则可能出错
    void Destory();
    void Hide();
    void Show();
    void SetPos(int x,int y);
    bool GetVisible(){return m_visible_l;}
    bool OnEvent (const SDL_Event* e,Core::Activity*);
};

class GalgameUI:public Core::Activity
{

private:
    GalgameUI_Clock m_clk;
    GalgameUI_GameMenuBtn m_menuBtn;
    GalgameUI_TextBox m_textBox;
public:
    GalgameUI();
    void OnShow();
    void OnHide();
    void OnNext();
    void OnDraw();
    void OnEvent(const SDL_Event* e);
    void OnEvent(Core::Control* c,const int);
};
