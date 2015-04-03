#ifndef _HEAD_BUTTTON_
#define _HEAD_BUTTTON_

#include "Sprite.h"
#include "Control.h"
#include "Activity.h"

namespace Core{
class Button : public Core::Sprite,public Core::Control
{
    public:
        Button();
        ~Button();

        bool OnEvent(const SDL_Event&,Core::Activity&);
};
}

#endif // _HEAD_BUTTTON_
