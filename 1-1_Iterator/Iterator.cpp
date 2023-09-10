#include <iostream>
#include <string>

using namespace std;

// �{��\���N���X
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

// �����グ�A�X�L�������s���C���^�t�F�[�X�y�����q�̖��z
class Iterator {
public:
	virtual bool hasNext() = 0;	// ���̗v�f�����݂��邩�ǂ����𒲂ׂ郁�\�b�h�i�������z�֐��j
	virtual Book next() = 0;	// ���̗v�f�𓾂邽�߂̃��\�b�h�i�������z�֐��j
};

// �W���̂�\���C���^�t�F�[�X�y�W���̖̂��z
class Aggregate {
public:
	virtual Iterator* iterator() = 0;	// �W���̂ɑΉ�����Iterator���P�쐬�i�������z�֐��j
};

// �{�I��\���N���X�y��̓I�ȏW���̖̂��z
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

// �{�I���X�L��������N���X�y��̓I�Ȕ����q�̖��z
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

// ����e�X�g�p�̃N���X
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

//�f�U�C���p�^�[���̓N���X�̍ė��p���𑣐i������́B���\�b�hiterator�̖߂�l��BookShelfIterator�^�̕ϐ��ɑ�������AIterator�^�̕ϐ���
//������Ă��闝�R�́A�P�̕��i���C�����Ă��A���̕��i�̏C�������Ȃ��Ă��ނ悤�ɂ��邽�߁B

//��̓I�ȃN���X�������g���ƁA�N���X�Ԃ̌����������Ȃ��Ă��܂��A���i�Ƃ��čė��p���邱�Ƃ�����Ȃ�B���̂��߁A��������߁A
//�N���X�𕔕i�Ƃ��čė��p���₷�����邽�߂ɁA���ۃN���X��C���^�t�F�[�X�����������B

//deleteIterator���K�v�����A����͎������Ă��Ȃ��B�iJava�Ȃ�s�v�j