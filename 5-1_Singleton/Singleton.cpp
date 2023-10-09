#include <iostream>
#include <string>

using namespace std;

// インスタンスが１つしか存在しないクラス
class Singleton {
private:
    static Singleton* singleton;

    // コンストラクタはprivate
    Singleton() {
        cout << "インスタンスを生成しました。" << endl;
    }

public:
    // コピーコンストラクタと代入演算子を明示的に削除（シングルトンのインスタンスが複製されることを防ぐ）
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    // インスタンスを得るメソッド
    static Singleton* getInstance() {
        if (singleton == nullptr) {
            singleton = new Singleton();
        }
        return singleton;
    }
};

// クラス内で静的メンバを宣言しているので、このメンバはクラスの全インスタンス間で共有される
// 静的メンバ変数は、クラス内での宣言とは別に、クラスの外側で実際の定義（メモリ確保）が必要
Singleton* Singleton::singleton = nullptr;

// 動作テスト用のクラス
int main() {
    cout << "Start." << endl;

    Singleton* obj1 = Singleton::getInstance();
    Singleton* obj2 = Singleton::getInstance();

    if (obj1 == obj2) {
        cout << "obj1とobj2は同じインスタンスです。" << endl;
    }
    else {
        cout << "obj1とobj2は同じインスタンスではありません。" << endl;
    }

    cout << "End." << endl;

    // プログラムの最後でメモリリークを防ぐためにシングルトンのインスタンスを解放する
    delete obj1; // obj1とobj2は同じインスタンスのアドレスを指している（シングルトンパターンの特性）
    return 0;
}

// Singletonパターンでは、インスタンスの数に制限を設けている。インスタンスが１個しか生成されないことを保証する。