#include <string>
#include <vector>
#include <list>
#include "Core.h"
/*
#define NOEVENT 0   //闲置
#define TXT_SHOWING 1  //文字显示中
//define TXT_CHANGWORD 2 //文字交替中
#define TXT_KILLING 3   //文字消除中
#define TXT_STOPSPEAK 4 //文字全部强制显示

//define RECT_SHOW 10   //全局显示
#define RECT_HIDE 11   //全局隐藏
#define RECT_SHOWING 12 //正在全局显示
#define RECT_HIDING 13  //正在全局隐藏
*/
namespace ACGCross {
namespace Galgame {

class TextBox
{
    enum Stat{
        NOEVENT,    //闲置
        TXT_SHOWING,    //文字显示中
        TXT_KILLING,    //文字消除中
        TXT_STOPSPEAK,  //强制显示文字中

        RECT_HIDING,    //正在全局隐藏
        RECT_SHOWING,   //正在全局显示
        RECT_HIDE   ////全局隐藏
    };
    public:
        TextBox();
        ~TextBox();

        //字体接口
        void SetEffectSpeed(int time);
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
        void StopSpeak();

        //文字框接口
        void SetRect(int x,int y,int w,int h);
        void Hide();
        void Show();
        Stat GetStatus(){return m_stat;};

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
            m_fpsEffectSpeed;   //FPS特效速度
        Stat m_stat; //状态
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
