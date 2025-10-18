#include "file_utils.hpp"
#include <fstream>
#include <algorithm>
#include <sstream>

#ifdef _WIN32
#include <windows.h>
#else
#include <limits.h>
#include <unistd.h>
#endif

bool fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

std::string trim(const std::string& str) {
    size_t start = str.find_first_not_of(" \t\r\n");
    size_t end = str.find_last_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    return str.substr(start, end - start + 1);
}

bool loadJsonConfig(const std::string& filename, DefaultData& data) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    std::string line;
    std::stringstream json_content;
    while (std::getline(file, line)) {
        json_content << line;
    }

    file.close();

    std::string content = json_content.str();

    size_t pos = 0;


    pos = content.find("\"default_compiler\"");
    if (pos != std::string::npos) {
        pos = content.find(":", pos);
        size_t start = content.find("\"", pos) + 1;
        size_t end = content.find("\"", start);
        if (start != std::string::npos && end != std::string::npos) {
            data.default_compiler = content.substr(start, end - start);
        }
    }
    else return false;


    pos = content.find("\"default_name\"");
    if (pos != std::string::npos) {
        pos = content.find(":", pos);
        size_t start = content.find("\"", pos) + 1;
        size_t end = content.find("\"", start);
        if (start != std::string::npos && end != std::string::npos) {
            data.default_name = content.substr(start, end - start);
        }
    }
    else return false;

    pos = content.find("\"default_standard\"");
    if (pos != std::string::npos) {
        pos = content.find(":", pos);
        size_t start = content.find("\"", pos) + 1;
        size_t end = content.find("\"", start);
        if (start != std::string::npos && end != std::string::npos) {
            data.default_standard = content.substr(start, end - start);
        }
    }
    else return false;

    return true;
}

std::string getExecutablePath() {
#ifdef _WIN32
    char exePath[MAX_PATH];
    GetModuleFileNameA(NULL, exePath, MAX_PATH);
    return std::string(exePath);
#else
    char exePath[PATH_MAX];
    ssize_t count = readlink("/proc/self/exe", exePath, PATH_MAX);
    if (count != -1) {
        return std::string(exePath, count);
    }
    return "";
#endif
}

std::string getExecutableDirectory() {
    std::string exePath = getExecutablePath();
    if (exePath.empty()) {
        return "";
    }

#ifdef _WIN32
    size_t lastSlash = exePath.find_last_of("\\");
#else
    size_t lastSlash = exePath.find_last_of("/");
#endif

    if (lastSlash != std::string::npos) {
        return exePath.substr(0, lastSlash + 1);
    }

    return "";
}
