#include <iostream>
#include <string>
#include <set>

using namespace std;

int main()
{
    set<int> xs;

    cout << "输入以空格隔开的若干数字并回车，把数字写进集合。" << endl;
    while (true)
    {
        int x;
        cin >> x;
        xs.insert(x);

        if (cin.peek() == '\n')
        {
            cin.ignore();
            break;
        }
    }

    cout << "输入一个数字，程序会告诉你这个数字在不在集合里。输入-1结束。" << endl;
    while (true)
    {
        int x;
        cin >> x;
        if (x == -1)
        {
            break;
        }
        if (xs.find(x) == xs.end())
        {
            cout << "不存在" << endl;
        }
        else
        {
            cout << "存在" << endl;
        }
    }

    cout << "输入以空格隔开的若干数字并回车，从集合中删除这些数字。" << endl;
    while (true)
    {
        int x;
        cin >> x;
        
        // erase无需判断要删除的元素是否在set中, 不允许重复的容器会返回0/1
        // 否则见cppp p387
        xs.erase(x); 

        if (cin.peek() == '\n')
        {
            cin.ignore();
            break;
        }
    }

    cout << "集合现在还剩下的数字是：";
    for (auto x : xs)
    {
        cout << x << " ";
    }
    cout << endl;
    return 0;
}