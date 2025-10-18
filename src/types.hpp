#ifndef TYPES_HPP_
#define TYPES_HPP_

#include <string>
#include <vector>

enum class ParseSection{
    NONE,
    COMPILER,
    STD,
    FILES,
    NAME,
    FLAGS
};

struct CompileCommand{
    std::string compiler;
    std::string std_flag;
    std::vector<std::string> source_files;
    std::string output_name;
    std::vector<std::string> other_flags;
};

struct DefaultData{
    std::string default_compiler = "g++";
    std::string default_standard = "c++20";
    std::string default_name = "clown.exe"; 
};

#endif