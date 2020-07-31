#include <iostream>
#include <string>
#include <queue>

using namespace std;

int main()
{
    queue<int> numbers;
    for (int i = 1; i <= 10; i++) {
        numbers.push(i);
    }
    cout << numbers.front() << " " << numbers.back() << endl;
    int sum = 0;
    while(!numbers.empty()) {
        sum += numbers.front(); // 返回队头
        numbers.pop(); // pop没有返回值
    }
    cout << sum << endl;
    return 0;
}