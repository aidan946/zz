#pragma once

#include <cstdint>

namespace zz {

enum class Sorting {
    FOLDER_FILE,
    FILE_FOLDER,
    NONE
};

struct Options {
    uint8_t recursive = 0;
    bool highlighting = false;
    bool icons = true;
    bool list = true;
    bool use_gitignore = true;
    Sorting sorting = Sorting::FOLDER_FILE;
};

} // namespace zz
