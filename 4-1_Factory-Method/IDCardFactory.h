#pragma once

#include "Factory.h"
#include "IDCard.h"
#include <vector>

// メソッドcreateProduct、registerProductを実装しているクラス
class IDCardFactory : public Factory {
private:
    std::vector<std::string> owners;
protected:
    Product* createProduct(const std::string& owner) override {
        return new IDCard(owner);
    }
    void registerProduct(Product* product) override {
        owners.push_back(static_cast<IDCard*>(product)->getOwner());
    }
public:
    std::vector<std::string> getOwners() {
        return owners;
    }
};