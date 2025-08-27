
#include <filesystem>
#include <vector>

#include "sorter.hpp"
#include "types.hpp"

namespace fs = std::filesystem;

namespace zz {

std::vector<fs::directory_entry> Sorter::sortDirectory(const fs::path &dirPath,
                                                       Sorting sorting) {
  std::vector<fs::directory_entry> entries;
  std::error_code ec;
  for (const auto &entry : fs::directory_iterator(dirPath, ec)) {
    entries.push_back(entry);
  }
  return entries;
}

} // namespace zz
