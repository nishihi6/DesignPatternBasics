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

class Factory {
public:
    static std::shared_ptr<Factory> getFactory(const std::string& classname);
    virtual std::shared_ptr<Link> createLink(const std::string& caption, const std::string& url) = 0;
    virtual std::shared_ptr<Tray> createTray(const std::string& caption) = 0;
    virtual std::shared_ptr<Page> createPage(const std::string& title, const std::string& author) = 0;
};

class Item {
protected:
    std::string caption;
public:
    Item(const std::string& caption) : caption(caption) {}
    virtual std::string makeHTML() = 0;
};

class Link : public Item {
protected:
    std::string url;
public:
    Link(const std::string& caption, const std::string& url) : Item(caption), url(url) {}
};

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

class Tray : public Item {
protected:
    std::vector<std::shared_ptr<Item>> tray;
public:
    Tray(const std::string& caption) : Item(caption) {}
    void add(std::shared_ptr<Item> item) {
        tray.push_back(item);
    }
};