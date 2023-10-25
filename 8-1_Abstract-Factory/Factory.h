#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <memory>
#include <fstream>

class Item;
class Link;
class Tray;
class Page;

// 抽象的な工場を表すクラス（Link、Tray、Pageを作る）
class Factory {
public:
    static std::shared_ptr<Factory> getFactory(const std::string& classname);
    virtual std::shared_ptr<Link> createLink(const std::string& caption, const std::string& url) = 0;
    virtual std::shared_ptr<Tray> createTray(const std::string& caption) = 0;
    virtual std::shared_ptr<Page> createPage(const std::string& title, const std::string& author) = 0;
};

// LinkとTrayを統一的に扱うためのクラス
class Item {
protected:
    std::string caption;
public:
    Item(const std::string& caption) : caption(caption) {}
    virtual std::string makeHTML() = 0;
};

// 抽象的な部品：HTMLのリンクを表すクラス
class Link : public Item {
protected:
    std::string url;
public:
    Link(const std::string& caption, const std::string& url) : Item(caption), url(url) {}
};

// 抽象的な製品：HTMLのページを表すクラス
class Page {
protected:
    std::string title;
    std::string author;
    std::vector<std::shared_ptr<Item>> content;
public:
    Page(const std::string& title, const std::string& author) : title(title), author(author) {}
    void add(std::shared_ptr<Item> item) {
        content.push_back(item);
    }
    virtual void output();
    virtual std::string makeHTML() = 0;
};
// shared_ptrはJavaの参照に相当する

// 抽象的な部品：LinkやTrayを集めたクラス
class Tray : public Item {
protected:
    std::vector<std::shared_ptr<Item>> tray;
public:
    Tray(const std::string& caption) : Item(caption) {}
    void add(std::shared_ptr<Item> item) {
        tray.push_back(item);
    }
};