#include <stdlib.h>
#include <iostream>
#include "AI.h"

using namespace std;

void AI::pick(World *world) {
    world->chooseDeckById({1, 3, 4, 5, 6, 7, 8, 0});
}

void AI::turn(World *world) {
    static bool tmp = false;
    tmp = ~tmp;
//    world->getMe();
//    cerr<<world->getMe()->hand().size()<<endl;
    if(world->getMe()->hand().size() == 0)
        return;
    int unit = world->getMe()->hand()[0]->typeId();
    if(world->getMe()->playerId() == 1) {
        int path = world->getMe()->getPathsFromPlayer()[0]->id();
        world->putUnit(unit, path);
    } else {
        int path = world->getMe()->getPathToFriend()->id();
        world->putUnit(unit, path);
    }


}

void AI::end(World *world, std::map<int, int> &scores) {

}
