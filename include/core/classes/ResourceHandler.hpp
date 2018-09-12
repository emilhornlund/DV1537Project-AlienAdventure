/**
 * @file ResourceHandler.hpp
 * @date 2018-09-04
 * @author Emil Hörnlund
 */

#ifndef ALIENADVENTURE_RESOURCEHANDLER_HPP
#define ALIENADVENTURE_RESOURCEHANDLER_HPP

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>

template <typename Resource>
class ResourceHandler {
private:
    std::map<std::string, Resource*> resources;

    bool hasResource(const std::string &filePath);

    Resource& get(const std::string& filePath) const;
public:
    ResourceHandler() = default;

    ~ResourceHandler();

    ResourceHandler(const ResourceHandler &original) = delete;

    ResourceHandler& operator=(const ResourceHandler &original) = delete;

    Resource& load(const std::string &filePath);

    Resource& open(const std::string &filePath);
};

template<typename Resource>
ResourceHandler<Resource>::~ResourceHandler() {
    for (auto it = this->resources.begin(); it != this->resources.end(); it++) {
        delete (it->second);
    }
    this->resources.clear();
}

template<typename Resource>
Resource & ResourceHandler<Resource>::load(const std::string &filePath) {
    if (!this->hasResource(filePath)) {
        auto *resource = new Resource;
        if (!resource->loadFromFile(filePath))
            throw std::runtime_error("Failed to load " + filePath);
        this->resources.insert(std::make_pair(filePath, resource));
    }
    return this->get(filePath);
}

template<typename Resource>
Resource &ResourceHandler<Resource>::open(const std::string &filePath) {
    if (!this->hasResource(filePath)) {
        auto *resource = new Resource;
        if (!resource->openFromFile(filePath))
            throw std::runtime_error("Failed to load " + filePath);
        this->resources.insert(std::make_pair(filePath, resource));
    }
    return this->get(filePath);
}

template<typename Resource>
bool ResourceHandler<Resource>::hasResource(const std::string &filePath) {
    auto found = this->resources.find(filePath);
    return (found != this->resources.end());
}

template<typename Resource>
Resource &ResourceHandler<Resource>::get(const std::string &filePath) const {
    auto found = resources.find(filePath);
    if (found == resources.end())
        throw std::runtime_error("Failed to get resource: " + filePath);
    return *found->second;
}

#endif //ALIENADVENTURE_RESOURCEHANDLER_HPP
