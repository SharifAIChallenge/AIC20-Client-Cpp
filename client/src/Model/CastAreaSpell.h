#ifndef AIC20_CLIENT_CPP_CASTAREASPELL_H
#define AIC20_CLIENT_CPP_CASTAREASPELL_H

#include "CastSpell.h"
#include "Cell.h"

class CastAreaSpell : public CastSpell {
public:
    CastAreaSpell() = default;

    ~CastAreaSpell() = default;

    int getRemainingTurns() const;

private:
    int remaining_turns_;

    friend class TurnMessage;
    friend class ShutdownMessage;
    friend class Game;
};


#endif //AIC20_CLIENT_CPP_CASTAREASPELL_H
