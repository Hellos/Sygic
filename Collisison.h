#ifndef COLLISISON_H
#define COLLISISON_H

#include "SDL.h"

class ColliderComponent;

class Collision{
public:
    static bool AABB(const SDL_Rect& recA, const SDL_Rect& recB);
    static bool AABB(const ColliderComponent& colA, const ColliderComponent& colB);

};

#endif // COLLISISON_H
