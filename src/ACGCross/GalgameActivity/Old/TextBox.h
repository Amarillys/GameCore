#pragma once
namespace ACGCross{
namespace Galgame{

class TextBox
{
private:
    //文字窗样式
    SDL_Rect m_window;

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
    void Destory();
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

}
}
