#include "ACGCross/GalgameActivity/TextBox.h"

using namespace Core;
using namespace std;

namespace ACGCross {
namespace Galgame {

#define NOEVENT 0   //����
#define TXT_SHOW 1  //������ʾ��
#define TXT_CHANGWORD 2 //���ֽ�����
#define TXT_KILLING 3   //����������
#define TXT_STOPSPEAK 4 //����ȫ��ǿ����ʾ
#define RECT_SHOW 10   //ȫ����ʾ
#define RECT_HIDE 11   //ȫ������
#define RECT_SHOWING 12 //����ȫ����ʾ
#define RECT_HIDING 13  //����ȫ������

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

void TextBox::Br()  //TODO:δ���
{m_lineWord.push_back(0);}

void TextBox::Clear()
{
    m_lineWord.clear();
    m_text.clear();
    m_stat = 3;
}

void TextBox::AddText(const std::wstring& s)
{
    FOR_EACH(p,s.begin(),s.end())
    {
        m_lineWord[m_lineWord.size()-1] ++;
        m_text.push_back(Core::Texture());

        auto pTex = --m_text.end();
        string str;
        str += *p;
        pTex -> Load(*m_font,str);
        pTex -> SetColor(m_r,m_g,m_b);
        pTex -> SetAlpha(0);

        //�ж��Ƿ���Ҫ���С�
        int w,h;
        pTex -> GetInfo(w,h);
    }
    m_stat = 1;
}

void TextBox::OnNext()
{

}

void TextBox::OnDraw()
{

}

bool TextBox::Finished()
{return m_stat == NOEVENT;}

void TextBox::Init()
{
    m_fpsSpeed = 20;
    m_stat = 0;
    m_nowFps = 0;
    SetColor(255,255,255);
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
