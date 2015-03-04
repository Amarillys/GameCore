#ifndef _HEAD_MISC_
#define _HEAD_MISC_
#include <fstream>
struct SDL_Rect;
namespace Core
{
    void GetString(std::ifstream&,std::string&);    //从二进制文件流中取出一个字符串，遇到\0结尾

    void Pos(SDL_Rect& opr,float x,float y);    //使用百分比相对定位
    void Pos(SDL_Rect& opr,const char base,int x,int y);    //使用基点相对定位
        /* 基点(Base)的用法 */
            //base是一个16进制数
            //把屏幕纵横切5刀，base的第一位是x位置
            //如0x00为最左边
            //0x20为中间
            //0x40为右边
            //第二位是纵向位置
            //0x00是最上边
            //0x02是中间
            //0x40是最下边
            //两个位置组合起来形成基位置，后边的x和y会相对于基位置进行计算
}


#endif
