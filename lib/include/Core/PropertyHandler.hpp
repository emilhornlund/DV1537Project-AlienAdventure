//
// Created by Emil Hörnlund on 2018-09-06.
//

#ifndef COREGAMELIB_PROPERTYHANDLER_HPP
#define COREGAMELIB_PROPERTYHANDLER_HPP

#include <string>
#include <map>
#include <memory>
#include <iostream>
#include <utility>

namespace CGL { //CoreGameLib
    class PropertyHandler {
    private:
        class IProperty {
        private:
            IProperty(const IProperty &original);

            IProperty &operator=(const IProperty &original);

        public:
            IProperty() = default;

            virtual ~IProperty() = default;;
        };

        template<class T=unsigned int>
        class TProperty : public IProperty {
        private:
            T value;

            TProperty(const TProperty &original);

            TProperty &operator=(const TProperty &original);

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

        std::map<const std::string, IProperty *> properties;

        PropertyHandler(const PropertyHandler &original);

        PropertyHandler &operator=(const PropertyHandler &original);
    public:
        PropertyHandler() = default;

        ~PropertyHandler() {
            std::map<const std::string, IProperty *>::iterator it;
            for (it = this->properties.begin(); it != this->properties.end(); it++) {
                delete (it->second);
            }
            this->properties.clear();
        }

        template<class T>
        inline T get(const std::string &id) {
            if (this->properties.find(id) != this->properties.end()) {
                return static_cast<TProperty<T> *>(this->properties.at(id))->getValue();
            } else {
                return T();
            }
        }

        template<class T>
        void set(const std::string &id, T value) {
            if (this->properties.find(id) == this->properties.end()) {
                this->properties.insert(std::make_pair(id, new TProperty<T>(value)));
            } else {
                static_cast<TProperty<T> *>(this->properties.at(id))->setValue(value);
            }
        }

        bool hasProperty(const std::string &id) {
            return (this->properties.find(id) != this->properties.end());
        }
    };
}

#endif //COREGAMELIB_PROPERTYHANDLER_HPP
