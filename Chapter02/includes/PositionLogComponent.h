//
// Created by oliver on 21/11/26.
//

#ifndef GAMEPROGRAMMINGCPP_POSITIONLOGCOMPONENT_H
#define GAMEPROGRAMMINGCPP_POSITIONLOGCOMPONENT_H
#include "Component.h"
#include "Actor.h"
#include <iostream>


class PositionLogComponent : public Component {
public:
    PositionLogComponent(Actor *actor);
    void Update(float deltaTime) override;
};


#endif //GAMEPROGRAMMINGCPP_POSITIONLOGCOMPONENT_H
