#include <iostream>
#include <string>

using namespace std;

// 本を表すクラス
class Book {
private:
	string name;
public:
	Book() {}
	Book(string name) : name(name) {}
	string getName() {
		return name;
	}
};

// 数え上げ、スキャンを行うインタフェース【反復子の役】
class Iterator {
public:
	virtual bool hasNext() = 0;	// 次の要素が存在するかどうかを調べるメソッド（純粋仮想関数）
	virtual Book next() = 0;	// 次の要素を得るためのメソッド（純粋仮想関数）
};

// 集合体を表すインタフェース【集合体の役】
class Aggregate {
public:
	virtual Iterator* iterator() = 0;	// 集合体に対応するIteratorを１個作成（純粋仮想関数）
};

// 本棚を表すクラス【具体的な集合体の役】
class BookShelf : public Aggregate {
private:
	Book* books;
	int last = 0;
public:
	BookShelf(int maxsize) {
		this->books = new Book[maxsize];
	}
	Book getBookAt(int index) {
		return books[index];
	}
	void appendbook(Book book) {
		this->books[last] = book;
		last++;
	}
	int getLength() {
		return last;
	}
	Iterator* iterator();
};

// 本棚をスキャンするクラス【具体的な反復子の役】
class BookShelfIterator : public Iterator {
private:
	BookShelf bookShelf;
	int index;
public:
	BookShelfIterator(BookShelf bookShelf) : bookShelf(bookShelf), index(0) {}
	bool hasNext() {
		if (index < bookShelf.getLength()) {
			return true;
		}
		else {
			return false;
		}
	}
	Book next() {
		Book book = bookShelf.getBookAt(index);
		index++;
		return book;
	}
};

Iterator* BookShelf::iterator() {
	return new BookShelfIterator(*this);
}

// 動作テスト用のクラス
int main() {
	BookShelf bookShelf = BookShelf(4);
	bookShelf.appendbook(Book("Around the World in 80 Days"));
	bookShelf.appendbook(Book("Bible"));
	bookShelf.appendbook(Book("Cinderella"));
	bookShelf.appendbook(Book("Daddy-Long-Legs"));
	Iterator* it = bookShelf.iterator();
	while (it->hasNext()) {
		Book book = it->next();
		cout << book.getName() << endl;
	}
}

//デザインパターンはクラスの再利用化を促進するもの。メソッドiteratorの戻り値をBookShelfIterator型の変数に代入せず、Iterator型の変数に
//代入している理由は、１つの部品を修正しても、他の部品の修正が少なくてすむようにするため。

//具体的なクラスだけを使うと、クラス間の結合が強くなってしまい、部品として再利用することが難しくなる。そのため、結合を弱め、
//クラスを部品として再利用しやすくするために、抽象クラスやインタフェースが導入される。

//deleteIteratorが必要だが、今回は実装していない。（Javaなら不要）