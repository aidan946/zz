#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include "types.hpp"

namespace fs = std::filesystem;

namespace zz {

class Printer {
public:
  static void printDirectory(const fs::path &dirPath, Options &options,
                             uint8_t depth,
                             const std::vector<std::string> &gitignorePatterns);
private:
  static std::string getIndentation(uint8_t depth);
  static std::string getIcon(const fs::directory_entry &entry, bool useIcons);
  static std::string getEntryKind(const fs::directory_entry &entry);
  static bool shouldRecursivePrint(const Options &options, uint8_t depth, const std::string &entryKind);
  static bool isGitIgnored(const std::string &name,
                    const std::vector<std::string> &patterns);
};

} // namespace zz
