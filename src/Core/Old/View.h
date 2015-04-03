#ifndef _HEAD_VIEW_
#define _HEAD_VIEW_

#include <string>
#include "SDLbase.h"
#include "RenderDrawer.h"
//视图节点类
namespace Core{
    class View:public RenderDrawer    //视图树节点基类，根节点为Activity
    {
    /* 子类构造函数请不要有参数，或者提供一个无参构造函数 */
    private:
        std::string m_ID;    //节点的ID

    protected:
        SDL_Rect* m_parent;   //绝对坐标表示的父节点矩形框

        void CRect(SDL_Rect& opr,
                    float x,float y);
        void CRect(SDL_Rect& opr,
                        const char base,int x,int y);
                    //base是一个16进制数
                    //把父Layer纵横切5刀，base的第一位是x位置
                    //如0x00为最左边
                    //0x20为中间
                    //0x40为右边
                    //第二位是纵向位置
                    //0x00是最上边
                    //0x02是中间
                    //0x40是最下边
                    //两个位置组合起来形成基位置，后边的x和y会相对于基位置进行计算

    public:
        virtual View* Find(const std::string&);    //在树中查找一个View
        void SetID (const std::string&);   //设置ID
        std::string GetID(); //取得ID
        void SetParent(SDL_Rect*);
        //void SetRect(const float,const float,const float,const float,const float);  //设置相对父节点框的百分比位置
        //相对父节点左上角的x坐标为 float * 父节点宽度
        //相对父节点左上角的y坐标为 float * 父节点高度
        //节点在屏幕上宽度为 float * 父节点宽度
        //节点在屏幕上高度为 float * 父节点高度
        //void SetRect(const char base,const int,const int,const int,const int);  //设置相对父节点框的相对位置
        //base参见CRect函数下的注释
        virtual void OnParentChanged(){}; //回调，当父节点改变时
        virtual ~View(){};  //节点销毁时
    };
}

#endif // _HEAD_VIEW_
