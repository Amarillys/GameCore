#ifndef _HEAD_MISC_
#define _HEAD_MISC_
#include <fstream>
struct SDL_Rect;
namespace Core
{
    void GetString(std::ifstream&,std::string&);    //�Ӷ������ļ�����ȡ��һ���ַ���������\0��β

    void Pos(SDL_Rect& opr,float x,float y);    //ʹ�ðٷֱ���Զ�λ
    void Pos(SDL_Rect& opr,const char base,int x,int y);    //ʹ�û�����Զ�λ
        /* ����(Base)���÷� */
            //base��һ��16������
            //����Ļ�ݺ���5����base�ĵ�һλ��xλ��
            //��0x00Ϊ�����
            //0x20Ϊ�м�
            //0x40Ϊ�ұ�
            //�ڶ�λ������λ��
            //0x00�����ϱ�
            //0x02���м�
            //0x40�����±�
            //����λ����������γɻ�λ�ã���ߵ�x��y������ڻ�λ�ý��м���
}


#endif
