#include <algorithm>
#include "Path.h"

Path::Path(const Path &obj, bool reverse):
        cells_(obj.cells_) {
    this->id_ = obj.id_;
    if(reverse){
        std::reverse(cells_.begin(), cells_.end());
    }
}

int Path::id() const {
    return id_;
}

std::vector<const Cell *> Path::cells() const {
    return cells_;
}

bool Path::operator==(const Path &obj) {
    return obj.id_ == this->id_;
}
