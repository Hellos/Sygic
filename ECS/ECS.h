#ifndef ECS_H
#define ECS_H

#include <iostream>
#include <array>
#include <bitset>
#include <memory>
#include <algorithm>
#include <vector>


class Component;
class Entity;
class Manager;


using ComponentId = std::size_t;
using Group = std::size_t;

inline ComponentId getNewComponentTypeId(){
    static ComponentId lastId = 0;
    return lastId++;
}

template <typename T> inline ComponentId getComponentTypeId() noexcept{
    static ComponentId typeId = getNewComponentTypeId();
    return typeId;
}

constexpr size_t MaxComponents = 32;
constexpr size_t MaxGroups = 32;

using ComponentBitSet = std::bitset<MaxComponents>;

using GroupBitSet = std::bitset<MaxGroups>;

using ComponentArray = std::array<Component*, MaxComponents>;


class Component{
public:
    Entity* entity;

    virtual void init() {}
    virtual void update() {}
    virtual void draw() {}

    virtual ~Component() {}
};

class Entity{
private:
    Manager &manager;

    bool active = true;
    std::vector<std::unique_ptr<Component>> components;

    ComponentArray componentArray;
    ComponentBitSet componentBitSet;
    GroupBitSet groupBitSet;

public:
    Entity(Manager &mManager) : manager(mManager){}

    void update(){
        for(auto& c : components) c->update();
    }

    void draw() {
        for(auto& c : components) c->draw();
    }

    bool isActive() const { return active; }
    void destroy() { active = false; }

    bool hasGroup(Group mGroup){
        return groupBitSet[mGroup];
    }

    void addGroup(Group mGroup);
    void delGroup(Group mGroup){
        groupBitSet[mGroup] = false;
    }

    template<typename T> bool hasComponent() const {
        return componentBitSet[getComponentTypeId<T>()];
    }

    template<typename  T, typename... TArgs>
    T& addComponent(TArgs&&... mArgs){
        T* c(new T(std::forward<TArgs>(mArgs)...));
        c->entity = this;
        std::unique_ptr<Component> uPtr{c};
        components.emplace_back(std::move(uPtr));

        componentArray[getComponentTypeId<T>()] = c;
        componentBitSet[getComponentTypeId<T>()] = true;

        c->init();
        return *c;
    }

    template<typename T> T& getComponent() const{
        auto ptr(componentArray[getComponentTypeId<T>()]);
        return *static_cast<T*>(ptr);
    }
};

class Manager{
private:
    std::vector<std::unique_ptr<Entity>> entities;
    std::array<std::vector<Entity*>, MaxGroups> groupedEntities;

public:
    void update(){
        for(auto& e : entities) e->update();
    }

    void draw(){
        for(auto& e : entities) e->draw();
    }

    void refresh(){
        for(auto i(0u); i < MaxGroups; i++){
            auto& v(groupedEntities[i]);
            v.erase(
                    std::remove_if(std::begin(v), std::end(v),
                                   [i](Entity* mEntity)
                                    {
                                        return !mEntity->isActive() || !mEntity->hasGroup(i);
                                    }),
                                    std::end(v));
        }

        entities.erase(std::remove_if(std::begin(entities),std::end(entities),
                        [](const std::unique_ptr<Entity> &mEntity)
                        {
                            return !mEntity->isActive();
                        }),
                        std::end(entities));
    }

    void addToGroup(Entity* mEntity, Group mGroup){
        groupedEntities[mGroup].emplace_back(mEntity);
    }

    std::vector<Entity*>& getGroup(Group mGroup){
        return groupedEntities[mGroup];
    }

    Entity& addEntity(){
        Entity* e = new Entity(*this);
        std::unique_ptr<Entity> uPtr{e};
        entities.emplace_back(std::move(uPtr));
        return *e;
    }
};

#endif // ECS\ECS_H
