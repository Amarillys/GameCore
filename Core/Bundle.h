#ifndef _HEAD_BUNDLE_
#define _HEAD_BUNDLE_
#include "Globals.h"
#include <fstream>

/* 序列化数据包 */
/* 警告！写入或读入超过数据包长度的数据程序会直接崩溃！*/
namespace Core{
    template <Uint32 size>    //传入大小
    class Bundle{
    private:
        BYTE m_data[size];
        Uint32 m_wptr;
        Uint32 m_rptr;
    public:
        Bundle();
        void ResetPtr();    //重设读写指针
        template <typename type> void Write(type&);
        //在当前写位置写入一个数据，并把写指针挪向下一个数据
        //仅限基本类型！类似Uint32、BYTE及其已知大小的数组型

        template <typename type> void Read(type&);
        //从当前读位置读出一个数据，并把读指针挪向下一个数据
        //仅限基本类型！类似Uint32、BYTE及其已知大小的数组型

        void WriteStr(std::string&);    //写入字符串
        void ReadStr(std::string&);     //读出字符串

        void WriteToFile(std::ofstream&,Uint64 pos=0);
        //把数据包存到文件

        void ReadFromFile(std::ifstream&,Uint64 pos=0);
        //从文件读取数据包

        ~Bundle(){};
    };
}

#include "Bundle.cpp"
#endif // _HEAD_BUNDLE_
