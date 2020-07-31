// 所有权指谁负责delete
// 如果A的一个成员变量是指针,指向一个B的实例

// 1.独占所有权(所有权可以转移)
// A delete B, 如果C要持有B, A就要放弃, 比如成员变量设置为nullptr
// 并由C delete B

// 2.分享所有权
// 由最后一个持有该对象的类(不管A还是C)delete

// 3.弱引用
// A不负责delete, 如果B已经delete, A会收到通知
// 如果还试图使用B, 会拿到nullptr

// 4.普通指针
// 不知道什么时候被delete



// 比如
// unique_ptr

// 结果:
// A
// x为空
// A
#include <iostream>
#include <string>
#include <memory>

using namespace std;

class A
{
public:
    string name;

    A(const string& theName)
        :name{ theName }
    {
    }
};

int main()
{
    // unique_ptr<A> x;
    // make_unique构造类,返回unique_ptr
    // 当然没有指针算术
    auto x = make_unique<A>("A");
    cout << x->name << endl;

    // 放弃独占所有权, 构造新的unique_ptr
    // release()会返回指针A*, 用该指针初始化y, 实现了转移
    unique_ptr<A> y(x.release());

    // 可以隐式转换为bool判断是否为空
    if (x)
    {
        cout << "x不为空" << endl;
    }
    else
    {
        cout << "x为空" << endl;
    }
    cout << y->name << endl;
    return 0;
}



// shared_ptr, weak_ptr
// A
// A
// A
// w为空
class A
{
public:
    string name;

    A(const string& theName)
        :name{ theName }
    {
    }
};

int main()
{
    // shared_ptr<A> x;
    auto x = make_shared<A>("A");
    cout << x->name << endl;

    // y出了块自动销毁
    {
        // shared_ptr<A> y;
        // 拷贝shared_ptr, 增加引用计数
        auto y = x;
        cout << y->name << endl;
    }

    // 从shared_ptr构造weak_ptr
    // 注意w指向A, 而不是shared_ptr<A>
    weak_ptr<A> w = x;
    {
        // shared_ptr<A> y;
        // 必须调用lock()才能访问对象, 会先检查是否存在
        // 若存在, 返回指向对象的shared_ptr 否则返回空的shared_ptr
        auto y = w.lock();
        cout << y->name << endl;
    }

    // 没有shared_ptr拥有A, A被delete
    x = nullptr;
    {
        // 返回空shared_ptr
        auto y = w.lock();
        if (y)
        {
            cout << "w不为空" << endl;
        }
        else
        {
            cout << "w为空" << endl;
        }
    }
    return 0;
}

// 此外, unique和shared有get函数, 在不放弃所有权的情况下返回普通指针
// reset函数类似于赋值nullptr
// weak_ptr有expired函数检查所指的对象是否存在, 仅仅判断的话无需用lock函数

// weak是否可以从unique构建? 不能
// lock返回shared, 而独占和分享互斥, 因此无法将unique和shared混合使用
// 如果有一个unique版本的weak, 那么如果lock返回unique就破坏了原来unique的所有权, 产生矛盾