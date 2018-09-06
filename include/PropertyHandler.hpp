//
// Created by Emil Hörnlund on 2018-09-06.
//

#ifndef ALIENADVENTURE_PROPERTYHANDLER_HPP
#define ALIENADVENTURE_PROPERTYHANDLER_HPP

#include <string>
#include <map>
#include <memory>
#include <iostream>
#include <utility>

#include "Core.hpp"

class PropertyHandler {
private:
    class IProperty {
    public:
        IProperty() = default;

        virtual ~IProperty() = default;;
    };

    template<class T=unsigned int>
    class TProperty : public IProperty {
    private:
        T value;
    public:
        explicit TProperty(T value) : IProperty(), value(value) {}

        ~TProperty() override = default;

        inline T getValue() const {
            return this->value;
        }

        inline void setValue(const T value) {
            this->value = value;
        }
    };

    std::map<const std::string, IProperty*> properties;
public:
    PropertyHandler() = default;

    ~PropertyHandler() {
        std::map<const std::string, IProperty*>::iterator it;
        for (it = this->properties.begin(); it != this->properties.end(); it++) {
            delete (it->second);
            this->properties.erase(it);
        }
    }

    template<class T>
    inline T get(const std::string& id) {
        if (this->properties.find(id) != this->properties.end()) {
            return static_cast<TProperty<T>*>(this->properties.at(id))->getValue();
        } else {
            throw std::runtime_error("Unable to find property");
        }
    }

    template<class T>
    void set(const std::string& id, T value) {
        if (this->properties.find(id) == this->properties.end()) {
            this->properties.insert(std::make_pair(id, new TProperty<T>(value)));
        } else {
            static_cast<TProperty<T>*>(this->properties.at(id))->setValue(value);
        }
    }
};

#endif //ALIENADVENTURE_PROPERTYHANDLER_HPP
