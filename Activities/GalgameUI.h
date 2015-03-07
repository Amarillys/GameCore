#include "../Core/Core.h"
#include "../Misc/MathFunc.h"
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
    void OnNext();
    void OnDraw();
    void OnInit(const std::string& num,const std::string& fg);  //������Init��������ܳ���
    void Destory();
    void Hide();
    void Show();
    void SetPos(int x,int y);
    bool GetVisible(){return m_visible_l;}
};

class GalgameUI:public Core::Activity
{

private:
    Clock m_clk;
public:
    GalgameUI(){};
    void OnShow();
    void OnHide(){};
    void OnNext();
    void OnDraw();
    void OnEvent(const SDL_Event* e);
};
