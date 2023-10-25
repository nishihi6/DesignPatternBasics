#include "Factory.h"
#include "ListFactory.h"
// 他のFactory派生クラスのインクルードもここに追加する

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " class.name.of.ConcreteFactory" << std::endl;
        std::cout << "Example 1: " << argv[0] << " ListFactory" << std::endl;
        std::cout << "Example 2: " << argv[0] << " TableFactory" << std::endl;
        // 他の例もここに追加する
        return 0;
    }
    auto factory = Factory::getFactory(argv[1]);
    if (!factory) {
        std::cout << "Unknown factory name: " << argv[1] << std::endl;
        return 1;
    }

    auto asahi = factory->createLink("朝日新聞", "http://www.asahi.com/");
    auto yomiuri = factory->createLink("読売新聞", "http://www.yomiuri.co.jp/");

    auto us_yahoo = factory->createLink("Yahoo!", "http://www.yahoo.com/");
    auto jp_yahoo = factory->createLink("Yahoo!Japan", "http://www.yahoo.co.jp/");
    auto excite = factory->createLink("Excite", "http://www.excite.com/");
    auto google = factory->createLink("Google", "http://www.google.com/");

    auto traynews = factory->createTray("新聞");
    traynews->add(asahi);
    traynews->add(yomiuri);

    auto trayyahoo = factory->createTray("Yahoo!");
    trayyahoo->add(us_yahoo);
    trayyahoo->add(jp_yahoo);

    auto traysearch = factory->createTray("サーチエンジン");
    traysearch->add(trayyahoo);
    traysearch->add(excite);
    traysearch->add(google);

    auto page = factory->createPage("LinkPage", "弐四火呂");
    page->add(traynews);
    page->add(traysearch);
    page->output();

    return 0;
}