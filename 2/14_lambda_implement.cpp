// lambda: []中为成员变量, ()和{}为operator()的参数和函数体
// 如果值类型对象有operator()成员函数, 就可以被调用
// 复习
// 值类型对象: 可以构造, 复制, 传递, 无需担心new和delete
// 要求: 
// 1. 构造和析构可见
// 2. 可以用operator=和复制构造函数实现复制, 还需要移动构造函数

// 比如排序vector
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> numbers = {7, 1, 12, 2, 8, 3, 11, 4, 9, 5, 13, 6, 10};
    sort(begin(numbers), end(numbers), [](int a, int b)
    {
        return a < b;
    });
}

// 可以写一个struct代替lambda
// 也就是说lambda其实是一个匿名类
// []中为成员变量, ()和{}为operator()的参数和函数体
// STL中接受的函数参数几乎声明成模板参数的类型, 比如下面的Compare

// class和typename没有区别, 表示同一个意思
// template <class RandomAccessIterator, class Compare>
//     void sort (RandomAccessIterator first, RandomAccessIterator last, Compare comp);
struct FIEWNFKLDHIOHEIOFHJDKSFUIOEJWKFLDS
{
    bool operator()(int a, int b)const
    {
        return a < b;
    }
};

int main()
{
    vector<int> numbers = {7, 1, 12, 2, 8, 3, 11, 4, 9, 5, 13, 6, 10};
    sort(begin(numbers), end(numbers), FIEWNFKLDHIOHEIOFHJDKSFUIOEJWKFLDS{});
}

// 找2个vector交集的大小
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    vector<int> xs = { 1, 2, 3, 4, 5 };
    vector<int> ys = { 3, 4, 5, 6, 7 };
    // xs从头到尾遍历, 看其中每个元素是否在y中
    auto count = count_if(begin(xs), end(xs), [&ys](int x)
    {
        return find(begin(ys), end(ys), x) != end(ys);
    });
    cout << count << endl;
}

// 改写, 注意ys引用的捕获成为了匿名类的成员变量
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct LKFJDKLSJFKLDJFIOEJIFODJSKLFJIEOSS
{
private:
    vector<int>& ys; // 没有复制, 是引用
public:
    LKFJDKLSJFKLDJFIOEJIFODJSKLFJIEOSS(vector<int>& theYs)
        :ys{theYs}
    {
    }

    bool operator()(int x)const
    {
        return find(begin(ys), end(ys), x) != end(ys);
    }
};


int main()
{
    vector<int> xs = { 1, 2, 3, 4, 5 };
    vector<int> ys = { 3, 4, 5, 6, 7 };
    auto count = count_if(begin(xs), end(xs), LKFJDKLSJFKLDJFIOEJIFODJSKLFJIEOSS{ys});
    cout << count << endl;
}


// 如果要用function保存返回的lambda函数, 而且要捕获局部变量怎么办?
// 如果捕获引用的话函数返回后变量就销毁了
// 因此C++14提供了generalized lambda capture
// 可以写name = expr, 表达式中可以写看得见的名字, 然后保存到name

// lambda表达式是一个函数返回的，而ys则作为参数的一部分被move进lambda表达是里面。
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

function<bool(int)> Predicator(vector<int>&& ys)
{
    // 左边的ys指的是lambda表达是里面的ys，而右边的ys指的是函数Predicator的参数
    // 代码生成后二者不在嵌套的作用域里面, 可以重名
    // 这是个被返回的lambda函数, 返回后形参就失效了, 只能用左侧ys保存起来
    // 而且lambda内部无法使用外面的ys形参, 因此可以重名

    // 如果不加move, 那么由于传入的ys获得了名字, 会变成左值引用
    // 即move(ys)中ys类型是vector<int>&
    // 这里也可以用forward进行原样传递, forward要传入类型<vector<int>>
    return [ys = move(ys)](int x)
    {
        return find(begin(ys), end(ys), x) != end(ys);
    };
}

int main()
{
    vector<int> xs = { 1, 2, 3, 4, 5 };
    vector<int> ys = { 3, 4, 5, 6, 7 };
    auto count = count_if(begin(xs), end(xs), Predicator({ 3, 4, 5, 6, 7 }));
    cout << count << endl;
}

// 改写
// 同样将返回的lambda改写成struct, 将返回lambda的函数独立出来
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using namespace std;

struct BFHDJSKHFUIENSJBFJDSHKJHFJEKIS
{
private:
    vector<int> ys;
public:
    // 即使写右值引用参数, 由于在内部获得了名字, 仍然是左值引用, 因此要加move
    BFHDJSKHFUIENSJBFJDSHKJHFJEKIS(vector<int>& theYs)
        :ys{move(theYs)}
    {
    }

    bool operator()(int x)const
    {
        return find(begin(ys), end(ys), x) != end(ys);
    }
};

function<bool(int)> Predicator(vector<int>&& ys)
{
    return BFHDJSKHFUIENSJBFJDSHKJHFJEKIS{ys};
}

int main()
{
    vector<int> xs = { 1, 2, 3, 4, 5 };
    vector<int> ys = { 3, 4, 5, 6, 7 };
    auto count = count_if(begin(xs), end(xs), Predicator({ 3, 4, 5, 6, 7 }));
    cout << count << endl;
}


// 为什么lambda用auto返回的话就不能捕获自己?(递归lambda)

// 以下代码如果是全局函数的话会有警告: 捕获非自动存储周期变量
// 因为如果是全局变量, 根本无需捕获(因为静态变量有固定地址, 编译时就已经知道, 也不用担心消失)
// 自动周期变量, 地址不固定, 因此捕获是为了保存一个拷贝或引用到lambda自身的成员变量

// 如果将function改成auto, 那么就成为一个死循环
// 要完成f的初始化需要知道捕获变量的类型, 而要知道捕获的类型又要等f初始化完成(知道返回类型), 因此无法用auto
function<int(int)> f = [&f](int x)
{
    return x == 0 ? 0 : f(x - 1);
};