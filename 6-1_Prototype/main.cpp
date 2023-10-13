#include "Manager.h"
#include "UnderlinePen.h"
#include "MessageBox.h"

// 動作テスト用のクラス
int main() {
    Manager manager;    // Managerインスタンス
    UnderlinePen upen('~'); // UnderlinePenインスタンスの登録
    MessageBox mbox('*');   // MessageBoxインスタンスの登録
    MessageBox sbox('/');

    manager.registerProduct("strong message", &upen);
    manager.registerProduct("warning box", &mbox);
    manager.registerProduct("slash box", &sbox);

    Product* p1 = manager.create("strong message");
    p1->use("Hello, world.");

    Product* p2 = manager.create("warning box");
    p2->use("Hello, world.");

    Product* p3 = manager.create("slash box");
    p3->use("Hello, world.");

    // Cleanup
    delete p1;
    delete p2;
    delete p3;

    return 0;
}

//クラスからインスタンスを作るのではなく、インスタンスからあたらしいインスタンスを作るのがPrototypeパターン。

//(1) 種類が多すぎてクラスにまとめられない場合
//(2) クラスからのインスタンス生成が難しい場合
//(3) フレームワークと生成するインスタンスを分けたい場合
//に、Prototypeパターンを利用する。

//ソースの中に利用するクラスの名前が書かれていると、そのクラスと切り離して再利用することはできなくなってしまう。
//部品として独立させなければならないクラスの名前がソースの中に書かれていることが問題になる。（オブジェクト指向プログラミングの目標に反する）