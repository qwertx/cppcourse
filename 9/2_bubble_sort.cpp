#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <list>

// 迭代器用法
// *i/++/--/prev(i)/next(i),不能-1/+1/比较大小


using namespace std;

// 该解法多了很多不必要的比较步骤
template<typename T>
void BubbleSort_Mod(T first, T last) // 左开右闭
{
    /* 如果在迭代器的范围里面没有至少两个数字的话，那可以直接返回，不需要排序 */
    if (first == last || next(first) == last) return;

    /* 请在这里完成冒泡排序 */
    int if_swap = 1;
    while(if_swap) {
        if_swap = 0;
        // 迭代器无法比较大小， 不能用curr < last
        // 也不能用+1或-1，只能用++和--
        for(auto curr = first; curr != prev(last); curr++) {
            if (*curr > *(next(curr))) {
                auto tmp = *curr;
                *curr = *(next(curr));
                *(next(curr)) = tmp;
                if_swap = 1;
            }
        }
    }
}

// 答案
// 每冒泡一遍，都有一个数处于正确位置（从小到大）
// 也可以将i放在最后，j从first开始，这样每一轮都有一个最大的数正确
template<typename T>
void BubbleSort(T first, T last) // 左开右闭
{
    /* 如果在迭代器的范围里面没有至少两个数字的话，那可以直接返回，不需要排序 */
    if (first == last || next(first) == last) return;
    
    for(auto i = first; i != prev(last); i++) {
        for(auto j = prev(last); j != i; j--) {
            auto k = prev(j);
            if (*j < *k) {
                auto t = *j;
                *j = *k;
                *k = t;
            }
        }
    }
}



int main()
{
    {
        vector<int> xs = { 3,5,1,4,2 };
        BubbleSort(begin(xs), end(xs));

        for (auto x : xs)cout << x << " ";
        cout << endl;
    }
    {
        list<int> xs = { 3,5,1,4,2 };
        BubbleSort(rbegin(xs), rend(xs));

        for (auto x : xs)cout << x << " ";
        cout << endl;
    }
    {
        int xs[] = { 7,3,5,1,4,2,0 };
        BubbleSort(&xs[1], &xs[6]);

        for (auto x : xs)cout << x << " ";
        cout << endl;
    }
    return 0;
}