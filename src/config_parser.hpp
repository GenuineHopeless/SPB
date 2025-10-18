#ifndef CONFIG_PARSER_HPP_
#define CONFIG_PARSER_HPP_

#include "types.hpp"
#include <string>

bool parseConfigFile(const std::string& filename, CompileCommand& result, DefaultData &data);

#endif