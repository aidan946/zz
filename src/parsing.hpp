#pragma once

#include <string>
#include <vector>
#include "types.hpp"

namespace zz {

class Parser {
public:
    static Options parseCommandLineArgs(int argc, char* argv[], Options& options);
    static std::vector<std::string> parseGitIgnore();

private:
    static bool isValidRecursiveArg(const std::string& arg);
};

} // namespace zz
