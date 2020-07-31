#include <iostream>

using namespace std;

int a = 0;

int main() {
    auto inc = [&](){ a++; }; // lambda捕获全局变量时,无法选择复制或引用,lambda肯定可以修改全局变量
    inc();
    inc();
    cout << a << endl;
    return 0;
}