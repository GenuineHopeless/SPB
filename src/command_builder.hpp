#ifndef COMMAND_BUILDER_HPP_
#define COMMAND_BUILDER_HPP_

#include "types.hpp"
#include <string>

std::string buildCommand(const CompileCommand& cmd);
void executeCommand(const std::string& command);

#endif