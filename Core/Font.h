#ifndef _HEAD_FONT_
#define _HEAD_FONT_

#include "SDLbase.h"
#include <string>
#include "FileSystem.h"

/* �����࣬��ֻ��Ҫ���������������弴�� */
namespace Core
{
    class Font
    {
    private:
        TTF_Font* m_font;
        ResFile m_file;
    public:
        Font(const std::string&,int pt = 32);
        void Open(const std::string&,int pt = 32);
        operator TTF_Font* ();
        //void SetStyle(const int);
        //TTF_STYLE_BOLD
        //TTF_STYLE_ITALIC
        //TTF_STYLE_UNDERLINE
        //TTF_STYLE_STRIKETHROUGH

        //void SetOutLine(const int);
        //void SetHinting(const int);
        //void SetKerning(const int);
        int GetCharWei(const char); //ȡ��һ��ASCII�ַ��Ŀ��
        ~Font();
    };
}

#endif // _HEAD_FONT_
