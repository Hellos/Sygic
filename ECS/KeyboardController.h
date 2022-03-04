#ifndef KEYBOARDCONTROLLER_H
#define KEYBOARDCONTROLLER_H

#include <game.h>
#include "ECS/ECS.h"
#include "ECS/Components.h"

class KeyboardController : public Component{
public:
    TransformComponent *transform;
    SpriteComponent *sprite;

    void init() override{
        transform = &entity->getComponent<TransformComponent>();
        sprite = &entity->getComponent<SpriteComponent>();
    }

    void update() override{
        const Uint8 *keystate = SDL_GetKeyboardState(NULL);
        if(keystate[SDL_SCANCODE_W]){
            sprite->play("Walk");
            transform->velocity.y = -1;
        }
        else if(keystate[SDL_SCANCODE_S]){
            sprite->play("Walk");
            transform->velocity.y = 1;
        }
        else{
             sprite->play("Idle");
             transform->velocity.y = 0;
        }

        if(keystate[SDL_SCANCODE_A]){
            sprite->play("Walk");
            sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
            transform->velocity.x = -1;
        }
        else if(keystate[SDL_SCANCODE_D]){
            sprite->play("Walk");
            sprite->spriteFlip = SDL_FLIP_NONE;
            transform->velocity.x = 1;
        }
        else{
             sprite->play("Idle");
             transform->velocity.x = 0;
        }
    }
};

#endif // KEYBOARDCONTROLLER_H
