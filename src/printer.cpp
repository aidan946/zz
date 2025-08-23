#include <filesystem>
#include <iostream>

#include "printer.hpp"
#include "types.hpp"

namespace fs = std::filesystem;

namespace zz {

std::string Printer::getIcon(const fs::directory_entry &entry, bool useIcons) {
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

std::string Printer::getEntryKind(const fs::directory_entry &entry) {
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

bool Printer::shouldRecursivePrint(const Options &options, uint8_t depth,
                                   const std::string &entryKind) {
  return entryKind == "directory" && options.recursive > 0 &&
         depth < options.recursive;
}

bool Printer::isGitIgnored(const std::string &name,
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

std::string Printer::getIndentation(uint8_t depth) {
  return std::string(depth * 2, ' ');
}

std::string Printer::getFileSize(const fs::directory_entry &entry,
                                 bool isDeatils) {
  if (isDeatils == true) {
    if (entry.is_directory()) {
      return "-";
    } else {
      auto size = entry.file_size();
      int o{};
      double mantissa = size;
      for (; mantissa >= 1024.; mantissa /= 1024., ++o)
        ;
      int humanizedSize = std::ceil(mantissa * 10.) / 10.;
      const char humanizedEnding = "BKMGTPE"[o];
      return o ? std::to_string(humanizedSize) + humanizedEnding + "B" + " "
               : std::to_string(humanizedSize) + humanizedEnding + " ";
    }
  } else {
    return " ";
  }
}

std::string Printer::getPermissions(const fs::directory_entry &entry,
                                    bool isDeatils) {
  if (isDeatils == true) {
    std::filesystem::perms p =
        std::filesystem::status(entry.path()).permissions();

    using std::filesystem::perms;
    auto show = [=](char op, perms perm) -> std::string {
      return (perms::none == (perm & p) ? "-" : std::string(1, op));
    };

    std::string output;
    output += show('r', perms::owner_read);
    output += show('w', perms::owner_write);
    output += show('x', perms::owner_exec);
    output += show('r', perms::group_read);
    output += show('w', perms::group_write);
    output += show('x', perms::group_exec);
    output += show('r', perms::others_read);
    output += show('w', perms::others_write);
    output += show('x', perms::others_exec);

    return output + " ";
  } else {
    return " ";
  }
}

void Printer::printDirectory(
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
    std::string size = getFileSize(entry, options.details);
    std::string permissions = getPermissions(entry, options.details);

    bool shouldPrint = true;
    if (options.use_gitignore && isGitIgnored(filename, gitignorePatterns)) {
      shouldPrint = false;
    }

    if (shouldPrint) {
      if (shouldRecursivePrint(options, depth, entryKind)) {
        std::cout << indentation << icon << " " << size << permissions
                  << filename << ending;
        printDirectory(entry.path(), options, depth + 1, gitignorePatterns);
      } else {
        std::cout << indentation << icon << " " << size << permissions
                  << filename << ending;
      }
    }
  }
}
} // namespace zz
