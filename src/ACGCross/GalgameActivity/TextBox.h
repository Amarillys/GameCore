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

        //����ӿ�
        void SetColor(int r,int g,int b);
        void SetFont(const std::string&);
        void SetHeight(int h);  //������ͬʱ���ſ��

        //�ı��ӿ�
        void Br();  //����
        void Clear();
        void AddText(const std::wstring&);  //׷���ı�

        //ϵͳ�ӿ�
        void OnNext();
        void OnDraw();
        bool Finished();
        void Init();
        void Destroy();

        //�Ի��ӿ�
        void SetSpeed(int time);
        void StopSpeak(int time);

        //���ֿ�ӿ�
        void SetRect(int x,int y,int w,int h);
        void Hide();
        void Show();

    protected:
    private:
        std::vector<int> m_lineWord;    //ÿ��������
        std::vector<Core::Texture> m_text;  //����
        int m_r,m_g,m_b,    //��ɫ
            m_fpsSpeed, //FPS/�� �ٶ�
            m_stat, //״̬
            m_nowFps;   //FPS������
};

} // namespace Galgame
} // namespace ACGCross
