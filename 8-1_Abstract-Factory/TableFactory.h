#pragma once
#include "Factory.h"

class TableFactory : public Factory {
public:
    std::shared_ptr<Link> createLink(const std::string& caption, const std::string& url) override;
    std::shared_ptr<Tray> createTray(const std::string& caption) override;
    std::shared_ptr<Page> createPage(const std::string& title, const std::string& author) override;
};

class TableLink : public Link {
public:
    TableLink(const std::string& caption, const std::string& url);
    std::string makeHTML() override;
};

class TablePage : public Page {
public:
    TablePage(const std::string& title, const std::string& author);
    std::string makeHTML() override;
};

class TableTray : public Tray {
public:
    TableTray(const std::string& caption);
    std::string makeHTML() override;
};