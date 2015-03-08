#pragma once
#include "../Core/Texture.h"

class NumTexture:public Core::Texture
{
public:
    void SetNum(char n);
    void Load(const std::string&);
    int GetWei();
};
