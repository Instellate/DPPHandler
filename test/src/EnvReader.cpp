//
// Created by instellate on 3/3/23.
//

#include "EnvReader.h"

void EnvReader::parseFile(const std::string &filePath) {
    std::fstream stream;
    stream.open(filePath, std::ios_base::in);

    if (!stream.is_open()) {
        std::cout << "Couldn't open stream\n";
        return;
    }

    while (!stream.eof()) {
        std::string key, value;

        char c;
        stream.get(c);
        while (c != '=') {
            if (stream.eof())
                break;
            key += c;
            stream.get(c);
        }

        stream.get(c);
        while (c != '\n') {
            if (stream.eof())
                break;
            value += c;
            stream.get(c);
        }
        secrets[key] = value;
    }
}
