//
// Created by Emil Hörnlund on 2019-02-20.
//

#include <Core/ConfigParser.hpp>

#include <iostream>
#include <fstream>

bool CGL::ConfigParser::loadFromFile(const std::string &filename) {
    std::ifstream in(filename);
    if (!in.is_open()) {
        return false;
    }

    std::string line;
    while(std::getline(in, line)) {
        std::pair<std::string, std::string> keyValuePair = this->parseLine(line);
        if (!keyValuePair.first.empty()) {
            this->m_data[keyValuePair.first] = keyValuePair.second;
        }
    }

    in.close();
    return true;
}

std::pair<std::string, std::string> CGL::ConfigParser::parseLine(const std::string &line) const {
    if (!line.empty() && line[0] != '#') {
        size_t index = 0;
        while(std::isspace(line[index], this->m_locale))
            index++;

        const size_t beginKeyString = index;
        while(!std::isspace(line[index], m_locale) && line[index] != '=')
            index++;
        const std::string key = line.substr(beginKeyString, index - beginKeyString);

        while(std::isspace(line[index], m_locale) || line[index] == '=')
            index++;

        const std::string value = line.substr(index, line.size() - index);
        return std::make_pair(key, value);
    }
    return std::make_pair(std::string(), std::string());
}