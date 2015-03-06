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
    /*  ����汾�����ü����汾v����SDL��֧�ֶ�����������Ϊ��ͨ������ָ��ģʽ
    class Mutex;
    class Thread;
    struct ResFile_Point{
        BYTE* mem;
        SDL_RWops* rw;
        Uint16 count;

        Sint8 pkg;    //-1ʱΪ�ļ�����
        Uint32 start;
        Uint32 size;

        bool reg;   //�����ͷš�
    };

    class ResFile{  //����԰�������һ���ļ�ʵ��������Ҫ�����ڴ��Ƿ��ͷţ�����ʹ�þ���
        //��Ҳ���Ե��ú���ʱֱ�Ӵ��ݶ���ʵ����ʵ���ϸ�ʵ�������Ǹ����ü���ָ��
        //��������ü����汾
    private:
        static std::vector<std::ifstream*> m_pkgs;
        static std::map<std::string,ResFile_Point> m_fs;
        static std::string m_pkgpw;
        static BYTE m_nullptr;
        static Core::Mutex m_mut;

        ResFile_Point* m_file;

    protected:
        static void CreateRWops(const std::string&);    //���ļ�����SDL_RWopsָ��
        static void CreateRWops(ResFile_Point*);
        static void LoadPkgFile(const std::string&);    //�Ӱ��м����ļ�
        static void LoadFile(const std::string&);   //�����ļ�
        static void ForceFree(ResFile_Point*);  //ǿ���ͷ�
        static void ForceFree(const std::string&);
        static bool ExistInPkg(const std::string&); //�Ƿ�����ڰ���
        static void LoadLocalFileFirst(const std::string& name,ResFile_Point* rf);
        //���ر����ļ������޳��Σ��¸��������ú����
        static void LoadLocalFile(const std::string&);  //���ر����ļ�
    public:
        static void Init(const std::string& pw);    //��ʼ���������ļ�������
        static void Quit(); //���ڻ����ͷ��ڴ�
        static bool OpenPkg(const std::string&);    //���ļ���
        static void SetReg(const std::string&,const bool);  //��ĳһ�Ѿ����ع����ļ������Ż������ֲ��ͷżӿ��ٶ�

        ResFile();
        ResFile(const ResFile&);    //����ʱ�����ļ�
        ResFile(const std::string&);

        ~ResFile();

        void Load(const std::string&);  //�����ļ�������Ҫ�����Ƿ��ͷţ��Զ��ͷ�
        void Free();    //�ͷŵ�ǰ�ļ�
        Uint32 Size() const;    //ȡ��С

        operator BYTE* () const;    //ȡ�ֽ���ָ��
        operator SDL_RWops* () const;   //ȡSDL_RWopsָ��
        operator void* () const;    //ȡvoid*��ָ��
        operator char* () const;    //ȡchar*��ָ��

        BYTE& operator [] (Uint32) const;   //ʹ���±����ĳ�ֽ�

        operator bool () const; //�Ƿ��Ѿ������ļ�
    };
    */
    struct ResFile_Point{
        Sint8 pkg;    //-1ʱΪ�ļ�����
        Uint32 start;
        Uint32 size;
    };

    class ResFile FDBGCLASS{  //����԰�������һ���ļ�ʵ��������Ҫ�����ڴ��Ƿ��ͷţ�����ʹ�þ���
        //��Ҳ���Ե��ú���ʱֱ�Ӵ��ݶ���ʵ��
        //�����һ��һ�汾
    private:
        static std::vector<std::ifstream*> m_pkgs;
        static std::string m_pkgpw;
        static std::map<std::string,ResFile_Point> m_fs;
        BYTE* m_mem;
        Uint32 m_size;
        SDL_RWops* m_rw;

    public:
        static void Init(const std::string& pw);    //��ʼ���������ļ�������
        static void Quit(); //���ڻ����ͷ��ڴ�
        static bool OpenPkg(const std::string&);    //���ļ���

        ResFile();
        ResFile(const ResFile&);
        ResFile(ResFile&&);
        ResFile(const std::string&);

        ~ResFile();

        void Load(const std::string&);  //�����ļ�������Ҫ�����Ƿ��ͷţ��Զ��ͷ�
        void Free();    //�ͷŵ�ǰ�ļ�
        Uint32 Size() const;    //ȡ��С

        operator BYTE* () const;    //ȡ�ֽ���ָ��
        operator SDL_RWops* () const;   //ȡSDL_RWopsָ��
        operator void* () const;    //ȡvoid*��ָ��
        operator char* () const;    //ȡchar*��ָ��

        BYTE& operator [] (Uint32) const;   //ʹ���±����ĳ�ֽ�

        operator bool () const; //�Ƿ��Ѿ������ļ�
    };
}
#endif
