#include "gameobject.h"

gameObject::gameObject(const char* spriteSheet, int x, int y)
{
    objTexture = textureManager::loadTexture(spriteSheet);
    xpos = x;
    ypos = y;
}

void gameObject::update(){
    xpos++;
    ypos++;

    srcRect.h = 20;
    srcRect.w = 16;
    srcRect.x = 368;
    srcRect.y = 268;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w * 4;
    destRect.h = srcRect.h * 4;
}

void gameObject::render(){
    SDL_RendererFlip flip = SDL_FLIP_VERTICAL;
    SDL_RenderCopyEx(Game::renderer,objTexture,&srcRect, &destRect,180,0,flip);

}
