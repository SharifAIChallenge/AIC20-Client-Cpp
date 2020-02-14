#ifndef AIC20_CLIENT_CPP_CASTUNITSPELL_H
#define AIC20_CLIENT_CPP_CASTUNITSPELL_H

#include "CastSpell.h"
#include "Path.h"

class CastUnitSpell : public CastSpell {
public:
    CastUnitSpell() = default;

    ~CastUnitSpell() = default;

    const Unit *getUnit() const;

    const Path *getPath() const;


private:
    const Unit *unit_;
    const Path *path_;

    friend class TurnMessage;
    friend class ShutdownMessage;
    friend class Game;
};


#endif //AIC20_CLIENT_CPP_CASTUNITSPELL_H
