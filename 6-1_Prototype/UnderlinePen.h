#pragma once

#include "Product.h"
#include <iostream>

// 文字列に下線を引いて表示するクラス（useとcreateCloneを実装）
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