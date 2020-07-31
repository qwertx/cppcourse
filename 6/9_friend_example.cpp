#include <iostream>
#include <string>
#include <memory>

using namespace std;
// make_shared声明(C++ 11)
// template<class T, class... Args>
// shared_ptr<T> make_shared(TArgs&&... args);

struct Node
{
    int data;

private:
    template<class T, class... TArgs>
    friend shared_ptr<T> std::make_shared(TArgs&&... args);

    Node() = default;
    ~Node() = default;
};

int main()
{
    auto node = make_shared<Node>();
    return 0;
}