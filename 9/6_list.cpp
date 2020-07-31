#include <iostream>
#include <string>
#include <list>
#include <numeric>

using namespace std;

int main()
{
    list<int> numbers;
    for(int i = 1; i <= 5; i++) {
        numbers.push_front(i);
    }
    for(int i = 6; i <= 10; i++) {
        numbers.push_back(i);
    }
	for(auto number: numbers) {
        cout << number << " ";
    }
    cout << endl;
    // 头/尾/初始值/二元谓词(参数分别是当前元素和上一次的值)
    // 初始值使用" "可以连接字符串
    // 最后一个参数可以用multiplies<int>()代替
    cout << accumulate(begin(numbers), end(numbers), 1, [](int a, int b){return a*b;});
    return 0;
}