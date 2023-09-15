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
class PrintBanner : public Banner, public Print {
public:
	//コンストラクタ初期化リスト「: Banner(str)」は、基底クラスのコンストラクタを呼び出している。
	//これにより、PrintBannerクラスがインスタンス化されるときに、Bannerクラスのコンストラクタも自動的に呼び出される。
	PrintBanner(string str) : Banner(str) {
		//基底クラスBannerのコンストラクタがすでに必要な初期化を行っているため、追加の初期化は不要。
	}
	void printWeak() {
		showWithParen();
	}
	void printStrong() {
		showWithAster();
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

//このコードは、C++の多態性と参照を利用して、基底クラスの参照を使用して派生クラスのメソッドを呼び出すデモンストレーションを提供しています。