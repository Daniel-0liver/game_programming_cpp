//
// Created by oliver on 21/11/26.
//

#ifndef GAMEPROGRAMMINGCPP_MOVECOMPONENT_H
#define GAMEPROGRAMMINGCPP_MOVECOMPONENT_H
#include "Component.h"
#include "Actor.h"

class MoveComponent : public Component {
protected:
    Vector2 mVelocity;
public:
    MoveComponent(Actor *actor, const Vector2 &velocity);

    void Update(float deltaTime) override;
};


#endif //GAMEPROGRAMMINGCPP_MOVECOMPONENT_H
