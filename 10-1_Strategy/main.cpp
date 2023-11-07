#include <iostream>
#include <string>
#include <memory>
#include <cstdlib>

// クラスの前方宣言
class Hand;
class Strategy;

// Handクラス（じゃんけんの「手」を表すクラス）
class Hand {
public:
    static const int HANDVALUE_GUU = 0;
    static const int HANDVALUE_CHO = 1;
    static const int HANDVALUE_PAA = 2;
    static Hand* hand[3];
    static std::string name[3];
private:
    int handvalue;
    Hand(int handvalue) : handvalue(handvalue) {}
public:
    static Hand* getHand(int handvalue) {   // 手の値を引数で与えると、インスタンスが戻り値となる（Singletonパターンの一種）
        return hand[handvalue];
    }
    bool isStrongerThan(Hand* h) {
        return fight(h) == 1;
    }
    bool isWeakerThan(Hand* h) {
        return fight(h) == -1;
    }
    int fight(Hand* h) {
        if (this == h) {
            return 0;
        }
        else if ((this->handvalue + 1) % 3 == h->handvalue) {   // thisがhより強い場合
            return 1;
        }
        else {
            return -1;
        }
    }
    std::string toString() {
        return name[handvalue];
    }
};

// Handの静的メンバの初期化
Hand* Hand::hand[3] = { new Hand(HANDVALUE_GUU), new Hand(HANDVALUE_CHO), new Hand(HANDVALUE_PAA) };
std::string Hand::name[3] = { "グー", "チョキ", "パー" };

// Strategyインタフェース（じゃんけんの「戦略」を表すインタフェース）
class Strategy {
public:
    virtual Hand* nextHand() = 0;       // 次に出す手を得るためのメソッド
    virtual void study(bool win) = 0;   // 1回前に出した手によって勝ったかどうかを学習するためのメソッド
    virtual ~Strategy() {}
};

// WinningStrategyクラス（勝ったら次も同じ手を出す戦略を表すクラス）
class WinningStrategy : public Strategy {
private:
    bool won = false;
    Hand* prevHand = nullptr;
    int seed;
public:
    WinningStrategy(int seed) : seed(seed) {}
    Hand* nextHand() override { // 前回の勝負に負けたならば、次の手は乱数を使って決定する
        if (!won) {
            prevHand = Hand::getHand(rand() % 3);
        }
        return prevHand;
    }
    void study(bool win) override { // 前回の勝負の結果を保持する
        won = win;
    }
};

// ProbStrategyクラス（1回前の手から次の手を確率的に計算する戦略を表すクラス）
class ProbStrategy : public Strategy {
private:
    int prevHandValue = 0;
    int currentHandValue = 0;
    int history[3][3] = { { 1, 1, 1 }, { 1, 1, 1 }, { 1, 1, 1 } };  // 過去の勝敗を反映した確率計算のための表
    int seed;
public:
    ProbStrategy(int seed) : seed(seed) {}
    Hand* nextHand() override {
        int bet = rand() % getSum(currentHandValue);
        int handvalue = 0;
        if (bet < history[currentHandValue][0]) {
            handvalue = 0;
        }
        else if (bet < history[currentHandValue][0] + history[currentHandValue][1]) {
            handvalue = 1;
        }
        else {
            handvalue = 2;
        }
        prevHandValue = currentHandValue;
        currentHandValue = handvalue;
        return Hand::getHand(handvalue);
    }
    int getSum(int hv) {
        int sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += history[hv][i];
        }
        return sum;
    }
    void study(bool win) override { // nextHandメソッドで返した手の勝敗を元に、historyフィールドの内容を更新する
        if (win) {
            history[prevHandValue][currentHandValue]++;
        }
        else {
            history[prevHandValue][(currentHandValue + 1) % 3]++;
            history[prevHandValue][(currentHandValue + 2) % 3]++;
        }
    }
};

// Playerクラス（じゃんけんを行うプレイヤーを表すクラス）
class Player {
private:
    std::string name;
    Strategy* strategy;
    int wincount = 0;
    int losecount = 0;
    int gamecount = 0;
public:
    Player(const std::string& name, Strategy* strategy) : name(name), strategy(strategy) {}
    ~Player() {
        delete strategy;
    }
    Hand* nextHand() {  // 実際に次の手を決定するのは自分の「戦略」となる（自分の行うべき処理をStrategyに委譲している）
        return strategy->nextHand();
    }
    void win() {
        strategy->study(true);  // Strategyフィールドを通してstudyメソッドを呼び出す
        wincount++;
        gamecount++;
    }
    void lose() {
        strategy->study(false);
        losecount++;
        gamecount++;
    }
    void even() {
        gamecount++;
    }
    friend std::ostream& operator<<(std::ostream& os, const Player& player);    // javaコードだと"public String toString(){}"の処理
};

std::ostream& operator<<(std::ostream& os, const Player& player) {  // フレンド関数として定義されており、プライベートメンバにアクセスする
    os << "[" << player.name << ":" << player.gamecount << " games, " << player.wincount << " win, " << player.losecount << " lose]";
    return os;
}

// Main関数（動作テスト用のクラス）
int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cout << "Usage: " << argv[0] << " randomseed1 randomseed2" << std::endl;
        std::cout << "Example: " << argv[0] << " 314 15" << std::endl;
        return 0;
    }
    int seed1 = std::atoi(argv[1]);
    int seed2 = std::atoi(argv[2]);
    srand(seed1); // 乱数生成用のシード
    Player player1("Taro", new WinningStrategy(seed1));
    srand(seed2); // 乱数生成用のシード（2人目）
    Player player2("Hana", new ProbStrategy(seed2));

    for (int i = 0; i < 10000; i++) {
        Hand* nextHand1 = player1.nextHand();
        Hand* nextHand2 = player2.nextHand();
        if (nextHand1->isStrongerThan(nextHand2)) {
            std::cout << "Winner:" << player1 << std::endl;
            player1.win();
            player2.lose();
        }
        else if (nextHand2->isStrongerThan(nextHand1)) {
            std::cout << "Winner:" << player2 << std::endl;
            player1.lose();
            player2.win();
        }
        else {
            std::cout << "Even..." << std::endl;
            player1.even();
            player2.even();
        }
    }
    std::cout << "Total result:" << std::endl;
    std::cout << player1 << std::endl;
    std::cout << player2 << std::endl;

    // Handインスタンスのクリア
    delete Hand::hand[0];
    delete Hand::hand[1];
    delete Hand::hand[2];

    return 0;
}

// Strategyパターンでは、アルゴリズムの部分を他の部分と意識的に分離し、アルゴリズムとのインタフェースの部分だけを規定し、
//プログラムから委譲によってアルゴリズムを利用する

// 委譲というゆるやかな結びつきを使っているため、アルゴリズムを容易に切り替えることができる

// 例えば、メモリが少ない環境とメモリが多い環境で異なる戦略を使うなどができる