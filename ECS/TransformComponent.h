#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <ECS/Components.h>
#include <Vector2D.h>

class TransformComponent : public Component{
public:
    Vector2D position;
    Vector2D velocity;

    int height = 20;
    int width = 16;
    int scale = 4;

    int speed = 3;

    TransformComponent(){
        position.Zero();
    }

    TransformComponent(int sc){
        position.Zero();
        scale = sc;
    }

    TransformComponent(float x, float y, int h, int w, int sc){
        position.x = x;
        position.y = y;
        height = h;
        width = w;
        scale = sc;
    }

    void init() override{
        velocity.Zero();
    }

    void update() override{
        position.x += velocity.x * speed;
        position.y += velocity.y * speed;
    }

};


#endif // TRANSFORMCOMPONENT_H
