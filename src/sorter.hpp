#pragma once

#include <filesystem>
#include <vector>

#include "types.hpp"

namespace fs = std::filesystem;

namespace zz {

class Sorter {
public:
  static std::vector<fs::directory_entry> sortDirectory(const fs::path &dirPath,
                                                        Sorting sorting);

  static void sort_file_folder(std::vector<fs::directory_entry>&);
  static void sort_folder_file(std::vector<fs::directory_entry>&);
};

} // namespace zz
