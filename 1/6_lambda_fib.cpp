#include <iostream>
#include <functional>

using namespace std;

int main()
{
    function<int(int)> fib = [&fib](int i)->int { if (i < 2) { //使用function存放lambda表达式类型, ->显式指明返回值类型
        return 1;
    	}
        else {
            return fib(i-1) + fib(i-2);
        }};
    for (int i = 0; i < 10; i++)
    {
        cout << fib(i) << endl;
    }
    return 0;
}