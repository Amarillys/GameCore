#include "error.h"
#include <iostream>
#include <stdlib.h>
#include "../Debug.h"
#define ERROR_COUNT 128

#ifdef _OS_WINDOWS
#include <windows.h>
#define ERROR_MSGBOX(msg) MessageBox(nullptr,msg.c_str(),"´íÎó",MB_ICONHAND|MB_ICONSTOP|MB_ICONERROR)
#endif

using namespace std;
using namespace Core;

Error::Error(Uint32 code,string msg)
{
    m_code = code;
    m_msg = msg;
    Proc();
}

std::string Error::GetMsg()
{
    return m_msg;
}

Uint8 Error::GetLevel()
{
    return m_code>>12;
}

void Error::Print()
{
    PNT(std::endl);
    PNT("Error:");
    PNT("Code = ");
    PNT(m_code);
    PNT("    ");
    PNT(GetMsg());
    PNT(std::endl);
}

void Error::Proc()
{
    switch(GetLevel()){
    case 1:
        Print();
        break;
    case 2:
        Print();
        ERROR_MSGBOX(GetMsg());
        break;
    case 3:
        Print();
        ERROR_MSGBOX(GetMsg());
        exit(-1);
        break;
    default:
        Print();
        exit(-1);
        break;
    }
}
