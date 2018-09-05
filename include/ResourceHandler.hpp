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
public:
    ResourceHandler() = default;

    ~ResourceHandler();

    void load(const std::string& filename);

    void open(const std::string& filename);

    Resource& get(const std::string& filename);

    bool isLoaded(const std::string& filename);
};

template<typename Resource>
ResourceHandler<Resource>::~ResourceHandler() {
    for (auto it = this->resources.begin(); it != this->resources.end(); it++) {
        delete (it->second);
    }
    this->resources.clear();
}

template<typename Resource>
bool ResourceHandler<Resource>::isLoaded(const std::string &filename) {
    auto found = this->resources.find(filename);
    return (found != this->resources.end());
}

template<typename Resource>
void ResourceHandler<Resource>::load(const std::string &filename) {
    auto *resource = new Resource;
    if (!resource->loadFromFile(filename))
        throw std::runtime_error("Failed to load " + filename);
    this->resources.insert(std::make_pair(filename, resource));
}

template<typename Resource>
void ResourceHandler<Resource>::open(const std::string &filename) {
    auto *resource = new Resource;
    if (!resource->openFromFile(filename))
        throw std::runtime_error("Failed to open " + filename);
    this->resources.insert(std::make_pair(filename, resource));
}

template<typename Resource>
Resource &ResourceHandler<Resource>::get(const std::string &filename) {
    auto found = resources.find(filename);
    if (found == resources.end())
        throw std::runtime_error("Failed to get resource: " + filename);
    return *found->second;
}

#endif //ALIENADVENTURE_RESOURCEHANDLER_HPP
