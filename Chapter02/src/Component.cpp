//
// Created by oliver on 07/11/26.
//

#include "Component.h"

Component::Component(Actor *actor, int updateOrder)
    : mActor(actor), updateOrder(updateOrder){}

int Component::getUpdateOrder() const {
    return updateOrder;
}
