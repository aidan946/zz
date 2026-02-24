#pragma once

#include "types.hpp"
#include <span>
#include <string>
#include <vector>

namespace zz {

Options parseCommandLineArgs(std::span<char *> args);
std::vector<std::string> parseGitIgnore();

} // namespace zz
