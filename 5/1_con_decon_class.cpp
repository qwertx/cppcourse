// 一般用new和delete构造类

// 以下是抽象工厂模式的代码示例
// 但是很别扭, 属于滥用设计模式
#include <iostream>
#include <string>

using namespace std;

class Animal
{
public:
    string name;

    virtual string Introduce() = 0;
};

class IAnimalFactory
{
public:
    virtual Animal* CreateAnimal() = 0;
};

class Cat : public Animal
{
public:
    string Introduce()override
    {
        return "我是一只猫，我的名字是" + name + "。";
    }
};

class CatFactory : public IAnimalFactory
{
public:
    Animal* CreateAnimal()override
    {
        auto cat = new Cat;
        cat->name = "Tom";
        return cat;
    }
};

void IntroduceAnimalFromFactory(IAnimalFactory* factory)
{
    auto animal = factory->CreateAnimal();
    cout << animal->Introduce() << endl;
    // 你怎么知道CreateAnimal是通过new构造的?
    // 这不面向接口
    // 比如可能是malloc后用placement new, 或者返回成员变量的指针
    delete animal;
}

int main()
{
    CatFactory factory;
    IntroduceAnimalFromFactory(&factory);
    return 0;
}



// 因此必须放在IAnimalFactory内来delete   
// 谁构造谁释放
// 正确写法如下
// 仍不完美, 比如有人调用了DestroyAnimal, 但并没有通过CreateAnimal创建对象?
class IAnimalFactory
{
public:
    virtual Animal* CreateAnimal() = 0;
    virtual void DestroyAnimal(Animal* animal) = 0;
};

class CatFactory : public IAnimalFactory
{
public:
    Animal* CreateAnimal()override
    {
        auto cat = new Cat;
        cat->name = "Tom";
        return cat;
    }

    void DestroyAnimal(Animal* animal)override
    {
        delete animal;
    }
};

void IntroduceAnimalFromFactory(IAnimalFactory* factory)
{
    auto animal = factory->CreateAnimal();
    cout << animal->Introduce() << endl;
    factory->DestroyAnimal(animal);
}


// 但如下写也是正确的, 满足谁构造谁释放
// 如果不通过make_shared函数或new构造shared_ptr
// shared_ptr允许传入自定义的deleter进行析构, 而非调用delete
// 比如shared_ptr<T> p(&t, end_T);
#include <memory>
class IAnimalFactory
{
public:
    virtual shared_ptr<Animal> CreateAnimal() = 0;
};




// 补充:
// 重载new/operator new函数, 只分配空间, 不调用构造函数
// void* operator new(size_t size) // 第一个参数为空间大小(字节), 可以加入其他参数
// 函数体一般为return ::operator new(size);
// 同样要实现void operator delete(void* pointee) {::operator delete(pointee);}
// ::前面什么都不写为全局函数

// placement new
// throw()表示声明不会抛出异常, 不要放入try/catch中
// void *operator new( size_t, void * p ) throw() { return p; }
// 没有自定义版本, 但允许用户把对象放到一个特定的地方
// 比如auto pi = new (ptr) int; 将在ptr指向的内存处分配对象

// new: 调用operator new分配内存--调用构造函数--返回对象指针
// operator new: 自定义的重载new函数
// placement new: operator new的一个重载版本
// 不分配内存, 允许你在已经分配的内存中构造对象

// 比如可以先malloc再用placement new

