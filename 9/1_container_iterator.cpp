// 所有容器都有迭代器
// 分为只读/可写/随机/顺序等等, 可以当做指针使用, 比如++/--/*/->等
// 迭代器对不同容器提供了一致的使用方法, 这样写一遍模板函数就可以支持各种容器
// STL自带算法在<algorithm>中


// 获取迭代器
// std::begin(c)和std::end(c)
// 还有cbegin/rbegin/crbegin以及对应的end版本(cbegin: 只需要读对象)
// 一对迭代器范围是左闭右开的
// 判断c是否在范围内: a<=c && c<b(不是所有迭代器都支持比较)
// end是尾后迭代器, 不能*解引用
// ==std::end(c)证明已经到末尾

// 容器被修改的话迭代器可能失效
// begin和end函数也支持数组(不是指针), 如int* pbegin = begin(arr)


// 举例
vector<int> xs = { 3,5,1,4,2 }
// 输出35142
for (auto i = begin(xs); i != end(xs); i++)
{
    cout << *i << endl;
}
// 24153
for (auto i = rbegin(xs); i != rend(xs); i++)
{
    cout << *i << endl;
}

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
    vector<int> xs = { 3,5,1,4,2 };

    sort(begin(xs), end(xs));
    for (auto x : xs) cout << x << " "; // 12345
    cout << endl;

    sort(rbegin(xs), rend(xs));
    // 因为提供的是rbegin和rend, 排序完会反着写进xs
    for (auto x : xs) cout << x << " "; // 54321
    cout << endl;
    return 0;
}