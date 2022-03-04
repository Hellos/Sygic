#ifndef COLLIDERCOMPONENT_H
#define COLLIDERCOMPONENT_H

#include <string>
#include "SDL.h"
#include "ECS/Components.h"

class ColliderComponent : public Component{
public:
    SDL_Rect collider;
    std::string tag;

    SDL_Texture* tex;
    SDL_Rect srcR, dstR;

    TransformComponent *transform;

    ColliderComponent(std::string t){
        tag = t;
    }

    ColliderComponent(std::string t, int xpos, int ypos, int size){
        tag = t;
        collider.x = xpos;
        collider.y = ypos;
        collider.h = collider.w = size;
    }

    void init() override{
        if(!entity->hasComponent<TransformComponent>()){
            entity->addComponent<TransformComponent>();
        }
        transform = &entity->getComponent<TransformComponent>();

        tex = textureManager::loadTexture("assets/collTex.png");
        srcR = {0, 0, 64, 64};
        dstR = {collider.x, collider.y, collider.w, collider.h};
    }

    void update() override{
        if(tag != "terrain"){
            collider.x = static_cast<int>(transform->position.x);
            collider.y = static_cast<int>(transform->position.y);
            collider.w = transform->width * transform->scale;
            collider.h = transform->height * transform->scale;
        }
        dstR.x = collider.x;
        dstR.y = collider.y;
    }

    void draw() override{
        textureManager::draw(tex,srcR, dstR, SDL_FLIP_NONE);
    }
};

#endif // COLLIDERCOMPONENT_H
