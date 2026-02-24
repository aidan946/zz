#pragma once

#include "types.hpp"
#include <filesystem>
#include <string>
#include <vector>

namespace zz {

void printDirectory(const std::filesystem::path &dirPath,
                    const Options &options, uint8_t depth,
                    const std::vector<std::string> &gitignorePatterns);

} // namespace zz
