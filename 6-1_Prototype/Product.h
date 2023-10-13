#pragma once

#include <string>

// 抽象メソッドuseとcreateCloneが宣言されているインターフェース
class Product {
public:
    virtual ~Product() = default;
    virtual void use(const std::string& s) = 0;
    virtual Product* createClone() = 0; // インスタンスの複製を行う
};

//より優れたメモリ管理のためにスマートポインタを検討するとよい