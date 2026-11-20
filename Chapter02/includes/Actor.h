//
// Created by oliver on 07/11/26.
//

#ifndef GAMEPROGRAMMINGCPP_ACTOR_H
#define GAMEPROGRAMMINGCPP_ACTOR_H

#include <vector>
#include <memory>
#include <iostream>
#include "Component.h"

class Actor {
private:
    std::vector<std::unique_ptr<Component>> mComponents;
public:
    void Update(float deltaTime);
    void AddComponent(Component* component);
    void UpdateComponents(float deltaTime);
};

#endif //GAMEPROGRAMMINGCPP_ACTOR_H
