#pragma once

#include <unordered_map>
#include <string>
#include "Product.h"

// createCloneを使ってインスタンスを複製するクラス
class Manager {
private:
    std::unordered_map<std::string, Product*> showcase;

public:
    void registerProduct(const std::string& name, Product* proto) {
        showcase[name] = proto;
    }

    Product* create(const std::string& protoname) {
        Product* p = showcase[protoname];
        return p->createClone();
    }
};

//ProductとManagerはMessageBoxやUnderlinePenクラスなどとは独立に修正ができる