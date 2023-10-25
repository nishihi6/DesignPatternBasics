#include "Factory.h"
#include "ListFactory.h"
#include "TableFactory.h"
// 他のFactory派生クラスのインクルードもここに追加する

std::shared_ptr<Factory> Factory::getFactory(const std::string& classname) {
    // リフレクションがC++にはないため、明示的なインスタンス化が必要
    if (classname == "ListFactory") {
        return std::make_shared<ListFactory>();
    }
    if (classname == "TableFactory") {
        return std::make_shared<TableFactory>();
    }
    // 他のFactoryの名前に対する条件もここに追加する
    return nullptr;
}

void Page::output() {
    std::ofstream out(title + ".html");
    out << this->makeHTML();    // out << this->makeHTML();でもよい
    out.close();
    std::cout << title + ".html" << "を作成しました。" << std::endl;
}