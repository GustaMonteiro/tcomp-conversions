#pragma once

#include <vector>
#include <map>
#include <string>

using Transitions = std::map<char, std::map<char, char>>;
using Productions = std::map<char, std::vector<std::string>>;
