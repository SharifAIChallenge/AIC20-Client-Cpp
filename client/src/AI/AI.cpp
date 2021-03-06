#include <stdlib.h>
#include <iostream>
#include "AI.h"
#include <cstdlib>

using namespace std;

//Some global variable(s) to access in different turns:
int pathIDForMyUnits;

//CAUTION: NEVER DEFINE POINTERS IN THE GLOBAL VARIABLES (BECAUSE
// THE MEMORY OF "World *world" GETS FREED AT THE END OF EVERY TURN
// AND ASSIGNING THAT POINTER TO A PART OF *world IS INCORRECT).
//
// e.g. This wrong:
// const path* pathForMyUnits;
//
// But this is correct:
// int pathIDForMyUnits;
//
// BUT IT'S OK TO DEFINE A POINTER IN THE BELOW FUNCTIONS(pick, turn & end).

void AI::pick(World *world) {
    cout << "pick started" << endl;

    // preprocess
    const Map* map = world->getMap();
    int rows = map->getRowNum();
    int cols = map->getColNum();

    vector<const BaseUnit*> allBaseUnits = world->getAllBaseUnits();
    vector<const BaseUnit*> myHand;

    // choosing all flying units
    for (const BaseUnit *baseUnit : allBaseUnits) {
        if (baseUnit->isFlying())
            myHand.push_back(baseUnit);
    }

    // picking the chosen hand - rest of the hand will automatically be filled with random baseUnits
    world->chooseHand(myHand);

    //other preprocess
    pathIDForMyUnits = world->getFriend()->getPathsFromPlayer()[0]->getId();
}

void AI::turn(World *world) {
    cout << "turn started: " << endl;

    const Player *myself = world->getMe();
    int maxAp = world->getGameConstants()->getMaxAp();

    // play all of hand once your ap reaches maximum. if ap runs out, putUnit doesn't do anything
    if (myself->getAp() == maxAp) {
        for (const BaseUnit *baseUnit : myself->getHand()) {
            world->putUnit(baseUnit, pathIDForMyUnits);
        }
    }

    // this code tries to cast the received spell
    const Spell *receivedSpell = world->getReceivedSpell();
    if (receivedSpell != nullptr) {
        if (receivedSpell->isAreaSpell()) {
            if (receivedSpell->getTarget() == ENEMY) {
                vector<const Unit *> enemyUnits = world->getFirstEnemy()->getUnits();
                if (!enemyUnits.empty())
                    world->castAreaSpell(enemyUnits[0]->getCell(), receivedSpell);

            } else if (receivedSpell->getTarget() == ALLIED) {
                vector<const Unit *> friendUnits = world->getFriend()->getUnits();
                if (!friendUnits.empty())
                    world->castAreaSpell(friendUnits[0]->getCell(), receivedSpell);

            } else if (receivedSpell->getTarget() == SELF) {
                vector<const Unit*> myUnits = myself->getUnits();
                if (!myUnits.empty())
                    world->castAreaSpell(myUnits[0]->getCell(), receivedSpell);

            }
        } else {
            vector<const Unit*> myUnits = myself->getUnits();
            if (!myUnits.empty()) {
                const Unit *unit = myUnits[0];
                vector<const Path*> myPaths = myself->getPathsFromPlayer();
                const Path *path = myPaths[rand() % myPaths.size()];
                int size = path->getCells().size();
                const Cell *cell = path->getCells()[(size + 1) / 2];
                world->castUnitSpell(unit, path, cell, receivedSpell);
            }
        }
    }

    // this code tries to upgrade damage of first unit. in case there's no damage token, it tries to upgrade range
    if (myself->getUnits().size() != 0) {
        const Unit *unit = myself->getUnits()[0];
        world->upgradeUnitDamage(unit);
        world->upgradeUnitRange(unit);
    }



}

void AI::end(World *world, std::map<int, int> &scores) {
    cout << "Results:" << endl;
    cout << "Me: " << scores[world->getMe()->getPlayerId()] << endl;
    cout << "My Friend: " << scores[world->getFriend()->getPlayerId()] << endl;
    cout << "Opponent #1: " << scores[world->getFirstEnemy()->getPlayerId()] << endl;
    cout << "Opponent #2: " << scores[world->getSecondEnemy()->getPlayerId()] << endl;
    cout << "------------------" << endl;
}
