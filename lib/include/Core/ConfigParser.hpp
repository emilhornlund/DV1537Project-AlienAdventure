//
// Created by Emil Hörnlund on 2019-02-20.
//

#ifndef COREGAMELIB_CONFIGPARSER_HPP
#define COREGAMELIB_CONFIGPARSER_HPP

#include <string>
#include <map>
#include <locale>
#include <sstream>
#include <algorithm>

namespace CGL { //CoreGameLib
    class ConfigParser final {
    private:
        std::map<std::string, std::string> m_data;

        const std::locale m_locale;

        std::pair<std::string, std::string> parseLine(const std::string &line) const;

        template<typename T>
        T convertToType(const std::string &input) const;
    public:
        ConfigParser() = default;

        ~ConfigParser() = default;

        bool loadFromFile(const std::string &filename);

        template<typename T>
        T get(const std::string &key, const T &defaultValue = T()) const;
    };

    template<typename T>
    T ConfigParser::get(const std::string &key, const T &defaultValue) const {
        auto it = this->m_data.find(key);
        if (it != m_data.end()){
            T value = convertToType<T>(it->second);
            return value;
        }
        return defaultValue;
    }

    template<typename T>
    inline T ConfigParser::convertToType(const std::string &input) const {
        throw std::runtime_error("Unconvertable type encountered");
    }

    template<>
    inline int ConfigParser::convertToType<int>(const std::string &input) const {
        int value;
        std::stringstream ss(input);
        ss >> value;
        return value;
    }

    template<>
    inline bool ConfigParser::convertToType<bool>(const std::string &input) const {
        return input == "TRUE";
    }
}

#endif //COREGAMELIB_CONFIGPARSER_HPP
