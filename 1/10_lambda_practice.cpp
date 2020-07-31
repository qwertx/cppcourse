#include <iostream>
#include <functional>
using namespace std;
auto Pair = [](auto u, auto v) {
	return [=](auto f) {
		return f(u, v);
	};
};

// 传入的只有Pair的返回值t, 必定通过t()得到结果, 因此看Pair返回的那个函数
// 可以看出pair的返回函数需要一个lambda函数f作为参数, 先写出t([](){})
// 再看内层, 可以看出f又额外需要两个参数, 因此可以写出f得到结果
auto First = [](auto t){
    return t([](auto u, auto v) {
        return u;
    });
}; 


auto Second = [](auto t){
    return t([](auto u, auto v) {
        return v;
    });
};


void PrintAll(nullptr_t) {

}
template<typename T>
void PrintAll(T t) {
	cout << First(t) << endl;
	PrintAll(Second(t));
}

int main()
{
	auto t = Pair(1, "two");
	auto one = First(t);
	auto two = Second(t);
	cout << one << ", " << two << endl;
	auto numbers = Pair(1, Pair(2, Pair(3, Pair(4, Pair(5, nullptr)))));
	PrintAll(numbers);

    return 0;
}
