#ifndef _HEAD_FILESYSTEM_
#define _HEAD_FILESYSTEM_
#include <fstream>
#include <map>
#include <vector>
#include "Globals.h"
#include "../Debug.h"

#define ENC_LEN 64*1024

namespace Core
{
    /*  这个版本是引用计数版本v，因SDL不支持而废弃，更换为普通的智能指针模式
    class Mutex;
    class Thread;
    struct ResFile_Point{
        BYTE* mem;
        SDL_RWops* rw;
        Uint16 count;

        Sint8 pkg;    //-1时为文件包外
        Uint32 start;
        Uint32 size;

        bool reg;   //永不释放。
    };

    class ResFile{  //你可以把它当成一个文件实例，不需要关心内存是否释放，尽情使用就是
        //你也可以调用函数时直接传递对象实例，实际上该实例仅仅是个引用计数指针
        //这个是引用计数版本
    private:
        static std::vector<std::ifstream*> m_pkgs;
        static std::map<std::string,ResFile_Point> m_fs;
        static std::string m_pkgpw;
        static BYTE m_nullptr;
        static Core::Mutex m_mut;

        ResFile_Point* m_file;

    protected:
        static void CreateRWops(const std::string&);    //给文件创建SDL_RWops指针
        static void CreateRWops(ResFile_Point*);
        static void LoadPkgFile(const std::string&);    //从包中加载文件
        static void LoadFile(const std::string&);   //加载文件
        static void ForceFree(ResFile_Point*);  //强制释放
        static void ForceFree(const std::string&);
        static bool ExistInPkg(const std::string&); //是否存在于包中
        static void LoadLocalFileFirst(const std::string& name,ResFile_Point* rf);
        //加载本地文件（仅限初次，下个函数调用后调用
        static void LoadLocalFile(const std::string&);  //加载本地文件
    public:
        static void Init(const std::string& pw);    //初始化，输入文件包密码
        static void Quit(); //终期化，释放内存
        static bool OpenPkg(const std::string&);    //打开文件包
        static void SetReg(const std::string&,const bool);  //对某一已经加载过的文件进行优化，保持不释放加快速度

        ResFile();
        ResFile(const ResFile&);    //创建时加载文件
        ResFile(const std::string&);

        ~ResFile();

        void Load(const std::string&);  //加载文件，不需要考虑是否释放，自动释放
        void Free();    //释放当前文件
        Uint32 Size() const;    //取大小

        operator BYTE* () const;    //取字节型指针
        operator SDL_RWops* () const;   //取SDL_RWops指针
        operator void* () const;    //取void*型指针
        operator char* () const;    //取char*型指针

        BYTE& operator [] (Uint32) const;   //使用下标访问某字节

        operator bool () const; //是否已经加载文件
    };
    */
    struct ResFile_Point{
        Sint8 pkg;    //-1时为文件包外
        Uint32 start;
        Uint32 size;
    };

    class ResFile FDBGCLASS{  //你可以把它当成一个文件实例，不需要关心内存是否释放，尽情使用就是
        //你也可以调用函数时直接传递对象实例
        //这个是一对一版本
    private:
        static std::vector<std::ifstream*> m_pkgs;
        static std::string m_pkgpw;
        static std::map<std::string,ResFile_Point> m_fs;
        BYTE* m_mem;
        Uint32 m_size;
        SDL_RWops* m_rw;

    public:
        static void Init(const std::string& pw);    //初始化，输入文件包密码
        static void Quit(); //终期化，释放内存
        static bool OpenPkg(const std::string&);    //打开文件包

        ResFile();
        ResFile(const ResFile&);
        ResFile(ResFile&&);
        ResFile(const std::string&);

        ~ResFile();

        void Load(std::string);  //加载文件，不需要考虑是否释放，自动释放
        void Free();    //释放当前文件
        Uint32 Size() const;    //取大小

        operator BYTE* () const;    //取字节型指针
        operator SDL_RWops* () const;   //取SDL_RWops指针
        operator void* () const;    //取void*型指针
        operator char* () const;    //取char*型指针

        BYTE& operator [] (Uint32) const;   //使用下标访问某字节

        operator bool () const; //是否已经加载文件
    };
}
#endif
