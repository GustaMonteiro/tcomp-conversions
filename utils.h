#pragma once

#include <string>
#include <set>

#include "definitions.h"

std::string set_as_string(const std::set<char>& set, std::string name = "");

std::string productions_as_string(const Productions& productions, std::string name = "");
