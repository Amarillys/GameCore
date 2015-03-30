#pragma once

#include "Control.h"

/**** 鼠标类事件收集翻译器 ****/
/* 收集鼠标和触屏事件
 * 并将其转换成同一事件
 * 拦截直接发送的鼠标类事件并用控件方式发送给活动。
 */

class MouseTouchEventGetter:public Control{
public:
    virtual bool OnEvent (const SDL_Event&,Activity&);

    bool IsDown();
    const SDL_Point& GetPos();
    bool IsMouse();

};
