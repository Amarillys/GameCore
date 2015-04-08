#pragma once
#include "Texture.h"
#include "Animation.h"
#include "Control.h"

//TODO:未实现
namespace Core{
class Sprite:public Texture,public AnimationPool,public Control{
public:
    bool OnEvent (const SDL_Event&,Activity&);
    //输出鼠标按下，弹出，进入，退出的消息
};
}
