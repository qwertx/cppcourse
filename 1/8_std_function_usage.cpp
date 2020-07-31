#include <iostream>
#include <functional>

using namespace std;

int main() {
    // 没有问题, double到int和int到double都是隐式类型转换
    function<double(double)> inc = [](int x){ return 1 + x; };
    cout << inc(2) << endl;
    // 没有问题, 如果lambda不捕获任何东西, 那么它和全局函数没有本质区别
    int(*square)(int) = [](int x){ return x * x; };
    cout << square(8) << endl;
}