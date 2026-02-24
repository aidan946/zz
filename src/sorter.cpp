
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

  if (sorting == Sorting::FILE_FOLDER) {
    sort_file_folder(entries);
  } else if (sorting == Sorting::FOLDER_FILE) {
    sort_folder_file(entries);
  }
  return entries;
}

void Sorter::sort_file_folder(std::vector<fs::directory_entry> &v) {
  int n = v.size();
  std::vector<fs::directory_entry> files;
  std::vector<fs::directory_entry> folders;
  for (int i = 0; i < n - 1; i++) {
    if (v[i].is_directory()) {
      files.push_back(v[i]);
    } else if (v[i].is_regular_file()) {
      files.push_back(v[i]);
    }
  }
}

void Sorter::sort_folder_file(std::vector<fs::directory_entry> &v) {
  int n = v.size();
  std::vector<fs::directory_entry> files;
  std::vector<fs::directory_entry> folders;
  for (int i = 0; i < n - 1; i++) {
    if (v[i].is_regular_file()) {
      files.push_back(v[i]);
    } else if (v[i].is_directory()) {
      files.push_back(v[i]);
    }
  }
}
} // namespace zz
