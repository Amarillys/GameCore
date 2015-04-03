#ifndef _HEAD_LAYER_
#define _HEAD_LAYER_

#include <list>
#include "View.h"

/* 布局节点(Layer) 介绍 */
/*
布局节点用于存放和统一管理一组View子类对象
因为Layer继承于View，所以它也可以嵌套。
Layer是树形的，它的根节点是一个Activity。
Layer下的子节点均在堆中创建。
*/
namespace Core
{
    class Layer: public View
    {
    private:
        std::list <View *> m_children;   //子节点，全部在堆中
        SDL_Rect m_rect;    //Layer的绝对位置

        bool m_usingXD; //使用相对位置
        float m_x1,m_y1,m_w1,m_h1;
        int m_x2,m_y2,m_w2,m_h2;
        char m_base;

    public:
        void SetRect(char base,int x,int y,int w,int h);
        void SetRect(float x,float y,float w,float h);
        virtual void OnDraw();  //通知各子节点绘制自身
        virtual View* Find(const std::string&); //根据ID递归寻找一个子节点
        template<class T> T * NewView(const std::string&);    //新建子节点
        void DeleteView(const std::string&);    //删除子节点
        void ClearView();   //清空子节点
        virtual void OnParentChanged();
        ~Layer();   //回收子节点
    };
}

template<class T> T * Core::Layer::NewView(const std::string& ID)
{
    Core::View* p = (Core::View*)new T;
    m_children.push_back(p);
    return p;
}

#endif
