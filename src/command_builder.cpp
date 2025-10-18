#include "command_builder.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>

std::string buildCommand(const CompileCommand& cmd) {
    std::stringstream ss;

    ss << cmd.compiler;

    if (!cmd.std_flag.empty()){
        ss << " " << cmd.std_flag;
    }

    for (const auto& flag : cmd.other_flags){
        ss << " " << flag;
    }

    for (const auto& file: cmd.source_files){
        ss << " " << file;
    }

    if (!cmd.output_name.empty()){
        ss << " -o " << cmd.output_name;
    }

    return ss.str();
}

void executeCommand(const std::string& command) {
    int result = system(command.c_str());
    // result == 0 - success
    // result == 1 - fail
}