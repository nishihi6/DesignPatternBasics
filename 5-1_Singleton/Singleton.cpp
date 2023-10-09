#include <iostream>
#include <string>

using namespace std;

// �C���X�^���X���P�������݂��Ȃ��N���X
class Singleton {
private:
    static Singleton* singleton;

    // �R���X�g���N�^��private
    Singleton() {
        cout << "�C���X�^���X�𐶐����܂����B" << endl;
    }

public:
    // �R�s�[�R���X�g���N�^�Ƒ�����Z�q�𖾎��I�ɍ폜�i�V���O���g���̃C���X�^���X����������邱�Ƃ�h���j
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

    // �C���X�^���X�𓾂郁�\�b�h
    static Singleton* getInstance() {
        if (singleton == nullptr) {
            singleton = new Singleton();
        }
        return singleton;
    }
};

// �N���X���ŐÓI�����o��錾���Ă���̂ŁA���̃����o�̓N���X�̑S�C���X�^���X�Ԃŋ��L�����
// �ÓI�����o�ϐ��́A�N���X���ł̐錾�Ƃ͕ʂɁA�N���X�̊O���Ŏ��ۂ̒�`�i�������m�ہj���K�v
Singleton* Singleton::singleton = nullptr;

// ����e�X�g�p�̃N���X
int main() {
    cout << "Start." << endl;

    Singleton* obj1 = Singleton::getInstance();
    Singleton* obj2 = Singleton::getInstance();

    if (obj1 == obj2) {
        cout << "obj1��obj2�͓����C���X�^���X�ł��B" << endl;
    }
    else {
        cout << "obj1��obj2�͓����C���X�^���X�ł͂���܂���B" << endl;
    }

    cout << "End." << endl;

    // �v���O�����̍Ō�Ń��������[�N��h�����߂ɃV���O���g���̃C���X�^���X���������
    delete obj1; // obj1��obj2�͓����C���X�^���X�̃A�h���X���w���Ă���i�V���O���g���p�^�[���̓����j
    return 0;
}

// Singleton�p�^�[���ł́A�C���X�^���X�̐��ɐ�����݂��Ă���B�C���X�^���X���P������������Ȃ����Ƃ�ۏ؂���B