#include <iostream>
#include <string>
#include "config_parser.hpp"
#include "command_builder.hpp"
#include "file_utils.hpp"

const std::string json_path = "/settings.json";

int main(int argc, char* argv[]){
    if (argc < 2){
        return 1; // неверное кол-во аргументов
    }

    std::string filename = argv[1];

    if (filename.find(".spb") == std::string::npos){
        return 1; // неверный тип файла
    }

    DefaultData data;
    if (!loadJsonConfig(getExecutableDirectory() + json_path, data)){
        return 1;  // ошибка загрузка json
    }

    CompileCommand parsed;
    if (!parseConfigFile(filename, parsed, data)){
        return 1; // ошибка при парсинге
    }

    std::string command = buildCommand(parsed);
    executeCommand(command);

    if (argc > 2){
        std::string flag = argv[2];

        if (flag == "--exe"){
            std::string exe = parsed.output_name;
            system(exe.c_str());
        }
    }

    return 0;    
}