#include <cctype>
#include <charconv>
#include <fstream>
#include <ranges>
#include <string>

#include "parsing.hpp"
#include "types.hpp"

namespace zz {

Options parseCommandLineArgs(std::span<char *> args) {
  Options options;
  bool nextArgRec = false;
  bool nextArgSort = false;

  for (const char *argPtr : args.subspan(1)) {
    std::string_view arg(argPtr);

    if (!arg.empty() && arg[0] == '-') {
      std::string_view argCleaned = arg.substr(1);
      nextArgRec = false;
      nextArgSort = false;

      if (!argCleaned.empty() && argCleaned.starts_with('r')) {
        nextArgRec = true;
      } else if (argCleaned == "sort") {
        nextArgSort = true;
      } else if (argCleaned == "no-highlights") {
        options.highlighting = false;
      } else if (argCleaned == "no-icons") {
        options.icons = false;
      } else if (argCleaned == "no-list") {
        options.list = false;
      } else if (argCleaned == "no-gitignore") {
        options.use_gitignore = false;
      } else if (argCleaned == "details") {
        options.details = true;
      }
    } else if (nextArgRec) {
      auto result = std::from_chars(arg.data(), arg.data() + arg.size(),
                                    options.recursive);
      if (result.ec == std::errc{}) {
        options.recursive = std::min(options.recursive, 255);
      } else {
        options.recursive = 0;
      }
      nextArgRec = false;
    } else if (nextArgSort) {
      if (arg == "folder-file") {
        options.sorting = Sorting::FOLDER_FILE;
      } else if (arg == "file-folder") {
        options.sorting = Sorting::FILE_FOLDER;
      } else if (arg == "none") {
        options.sorting = Sorting::NONE;
      }
      nextArgSort = false;
    }
  }

  return options;
}

struct Line : std::string {
  friend std::istream &operator>>(std::istream &is, Line &l) {
    return std::getline(is, l);
  }
};

std::vector<std::string> parseGitIgnore() {
  std::vector<std::string> patterns{".jj", ".git"};

  std::ifstream file(".gitignore");
  if (!file) {
    return patterns;
  }

  auto lines =
      std::ranges::istream_view<Line>(file) |
      std::views::filter([](const std::string &line) {
        return !line.empty() && !line.starts_with('#');
      }) |
      std::views::transform([](std::string line) {
        auto isSpace = [](unsigned char c) { return std::isspace(c); };
        return line | std::views::drop_while(isSpace) | std::views::reverse |
               std::views::drop_while(isSpace) | std::views::reverse |
               std::ranges::to<std::string>();
      }) |
      std::views::filter([](const std::string &line) { return !line.empty(); });

  std::ranges::copy(lines, std::back_inserter(patterns));

  return patterns;
}

} // namespace zz
