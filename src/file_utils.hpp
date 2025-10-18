#ifndef FILE_UTILS_HPP_
#define FILE_UTILS_HPP_

#include <string>
#include "types.hpp"

bool fileExists(const std::string& filename);
std::string trim(const std::string& str);
bool loadJsonConfig(const std::string& filename, DefaultData& data);

std::string getExecutablePath();
std::string getExecutableDirectory();

#endif