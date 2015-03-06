#include "FileSystem.h"
#include "../Debug.h"
#include "Misc.h"
#include "Thread.h"
#include <string.h>

using namespace Core;
std::vector<std::ifstream*> ResFile::m_pkgs;
std::map<std::string,ResFile_Point> ResFile::m_fs;
std::string ResFile::m_pkgpw;

void ResFile::Init(const std::string& pw)
{
    m_pkgpw = pw;
}

/* 普通版实现 */

void ResFile::Quit()
{
    if(!m_pkgs.empty())
    for(auto p = m_pkgs.begin();p != m_pkgs.end();++p){
        (*p) -> close();
        delete *p;
    }
}

bool ResFile::OpenPkg(const std::string& pkg)
{

    int index = m_pkgs.size();
    std::ifstream* pPkgf = new std::ifstream(pkg.c_str(),std::ios::binary);
    if(!(*pPkgf)) return false;
    m_pkgs.push_back(pPkgf);

    Uint32 File_Count;
    pPkgf -> read((char*)&File_Count,sizeof(Uint32));

    ResFile_Point Point;
    Point.pkg = index;
    Point.start = 0;

    for(Uint32 i = 0;i < File_Count;++i)
    {
        std::string fName;
        Core::GetString(*pPkgf,fName);
        pPkgf -> read((char*)&Point.size,sizeof(Point.size));
        if(m_fs.count(fName)) {PNT("错误：某两个包内有重名的文件" + fName);return false;}
        m_fs [fName] = Point;
        Point.start += Point.size;
    }

    const register Uint32 PkgDataStart = pPkgf -> tellg();
    for(auto p = m_fs.begin();p != m_fs.end();++p) (p -> second).start += PkgDataStart;
    return true;
}

ResFile::ResFile()
{
    m_mem = nullptr;
    m_size = 0;
    m_rw = nullptr;
}

ResFile::ResFile(const ResFile& k)
{
    m_size = k.m_size;
    m_mem = new BYTE [m_size];
    memcpy(m_mem,k.m_mem,m_size);
    m_rw = SDL_RWFromConstMem(m_mem,m_size);
}

ResFile::ResFile(ResFile&& k)
{
    m_size = k.m_size;
    m_mem = k.m_mem;
    m_rw = k.m_rw;
    k.m_mem = nullptr;
    k.m_size = 0;
    k.m_rw = nullptr;
}

ResFile::ResFile(const std::string& s)
{
    ResFile();
    Load(s);
}

ResFile::~ResFile()
{
    Free();
    PNT("ResFile Killed:"<<this<<std::endl);
}

void ResFile::Load(const std::string& f)
{
    Free();
    if(m_fs.count(f) == 1){ //包中有文件则从包中加载
        m_size = m_fs[f].size;
        m_mem = new BYTE [m_size];
        m_pkgs[m_fs[f].pkg] -> read((char*)m_mem,m_size);
        if(!m_pkgpw.empty()) for(Uint16 i = 0;i < ENC_LEN && i < m_size;++i) *(m_mem+i) ^= m_pkgpw[i%m_pkgpw.length()];
    }else{  //否则从本地加载
        std::ifstream in(f.c_str(),std::ios::binary);
        in.seekg(0,std::ios::end);
        m_size = in.tellg();
        in.seekg(0,std::ios::beg);
        m_mem = new BYTE [m_size];
        in.read((char*)m_mem,m_size);
        in.close();
    }
    m_rw = SDL_RWFromConstMem((void*)m_mem,m_size);
}

void ResFile::Free()
{
    if(m_rw != nullptr) SDL_FreeRW(m_rw);
    if(m_mem != nullptr) delete [] m_mem;
    m_mem = nullptr;
    m_size = 0;
    m_rw = nullptr;
}

Uint32 ResFile::Size() const
{
    return m_size;
}

ResFile::operator BYTE* () const
{
    return m_mem;
}

ResFile::operator SDL_RWops* () const
{
    return m_rw;
}

ResFile::operator void* () const
{
    return (void*)m_mem;
}

ResFile::operator char* () const
{
    return (char*)m_mem;
}

BYTE& ResFile::operator [] (Uint32 i) const
{
    return *(m_mem + i);
}

ResFile::operator bool () const
{
    return m_mem != nullptr;
}


/* 引用计数版 实现
Mutex ResFile::m_mut;
BYTE ResFile::m_nullptr = '\0';



void ResFile::Quit()
{
    for(auto p = m_fs.begin();p != m_fs.end();++p) ForceFree(&(p -> second));

    for(auto p = m_pkgs.begin();p != m_pkgs.end();++p){
        (*p) -> close();
        delete *p;
    }
}

void ResFile::CreateRWops(const std::string& file)
{
    if(m_fs[file].rw != nullptr) m_fs[file].rw = SDL_RWFromConstMem((char*)(m_fs[file].mem),m_fs[file].size);
}

void ResFile::CreateRWops(ResFile_Point* file)
{
    if(file -> rw == nullptr) file -> rw = SDL_RWFromConstMem((char*)(file -> mem),file -> size);
}

void ResFile::ForceFree(ResFile_Point* p)
{
    p -> count = 0;
    p -> reg = false;
    if(p -> rw != nullptr) SDL_FreeRW(p -> rw);
    p -> rw = nullptr;
    if(p -> mem != nullptr) delete [] p -> mem;
    p -> mem = nullptr;
}

void ResFile::ForceFree(const std::string& file)
{
    ResFile_Point* p = &m_fs[file];
    ForceFree(p);
}

void ResFile::LoadLocalFileFirst(const std::string& name,ResFile_Point* rf)
{
    std::ifstream in(name.c_str(),std::ios::binary);
    in.seekg(0,std::ios::end);
    rf -> size = in.tellg();
    in.close();
    LoadLocalFile(name);
}

void ResFile::LoadLocalFile(const std::string& name)
{
    std::ifstream in(name.c_str(),std::ios::binary);
    ResFile_Point* rs = &m_fs[name];
    rs -> mem = new BYTE [rs -> size];
    in.read((char*)rs -> mem,rs -> size);
    in.close();
}
void ResFile::LoadFile(const std::string& name)
{
    if (m_fs.count(name) == 0)
    {
        m_fs [name].count = 0;
        m_fs [name].pkg = -1;
        m_fs [name].rw = nullptr;
        m_fs [name].start = 0;
        m_fs [name].reg = false;
        LoadLocalFileFirst(name,&m_fs [name]);
    }
    else if (m_fs[name].mem != nullptr) return;
    else if (m_fs[name].pkg >= 0) LoadPkgFile(name);
    else if (m_fs[name].mem == nullptr) LoadLocalFile(name);
}

void ResFile::LoadPkgFile(const std::string& file)
{
    const static Uint16 pwlen = m_pkgpw.length();
    m_fs[file].mem = new BYTE[m_fs[file].size];
    m_pkgs[m_fs[file].pkg] -> read((char*)m_fs[file].mem,m_fs[file].size);
    if(!m_pkgpw.empty()) for(Uint16 i = 0;i < ENC_LEN && i < m_fs[file].size;++i) *(m_fs[file].mem+i) ^= m_pkgpw[i%pwlen];
}

bool ResFile::ExistInPkg(const std::string& file)
{
    return m_fs[file].pkg != -1;
}

bool ResFile::OpenPkg(const std::string& pkg)
{

    int index = m_pkgs.size();
    std::ifstream* pPkgf = new std::ifstream(pkg.c_str(),std::ios::binary);
    if(!(*pPkgf)) return false;
    m_pkgs.push_back(pPkgf);

    Uint32 File_Count;
    pPkgf -> read((char*)&File_Count,sizeof(Uint32));

    ResFile_Point Point;
    Point.mem = nullptr;
    Point.count = 0;
    Point.pkg = index;
    Point.rw = nullptr;
    Point.start = 0;
    Point.reg = false;

    for(Uint32 i = 0;i < File_Count;++i)
    {
        std::string fName;
        Core::GetString(*pPkgf,fName);
        pPkgf -> read((char*)&Point.size,sizeof(Point.size));
        if(m_fs.count(fName)) {PNT("错误：某两个包内有重名的文件" + fName +"该错误会导致内存泄漏。");return false;}
        m_fs [fName] = Point;
        Point.start += Point.size;
    }

    const register Uint32 PkgDataStart = pPkgf -> tellg();
    for(auto p = m_fs.begin();p != m_fs.end();++p) (p -> second).start += PkgDataStart;
    return true;
}

void ResFile::SetReg(const std::string& file,const bool reg)
{
    m_fs [file].reg = reg;
    if(reg == false && m_fs[file].count == 0) ForceFree(file);
}

//ResFile文件指向部分实现

ResFile::ResFile()
{
    m_file = nullptr;
}

ResFile::ResFile(const ResFile& from)
{
    m_mut.Lock();
    this -> m_file = from.m_file;
    this -> m_file -> count ++;
    m_mut.Unlock();
}

ResFile::ResFile(const std::string& name)
{
    m_file = nullptr;;
    Load(name);
}

ResFile::~ResFile()
{
    Free();
}

void ResFile::Load(const std::string& file)
{
    m_mut.Lock();
    if (m_file != nullptr) Free();
    LoadFile(file);
    m_file = &m_fs [file];
    m_file -> count ++;
    m_mut.Unlock();
}

void ResFile::Free()
{
    m_mut.Lock();
    if(m_file == nullptr) return;
    -- m_file -> count;
    if(m_file -> count <= 0 && !m_file -> reg) ForceFree(m_file);
    m_file = nullptr;
    m_mut.Unlock();
}

Uint32 ResFile::Size() const
{
    if (m_file != nullptr) return m_file -> size;
    else return 0;
}

ResFile::operator BYTE* () const
{
    if (m_file != nullptr) return m_file -> mem;
    else return 0;
}

ResFile::operator SDL_RWops*() const
{
    if (m_file != nullptr && m_file -> rw != nullptr) return m_file -> rw;
    else if (m_file -> rw == nullptr) {CreateRWops(m_file);return m_file -> rw;}
    else return nullptr;
}

ResFile::operator void*() const
{
    return (void*)operator BYTE*();
}

ResFile::operator char*() const
{
    return (char*)operator BYTE*();
}

BYTE& ResFile::operator [] (Uint32 i) const
{
    BYTE* b = operator BYTE*();
    if (b != nullptr) return *(b + i);
    return m_nullptr;
}

ResFile::operator bool() const
{
    return m_file;
}*/

