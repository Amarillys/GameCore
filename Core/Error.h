#ifndef _HEAD_ERROR_
#define _HEAD_ERROR_
#include "SDLbase.h"
#include <string>

#include "OS.h"
#define CATCH_BADALLOC catch(bad_alloc){Error(0x30000000,"�ڴ治��");}
namespace Core{
    class Error{
    private:
        //���󼶱�
        //0-���Ǵ���
        //1-��Ӱ�����,PNT�����
        //2-����,PNT���,���������
        //3-��������,PNT���,���������,����
        //4-�����Դ���,ǿ������
        Uint32 m_code;  //������룬������ѯ������������
        //��һλhex�Ǵ��󼶱�

        std::string m_msg;
    protected:
        std::string GetMsg();
        Uint8 GetLevel();
        void Proc();    //�������
        void Print();
    public:
        Error(Uint32,std::string);
    };
}

#endif // _HEAD_ERROR_
