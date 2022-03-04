#include "texturemanager.h"

SDL_Texture* textureManager::loadTexture(const char* name){
    SDL_Surface* tmpSurface = IMG_Load(name);
    if(tmpSurface == NULL){
        std::cout << "Error while loading texture";
    }
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    return tex;
}

void textureManager::draw(SDL_Texture *tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip){
    SDL_RenderCopyEx(Game::renderer, tex, &src, &dest, NULL, NULL, flip);
}
