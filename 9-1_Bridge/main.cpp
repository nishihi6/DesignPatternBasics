#include <iostream>
#include <string>

// �B�����̃N���X�K�w�FDisplayImpl�N���X�i�����̃N���X�K�w�̍ŏ�ʃN���X�j
class DisplayImpl {
public:
    virtual void rawOpen() = 0;     // �O����
    virtual void rawPrint() = 0;    // �\������
    virtual void rawClose() = 0;    // �㏈��
    virtual ~DisplayImpl() {}
};

// �@�@�\�̃N���X�K�w�FDisplay�N���X�i�@�\�̃N���X�̍ŏ�ʃN���X�j
class Display {
private:
    DisplayImpl* impl;  // ������\���C���X�^���X�iimplementation�j
public:
    Display(DisplayImpl* impl) : impl(impl) {}  // �R���X�g���N�^�i������\���N���X�̃C���X�^���X��n���j
    void open() {
        impl->rawOpen();    // �\���̑O����
    }
    void print() {
        impl->rawPrint();   // �\������
    }
    void close() {
        impl->rawClose();   // �\���̌㏈��
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

// �A�@�\�̃N���X�K�w�FCountDisplay�N���X�iDisplay�N���X�ɋ@�\��ǉ��j
class CountDisplay : public Display {
public:
    CountDisplay(DisplayImpl* impl) : Display(impl) {}
    void multiDisplay(int times) {  // �w��񐔂����\������
        open();
        for (int i = 0; i < times; i++) {
            print();
        }
        close();
    }
};

// �C�����̃N���X�K�w�FStringDisplayImpl�N���X�i�{���̎����j
class StringDisplayImpl : public DisplayImpl {
private:
    std::string string; // �\������ׂ�������
    int width;          // �o�C�g�P�ʂŌv�Z����������̕�
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

// main�֐�
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

// Bridge�p�^�[���̓����́A"�@�\�̃N���X�K�w"��"�����̃N���X�K�w"�𕪂��邱�ƂŁA�g������̂��y�ɂȂ�Ƃ����_�ɂ���iOS�ˑ��̗Ⴊ�킩��₷���j

// �p���͌ł����т��ł���̂ŁA�K�v�ɉ����ăN���X�Ԃ̊֌W��؂�ւ������Ƃ��ɂ͌p�����g���͕̂s�K�؂ł���
//���̂��߁A�ڏ����s���i���̃R�[�h�ł́ADisplay�N���X�̒��ňڏ����g���Ă���iimpl�Ɏ��s���̏�����C���Ă���j�j

// Main�N���X�ł̏C�������Ŏ�����؂�ւ��邱�Ƃ��ł���

// 2��ނ̃N���X�K�w�𕪗����邱�ƂŁA�N���X�̊g�������ʂ��悭�s�����Ƃ��ł���