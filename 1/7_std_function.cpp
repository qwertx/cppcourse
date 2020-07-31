// 1. 使用模板参数代表函数使用lambda
// 2. 如果要保存lambda, 使用std::function
// 3. bind函数失去了意义
// 比如 
#include <iostream>
#include <functional>

using namespace std;
// Adder返回一个函数, 给整数加x
function<int(int)> Adder(int x) {
    return [=](int y) {return x + y; };
}

function<int(int)> Compose(function<int(int)> f, function<int(int)> g) {
    return [=](int y) { return f(g(y)); };
}


int main() {
    auto f = Adder(1);
    cout << f(2) << endl; // 3
    auto adder = Compose(Adder(1), Adder(2));
    cout << adder(3) << endl; // 6

    // 详解
    // 展开Compose
    auto f1 = Adder(1);
    auto g1 = Adder(2);
    auto adder1 = [=](int y){ return f1(g1(y)); };
    cout << adder1(3) << endl;

    // 展开Adder
    auto f2 = [](int y) { return 1 + y; };
    auto g2 = [](int y) { return 2 + y; };
    auto adder2 = [=](int y){ return f2(g2(y)); };
    cout << adder2(3) << endl;

    // 展开f
    auto g3 = [](int y) { return 2 + y; };
    auto adder3 = [=](int y){ return 1 + (g3(y)); };
    cout << adder3(3) << endl;

    // 展开g
    auto adder4 = [](int y){ return 1 + 2 + y; };
    cout << adder4(3) << endl;

    // 展开adder
    cout << 1 + 2 + 3 << endl;

    return 0;
}


