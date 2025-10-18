#include "config_parser.hpp"
#include "file_utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

bool parseConfigFile(const std::string& filename, CompileCommand& result, DefaultData& data) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return false;
    }

    std::string line;
    ParseSection current_section = ParseSection::NONE;

    bool has_compiler = false;
    bool has_std = false;
    bool has_files = false;
    bool has_name = false;
    bool has_flags = false;

    while (std::getline(file, line)) {
        std::string trimmed_line = trim(line);

        if (trimmed_line.empty() || trimmed_line[0] == '#') {
            continue;
        }

        if (trimmed_line == "<COMPILER>") {
            current_section = ParseSection::COMPILER;
            continue;
        }
        else if (trimmed_line == "<STD>") {
            current_section = ParseSection::STD;
            continue;
        }
        else if (trimmed_line == "<FILES>") {
            current_section = ParseSection::FILES;
            continue;
        }
        else if (trimmed_line == "<NAME>") {
            current_section = ParseSection::NAME;
            continue;
        }
        else if (trimmed_line == "<FLAGS>") {
            current_section = ParseSection::FLAGS;
            continue;
        }
        else if (trimmed_line.find('<') == 0 && trimmed_line.find('>') != std::string::npos) {
            current_section = ParseSection::NONE;
            continue;
        }

        switch (current_section) {
        case ParseSection::COMPILER:
            result.compiler = trim(trimmed_line);
            has_compiler = true;
            current_section = ParseSection::NONE;
            break;

        case ParseSection::STD:
            result.std_flag = "-std=" + trim(trimmed_line);
            has_std = true;
            current_section = ParseSection::NONE;
            break;

        case ParseSection::FILES: {
            std::string file_path = trim(trimmed_line);
            if (!file_path.empty()) {
                result.source_files.push_back(file_path);
                has_files = true;
            }
            break;
        }

        case ParseSection::NAME:
            result.output_name = trim(trimmed_line);
            has_name = true;
            current_section = ParseSection::NONE;
            break;

        case ParseSection::FLAGS: {
            std::string flag = trim(trimmed_line);
            if (!flag.empty()) {
                result.other_flags.push_back(flag);
                has_flags = true;
            }
            break;
        }
        case ParseSection::NONE:
            break;
        }
    }

    if (!has_compiler) {
        result.compiler = data.default_compiler;
    }

    if (!has_std){
        result.std_flag = "-std=" + data.default_standard;
    }

    if (!has_files) {
        result.source_files.push_back("");
    }

    if (!has_name) {
        result.output_name = data.default_name;
    }

    if (!has_flags){
        result.other_flags.push_back("");
    }

    return true;
}
