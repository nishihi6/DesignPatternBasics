#pragma once

// 抽象メソッドuseのみ定義されている抽象クラス
class Product {
public:
    virtual ~Product() {}
    virtual void use() = 0;
};

//C++では、あるクラスが他のクラスから派生される可能性がある場合、その基底クラスのデストラクタは常にvirtualであるべき。