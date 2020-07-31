// 除了左值引用, 还有右值引用如String&&, 引用折叠
// 左值: 非临时对象 右值: 临时对象
// T().set().get(), 此处T()生成的临时对象是右值, 而且可以被修改
// 用于转移语义,相当于剪切, 对右值的拷贝和赋值会调用移动构造函数和移动赋值操作符
// 左值当做右值: move, 用于swap函数非常有效
// perfect forwarding: 将参数原封不动地传递给另一个函数
// 包括值/左右/是否const, 这样传统写法的话每个参数都要重载2次
// 只要加入右值引用, 就可以满足所有情况的调用

#include <iostream>
#include <vector>
#include <utility>

using namespace std;

// 共创建了3个vector, 分别是MakeVector初始化, 返回以及Sum构造函数
// 其中return使用了vector的右值引用的拷贝构造函数(移动构造函数), 因此实际只构造了2个vector
// vector在移动构造时会将被复制的指针改为nullptr, 以防止重复析构
// 对Sum加入右值引用构造函数, 即可将代码优化为只构造1次vector
vector<int> MakeVector(int start, int stop) {
    vector<int> numbers;
    for (int i = start; i <= stop; i++) {
        numbers.push_back(i);
    }
    return numbers;
}


class Sum {
    private:
        vector<int> numbers;
    public: 
        // 不能用于隐式转换和复制初始化--用等于号或参数传递初始化
        // 比如Sum sum = MakeVector(1, 10)
        explicit Sum(const vector<int>& theNumbers) 
        : numbers{theNumbers} {
        }
        explicit Sum(vector<int>&& theNumbers) // 不能用const!!
        : numbers{forward<vector<int>>(theNumbers)} { // forward完美转发, 保证theNumbers为右值
        }

        int Get() {
            int sum = 0;
            for(auto i: numbers) {
                sum += 1;
            }
            return sum;
        }
};

int main() {
    Sum sum{MakeVector(1, 10)};
    cout << sum.Get() << endl;
    return 0;
}

// 返回右值
// 1.return局部变量(是)
// 2.表达式返回值是左值引用(不是), 比如a=b实际是返回指向a的左值引用
// 甚至a[b], a->b, a.b也一样是左值引用
// 3.表达式返回值是值类型的时候的那个值(是)
// 4.表达式返回右值引用(是)
// 但U& &&相当于U&, 引用折叠, 即非纯右值引用都是左值引用
// String&和String&&可以转为const String&, 但&和&&无法转换

// 以下为演示
//拷贝构造函数时, 既复制stack区,也复制heap区内容
// vector(const vector& v)
// {
//   stack = v.stack;
//   copy(this.heap_pointer,v.heap_pointer);
// }

//移动构造函数, 直接复制heap pointer(类似浅复制),
// 然后原heap pointer指向nullptr, rvalue被析构
// vector(vector&& rvalue)
// {
//   stack = rvalue.stack;
//   heap_pointer = rvalue.heap_pointer;
//   rvalue.heap_pointer = nullptr;
// }