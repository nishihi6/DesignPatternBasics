#pragma once

#include "Factory.h"

// 具体的な工場を表すクラス（ListLink、ListTray、ListPageを作る）
class ListFactory : public Factory {
public:
    std::shared_ptr<Link> createLink(const std::string& caption, const std::string& url) override;
    std::shared_ptr<Tray> createTray(const std::string& caption) override;
    std::shared_ptr<Page> createPage(const std::string& title, const std::string& author) override;
};

// 具体的な部品：HTMLのリンクを表す
class ListLink : public Link {
public:
    ListLink(const std::string& caption, const std::string& url) : Link(caption, url) {}
    std::string makeHTML() override;
};

// 具体的な製品：HTMLのページを表すクラス
class ListPage : public Page {
public:
    ListPage(const std::string& title, const std::string& author) : Page(title, author) {}
    std::string makeHTML() override;
};

// 具体的な部品：LinkやTrayを集めたクラス
class ListTray : public Tray {
public:
    ListTray(const std::string& caption) : Tray(caption) {}
    std::string makeHTML() override;
};