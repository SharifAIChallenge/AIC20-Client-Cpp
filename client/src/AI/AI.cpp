#include <stdlib.h>
#include "AI.h"

using namespace std;

void AI::pick(World *world) {
    world->chooseDeck({1, 3, 4, 5, 6, 7, 8, 0});
}

void AI::turn(World *world) {
//    int unit = world->getHand()[0]->typeId();
//    int path = world->getPathsFromPlayer(world->getMyId())[0]->pathId();
//    world->putUnit(unit, path);
}
