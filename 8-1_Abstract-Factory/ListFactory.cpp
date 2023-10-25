#include "ListFactory.h"

std::shared_ptr<Link> ListFactory::createLink(const std::string& caption, const std::string& url) {
    return std::make_shared<ListLink>(caption, url);
}

std::shared_ptr<Tray> ListFactory::createTray(const std::string& caption) {
    return std::make_shared<ListTray>(caption);
}

std::shared_ptr<Page> ListFactory::createPage(const std::string& title, const std::string& author) {
    return std::make_shared<ListPage>(title, author);
}

std::string ListLink::makeHTML() {
    return "  <li><a href=\"" + url + "\">" + caption + "</a></li>\n";
}

std::string ListPage::makeHTML() {
    std::string buffer;
    buffer.append("<html><head><title>" + title + "</title></head>\n");
    buffer.append("<body>\n");
    buffer.append("<h1>" + title + "</h1>\n");
    buffer.append("<ul>\n");
    for (const auto& item : content) {
        buffer.append(item->makeHTML());
    }
    buffer.append("</ul>\n");
    buffer.append("<hr><address>" + author + "</address>");
    buffer.append("</body></html>\n");
    return buffer;
}

std::string ListTray::makeHTML() {
    std::string buffer;
    buffer.append("<li>\n");
    buffer.append(caption + "\n");
    buffer.append("<ul>\n");
    for (const auto& item : tray) {
        buffer.append(item->makeHTML());
    }
    buffer.append("</ul>\n");
    buffer.append("</li>\n");
    return buffer;
}