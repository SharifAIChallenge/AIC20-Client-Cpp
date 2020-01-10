#include "Path.h"

int Path::pathId() const {
    return path_id_;
}

std::vector<const Cell *> Path::cells() const {
    return cells_;
}
