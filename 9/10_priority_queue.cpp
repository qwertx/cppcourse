// 具有优先级的队列, 最高优先级的最先删除
// priority_queue<Type, Container, Functional>
// 数据类型, 容器类型, 比较方式
// Functional一般为greater<int>或less<int>,是std中的两个仿函数
// greater是小顶堆(先输出最小), less为大顶堆
// 仿函数:实现了operator()的类,可以像函数一样使用

#include <iostream>
#include <string>
#include <queue>
#include <functional>

using namespace std;

int main()
{
    priority_queue<int, vector<int>, greater<int>> xs;

    while (true)
    {
        int x;
        cin >> x;
        xs.push(x);

        if (cin.peek() == '\n')
        {
            cin.ignore();
            break;
        }
    }

    while (!xs.empty())
    {
        cout << xs.top() << " ";
        xs.pop();
    }
    cout << endl;
    return 0;
}