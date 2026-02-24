#pragma once

namespace zz {

enum class Sorting { FOLDER_FILE, FILE_FOLDER, NONE };

enum class EntryKind {
  Directory,
  File,
  Symlink,
  BlockDevice,
  CharacterDevice,
  NamedPipe,
  Socket,
  Unknown,
};

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
