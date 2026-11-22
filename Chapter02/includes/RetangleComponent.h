//
// Created by oliver on 21/11/26.
//

#ifndef GAMEPROGRAMMINGCPP_SQUARECOMPONENT_H
#define GAMEPROGRAMMINGCPP_SQUARECOMPONENT_H
#include "Component.h"

class RetangleComponent : public Component {
protected:
    float width;
    float height;

    SDL_Color color;
public:
    RetangleComponent(Actor *actor, float newWidth, float newHeight, SDL_Color newColor);
    void Draw(SDL_Renderer *render) const override;
};


#endif //GAMEPROGRAMMINGCPP_SQUARECOMPONENT_H
