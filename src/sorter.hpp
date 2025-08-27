#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include "types.hpp"

namespace fs = std::filesystem;

namespace zz {

class Sorter {
public:
  static std::vector<fs::directory_entry> sortDirectory(const fs::path &dirPath,
                                                        Sorting sorting);
};

} // namespace zz
