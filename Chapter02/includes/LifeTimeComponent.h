//
// Created by oliver on 22/11/26.
//

#ifndef GAMEPROGRAMMINGCPP_LIFETIMECOMPONENT_H
#define GAMEPROGRAMMINGCPP_LIFETIMECOMPONENT_H
#include "Component.h"


class LifeTimeComponent : public Component{
protected:
    float mLifeTime;
public:
    float getLifeTime() const;
    LifeTimeComponent(Actor *actor, float lifeTime);
    void Update(float deltaTime) override;
};


#endif //GAMEPROGRAMMINGCPP_LIFETIMECOMPONENT_H
