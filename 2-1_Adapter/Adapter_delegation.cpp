#include <iostream>
#include <string>

using namespace std;

// Bannerクラス（提供されているもの）
class Banner {
private:
	string str;
public:
	Banner(string str) {
		this->str = str;
	}
	void showWithParen() {
		cout << "(" + str + ")" << endl;
	}
	void showWithAster() {
		cout << "*" + str + "*" << endl;
	}
};

// Printインターフェース（必要なもの）
class Print {
public:
	virtual void printWeak() = 0;
	virtual void printStrong() = 0;
};

// PrintBannerクラス（変換装置）
class PrintBanner : public Print {
private:
	Banner banner;
public:
	PrintBanner(string str) : banner(str) {}
	void printWeak() {
		banner.showWithParen();
	}
	void printStrong() {
		banner.showWithAster();
	}
};

int main() {
	PrintBanner p("Hello");
	p.printWeak();
	p.printStrong();

	Print& p2 = p;
	p2.printWeak();
	p2.printStrong();

	cout << &p2 << " = " << &p << endl;
}

//委譲（delegation）は、特定の動作や責任を他のオブジェクトに移譲するテクニックである。
//コンポジションを使用してBannerクラスのインスタンスを含め、そのメソッドをPrintBannerクラスのメソッドから呼び出すことで、委譲を実現できる。

//継承（Inheritance）は一般的にis-a関係を表現する（PrintBannerはBannerである）。
//コンポジション（Composition）は"has-a"関係を表現する（PrintBannerはBannerを持っている）。
//コンポジションは、クラス間の関係をより柔軟にし、再利用を容易にする。
//また、継承の代わりにコンポジションを使用することで、クラス階層が複雑になるのを避けることができる。

//Adapterパターンは、既存のクラスにまったく手を加えずに、目的のインタフェース（API）にあわせようとするものである。
//Adapterパターンは、インタフェース（API）が異なっているクラス同士を結びつけるパターンで、インタフェース（API）のずれを埋めるためにパターンである。