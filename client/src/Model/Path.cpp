#include "Path.h"

Path::Path(const Path &obj) {
    this->id_ = obj.id_;
    //No need to init cells_
}

int Path::id() const {
    return id_;
}

std::vector<const Cell *> Path::cells() const {
    return cells_;
}
