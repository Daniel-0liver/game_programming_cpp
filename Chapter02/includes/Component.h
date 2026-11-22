//
// Created by oliver on 07/11/26.
//

#ifndef GAMEPROGRAMMINGCPP_COMPONENT_H
#define GAMEPROGRAMMINGCPP_COMPONENT_H

#include <SDL3/SDL.h>

class Actor;

class Component {
protected:
    Actor *mActor;
    int updateOrder;
public:
    virtual ~Component() = default;
    Component(Actor *actor, int updateOrder = 100);

    int getUpdateOrder() const;

    virtual void Update(float) {};

    virtual void Draw(SDL_Renderer*) const {};
};

#endif //GAMEPROGRAMMINGCPP_COMPONENT_H
