#ifndef AIC20_CLIENT_CPP_MAP_H
#define AIC20_CLIENT_CPP_MAP_H

#include <vector>

#include "Path.h"
#include "Unit.h"
#include "King.h"

class Map {
public:
    Map() = default;

    Map(const Map&);

    Map& operator=(const Map&) = delete;

    ~Map();

    int getRowNum() const;

    int getColNum() const;

    std::vector<const Path *> getPaths() const;

    const Cell *cell(int row, int col) const;

    std::vector<const Unit *> getUnits() const;

    std::vector<const King *> getKings() const;

private:
    int rows_;
    int cols_;
    std::vector<std::vector<Cell *>> cells_;
    std::vector<const Path *> paths_;
    std::vector<const Unit *> units_;//This is for our own use
    std::vector<const King *> kings_;
    std::vector<const Unit *> died_units_;

    void initCells();

    std::vector<King *> local_kings_;//Our us
    King * give_king_by_playerId(int player_id);

    friend class InitMessage;

    friend class TurnMessage;

    friend class ShutdownMessage;

    friend class Game;
};


#endif //AIC20_CLIENT_CPP_MAP_H
