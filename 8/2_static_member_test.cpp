#include <iostream>
#include <string>
#include <memory>

using namespace std;

class MyClass
{
private:
    int data;

public:
    MyClass(int theData)
        :data{ theData }
    {
    }

    int A()
    {
        return data;
    }

    static int B(const MyClass& myClass)
    {
        return myClass.data;
    }
};

int main()
{
    MyClass a(10);
    // 此处a.B和Myclass::B效果一样
    cout << a.B(a) << endl;
}