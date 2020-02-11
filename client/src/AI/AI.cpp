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
    if(world->getMe()->getHand().size() == 0) {
        cerr << "Empty hand!!!" << endl;
        return;
    }
    int unit = world->getMe()->getHand()[0]->typeId();
    if(true || world->getMe()->getPlayerId() == 1) {
        const Path* path = world->getShortestPathToCell(
                world->getMe(),
                5,6);
        if(path == nullptr){
            cerr << "No path found" << endl;
            return;
        }
        world->putUnit(unit, path);
//        cerr << "INSERTED" << endl;
        cout << "My spells count " << world->getMe()->getSpellCount() <<endl;
        cout << "Friend spells count " << world->getMe()->getSpellCount() <<endl;
        cout << "1st opponent spells count " << world->getMe()->getSpellCount() <<endl;
        cout << "2nd opponent spells count " << world->getMe()->getSpellCount() <<endl;
    }
//    else if(world->getMe()->getPlayerId() == 2) {
//        const Path* path = world->getShortestPathToCell(
//                world->getMe(),
//                4,10);
//        world->putUnit(unit, path);
//        cerr << "INSERTED" << endl;
//    }


}

void AI::end(World *world, std::map<int, int> &scores) {
    cout << "Results:" << endl;
    cout << "Me: " << scores[world->getMe()->getPlayerId()] << endl;
    cout << "My Friend: " << scores[world->getFriend()->getPlayerId()] << endl;
    cout << "Opponent #1: " << scores[world->getFirstEnemy()->getPlayerId()] << endl;
    cout << "Opponent #2: " << scores[world->getSecondEnemy()->getPlayerId()] << endl;
    cout << "------------------" << endl;
}
