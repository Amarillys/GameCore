#ifndef _HEAD_TEXTURE_
#define _HEAD_TEXTURE_

#include "Globals.h"
#include "RenderDrawer.h"
#include "FileSystem.h"


/* ������ ����SDL��װ���֣���Ҫ�ڻ��ʹ�á�*/
namespace Core
{
    class Font;
    class Texture: public RenderDrawer
    {
    protected:
        SDL_Texture * m_tex;
        SDL_Rect m_src;
        SDL_Rect m_dst;
        ResFile m_file;
    public:
        Texture();
        void OnDraw();
        void Clear();
        void LoadImage(const std::string& file);  //���ļ�����ͼ��
        void LoadText(Font&,const std::string&); //��������
        void SetSrc(int x, int y, int w, int h); //ͼ�����
        void SetPos(int x, int y);   //����λ��
        void SetPos(char base,int x,int y);
        void SetPos(float x,float y);
        void SetZoom(int w, int h);  //��������
        void SetAlpha(Uint8);   //͸����
        void SetColor(Uint8 R,Uint8 G,Uint8 B); //ɫ������
        void SetBlend(SDL_BlendMode);   //����SDL͸����ʽ
        /*
        std::SDL_BLENDMODE_NONE  ��͸����Ĭ�ϣ�
        std::SDL_BLENDMODE_BLEND ��ͨ͸��
        std::SDL_BLENDMODE_ADD   ����ɫ��͸��
        std::SDL_BLENDMODE_MOD   �ڰ���͸��
        */
        void GetInfo(int& w,int& h);    //ȡ����Ϣ
        bool InRect(int x, int y);   //�ж�ĳ�����Ƿ��ڸ�����Χ��
        virtual ~Texture();
    };
}
#endif // _HEAD_TEXTURE_
