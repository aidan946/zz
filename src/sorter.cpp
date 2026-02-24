
#include <expected>
#include <filesystem>
#include <system_error>
#include <vector>

#include "sorter.hpp"
#include "types.hpp"

namespace fs = std::filesystem;

namespace {

static void sortFileFolder(std::vector<fs::directory_entry> &v) {
  std::vector<fs::directory_entry> newEntriesVector;
  for (const auto &e : v) {
    if (e.is_directory()) {
      newEntriesVector.push_back(e);
    } else if (e.is_regular_file()) {
      newEntriesVector.push_back(e);
    }
  }
  v = newEntriesVector;
}

static void sortFolderFile(std::vector<fs::directory_entry> &v) {
  std::vector<fs::directory_entry> new_entries_vector;
  for (const auto &e : v) {
    if (e.is_regular_file()) {
      new_entries_vector.push_back(e);
    } else if (e.is_directory()) {
      new_entries_vector.push_back(e);
    }
  }
  v = new_entries_vector;
}

} // namespace

namespace zz {

std::expected<std::vector<fs::directory_entry>, std::error_code>
sortDirectory(const fs::path &dirPath, Sorting sorting) {
  std::vector<fs::directory_entry> entries;
  std::error_code ec;

  for (const auto &entry : fs::directory_iterator(dirPath, ec)) {
    entries.push_back(entry);
  }

  if (ec) {
    return std::unexpected(ec);
  }

  if (sorting == Sorting::FILE_FOLDER) {
    sortFileFolder(entries);
  } else if (sorting == Sorting::FOLDER_FILE) {
    sortFolderFile(entries);
  }
  return entries;
}

} // namespace zz
