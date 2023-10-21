#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

// Builder クラスの定義（文章を構成するためのメソッドを定めた抽象クラス）
class Builder {
public:
    virtual ~Builder() = default;
    virtual void makeTitle(const std::string& title) = 0;
    virtual void makeString(const std::string& str) = 0;
    virtual void makeItems(const std::vector<std::string>& items) = 0;
    virtual void close() = 0;   // 文章を完成させるメソッド
};

// Director クラスの定義（１つの文章を作るクラス）
class Director {
private:
    Builder* builder;
public:
    Director(Builder* builder) : builder(builder) {}    // 引数はBuilderクラスのサブクラス
    void construct() {  // 文章を作るメソッド
        builder->makeTitle("Greeting");
        builder->makeString("朝から昼にかけて");
        builder->makeItems({ "おはようございます。", "こんにちは。" });
        builder->makeString("夜に");
        builder->makeItems({ "こんばんは。", "おやすみなさい。", "さようなら。" });
        builder->close();
    }
};

// TextBuilder クラスの定義（プレーンテキスト（普通の文字列）を使って文章を作るクラス）
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

    std::string getResult() const { // 結果はstringとして返す
        return buffer.str();
    }
};

// HTMLBuilder クラスの定義（HTMLファおるを作って文章を作るクラス）
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

// Main 関数（動作テスト用のクラス）
int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " plain | html" << std::endl;  // エラーメッセージ
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

// javaであればStringBufferに文字列をappendしていく処理を、C++ではstringstreamを利用している。

// Builderは、インスタンスを作成するためのインターフェース（API）を定める。実装をしているのがConcreteBuilder（TextBuilderなど）。
// Builderは文章を構築するという目的を達成するのに必要かつ十分なメソッド群を宣言している必要がある。また、固有のメソッドまでを提供してはいけない。

// Directorはインターフェース（API）を使ってインスタンスを作成する。ConcreteBuilder役がなんであってもうまく機能するように、Builder役の
//メソッドのみを使う。

// MainクラスがここではClientの役を担う。

// オブジェクト指向プログラミングでは、どのクラスがどのメソッドを使えるか（使ってよいか）に注意してプログラミングする必要がある。

// 正しく機能するのは、DirectorクラスがBuilderクラスの具体的なサブクラスを知らないから。
//知らないからこそ、入れ替えができる。入れ替えられるからこそ、部品としての価値が高い（交換可能性がある）。