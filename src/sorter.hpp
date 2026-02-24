#pragma once

#include "types.hpp"
#include <expected>
#include <filesystem>
#include <system_error>
#include <vector>

namespace zz {

std::expected<std::vector<std::filesystem::directory_entry>, std::error_code>
sortDirectory(const std::filesystem::path &dirPath, Sorting sorting);

} // namespace zz
