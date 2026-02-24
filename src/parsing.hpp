#pragma once

#include "types.hpp"
#include <vector>
#include <string>

namespace zz {

class Parser {
public:
  static Options parseCommandLineArgs(int argc, char *argv[]);
  static std::vector<std::string> parseGitIgnore();
};

} // namespace zz
