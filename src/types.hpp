#pragma once

namespace zz {

enum class Sorting { FOLDER_FILE, FILE_FOLDER, ALPHABETICAL, NONE };

struct Options {
  int recursive = 0;
  bool details = false;
  bool highlighting = false;
  bool icons = true;
  bool list = true;
  bool use_gitignore = true;
  Sorting sorting = Sorting::FOLDER_FILE;
};

} // namespace zz
