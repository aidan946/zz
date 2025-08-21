#include <iostream>
#include <string>
#include <vector>

#include "parsing.hpp"
#include "types.hpp"
#include "printer.hpp"


int main(int argc, char *argv[]) {
  using namespace zz;

  Options defaultOptions;
  Options parsedOptions =
      Parser::parseCommandLineArgs(argc, argv, defaultOptions);

  std::cout << "Option rec: " << static_cast<int>(parsedOptions.recursive)
            << "\n";
  std::cout << "Options icons: " << static_cast<int>(parsedOptions.icons)
            << "\n";
  std::cout << "\n\nFiles & dirs ---------------------------\n";

  std::vector<std::string> gitignorePatterns = Parser::parseGitIgnore();

  try {
    Printer::printDirectory(fs::current_path(), parsedOptions, 0,
                                    gitignorePatterns);
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
