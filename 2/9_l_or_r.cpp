#include <iostream>

using namespace std;

void Print(int& x)
{
    cout << "x is int&" << endl;
}

void Print(int&& x)
{
    cout << "x is int&&" << endl;
}

template<typename T>
void CallPrint(T&& x)
{
    Print(x);
}

int main()
{
    int x = 0;
    // x为左值, CallPrint参数为T&&, 那么T为int&
    // 参数x为int& &&,即int&
    CallPrint(x);
    // 0为右值, 因此T为int, 参数x为int&&
    // 但是, 此处Print(x)之后可以继续使用x, 因此x是一个左值引用!!
    // 这和int& int&&无法转换无关(因为右值只是0, 传入后使用的参数为x, 并不是传入的0, 因此边成了左值)
    // 而且函数内所有的参数其实都是左值, 除非用move/forward, 此处应用forward
    CallPrint(0);
    return 0;
}