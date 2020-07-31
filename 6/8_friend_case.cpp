#include <iostream>
#include <string>
#include <memory>

using namespace std;

struct B;
extern void F(B* b);

// A是B的内部类, 可以看到B的所有东西
// 但A不能替B作出friend决定
// F还是只能看到A内部
struct B
{
    struct A
    {
        friend void F(B* b);
    };
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
    return 0;
}