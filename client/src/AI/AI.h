#ifndef AIC19_CLIENT_CPP_AI_H
#define AIC19_CLIENT_CPP_AI_H

#include <Model/World.h>

class AI {
public:
    void pick(World *world);

    void turn(World *world);
};

#endif // AIC19_CLIENT_CPP_AI_H
