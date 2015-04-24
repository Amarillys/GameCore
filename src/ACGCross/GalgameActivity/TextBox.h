#include <string>
#include <vector>
#include <list>
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
        void SetFont(Core::Font&);
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
        std::list<Core::Texture> m_text;  //����
        Core::Font* m_font;  //����
        int m_r,m_g,m_b,    //��ɫ
            m_fpsSpeed, //FPS/�� �ٶ�
            m_stat, //״̬
            m_nowFps;   //FPS������
        SDL_Rect m_rect;    //���ֿ�λ��
        int m_word_h;  //���ֳ���
        int m_showing_word; //��ʾ�е�����
};

} // namespace Galgame
} // namespace ACGCross
