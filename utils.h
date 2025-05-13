#pragma once

#include <ostream>
#include <string>
#include <set>

#include "definitions.h"
#include "stringfiable.h"

std::string vector_as_string(const std::vector<char>& set, std::string name = "");
std::string vector_as_string(const std::vector<State>& set, std::string name = "");

std::string set_as_string(const std::set<char>& set, std::string name = "");

std::string productions_as_string(const Productions& productions, std::string name = "");

std::string transitions_as_string(const Transitions& transitions, std::string name = "");

std::ostream& operator<<(std::ostream& stream, const Stringfiable& object);
