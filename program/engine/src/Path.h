#pragma once
#include <filesystem>

namespace fs = std::filesystem;

inline const fs::path ROOT = fs::current_path();

#define MODEL(location)  (ROOT / "img"    / location).string()
#define SHADER(location) (ROOT / "program/engine/shader/rec" / location).string()