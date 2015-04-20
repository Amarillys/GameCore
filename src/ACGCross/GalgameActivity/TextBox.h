#include <string>
#include <vector>
#include "../../Core/Core.h"

namespace ACGCross {
namespace Galgame {

class TextBox
{
    public:
        TextBox();
        ~TextBox();

        //字体接口
        void SetColor(int r,int g,int b);
        void SetFont(const std::string&);
        void SetHeight(int h);  //按比例同时缩放宽度

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

    protected:
    private:
        std::vector<int> m_lineWord;    //每行文字数
        std::vector<Core::Texture> m_text;  //文字
        int m_r,m_g,m_b,    //颜色
            m_fpsSpeed, //FPS/字 速度
            m_stat, //状态
            m_nowFps;   //FPS计数器
};

} // namespace Galgame
} // namespace ACGCross
