#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "game.h"

class textureManager
{
public:
    textureManager();
    static SDL_Texture* loadTexture(const char* name);
    static void draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip);
};

#endif // TEXTUREMANAGER_H
