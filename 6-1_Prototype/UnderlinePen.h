#pragma once

#include "Product.h"
#include <iostream>

class UnderlinePen : public Product {
private:
    char ulchar;

public:
    UnderlinePen(char ulchar) : ulchar(ulchar) {}

    void use(const std::string& s) override {
        int length = s.length();
        std::cout << "\"" << s << "\"" << std::endl;
        std::cout << " ";
        for (int i = 0; i < length; i++) {
            std::cout << ulchar;
        }
        std::cout << std::endl;
    }

    Product* createClone() override {
        return new UnderlinePen(*this);
    }
};