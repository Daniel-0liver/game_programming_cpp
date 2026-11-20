//
// Created by oliver on 07/11/26.
//

#ifndef GAMEPROGRAMMINGCPP_COMPONENT_H
#define GAMEPROGRAMMINGCPP_COMPONENT_H


class Component {
public:
    virtual ~Component() = default;
    virtual void Update(float deltaTime);
};


#endif //GAMEPROGRAMMINGCPP_COMPONENT_H
