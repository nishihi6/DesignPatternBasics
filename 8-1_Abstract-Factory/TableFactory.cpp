#include "TableFactory.h"

std::shared_ptr<Link> TableFactory::createLink(const std::string& caption, const std::string& url) {
    return std::make_shared<TableLink>(caption, url);
}

std::shared_ptr<Tray> TableFactory::createTray(const std::string& caption) {
    return std::make_shared<TableTray>(caption);
}

std::shared_ptr<Page> TableFactory::createPage(const std::string& title, const std::string& author) {
    return std::make_shared<TablePage>(title, author);
}

TableLink::TableLink(const std::string& caption, const std::string& url) : Link(caption, url) {}

std::string TableLink::makeHTML() {
    return "<td><a href=\"" + url + "\">" + caption + "</a></td>\n";
}

TablePage::TablePage(const std::string& title, const std::string& author) : Page(title, author) {}

std::string TablePage::makeHTML() {
    std::string buffer;
    buffer += "<html><head><title>" + title + "</title></head>\n";
    buffer += "<body>\n<h1>" + title + "</h1>\n";
    buffer += "<table width=\"80%\" border=\"3\">\n";
    for (auto& item : content) {
        buffer += "<tr>" + item->makeHTML() + "</tr>";
    }
    buffer += "</table>\n";
    buffer += "<hr><address>" + author + "</address>";
    buffer += "</body></html>\n";
    return buffer;
}

TableTray::TableTray(const std::string& caption) : Tray(caption) {}

std::string TableTray::makeHTML() {
    std::string buffer;
    buffer += "<td>";
    buffer += "<table width=\"100%\" border=\"1\"><tr>";
    buffer += "<td bgcolor=\"#cccccc\" align=\"center\" colspan=\"" + std::to_string(tray.size()) + "\"><b>" + caption + "</b></td>";
    buffer += "</tr>\n<tr>\n";
    for (auto& item : tray) {
        buffer += item->makeHTML();
    }
    buffer += "</tr></table>";
    buffer += "</td>";
    return buffer;
}