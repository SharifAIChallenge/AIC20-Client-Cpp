#include <stdlib.h>
#include "AI.h"

using namespace std;

void AI::pick(World *world) {
    world->chooseDeckById({1, 3, 4, 5, 6, 7, 8, 0});
}

void AI::turn(World *world) {
    static bool tmp = false;
    tmp = ~tmp;
    int unit = world->getHand()[0]->typeId();
    if(world->getMe()->playerId() == 1) {
        int path = world->getMe()->getPathsFromPlayer()[0]->pathId();
        world->putUnit(unit, path);
    } else {
        int path = world->getMe()->getPathToFriend()->pathId();
        world->putUnit(unit, path);
    }


}

void AI::end(World *world, std::map<int, int> &scores) {

}
