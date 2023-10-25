#pragma once

#include "Factory.h"

class ListFactory : public Factory {
public:
    std::shared_ptr<Link> createLink(const std::string& caption, const std::string& url) override;
    std::shared_ptr<Tray> createTray(const std::string& caption) override;
    std::shared_ptr<Page> createPage(const std::string& title, const std::string& author) override;
};

class ListLink : public Link {
public:
    ListLink(const std::string& caption, const std::string& url) : Link(caption, url) {}
    std::string makeHTML() override;
};

class ListPage : public Page {
public:
    ListPage(const std::string& title, const std::string& author) : Page(title, author) {}
    std::string makeHTML() override;
};

class ListTray : public Tray {
public:
    ListTray(const std::string& caption) : Tray(caption) {}
    std::string makeHTML() override;
};