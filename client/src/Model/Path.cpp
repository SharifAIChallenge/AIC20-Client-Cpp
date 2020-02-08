#include <algorithm>
#include "Path.h"

Path::Path(const Path &obj, bool reverse):
        cells_(obj.cells_) {
    this->path_id_ = obj.path_id_;
    if(reverse){
        std::reverse(cells_.begin(), cells_.end());
    }
}

int Path::pathId() const {
    return path_id_;
}

std::vector<const Cell *> Path::cells() const {
    return cells_;
}

bool Path::operator==(const Path &obj) {
    return obj.path_id_ == this->path_id_;
}
