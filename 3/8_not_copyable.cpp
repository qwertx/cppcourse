#include <cstdlib>
#include <string>

using namespace std;

class NotCopyable {
    NotCopyable() = default;
    NotCopyable(const NotCopyable&) = delete;
    NotCopyable(NotCopyable&&) = delete;
    NotCopyable& operator=(const NotCopyable&) = delete;
    NotCopyable& operator=(NotCopyable&&) = delete;
};

struct Student : private NotCopyable // Student没有必要访问基类, 因此用private继承
{
    string name;
    time_t birtyday;
};

int main()
{
    Student a;
    Student b = a; // 无法复制
    a = b;
    return 0;
}