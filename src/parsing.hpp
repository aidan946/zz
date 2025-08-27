#pragma once

#include "types.hpp"
#include <string>
#include <vector>

namespace zz {

class Parser {
public:
  static Options parseCommandLineArgs(int argc, char *argv[], Options &options);
  static std::vector<std::string> parseGitIgnore();
};

} // namespace zz
