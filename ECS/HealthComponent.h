#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

#include "ECS/ECS.h"


class HealthComponent : public Component{
public:
    int health;

    HealthComponent(){
        health = 100;
    }

    HealthComponent(int h){
        health = h;
    }

    HealthComponent &takeDamage(int damage){
        health = health - damage;
        return *this;
    }
};

#endif // HEALTHCOMPONENT_H
