#pragma once
#include "Factory.h"

// 具体的な工場を表すクラス（TableLink、TableTray、TablePageを作る）
class TableFactory : public Factory {
public:
    std::shared_ptr<Link> createLink(const std::string& caption, const std::string& url) override;
    std::shared_ptr<Tray> createTray(const std::string& caption) override;
    std::shared_ptr<Page> createPage(const std::string& title, const std::string& author) override;
};

// 具体的な部品：HTMLのリンクを表すクラス
class TableLink : public Link {
public:
    TableLink(const std::string& caption, const std::string& url);
    std::string makeHTML() override;
};

// 具体的な部品：TableLinkやTableTrayを集めたクラス
class TablePage : public Page {
public:
    TablePage(const std::string& title, const std::string& author);
    std::string makeHTML() override;
};

// 具体的な製品：HTMLのページを表すクラス
class TableTray : public Tray {
public:
    TableTray(const std::string& caption);
    std::string makeHTML() override;
};