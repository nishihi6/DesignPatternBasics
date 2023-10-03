#include <iostream>
#include <string>
#include <vector>

using namespace std;

// AbstractDisplayクラス（メソッドdisplayのみ実装されている抽象クラス）
class AbstractDisplay {
public:
    virtual void open() = 0;
    virtual void print() = 0;
    virtual void close() = 0;
    void display() {    // 抽象メソッドを使っているdisplayメソッドがテンプレートメソッド
        open(); // 実体がない抽象メソッド
        for (int i = 0; i < 5; i++) {
            print();    // 実体がない抽象メソッド
        }
        close();    // 実体がない抽象メソッド
    }
};

// CharDisplayクラス（メソッドopen, print, closeを実装しているサブクラス）
class CharDisplay : public AbstractDisplay {
private:
    char ch;
public:
    CharDisplay(char ch) : ch(ch) {}
    void open() override {  // 基底クラスから仮想メソッドをオーバーライド
        std::cout << "<<";
    }
    void print() override {
        std::cout << ch;
    }
    void close() override {
        std::cout << ">>" << std::endl;
    }
};

// StringDisplayクラス（メソッドopen, print, closeを実装しているサブクラス）
class StringDisplay : public AbstractDisplay {
private:
    std::string str;
    int width;
public:
    StringDisplay(std::string str) : str(str), width(str.length()) {}
    void open() override {
        printLine();
    }
    void print() override {
        std::cout << "|" << str << "|" << std::endl;
    }
    void close() override {
        printLine();
    }
    void printLine() {
        std::cout << "+";
        for (int i = 0; i < width; i++) {
            std::cout << "-";
        }
        std::cout << "+" << std::endl;
    }
};

// 動作テスト用のクラス
int main() {
    AbstractDisplay* d1 = new CharDisplay('H');
    AbstractDisplay* d2 = new StringDisplay("Hello, world.");
    AbstractDisplay* d3 = new StringDisplay("こんにちは。");
    d1->display();
    d2->display();
    d3->display();
    delete d1;
    delete d2;
    delete d3;
    return 0;
}

//Template Methodパターンとは、スーパークラスで処理の枠組みを定め、サブクラスでその具体的内容を定めるようなデザインパターンである。

//テンプレートメソッドに誤りが発見された場合でも、テンプレートメソッドさえ修正すればよくなる。

//スーパークラス型の変数に、サブクラスのインスタンスのどれを代入しても正しく動作するようにする、という原則は
//The Liskov Substitution Principle（LSP）と呼ばれている。LSPは継承の一般的な原則である。

//サブクラスには、スーパークラスで宣言されている抽象メソッドを実装するという責任が生じているといってもよく、
//これをsubclass responsibility（サブクラスの責任）という。

//抽象クラスはインスタンスを作ることができないが、抽象クラスの段階で処理の流れを形作るのは大切なことである。

