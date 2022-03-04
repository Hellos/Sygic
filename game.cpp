#include "game.h"
#include "texturemanager.h"
#include "gameobject.h"
#include "map.h"
#include "ECS/ECS.h"
#include "ECS/Components.h"
#include "Collisison.h"


SDL_Renderer* Game::renderer = nullptr;
Map* newMap;

Manager manager;

auto& Player(manager.addEntity());

const char* mapfile = "assets/tileset.png";

SDL_Event Game::event;

Game::Game()
{

}

Game::~Game(){

}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){
    int flags = 0;
    if(fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if(SDL_Init(SDL_INIT_EVERYTHING) == 0){
        std::cout << "Subsystems initialized!" << std::endl;

        window = SDL_CreateWindow(title,xpos,ypos,width,height,flags);
        if(window){
            std::cout << "Window created!" << std::endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer){
            SDL_SetRenderDrawColor(renderer,255,0,0,0);
            std::cout << "Renderer created!" << std::endl;
        }
        SDL_ShowCursor(SDL_DISABLE);
        isRunning = true;
    }
    else{
        isRunning = false;
    }


    newMap = new Map("assets/tileset.png", 1, 64);

    newMap->loadMap("map.txt",24,15);

    Player.addComponent<TransformComponent>();
    Player.addComponent<SpriteComponent>("assets/hero_anims.png", true);
    Player.addComponent<KeyboardController>();
    Player.addComponent<MouseController>();
    Player.addComponent<ColliderComponent>("player");
    Player.addGroup(groupPlayers);

    Player.getComponent<TransformComponent>().position.Add(Vector2D(500,500));
}

void Game::handelEvents(){
    SDL_PollEvent(&event);
    switch(event.type){
        case SDL_QUIT:
            isRunning = false;
            break;
        case SDL_KEYDOWN:
            if(event.key.keysym.sym == SDLK_ESCAPE){
                isRunning = false;
                break;
            }
            break;
        default:
            break;
    }
}

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& tilesCollision(manager.getGroup(Game::groupColliders));


void Game::update(){
    SDL_Rect playerCol = Player.getComponent<ColliderComponent>().collider;
    Vector2D playerPos = Player.getComponent<TransformComponent>().position;

    manager.refresh();
    manager.update();

    for(auto cc: tilesCollision){
        SDL_Rect cCol = cc->getComponent<ColliderComponent>().collider;
        if(Collision::AABB(cCol, playerCol)){
            Player.getComponent<TransformComponent>().position = playerPos;
            Player.getComponent<TransformComponent>().velocity * -1;
        }
    }

    if(Player.getComponent<TransformComponent>().position.x > 1460){
        Player.getComponent<TransformComponent>().position = playerPos;
    }
    if(Player.getComponent<TransformComponent>().position.x < 10){
        Player.getComponent<TransformComponent>().position = playerPos;
    }
    if(Player.getComponent<TransformComponent>().position.y > 880){
        Player.getComponent<TransformComponent>().position = playerPos;
    }




    SDL_PumpEvents();

}

void Game::render(){
    SDL_RenderClear(renderer);
    for(auto& t: tiles){
        t->draw();
    }
    for(auto& p: players){
        p->draw();
    }
    for(auto& c: tilesCollision){
        c->draw();
    }
    SDL_RenderPresent(renderer);
}

void Game::clean(){
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Game cleaned!" << std::endl;
}

void Game::createEnemies(int count)
{
    count++;
}

bool Game::running(){
    return isRunning;
}

