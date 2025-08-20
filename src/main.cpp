#include <filesystem>
#include <iostream>
#include <string>
#include <vector>

#include "parsing.hpp"
#include "types.hpp"

namespace fs = std::filesystem;

namespace zz {

class DirectoryLister {
public:
  static void printDirectory(const fs::path &dirPath, Options &options,
                             uint8_t depth,
                             const std::vector<std::string> &gitignorePatterns);

private:
  static std::string getIcon(const fs::directory_entry &entry, bool useIcons);
  static std::string getEntryKind(const fs::directory_entry &entry);
  static bool shouldRecursivePrint(const Options &options, uint8_t depth,
                                   const std::string &entryKind);
  static bool isGitIgnored(const std::string &name,
                           const std::vector<std::string> &patterns);
  static std::string getIndentation(uint8_t depth);
};

std::string DirectoryLister::getIcon(const fs::directory_entry &entry,
                                     bool useIcons) {
  if (!useIcons)
    return "";

  if (entry.is_directory()) {
    return "";
  } else if (entry.is_regular_file()) {
    return "";
  } else {
    return "";
  }
}

std::string DirectoryLister::getEntryKind(const fs::directory_entry &entry) {
  if (entry.is_directory()) {
    return "directory";
  } else if (entry.is_regular_file()) {
    return "file";
  } else if (entry.is_symlink()) {
    return "sym_link";
  } else if (entry.is_block_file()) {
    return "block_device";
  } else if (entry.is_character_file()) {
    return "character_device";
  } else if (entry.is_fifo()) {
    return "named_pipe";
  } else if (entry.is_socket()) {
    return "unix_domain_socket";
  } else {
    return "unknown";
  }
}

bool DirectoryLister::shouldRecursivePrint(const Options &options,
                                           uint8_t depth,
                                           const std::string &entryKind) {
  return entryKind == "directory" && options.recursive > 0 &&
         depth < options.recursive;
}

bool DirectoryLister::isGitIgnored(const std::string &name,
                                   const std::vector<std::string> &patterns) {
  for (const auto &pattern : patterns) {
    if (pattern == name) {
      return true;
    }

    // Handle directory patterns ending with '/'
    if (pattern.length() > 1 && pattern.back() == '/') {
      std::string dirPattern = pattern.substr(0, pattern.length() - 1);
      if (dirPattern == name) {
        return true;
      }
    }

    // Handle patterns starting with '/'
    if (pattern.length() > 1 && pattern.front() == '/') {
      std::string cleanPattern = pattern.substr(1);
      if (cleanPattern == name) {
        return true;
      }
    }
  }
  return false;
}

std::string DirectoryLister::getIndentation(uint8_t depth) {
  return std::string(depth * 2, ' ');
}

void DirectoryLister::printDirectory(
    const fs::path &dirPath, Options &options, uint8_t depth,
    const std::vector<std::string> &gitignorePatterns) {
  std::error_code ec;

  for (const auto &entry : fs::directory_iterator(dirPath, ec)) {
    if (ec) {
      std::cerr << "Error reading directory: " << ec.message() << std::endl;
      continue;
    }

    std::string icon = getIcon(entry, options.icons);
    std::string entryKind = getEntryKind(entry);
    std::string indentation = getIndentation(depth);
    std::string filename = entry.path().filename().string();
    std::string ending = options.list ? "\n" : "  ";

    bool shouldPrint = true;
    if (options.use_gitignore && isGitIgnored(filename, gitignorePatterns)) {
      shouldPrint = false;
    }

    if (shouldPrint) {
      if (shouldRecursivePrint(options, depth, entryKind)) {
        std::cout << indentation << icon << " " << filename << "(" << entryKind
                  << ")" << ending;
        printDirectory(entry.path(), options, depth + 1, gitignorePatterns);
      } else {
        std::cout << indentation << icon << " " << filename << "(" << entryKind
                  << ")" << ending;
      }
    }
  }
}

} // namespace zz

int main(int argc, char *argv[]) {
  using namespace zz;

  Options defaultOptions;
  Options parsedOptions =
      Parser::parseCommandLineArgs(argc, argv, defaultOptions);

  std::cout << "Option rec: " << static_cast<int>(parsedOptions.recursive)
            << "\n";
  std::cout << "\n\nFiles & dirs ---------------------------\n";

  std::vector<std::string> gitignorePatterns = Parser::parseGitIgnore();

  try {
    DirectoryLister::printDirectory(fs::current_path(), parsedOptions, 0,
                                    gitignorePatterns);
  } catch (const std::exception &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return 1;
  }

  return 0;
}
