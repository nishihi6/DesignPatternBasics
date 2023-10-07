#pragma once

#include "Product.h"
#include <iostream>
#include <string>

// メソッドcreateを実装している抽象クラス
class Factory {
public:
    Product* create(const std::string& owner) {
        Product* p = createProduct(owner);
        registerProduct(p);
        return p;
    }
protected:
    virtual Product* createProduct(const std::string& owner) = 0;
    virtual void registerProduct(Product* product) = 0;
};