#include "parsing.hpp"
#include "types.hpp"
#include <cctype>
#include <charconv>
#include <fstream>
#include <ranges>
#include <string>

namespace zz {

Options Parser::parseCommandLineArgs(int argc, char *argv[]) {
  Options options;
  bool nextArgRec = false;
  bool nextArgSort = false;

  for (int i = 1; i < argc; ++i) {
    std::string_view arg(argv[i]);

    if (!arg.empty() && arg[0] == '-') {
      std::string_view argCleaned = arg.substr(1);

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
      if (result.ec == std::errc::invalid_argument) {
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

std::vector<std::string> Parser::parseGitIgnore() {
  std::vector<std::string> patterns{".jj", ".git"};

  std::ifstream file(".gitignore");
  if (!file) {
    return patterns;
  }

  auto lines =
      std::ranges::istream_view<std::string>(file) |
      std::views::filter([](const std::string &line) {
        return !line.empty() && !line.starts_with('#');
      }) |
      std::views::transform([](std::string line) {
        auto trimmed = line | std::views::drop_while(::isspace) |
                       std::views::reverse | std::views::drop_while(::isspace) |
                       std::views::reverse;
        return std::string(trimmed.begin(), trimmed.end());
      }) |
      std::views::filter([](const std::string &line) { return !line.empty(); });

  std::ranges::copy(lines, std::back_inserter(patterns));

  return patterns;
}

} // namespace zz
