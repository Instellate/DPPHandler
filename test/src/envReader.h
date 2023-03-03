//
// Created by instellate on 3/3/23.
//

#include <unordered_map>
#include <fstream>
#include <iostream>
#include <string>

struct envReader {
    std::unordered_map<std::string, std::string> secrets;

    void parseFile(const std::string &filePath);
};
