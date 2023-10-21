#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

// Builder クラスの定義
class Builder {
public:
    virtual ~Builder() = default;
    virtual void makeTitle(const std::string& title) = 0;
    virtual void makeString(const std::string& str) = 0;
    virtual void makeItems(const std::vector<std::string>& items) = 0;
    virtual void close() = 0;
};

// Director クラスの定義
class Director {
private:
    Builder* builder;
public:
    Director(Builder* builder) : builder(builder) {}
    void construct() {
        builder->makeTitle("Greeting");
        builder->makeString("朝から昼にかけて");
        builder->makeItems({ "おはようございます。", "こんにちは。" });
        builder->makeString("夜に");
        builder->makeItems({ "こんばんは。", "おやすみなさい。", "さようなら。" });
        builder->close();
    }
};

// TextBuilder クラスの定義
class TextBuilder : public Builder {
private:
    std::stringstream buffer;
public:
    void makeTitle(const std::string& title) override {
        buffer << "==============================\n";
        buffer << "『" << title << "』\n\n";
    }

    void makeString(const std::string& str) override {
        buffer << '>' << str << "\n\n";
    }

    void makeItems(const std::vector<std::string>& items) override {
        for (const auto& item : items) {
            buffer << "　・" << item << "\n";
        }
        buffer << "\n";
    }

    void close() override {
        buffer << "==============================\n";
    }

    std::string getResult() const {
        return buffer.str();
    }
};

// HTMLBuilder クラスの定義
class HTMLBuilder : public Builder {
private:
    std::string filename;
    std::ofstream writer;

public:
    void makeTitle(const std::string& title) override {
        filename = title + ".html";
        writer.open(filename);

        writer << "<html><head><title>" << title << "</title></head><body>";
        writer << "<h1>" << title << "</h1>";
    }

    void makeString(const std::string& str) override {
        writer << "<p>" << str << "</p>";
    }

    void makeItems(const std::vector<std::string>& items) override {
        writer << "<ul>";
        for (const auto& item : items) {
            writer << "<li>" << item << "</li>";
        }
        writer << "</ul>";
    }

    void close() override {
        writer << "</body></html>";
        writer.close();
    }

    std::string getResult() const {
        return filename;
    }
};

// Main 関数
int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " plain | html" << std::endl;
        return 1;
    }

    if (std::string(argv[1]) == "plain") {
        TextBuilder textBuilder;
        Director director(&textBuilder);
        director.construct();
        std::cout << textBuilder.getResult() << std::endl;
    }
    else if (std::string(argv[1]) == "html") {
        HTMLBuilder htmlBuilder;
        Director director(&htmlBuilder);
        director.construct();
        std::cout << htmlBuilder.getResult() << "が作成されました。" << std::endl;
    }
    else {
        std::cerr << "Usage: " << argv[0] << " plain | html" << std::endl;
        return 1;
    }

    return 0;
}