#include <iostream>
#include <string>
#include <vector>

using namespace std;

// AbstractDisplay�N���X�i���\�b�hdisplay�̂ݎ�������Ă��钊�ۃN���X�j
class AbstractDisplay {
public:
    virtual void open() = 0;
    virtual void print() = 0;
    virtual void close() = 0;
    void display() {    // ���ۃ��\�b�h���g���Ă���display���\�b�h���e���v���[�g���\�b�h
        open(); // ���̂��Ȃ����ۃ��\�b�h
        for (int i = 0; i < 5; i++) {
            print();    // ���̂��Ȃ����ۃ��\�b�h
        }
        close();    // ���̂��Ȃ����ۃ��\�b�h
    }
};

// CharDisplay�N���X�i���\�b�hopen, print, close���������Ă���T�u�N���X�j
class CharDisplay : public AbstractDisplay {
private:
    char ch;
public:
    CharDisplay(char ch) : ch(ch) {}
    void open() override {  // ���N���X���牼�z���\�b�h���I�[�o�[���C�h
        std::cout << "<<";
    }
    void print() override {
        std::cout << ch;
    }
    void close() override {
        std::cout << ">>" << std::endl;
    }
};

// StringDisplay�N���X�i���\�b�hopen, print, close���������Ă���T�u�N���X�j
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

// ����e�X�g�p�̃N���X
int main() {
    AbstractDisplay* d1 = new CharDisplay('H');
    AbstractDisplay* d2 = new StringDisplay("Hello, world.");
    AbstractDisplay* d3 = new StringDisplay("����ɂ��́B");
    d1->display();
    d2->display();
    d3->display();
    delete d1;
    delete d2;
    delete d3;
    return 0;
}

//Template Method�p�^�[���Ƃ́A�X�[�p�[�N���X�ŏ����̘g�g�݂��߁A�T�u�N���X�ł��̋�̓I���e���߂�悤�ȃf�U�C���p�^�[���ł���B

//�e���v���[�g���\�b�h�Ɍ�肪�������ꂽ�ꍇ�ł��A�e���v���[�g���\�b�h�����C������΂悭�Ȃ�B

//�X�[�p�[�N���X�^�̕ϐ��ɁA�T�u�N���X�̃C���X�^���X�̂ǂ�������Ă����������삷��悤�ɂ���A�Ƃ���������
//The Liskov Substitution Principle�iLSP�j�ƌĂ΂�Ă���BLSP�͌p���̈�ʓI�Ȍ����ł���B

//�T�u�N���X�ɂ́A�X�[�p�[�N���X�Ő錾����Ă��钊�ۃ��\�b�h����������Ƃ����ӔC�������Ă���Ƃ����Ă��悭�A
//�����subclass responsibility�i�T�u�N���X�̐ӔC�j�Ƃ����B

//���ۃN���X�̓C���X�^���X����邱�Ƃ��ł��Ȃ����A���ۃN���X�̒i�K�ŏ����̗�����`���̂͑�؂Ȃ��Ƃł���B

