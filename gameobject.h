#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "texturemanager.h"

class gameObject
{
public:
    gameObject(const char* spriteSheet, int x, int y);
    ~gameObject();

    void update();
    void render();

private:
    int xpos;
    int ypos;

    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;
};

#endif // GAMEOBJECT_H
