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
    if(world->getMe()->hand().size() == 0) {
        cerr << "Empty hand!!!" << endl;
        return;
    }
    int unit = world->getMe()->hand()[0]->typeId();
    if(world->getMe()->playerId() == 1) {
        const Path* path = world->getShortestPathToCell(
                world->getMe(),
                5,6);
        if(path == nullptr){
            cerr << "No path found" << endl;
            return;
        }
        world->putUnit(unit, path);
        cerr << "INSERTED" << endl;
    }
//    else if(world->getMe()->playerId() == 2) {
//        const Path* path = world->getShortestPathToCell(
//                world->getMe(),
//                4,10);
//        world->putUnit(unit, path);
//        cerr << "INSERTED" << endl;
//    }


}

void AI::end(World *world, std::map<int, int> &scores) {
    cout << "Results:" << endl;
    cout << "Me: " << scores[world->getMe()->playerId()] << endl;
    cout << "My Friend: " << scores[world->getFriend()->playerId()] << endl;
    cout << "Enemy #1: " << scores[world->getFirstEnemy()->playerId()] << endl;
    cout << "Enemy #2: " << scores[world->getSecondEnemy()->playerId()] << endl;
    cout << "------------------" << endl;
}
