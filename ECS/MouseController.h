#ifndef MOUSECONTROLLER_H
#define MOUSECONTROLLER_H

#include "ECS/Components.h"

class MouseController : public Component{
public:
    TransformComponent *transform;
    SpriteComponent *sprite;

    void init() override{
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
    }

    void update() override{
        Uint32 mouseState = SDL_GetMouseState(NULL, NULL);
        if(mouseState & SDL_BUTTON(1)){
            SDL_Log("Left mouse button pressed");
            SDL_ShowCursor(SDL_ENABLE);
            sprite->animIndex = 1;
        }
        else if(mouseState & SDL_BUTTON(3)){
            SDL_Log("Right mouse button pressed");
            SDL_ShowCursor(SDL_ENABLE);
            sprite->animIndex = 0;
        }
        else{
            SDL_ShowCursor(SDL_DISABLE);
        }
    }
};

#endif // MOUSECONTROLLER_H
