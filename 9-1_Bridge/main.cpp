#include <iostream>
#include <string>

// ③実装のクラス階層：DisplayImplクラス（実装のクラス階層の最上位クラス）
class DisplayImpl {
public:
    virtual void rawOpen() = 0;     // 前処理
    virtual void rawPrint() = 0;    // 表示処理
    virtual void rawClose() = 0;    // 後処理
    virtual ~DisplayImpl() {}
};

// ①機能のクラス階層：Displayクラス（機能のクラスの最上位クラス）
class Display {
private:
    DisplayImpl* impl;  // 実装を表すインスタンス（implementation）
public:
    Display(DisplayImpl* impl) : impl(impl) {}  // コンストラクタ（実装を表すクラスのインスタンスを渡す）
    void open() {
        impl->rawOpen();    // 表示の前処理
    }
    void print() {
        impl->rawPrint();   // 表示処理
    }
    void close() {
        impl->rawClose();   // 表示の後処理
    }
    void display() {
        open();
        print();
        close();
    }
    virtual ~Display() {
        delete impl;
    }
};

// ②機能のクラス階層：CountDisplayクラス（Displayクラスに機能を追加）
class CountDisplay : public Display {
public:
    CountDisplay(DisplayImpl* impl) : Display(impl) {}
    void multiDisplay(int times) {  // 指定回数だけ表示する
        open();
        for (int i = 0; i < times; i++) {
            print();
        }
        close();
    }
};

// ④実装のクラス階層：StringDisplayImplクラス（本当の実装）
class StringDisplayImpl : public DisplayImpl {
private:
    std::string string; // 表示するべき文字列
    int width;          // バイト単位で計算した文字列の幅
public:
    StringDisplayImpl(const std::string& string) : string(string), width(static_cast<int>(string.length())) {}
    void rawOpen() override {
        printLine();
    }
    void rawPrint() override {
        std::cout << "|" << string << "|" << std::endl;
    }
    void rawClose() override {
        printLine();
    }
private:
    void printLine() {
        std::cout << "+";
        for (int i = 0; i < width; i++) {
            std::cout << "-";
        }
        std::cout << "+" << std::endl;
    }
};

// main関数
int main() {
    Display* d1 = new Display(new StringDisplayImpl("Hello, Japan."));
    Display* d2 = new Display(new StringDisplayImpl("Hello, World."));
    CountDisplay* d3 = new CountDisplay(new StringDisplayImpl("Hello, Universe."));
    d1->display();
    d2->display();
    d3->display();
    d3->multiDisplay(5);

    delete d1;
    delete d2;
    delete d3;

    return 0;
}

// Bridgeパターンの特徴は、"機能のクラス階層"と"実装のクラス階層"を分けることで、拡張するのが楽になるという点にある（OS依存の例がわかりやすい）

// 継承は固い結びつきであるので、必要に応じてクラス間の関係を切り替えたいときには継承を使うのは不適切である
//そのため、移譲を行う（このコードでは、Displayクラスの中で移譲が使われている（implに実行時の処理を任せている））

// Mainクラスでの修正だけで実装を切り替えることができる

// 2種類のクラス階層を分離することで、クラスの拡張を見通しよく行うことができる 