#include "parsing.hpp"
#include <algorithm>
#include <cctype>
#include <fstream>
#include <iostream>

namespace zz {

Options Parser::parseCommandLineArgs(int argc, char *argv[], Options &options) {
  bool nextArgRec = false;

  std::cout << "Program args ---------------------------\n\n";

  for (int i = 1; i < argc; ++i) {
    std::string arg(argv[i]);
    std::cout << arg << "\n";

    if (!arg.empty() && arg[0] == '-') {
      std::string argCleaned = arg.substr(1);

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
      if (isValidRecursiveArg(arg)) {
        try {
          options.recursive = static_cast<uint8_t>(std::stoi(arg));
        } catch (const std::exception &) {
          options.recursive = 0;
        }
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

bool Parser::isValidRecursiveArg(const std::string &arg) {
  return !arg.empty() && std::all_of(arg.begin(), arg.end(), ::isdigit);
}

} // namespace zz
