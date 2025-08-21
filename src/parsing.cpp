#include "parsing.hpp"
#include <cctype>
#include <charconv>
#include <fstream>
#include <iostream>
#include <string>

namespace zz {

Options Parser::parseCommandLineArgs(int argc, char *argv[], Options &options) {
  bool nextArgRec = false;

  std::cout << "Program args ---------------------------\n\n";

  for (int i = 1; i < argc; ++i) {
    std::string_view arg(argv[i]);
    std::cout << arg << "\n";

    if (!arg.empty() && arg[0] == '-') {
      std::string_view argCleaned = arg.substr(1);

      if (!argCleaned.empty() && argCleaned[0] == 'r') {
        nextArgRec = true;
      } else if (argCleaned == "no-highlights") {
        options.highlighting = false;
      } else if (argCleaned == "no-icons") {
        options.icons = false;
      } else if (argCleaned == "no-list") {
        options.list = false;
      } else if (argCleaned == "no-gitignore") {
        options.use_gitignore = false;
      }
    } else if (nextArgRec) {
      auto result = std::from_chars(arg.data(), arg.data() + arg.size(),
                                    options.recursive);
      if (result.ec == std::errc::invalid_argument) {
        options.recursive = 0;
      }
      nextArgRec = false;
    }
  }

  return options;
}

std::vector<std::string> Parser::parseGitIgnore() {
  std::vector<std::string> patterns;

  // Add default patterns
  patterns.push_back(".jj");
  patterns.push_back(".git");

  std::ifstream file(".gitignore");
  if (!file.is_open()) {
    return patterns;
  }

  std::string line;
  while (std::getline(file, line)) {
    // Skip empty lines and comments
    if (line.empty() || line[0] == '#') {
      continue;
    }

    // Trim whitespace
    line.erase(0, line.find_first_not_of(" \t\r"));
    line.erase(line.find_last_not_of(" \t\r") + 1);

    if (!line.empty()) {
      patterns.push_back(line);
    }
  }

  return patterns;
}

} // namespace zz
