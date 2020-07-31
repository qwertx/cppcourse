#include <string>
#include <iostream>

using namespace std;

class Animal
{
public:
    string name;

    virtual ~Animal(){}

    virtual string Introduce()
    {
        return "我不知道自己是什么动物。";
    }
};

class Cat : public Animal
{
public:
    string Introduce()override
    {
        return "我是一只猫，我的名字是\"" + name +"\"。";
    }
};

class Dog : public Animal
{
public:
    string Introduce()override
    {
        return "我是一只狗，我的名字是\"" + name +"\"。";
    }
};

// 段错误, 调用了空指针的虚函数
// 有时用空指针调用成员函数会让this变成nullptr, 但调用虚函数肯定不行
int main()
{
    auto pCat = new Cat;
    pCat->name = "Tom";

    auto pDog = dynamic_cast<Dog*>(pCat); // 返回nullptr
    cout << pDog->Introduce() << endl;
}

// 非继承关系无法使用static_cast 
int main()
{
    auto pCat = new Cat;
    pCat->name = "Tom";

    auto pDog = static_cast<Dog*>(pCat);
    cout << pDog->Introduce() << endl;
}