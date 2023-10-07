#pragma once

#include "Product.h"
#include <string>
#include <iostream>

// メソッドuseを実装しているクラス
class IDCard : public Product {
public:
    IDCard(const std::string& owner) : owner(owner) {
        std::cout << owner << "のカードを作ります。" << std::endl;
    }
    void use() override {
        std::cout << owner << "のカードを使います。" << std::endl;
    }
    std::string getOwner() {
        return owner;
    }
private:
    std::string owner;
};