#include "ACGCross/GalgameActivity/TextBox.h"
#include "ACGCross/MathFunc.h"

using namespace Core;
using namespace std;

namespace ACGCross {
namespace Galgame {

#define NOEVENT 0   //闲置
#define TXT_SHOWING 1  //文字显示中
//define TXT_CHANGWORD 2 //文字交替中
#define TXT_KILLING 3   //文字消除中
#define TXT_STOPSPEAK 4 //文字全部强制显示
//define RECT_SHOW 10   //全局显示
#define RECT_HIDE 11   //全局隐藏
#define RECT_SHOWING 12 //正在全局显示
#define RECT_HIDING 13  //正在全局隐藏

TextBox::TextBox()
{
    //ctor
}

TextBox::~TextBox()
{
    //dtor
}

void TextBox::SetColor(int r, int g, int b)
{m_r = r;m_g = g;m_b = b;}

void TextBox::SetFont(Core::Font& f)
{m_font = &f;}

void TextBox::SetHeight(int h)
{m_word_h = h;}

void TextBox::Br()
{
    m_lineWord.push_back(0);
    m_linePos = 0;
    m_heiPos += m_word_h;
}

void TextBox::ForceClear()
{
    m_text.clear();
    m_lineWord.clear();
    m_lineWord.push_back(0);
    m_stat = TXT_KILLING;
    m_linePos = 0;
    m_heiPos = 0;
    m_showing_word = 0;
    m_fpsCounter = m_nowFps;
}

void TextBox::Clear()
{
    m_stat = TXT_KILLING;
    m_fpsCounter = m_nowFps;
}

list<Texture>::iterator TextBox::ForceAddText(const std::wstring& s)
{
    list<Texture>::iterator pFirstTex = --m_text.end();
    FOR_EACH(p,s.begin(),s.end())
    {
        m_lineWord[m_lineWord.size()-1] ++;

        /*渲染文字纹理*/
        m_text.push_back(Core::Texture());
        auto pTex = --m_text.end();
        wstring str;
        str += *p;
        pTex -> Load(*m_font,str);

        pTex -> SetColor(m_r,m_g,m_b);
        pTex -> SetAlpha(255);

        /*求文字需要的数据*/
        //宽度
        int w;
        {
            int t_w,t_h;
            pTex -> GetInfo(t_w,t_h);
            float w_zoom = float(m_word_h) / t_h;
            w = w_zoom * t_w;
            pTex ->SetZoom(w,m_word_h);
        }

        //位置
        {
            if(w + m_linePos > m_rect.w)
                Br();

            pTex ->SetPos(m_rect.x + m_linePos,m_rect.y + m_heiPos);
            m_linePos += w;
        }
    }
    return ++pFirstTex;
}

void TextBox::AddText(const std::wstring& s)
{
    auto pstart = ForceAddText(s);
    FOR_EACH(p,pstart,m_text.end())
        p -> SetAlpha(0);
    m_stat = TXT_SHOWING;
    m_fpsCounter = m_nowFps;
}

void TextBox::OnNext()
{
    if(m_stat == TXT_SHOWING){
        m_nowFps++;
        if(m_nowFps - m_fpsCounter >= Uint16(m_fpsSpeed))
        {
            auto p = m_text.begin();
            for(int i = 0;i < m_showing_word ; ++i)
                ++p;
            p -> SetAlpha(255);

            m_showing_word ++;
            if(Uint32(m_showing_word) >= Uint32(m_text.size())){
                m_stat = NOEVENT;
                return;
            }
            m_fpsCounter = m_nowFps;
        }else{
            auto p = m_text.begin();
            for(int i = 0;i < m_showing_word ; ++i)
                ++p;
            p -> SetAlpha(
                ArcFunc(float(m_nowFps - m_fpsCounter) / FPS) * 255);
        }
    }else if(m_stat == TXT_KILLING){
        m_nowFps++;
        if(m_nowFps - m_fpsCounter >= Uint16(m_fpsSpeed)){
            ForceClear();
            m_stat = NOEVENT;
            return;
        }else{
            FOR_EACH(p,m_text.begin(),m_text.end())
                p -> SetAlpha(255 - ArcFunc(float(m_nowFps - m_fpsCounter) / FPS) * 255);
        }
    }
}

void TextBox::OnDraw()
{
    FOR_EACH(p,m_text.begin(),m_text.end())
        p -> OnDraw();
}

bool TextBox::Finished()
{return m_stat == NOEVENT;}

void TextBox::Init()
{
    m_lineWord.push_back(0);
    m_fpsSpeed = 20;
    m_stat = 0;
    m_nowFps = 0;
    SetColor(255,255,255);
    m_showing_word = 0;

    m_linePos = 0;  //现在已经显示到的横行坐标
    m_heiPos = 0;  //现在已经显示到的竖行坐标
}

void TextBox::Destroy()
{}

void TextBox::SetSpeed(int time)
{m_fpsSpeed = float(time) / 1000 * FPS;}

void TextBox::StopSpeak(int time)
{m_stat = 4;}

void TextBox::SetRect(int x, int y, int w, int h)
{m_rect = {x,y,w,h};}

void TextBox::Hide()
{m_stat = RECT_HIDING;}

void TextBox::Show()
{m_stat = RECT_SHOWING;}


} // namespace Galgame
} // namespace ACGCross
