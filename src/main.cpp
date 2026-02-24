#include <filesystem>
#include <iostream>
#include <span>
#include <vector>

#include "parsing.hpp"
#include "printer.hpp"
#include "types.hpp"

int main(int argc, char *argv[]) {
  zz::Options options = zz::parseCommandLineArgs(std::span(argv, argc));

  std::vector<std::string> gitignorePatterns;
  if (options.use_gitignore) {
    gitignorePatterns = zz::parseGitIgnore();
  }

  try {
    zz::printDirectory(std::filesystem::current_path(), options, 0,
                       gitignorePatterns);
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << "\n";
    return 1;
  }
}
