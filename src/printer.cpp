#include <algorithm>
#include <cstdint>
#include <expected>
#include <filesystem>
#include <format>
#include <iostream>
#include <print>

#include "printer.hpp"
#include "sorter.hpp"
#include "types.hpp"

namespace fs = std::filesystem;

namespace {

std::string getIcon(const fs::directory_entry &entry, bool useIcons) {
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

zz::EntryKind getEntryKind(const fs::directory_entry &entry) {
  using zz::EntryKind;
  if (entry.is_directory())
    return EntryKind::Directory;
  if (entry.is_regular_file())
    return EntryKind::File;
  if (entry.is_symlink())
    return EntryKind::Symlink;
  if (entry.is_block_file())
    return EntryKind::BlockDevice;
  if (entry.is_character_file())
    return EntryKind::CharacterDevice;
  if (entry.is_fifo())
    return EntryKind::NamedPipe;
  if (entry.is_socket())
    return EntryKind::Socket;
  return EntryKind::Unknown;
}

bool shouldRecursivePrint(const zz::Options &options, uint8_t depth,
                          zz::EntryKind kind) {
  return kind == zz::EntryKind::Directory && options.recursive > 0 &&
         depth < options.recursive;
}

bool isGitIgnored(const std::string &name,
                  const std::vector<std::string> &patterns) {
  auto matches = [&name](const std::string &pattern) {
    if (pattern == name)
      return true;
    // Handle directory patterns ending with '/'
    if (pattern.length() > 1 && pattern.back() == '/')
      return pattern.substr(0, pattern.length() - 1) == name;
    // Handle patterns starting with '/'
    if (pattern.length() > 1 && pattern.front() == '/')
      return pattern.substr(1) == name;
    return false;
  };
  return std::ranges::any_of(patterns, matches);
}

std::string getIndentation(uint8_t depth) {
  return std::string(depth * 2, ' ');
}

std::string getFileSize(const fs::directory_entry &entry, bool isDetails) {
  if (!isDetails)
    return " ";
  if (entry.is_directory())
    return "- ";

  auto size = entry.file_size();
  int o{};
  double mantissa = size;
  for (; mantissa >= 1024. && o < 6; mantissa /= 1024., ++o)
    ;
  constexpr std::string_view suffixes = "BKMGTPE";
  return o ? std::format("{:.1f}{}B ", mantissa, suffixes[o])
           : std::format("{:.1f}{} ", mantissa, suffixes[o]);
}

std::string getPermissions(const fs::directory_entry &entry, bool isDetails) {
  if (!isDetails)
    return " ";

  fs::perms p = entry.status().permissions();
  using fs::perms;
  auto bit = [&](char op, perms perm) -> char {
    return (perms::none == (perm & p)) ? '-' : op;
  };

  return std::format("{}{}{}{}{}{}{}{}{} ", bit('r', perms::owner_read),
                     bit('w', perms::owner_write), bit('x', perms::owner_exec),
                     bit('r', perms::group_read), bit('w', perms::group_write),
                     bit('x', perms::group_exec), bit('r', perms::others_read),
                     bit('w', perms::others_write),
                     bit('x', perms::others_exec));
}

} // namespace

namespace zz {

void printDirectory(const fs::path &dirPath, const Options &options,
                    uint8_t depth,
                    const std::vector<std::string> &gitignorePatterns) {

  auto result = sortDirectory(dirPath, options.sorting);
  if (!result) {
    std::println(std::cerr, "Error reading directory '{}': {}",
                 dirPath.string(), result.error().message());
    return;
  }

  for (const auto &entry : *result) {
    std::string icon = getIcon(entry, options.icons);
    EntryKind kind = getEntryKind(entry);
    std::string indentation = getIndentation(depth);
    std::string filename = entry.path().filename().string();
    std::string size = getFileSize(entry, options.details);
    std::string permissions = getPermissions(entry, options.details);

    if (options.use_gitignore && isGitIgnored(filename, gitignorePatterns))
      continue;

    if (options.list) {
      std::println("{}{} {}{}{}", indentation, icon, size, permissions,
                   filename);
    } else {
      std::print("{}{} {}{}{}  ", indentation, icon, size, permissions,
                 filename);
    }

    if (shouldRecursivePrint(options, depth, kind))
      printDirectory(entry.path(), options, depth + 1, gitignorePatterns);
  }
}

} // namespace zz
