#pragma once
namespace ACGCross{
namespace Galgame{

class Clock{
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

}
}