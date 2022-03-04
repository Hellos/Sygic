#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <ECS/Components.h>
#include <SDL.h>
#include "texturemanager.h"
#include "Animation.h"
#include <map>

class SpriteComponent : public Component{
private:
    TransformComponent *transform;
    SDL_Texture *tex;
    SDL_Rect srcRect, dstRect;

    bool animated = false;
    int frames = 0;
    int speed = 100;

public:
    int animIndex = 0;

    std::map<const char*, Animation> animations;

    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;


    SpriteComponent() = default;
    SpriteComponent(const char *path){
        setTex(path);
    }

    SpriteComponent(const char *path, bool isAnimated){
        animated = isAnimated;

        Animation idle = Animation(0, 4, 100);
        Animation walk = Animation(1, 4, 100);

        animations.emplace("Idle", idle);
        animations.emplace("Walk", walk);

        play("Idle");

        setTex(path);
    }

    void setTex(const char *path){
        tex = textureManager::loadTexture(path);
    }

    void init() override{
        transform = &entity->getComponent<TransformComponent>();

        srcRect.x = srcRect.y = 0;
        srcRect.h = transform->height;
        srcRect.w = transform->width;
    }

    void update() override{

        if(animated){
            srcRect.x = srcRect.w * static_cast<int>((SDL_GetTicks() / speed) % frames);
        }

        srcRect.y = animIndex * transform->height;

        dstRect.x = static_cast<int>(transform->position.x);
        dstRect.y = static_cast<int>(transform->position.y);
        dstRect.w = transform->width * transform->scale;
        dstRect.h = transform->height * transform->scale;
    }

    void draw() override{
        textureManager::draw(tex, srcRect, dstRect, spriteFlip);
    }

    ~SpriteComponent(){
        SDL_DestroyTexture(tex);
    }

    void play(const char* animName){
        frames = animations[animName].frames;
        animIndex = animations[animName].index;
        speed = animations[animName].speed;
    }
};

#endif // SPRITECOMPONENT_H
