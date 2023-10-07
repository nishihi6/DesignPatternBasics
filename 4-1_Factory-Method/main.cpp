#include "Factory.h"
#include "IDCardFactory.h"
#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

// 動作テスト用のクラス
int main() {
    std::unique_ptr<Factory> factory = std::make_unique<IDCardFactory>();

    std::unique_ptr<Product> card1(factory->create("弐四火呂"));
    std::unique_ptr<Product> card2(factory->create("三四火呂"));
    std::unique_ptr<Product> card3(factory->create("四四火呂"));

    card1->use();
    card2->use();
    card3->use();

    return 0;
}

//スーパークラス側で処理の骨組みを作り、サブクラス側で具体的な処理の肉付けを行うTemplate Methodパターンを、
//インスタンス生成の場面に適用したのがFactory Methodである。

//インスタンスの作り方をスーパークラス側で定めるが、具体的なクラス名までは定めない。
//具体的な肉付けはすべてサブクラス側で行う。
//これにより、インスタンス生成のための枠組み（フレームワーク）と、実際のインスタンス生成のクラスとを分けて考えることができる。

//１つのクラスだけを見るのではなく、クラスやインタフェースの相互関係に目を向けるようにするべきである。