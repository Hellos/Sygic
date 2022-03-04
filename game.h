#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "SDL_image.h"
#include <stdio.h>
#include <iostream>
#include <vector>

class ColliderComponent;

class Game
{
public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

    void handelEvents();
    void update();
    void render();
    void clean();

    void createEnemies(int count);

    bool running();

    static SDL_Renderer *renderer;
    static SDL_Event event;

    enum groupLabels: size_t{
        groupMap,
        groupPlayers,
        groupEnemies,
        groupColliders
    };

private:
    bool isRunning;
    SDL_Window *window;
};

#endif // GAME_H
