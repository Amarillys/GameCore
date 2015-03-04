#include <iostream>
#include <fstream>
#include <string>
#include <list>
#define ENC_LEN 64*1024

using namespace std;

int help()
{
    cout<<"+pk sourceDir outputFile password"<<endl;
    return 0;
}

void FixPath(string& path,bool isDir = false)
{
    for(int i = 0;i < path.length();++i)
        if(path[i] == '/') path[i] = '\\';
    if(isDir && path[path.size()-1] != '\\') path += '\\';
}

void GetFileList(const string& path,list<string>& lst)
{
    string cmd = "dir ";
    cmd += path;
    cmd += "/A:-D /B /S>fileList.tmp";
    system(cmd.c_str());

    ifstream fl("fileList.tmp");
    while(!fl.eof())
    {
        string file;
        getline(fl,file);
        if(file.empty()) continue;
        lst.push_back(file.substr(path.length(),file.length() - path.length()));
    }
}

void Head(ofstream& Pkg,const string& Dir,const string& Path)
{
    for(int i = 0;i < Path.length();++i)
        Pkg.put(Path[i]);
    Pkg.put(0x00);

    ifstream in((Dir + Path).c_str(),ios::binary | ios::ate);
    unsigned long int size = in.tellg();
    Pkg.write((char*)&size,sizeof(size));
    in.close();
}

void Encode(char* const p,const unsigned long int size,const string& pw)
{
    for(unsigned int i = 0;i < size && i < ENC_LEN;++i)
        *(p + i) ^= pw[i % pw.size()];
}

int main(int argc,char** argv)
{
    cout<<"+PK Package Tool 201501012"<<endl;
    if(argc != 4) return help();

    string sourceDir(*(argv + 1));
    ofstream pk(*(argv+2),ios::binary);
    const string pw(*(argv+3));

    FixPath(sourceDir,true);
    if(!pk) {cout<<"Can't write +pk file."<<endl;return -1;}

    list<string> files;
    GetFileList(sourceDir,files);

    unsigned long int FileCount = files.size();
    pk.write((char*)&FileCount,sizeof(FileCount));

    for(auto p = files.begin();p != files.end();++p) Head(pk,sourceDir,*p); //头部文件表
    for(auto pPath = files.begin();pPath != files.end();++pPath)    //写入内容
    {
        cout<<*pPath<<"...";
        ifstream in((sourceDir + *pPath).c_str(),ios::binary | ios::ate);
        unsigned long int size = in.tellg();
        in.seekg(0,ios::beg);

        char *p = NULL;
        try{
            p = new char [size];
        }catch(bad_alloc){
            cout<<"error:bad_alloc"<<endl;
            return 0;
        }
        in.read(p,size);
        in.close();
        Encode(p,size,pw);
        pk.write(p,size);
        delete [] p;
        cout<<"OK"<<endl;
    }
    pk.close();
}
