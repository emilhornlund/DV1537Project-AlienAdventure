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

#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif

#include <iostream>

template <typename Resource>
class ResourceHandler {
private:
    std::map<std::string, Resource*> resources;

    bool hasResource(const std::string &filename);

    Resource& get(const std::string &filename) const;

    std::string bundlePath();

    std::string resourcePath();
public:
    ResourceHandler() = default;

    ~ResourceHandler();

    ResourceHandler(const ResourceHandler &original) = delete;

    ResourceHandler& operator=(const ResourceHandler &original) = delete;

    Resource& load(const std::string &filename);

    Resource& open(const std::string &filename);
};

template<typename Resource>
ResourceHandler<Resource>::~ResourceHandler() {
    for (auto it = this->resources.begin(); it != this->resources.end(); it++) {
        delete (it->second);
    }
    this->resources.clear();
}

template<typename Resource>
Resource & ResourceHandler<Resource>::load(const std::string &filename) {
    if (!this->hasResource(filename)) {
        auto *resource = new Resource;
        if (!resource->loadFromFile(this->resourcePath() + filename))
            throw std::runtime_error("Failed to load " + filename);
        this->resources.insert(std::make_pair(filename, resource));
    }
    return this->get(filename);
}

template<typename Resource>
Resource &ResourceHandler<Resource>::open(const std::string &filename) {
    if (!this->hasResource(filename)) {
        auto *resource = new Resource;
        if (!resource->openFromFile(this->resourcePath() + filename))
            throw std::runtime_error("Failed to load " + filename);
        this->resources.insert(std::make_pair(filename, resource));
    }
    return this->get(filename);
}

template<typename Resource>
bool ResourceHandler<Resource>::hasResource(const std::string &filename) {
    auto found = this->resources.find(filename);
    return (found != this->resources.end());
}

template<typename Resource>
Resource &ResourceHandler<Resource>::get(const std::string &filename) const {
    auto found = resources.find(filename);
    if (found == resources.end())
        throw std::runtime_error("Failed to get resource: " + filename);
    return *found->second;
}

template<typename Resource>
std::string ResourceHandler<Resource>::bundlePath() {
#ifdef __APPLE__
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourcesURL = CFBundleCopyBundleURL(mainBundle);
    CFStringRef str = CFURLCopyFileSystemPath(resourcesURL, kCFURLPOSIXPathStyle );
    CFRelease(resourcesURL);
    char path[PATH_MAX];
    CFStringGetCString(str, path, FILENAME_MAX, kCFStringEncodingASCII);
    CFRelease(str);
    std::string myPath(path);
    return myPath + "/";
#else
    return "";
#endif
}

template<typename Resource>
std::string ResourceHandler<Resource>::resourcePath() {
#ifdef __APPLE__
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
    CFStringRef str = CFURLCopyFileSystemPath(resourcesURL, kCFURLPOSIXPathStyle );
    CFRelease(resourcesURL);
    char path[PATH_MAX];
    CFStringGetCString(str, path, FILENAME_MAX, kCFStringEncodingASCII);
    CFRelease(str);
    std::string myPath(path);
    return bundlePath() + myPath + "/";
#else
    return "./resources/";
#endif
}

#endif //ALIENADVENTURE_RESOURCEHANDLER_HPP
