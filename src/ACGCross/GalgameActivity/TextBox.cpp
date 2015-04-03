#include "../GalGameActivity.h"

using namespace std;
using namespace Core;
using namespace ACGCross::Galgame;

/*状态码解释

0 普通状态，没有字符被显示或输出已完成
1 输出状态，开始进行输出
2 全部输出的特效中状态，直接全部输出
3 消失中
4 隐藏
5 隐藏的消失中状态
6 Show()的特效中状态

*/




void TextBox::Init()
{

}

void TextBox::Destory()
{

}

void TextBox::SetWindow(char base, int x, int y, int w, int h)
{
    Pos(m_window.w,m_window.h,base,x,y);
    m_window.w = w;
    m_window.h = h;
}

void TextBox::SetFont(const std::string& font)
{
    m_font.Open(font);
}

void TextBox::SetEffect(int effectNumber, int fps)
{
    m_effectFps = fps;
    m_effectType = effectNumber;
}

void TextBox::ShowString(const std::wstring text)
{
    m_stat = 1;
    m_input = text;
    m_inputCut = 0;
}

void TextBox::Clear()
{
    m_stat = 3;
}

void TextBox::SetSpeed(int _time)
{
    m_speedFps = _time;
}

void TextBox::SetColor(Uint8 r,Uint8 g,Uint8 b)
{
    m_color = {r,g,b};
}

void TextBox::SetCharSize(int s)
{
    m_wordSize = s;
}

void TextBox::Hide()
{
    m_stat = 5;
}

void TextBox::Show()
{
    m_stat = 6;
}

bool TextBox::GetVisible()
{
    return m_stat != 4 || m_stat != 5;
}

void TextBox::OnDraw()
{
    if(m_stat == 0){
        return;
    }
}

void TextBox::OnNext()
{
    if(m_stat == 0){
        m_showedText.OnDraw();
    }
}

bool TextBox::Finished()
{
    return m_stat == 0 || m_stat == 4;
}

void TextBox::StopAnimation()
{
    m_stat = 2;
}

