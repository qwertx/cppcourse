#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

void PrintVector(vector<int>& numbers) // 打印vector内容
{
    for (auto it = begin(numbers); it != end(numbers); it++)
    {
        if (it != begin(numbers))
        {
            cout << ", ";
        }
        cout << *it;
    }
    cout << endl;
}

bool IsOdd(int a)
{
    return a % 2 == 1;
}

bool Not(bool b)
{
    return !b;
}

bool And(bool a, bool b)
{
    return a && b;
}

bool Or(bool a, bool b)
{
    return a || b;
}

decltype(auto) GreaterThan(int x) // C++14新特性, 自动确定函数返回类型, 而且lambda表达式类型没有名字
{
    return [=](int y)
    {
        return y > x;
    };
}

decltype(auto) EqualsTo(int x)
{
    return [=](int y)
    {
        return y == x;
    };
}


// 高阶函数

// 最外层中传入函数, 返回另一个函数, 在返回的函数中调用外层传入的函数, 同时提供了外层函数运行所需的参数
// 类似python的decorator
// 也就是返回的函数对传入的函数进行了"装饰"

// 比较难理解的地方是, 此处最终(最内层)返回的仍然是一个函数, 最终需要传入y才能真正运行

auto Compose = [](auto f, auto g){ // 返回函数H = f(g(x))
    return [=](auto x){
        return f(g(x)); 
    };
};

auto Combine = [](auto c, auto f, auto g){ // 返回函数H = c(f(x), g(x)), 即f和g的组合(比如or(>3, ==3))
    return [=](auto x) {
        return c(f(x), g(x));
    };
};

int main()
{
    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    {
        vector<int> odds;
        copy_if(begin(numbers), end(numbers), back_inserter(odds),
            IsOdd
            ); // copy_if(first, last, result(iterator), pred(谓词))
            // back_inserter: 插入迭代器, 相当于push_back, 作为目的位置使用
        PrintVector(odds);
    }
    {
        vector<int> evens;
        copy_if(begin(numbers), end(numbers), back_inserter(evens),
            Compose(Not, IsOdd)
            );
        PrintVector(evens);
    }
    {
        vector<int> one_two_nine_ten;
        copy_if(begin(numbers), end(numbers), back_inserter(one_two_nine_ten),
            Combine(Or,
                Combine(And,
                    Combine(Or, GreaterThan(1), EqualsTo(1)),
                    Compose(Not, GreaterThan(2))  // !([](int y){return y > 2;});
                    ),
                Combine(And,
                    Combine(Or, GreaterThan(9), EqualsTo(9)),
                    Compose(Not, GreaterThan(10))
                    )
                )
            );
        PrintVector(one_two_nine_ten);
    }
    return 0;
}


// 自动类型推断
// C++11, 写在参数后面是因为返回值类型需要使用参数

// template<typename T, typename U>
// auto Add(T t, U u) -> decltype(t+u) {
//     return t + u;
// }

// C++14, 全自动

// decltype(auto) Add(T t, U u) {
//     return t + u;
// }

// 但auto类型只能用于lambda不能用于普通函数