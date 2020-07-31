// 友元函数, 和前置声明一样, 尽量不要用
// 赋予别人访问自己的protected和private的能力

#include <iostream>
#include <string>
#include <memory>

using namespace std;



struct Node;
// extern 放在函数/变量前, 提示编译器在其他模块中寻找定义
// 但extern只能声明, 无法作为定义
// 比如在.h中声明extern int x;
// 还需要在同名cpp文件中定义int x;才能使用
// extern "C" void xxx(), 表示按C规则翻译函数名称
extern Node* CreateNode();
extern void DestroyNode(Node* node);

struct Node
{
private:
    Node() = default;
    ~Node() = default;
public:
    void Introduce()
    {
        cout << "我是Node。" << endl;
    }
};

Node* CreateNode()
{
    return new Node;
}

void DestroyNode(Node* node)
{
    delete node;
}

int main()
{
    auto node = CreateNode();
    node->Introduce();
    DestroyNode(node);
    return 0;
}



// 上面的代码无法通过编译, 因为Node的构造/析构均为private, 无法从外部访问
// 改成如下就可以
struct Node;
/*
这里的声明很重要，不然friend了一个在那个时候看不到名字的函数或者类X的话，名字会被强行认为是Node::X。
还有，只要你extern，就不会有C++那个函数声明跟变量声明混在一起不知道选谁的feature。
*/
// 不知道第二句话什么鬼, 这里删掉extern毫无影响
extern Node* CreateNode();
extern void DestroyNode(Node* node);

struct Node
{
    // friend写在里面是为了知道对于哪个函数, 可以访问我的私有成员
    // 类似于声明: 这个函数是我的朋友, 可以让他到家里来
    // 放在外面没有意义, 因为函数单方面声明这个类是朋友是没有用的
    friend Node* CreateNode();
    friend void DestroyNode(Node* node);
private:
    Node() = default;
    ~Node() = default;
public:
    void Introduce()
    {
        cout << "我是Node。" << endl;
    }
};


// 友元类类似
struct Node
{   
    // 对NodeFactory开发私有成员
    // class和struct不能混用
    // 如果NodeFactory是struct, 写成class就是错的
    friend struct NodeFactory;
};


// 友元无法继承
// F只能访问A的私有成员, 和基类或子类无关
struct B;
extern void F(B* b);

struct A
{
    friend void F();
};

struct B : A
{
private:
    int data;
};

void F(B* b)
{
    cout << b->data << endl;
}

int main()
{
    B b;
    F(&b);
}