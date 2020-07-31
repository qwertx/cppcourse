#include <string>
#include <iostream>

using namespace std;

void MyThrow()
{
    throw 0;
}

// 无论int, int&或者是const int&, 都可以抓住int类型的异常
// 答案: 程序有语法错误，因为两个catch语句都能抓住同一个类型(int)的异常，这是不行的
// 实际运行(g++): 输出"catch (const int&)"，因为int在const int&的位置之后出现，优先级低
int main()
{
    try
    {
        MyThrow();
    }
    catch (const int&)
    {
        cout << "catch (const int&)" << endl;
    }
    catch (int)
    {
        cout << "catch (int)" << endl;
    }
    return 0;
}