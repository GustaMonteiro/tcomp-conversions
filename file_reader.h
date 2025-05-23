#pragma once

#include <filesystem>
#include <fstream>

#include "glud.h"

GLUD read_grammar_from_file(std::filesystem::path file_path);