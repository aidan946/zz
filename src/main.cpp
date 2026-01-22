#include <iostream>
#include <string>
#include <vector>

#include "parsing.hpp"
#include "printer.hpp"
#include "types.hpp"

using std::string;

int main(int argc, char *argv[]) {
  using namespace zz;

  Options parsedOptions = Parser::parseCommandLineArgs(argc, argv);

  std::vector<string> gitignorePatterns = Parser::parseGitIgnore();

  try {
    Printer::printDirectory(fs::current_path(), parsedOptions, 0,
                            gitignorePatterns);
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
