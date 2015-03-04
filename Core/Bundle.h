#ifndef _HEAD_BUNDLE_
#define _HEAD_BUNDLE_
#include "Globals.h"
#include <fstream>

/* ���л����ݰ� */
/* ���棡д�����볬�����ݰ����ȵ����ݳ����ֱ�ӱ�����*/
namespace Core{
    template <Uint32 size>    //�����С
    class Bundle{
    private:
        BYTE m_data[size];
        Uint32 m_wptr;
        Uint32 m_rptr;
    public:
        Bundle();
        void ResetPtr();    //�����дָ��
        template <typename type> void Write(type&);
        //�ڵ�ǰдλ��д��һ�����ݣ�����дָ��Ų����һ������
        //���޻������ͣ�����Uint32��BYTE������֪��С��������

        template <typename type> void Read(type&);
        //�ӵ�ǰ��λ�ö���һ�����ݣ����Ѷ�ָ��Ų����һ������
        //���޻������ͣ�����Uint32��BYTE������֪��С��������

        void WriteStr(std::string&);    //д���ַ���
        void ReadStr(std::string&);     //�����ַ���

        void WriteToFile(std::ofstream&,Uint64 pos=0);
        //�����ݰ��浽�ļ�

        void ReadFromFile(std::ifstream&,Uint64 pos=0);
        //���ļ���ȡ���ݰ�

        ~Bundle(){};
    };
}

#include "Bundle.cpp"
#endif // _HEAD_BUNDLE_
