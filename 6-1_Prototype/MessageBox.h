#pragma once

#include "Product.h"
#include <iostream>

class MessageBox : public Product {
private:
    char decochar;

public:
    MessageBox(char decochar) : decochar(decochar) {}

    void use(const std::string& s) override {
        int length = s.length();
        for (int i = 0; i < length + 4; i++) {
            std::cout << decochar;
        }
        std::cout << std::endl;
        std::cout << decochar << " " << s << " " << decochar << std::endl;
        for (int i = 0; i < length + 4; i++) {
            std::cout << decochar;
        }
        std::cout << std::endl;
    }

    Product* createClone() override {
        return new MessageBox(*this);
    }
};