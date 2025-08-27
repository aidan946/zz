#pragma once

namespace zz {

enum class Sorting { FOLDER_FILE, FILE_FOLDER, NONE };

struct Options {
  int recursive = 0;
  bool details = false;
  bool highlighting = false;
  bool icons = true;
  bool list = true;
  bool use_gitignore = true;
  Sorting sorting = Sorting::FILE_FOLDER;
};

} // namespace zz
