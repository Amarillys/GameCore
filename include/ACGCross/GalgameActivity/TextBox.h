#include <string>
#include <vector>
#include <list>
#include "Core.h"

namespace ACGCross {
namespace Galgame {

class TextBox
{
    public:
        TextBox();
        ~TextBox();

        //字体接口
        void SetColor(int r,int g,int b);
        void SetFont(Core::Font&);
        void SetHeight(int h);  //按比例同时缩放宽度
        //可以在途中插入，但是必须先换行再设大小，每一行只能用相同大小，除非你智商够高

        //文本接口
        void Br();  //换行
        void Clear();
        void AddText(const std::wstring&);  //追加文本

        //系统接口
        void OnNext();
        void OnDraw();
        bool Finished();
        void Init();
        void Destroy();

        //对话接口
        void SetSpeed(int time);
        void StopSpeak(int time);

        //文字框接口
        void SetRect(int x,int y,int w,int h);
        void Hide();
        void Show();

        //强制添加文字接口，没有动画效果
        std::list<Core::Texture>::iterator ForceAddText(const std::wstring&);
        //返回迭代器，该迭代器指向输入文本的第一文字的迭代器

        std::list<Core::Texture>::iterator GetTextEnd()
        {return m_text.end();}

        void ForceClear();  //强制删除文字


    protected:
    private:
        std::vector<int> m_lineWord;    //每行文字数
        std::list<Core::Texture> m_text;  //文字
        Core::Font* m_font;  //字体
        int m_r,m_g,m_b,    //颜色
            m_fpsSpeed, //FPS/字 速度
            m_stat; //状态
        Uint32 m_nowFps;   //FPS计数器
        SDL_Rect m_rect;    //文字框位置
        int m_word_h;  //文字长度
        int m_showing_word; //显示中的文字
        Uint32 m_fpsCounter; //FPS的计数关键点

        int m_linePos;  //现在已经显示到的相对rect横行坐标
        int m_heiPos;  //现在已经显示到的相对rect竖行坐标
};

} // namespace Galgame
} // namespace ACGCross
