#include "Path.h"

Path::Path(const Path &obj) {
    this->path_id_ = obj.path_id_;
    //No need to init cells_
}

int Path::pathId() const {
    return path_id_;
}

std::vector<const Cell *> Path::cells() const {
    return cells_;
}
